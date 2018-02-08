/**
 * @file
 * @ingroup crDemoSlave2
 * Implementation of interface to server socket.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "CrDaServerSocket.h"
#include "CrDaConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwOutStreamUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "OutStream/CrFwOutStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include file for socket implementation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

/** Set the port number (must be same as the port number specified in <code>CrDaServerSocket.c</code> */
static int portno = 0;

/** The file descriptors for the socket */
static int sockfd = 0;

/** The file descriptors for the client sockets */
static int newsockfd[2];

/** Socket variable */
static struct sockaddr_in cli_addr;

/** Socket variable */
static socklen_t clilen;

/** The maximum size of an incoming packet */
static int pcktMaxLength;

/** The Read Buffers */
static unsigned char* readBuffer[2];

/**
 * Entry point for the thread which waits for the incoming connection from the client socket.
 * @param ptr unused argument (required with compatibility with pthread create function)
 */
static void* acceptThreadEntry(void* ptr);

/**
 * Poll the socket for data from one of the two clients.
 * @param nsockfd the socket which is to be polled
 * @param buffer the Read Buffer associated to the client which is to be polled
 */
static void serverSocketPoll(int nsockfd, unsigned char* buffer);

/**
 * Check whether a packet from the argument source is available.
 * @param src the source
 * @param nsockfd the socket which is to be polled
 * @param buffer the Read Buffer associated to the client which is to be polled
 * @return 1 if a packet is avaiable; 0 otherwise
 */
static CrFwBool_t serverSocketIsPcktAvail(CrFwDestSrc_t src, int nsockfd, unsigned char* buffer);

/**
 * Collect a packet from the argument source.
 * @param src the source
 * @param buffer the Read Buffer associated to the client from which the packet is read
 * @return the packet collected from the argument source
 */
static CrFwPckt_t serverSocketPcktCollect(CrFwDestSrc_t src, unsigned char* buffer);

/* ---------------------------------------------------------------------------------------------*/
void CrDaServerSocketInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	struct sockaddr_in serv_addr, cli_addr;
	pthread_t acceptThread;
	pthread_attr_t attr;

	/* Check if server socket has already been initialized */
	if (sockfd != 0) {
		if (streamData->typeId == CR_FW_INSTREAM_TYPE)
			CrFwInStreamDefInitAction(prDesc);
		else
			CrFwOutStreamDefInitAction(prDesc);
		return;
	}

	/* Create the read buffer */
	pcktMaxLength = (int)CrFwPcktGetMaxLength();
	readBuffer[0] = malloc(pcktMaxLength*sizeof(char));
	readBuffer[1] = malloc(pcktMaxLength*sizeof(char));

	/* Create the socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("CrDaServerSocketInitAction, Socket creation");
		streamData->outcome = 0;
		return;
	}

	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("CrDaServerSocketInitAction, Bind Socket");
		streamData->outcome = 0;
		return;
	}
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	/* Create thread which will accept the connection call from the client sockets */
	pthread_attr_init(&attr);
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
		perror("CrDaServerSocketInitAction, set detached state");
		streamData->outcome = 0;
		return;
	}
	if (pthread_create(&acceptThread, NULL, acceptThreadEntry, NULL) < 0) {
		streamData->outcome = 0;
		return;
	};

	/* Execute default initialization action for OutStream/InStream */
	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefInitAction(prDesc);
	else
		CrFwOutStreamDefInitAction(prDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrDaServerSocketShutdownAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwSmGetData(smDesc);

	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefShutdownAction(smDesc);
	else
		CrFwOutStreamDefShutdownAction(smDesc);

	if (sockfd != 0) {
		free(readBuffer[0]);
		free(readBuffer[1]);
		close(newsockfd[0]);
		close(newsockfd[1]);
		close(sockfd);
		sockfd = 0;
	}
}

/* ---------------------------------------------------------------------------------------------*/
void CrDaServerSocketConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* streamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	/* Clear Read Buffers */
	readBuffer[0][0] = 0;
	readBuffer[1][0] = 0;

	if (streamData->typeId == CR_FW_INSTREAM_TYPE)
		CrFwInStreamDefConfigAction(prDesc);
	else
		CrFwOutStreamDefConfigAction(prDesc);
}

/* ---------------------------------------------------------------------------------------------*/
void CrDaServerSocketPoll() {
	serverSocketPoll(newsockfd[0], readBuffer[0]);
	serverSocketPoll(newsockfd[1], readBuffer[1]);
}

/* ---------------------------------------------------------------------------------------------*/
static void serverSocketPoll(int nsockfd, unsigned char* buffer) {
	int n;
	FwSmDesc_t inStream;
	CrFwDestSrc_t src;

	if (buffer[0] != 0) {
		src = CrFwPcktGetSrc((CrFwPckt_t)buffer);
		inStream = CrFwInStreamGet(src);
		CrFwInStreamPcktAvail(inStream);
		return;
	}

	n = read(nsockfd, buffer, pcktMaxLength);
	if (n == -1)	/* no data are available from the socket */
		return;
	if (n == 0)	{
		printf("CrDaServerSocketPoll: Error reading from socket\n");
		return;
	}
	if (n == buffer[0]) {	/* a valid packet has arrived */
		src = CrFwPcktGetSrc((CrFwPckt_t)buffer);
		inStream = CrFwInStreamGet(src);
		CrFwInStreamPcktAvail(inStream);
		return;
	}
	if (n != buffer[0]) {
		printf("CrDaServerSocketPoll: invalid packet received from socket\n");
		buffer[0] = 0;
		return;
	}
}

/* ---------------------------------------------------------------------------------------------*/
CrFwPckt_t CrDaServerSocketPcktCollect(CrFwDestSrc_t src) {
	CrFwPckt_t pckt;

	pckt = serverSocketPcktCollect(src, readBuffer[0]);
	if (pckt != NULL)
		return pckt;
	pckt = serverSocketPcktCollect(src, readBuffer[1]);
	if (pckt != NULL)
		return pckt;

	return NULL;
}

/* ---------------------------------------------------------------------------------------------*/
static  CrFwPckt_t serverSocketPcktCollect(CrFwDestSrc_t src, unsigned char* buffer) {
	CrFwPckt_t pckt;
	CrFwDestSrc_t pcktSrc;

	if (buffer[0] != 0) {
		pcktSrc = CrFwPcktGetSrc((CrFwPckt_t)buffer);
		if (src == pcktSrc) {
			pckt = CrFwPcktMake((CrFwPcktLength_t)buffer[0]);
			memcpy(pckt, buffer, buffer[0]);
			buffer[0] = 0;
			return pckt;
		} else
			return NULL;
	} else
		return NULL;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrDaServerSocketIsPcktAvail(CrFwDestSrc_t src) {
	if (serverSocketIsPcktAvail(src, newsockfd[0], readBuffer[0]))
		return 1;

	if (serverSocketIsPcktAvail(src, newsockfd[1], readBuffer[1]))
		return 1;

	return 0;
}

/* ---------------------------------------------------------------------------------------------*/
static CrFwBool_t serverSocketIsPcktAvail(CrFwDestSrc_t src, int nsockfd, unsigned char* buffer) {
	int n;
	CrFwDestSrc_t pcktSrc;

	if (buffer[0] != 0) {
		return 1;
	}

	n = read(nsockfd, buffer, pcktMaxLength);
	if (n == -1)	/* no data are available from the socket (EAGAIN) */
		return 0;
	if (n == 0)	{
		printf("CrDaServerSocketPoll: Error reading from socket\n");
		return 0;
	}

	if (n == buffer[0]) {	/* a valid packet has arrived */
		pcktSrc = CrFwPcktGetSrc((CrFwPckt_t)buffer);
		if (src == pcktSrc)
			return 1;
		else
			return 0;
	}

	if (n != buffer[0]) {
		printf("CrDaServerSocketIsPcktAvail: invalid packet received from socket");
		buffer[0] = 0;
		return 0;
	}

	return 0;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrDaServerSocketPcktHandover(CrFwPckt_t pckt) {
	int len = (int)CrFwPcktGetLength(pckt);
	int n;
	CrFwDestSrc_t dest;

	dest = CrFwPcktGetDest(pckt);
	if (dest == CR_DA_MASTER)
		n = write(newsockfd[0], pckt, len);
	else
		n = write(newsockfd[1], pckt, len);

	if (n < 0)
		return 0;

	if (n != (int)CrFwPcktGetLength(pckt))  {
		printf("CrDaServerSocketPcktHandover: error writing to socket\n");
		return 0;
	}

	return 1;
}

/* ---------------------------------------------------------------------------------------------*/
static void* acceptThreadEntry(void* ptr) {
	int flags;

	printf("S1: Waiting for client socket in Master Application to connect ...\n");
	newsockfd[0] = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
	if (newsockfd < 0) {
		perror("CrDaServerSocketInitAction, Socket Accept");
	}

	/* Set the socket to non-blocking mode */
	if ((flags = fcntl(newsockfd[0], F_GETFL, 0)) < 0) {
		perror("CrDaServerSocketInitAction, Set socket attributes");
		return NULL;
	}
	if (fcntl(newsockfd[0], F_SETFL, flags | O_NONBLOCK) < 0) {
		perror("CrDaServerSocketInitAction, Set socket attributes");
		return NULL;
	}
	printf("S1: Client socket in Master Application successfully connected.\n");

	printf("S1: Waiting for client socket in Slave 2 Application to connect ...\n");
	newsockfd[1] = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
	if (newsockfd < 0) {
		perror("CrDaServerSocketInitAction, Socket Accept");
	}

	/* Set the socket to non-blocking mode */
	if ((flags = fcntl(newsockfd[1], F_GETFL, 0)) < 0) {
		perror("CrDaServerSocketInitAction, Set socket attributes");
		return NULL;
	}
	if (fcntl(newsockfd[1], F_SETFL, flags | O_NONBLOCK) < 0) {
		perror("CrDaServerSocketInitAction, Set socket attributes");
		return NULL;
	}
	printf("S1: Client socket in Slave 2 Application successfully connected.\n");

	return NULL;
}

/* ---------------------------------------------------------------------------------------------*/
void CrDaServerSocketInitCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	if (portno < 2000)
		outStreamData->outcome = 0;
	else
		outStreamData->outcome = 1;

	return;
}

/* ---------------------------------------------------------------------------------------------*/
void CrDaServerSocketConfigCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);

	if (newsockfd[0] > 0) {
		if (newsockfd[1] > 0)
			outStreamData->outcome = 1;
		else
			outStreamData->outcome = 0;
	} else
		outStreamData->outcome = 0;

	return;
}

/* ---------------------------------------------------------------------------------------------*/
void CrDaServerSocketSetPort(int n) {
	portno = n;
}
