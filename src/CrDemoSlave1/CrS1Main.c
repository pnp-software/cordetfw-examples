/**
 * @file
 * @ingroup crDemoSlave1
 * Main program for the Slave 1 Application of the CORDET Demo.
 * The CORDET Demo consists of three applications: the Master Application,
 * the Slave 1 Application and the Slave 2 Application.
 * The two slave applications are responsible for monitoring a temperature sensor.
 * If they find a limit violation, they send a report to the Master Application.
 * The Master Application is responsible for enabling and disabling the
 * monitoring in the slave applications and for setting the monitoring limits.
 *
 * The CORDET Demo supports one single service: the "Temperature Monitoring
 * Service".
 * The type identifier of the Temperature Monitoring Service is equal to: 64.
 * This service is implemented by the following commands and reports:
 * - Sub-Type 1: Command to enable temperature monitoring
 * - Sub-Type 2: Command to disable temperature monitoring
 * - Sub-Type 3: Command to set the temperature limit
 * - Sub-Type 4: Report to report a temperature limit violation
 * .
 * The logical links among the three applications are as follows:
 * - The Master Application sends commands to both Slave Applications
 * - Each Slave Application sends reports to the Master Application
 * .
 * Note that there is no logical link between the two slaves which are
 * completely independent of each other (see first figure below).
 *
 * The physical links among the three applications are as follows (see second figure
 * below):
 * - There is a socket-based link between the Master Application and Slave 1
 * - There is a socket-based link between the Slave 1 and Slave 2
 * .
 * Thus, messages between the Master Application and Slave 2 are routed through
 * Slave 1 (the routing is done by the CORDET Framework).
 *
 * The Master Application generates the commands to and receives the reports
 * from the Slave Applications.
 *
 * @image html DA_LogicalLinks.png
 * @image html DA_PhysicalLinks.png
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* Include Master Demo Files */
#include "CrS1Constants.h"
/* Include Common Demo Files */
#include "CrDaConstants.h"
#include "CrDaClientSocket.h"
#include "CrDaServerSocket.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include framework files */
#include "OutRegistry/CrFwOutRegistry.h"
#include "Aux/CrFwAux.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutLoader/CrFwOutLoader.h"
#include "OutStream/CrFwOutStream.h"
#include "InFactory/CrFwInFactory.h"
#include "InRegistry/CrFwInRegistry.h"
#include "InStream/CrFwInStream.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include configuration files */
#include "CrFwOutRegistryUserPar.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwInFactoryUserPar.h"
#include "CrFwCmpData.h"

/**
 * Main program for the Slave 1 Application.
 * This Main Program performs the following actions:
 * - It checks the consistency of the configuration parameters using
 *   <code>::CrFwAuxConfigCheck</code>.
 * - It initializes and configures the InStreams and OutStreams components
 *   (note that their initialization action initializes the server socket and
 *   this must be synchronized with the initialization of the client socket
 *   in the Master Application).
 * - It initializes and configures all framework components used by the
 *   Slave 1 Application.
 * - It executes a loop and in every cycle of the loop commands may be
 *   received from the Master Applications and reports may be sent to it.
 * .
 * In all control cycles, the server socket waiting for commands from the
 * Master Application or reports from the Slave 2 Application is polled
 * through a call to <code>::CrDaServerSocketPoll</code>.
 *
 * In principle, in all control cycles, the temperature to be monitored
 * should be acquired from some external device.
 * In this example, instead, the temperature is set to a "low" value in all
 * cycles except those which are multiples of 10 when it is set to a "high"
 * value.
 * @return always returns EXIT_SUCCESS
 */
int main() {
	FwSmDesc_t fwCmp[CR_S1_N_OF_FW_CMP];
	FwSmDesc_t inStream1, inStream2, outStream1, outStream2;
	CrFwConfigCheckOutcome_t configCheckOutcome;
	int i;
	char temp;

	/* Check consistency of configuration parameters */
	configCheckOutcome = CrFwAuxConfigCheck();
	if (configCheckOutcome != crConsistencyCheckSuccess) {
		if (configCheckOutcome == crOutRegistryConfigParInconsistent)
			printf("Consistency check of OutRegistry parameters failed\n");
		if (configCheckOutcome == crOutFactoryConfigParInconsistent)
			printf("Consistency check of OutFactory parameters failed\n");
		if (configCheckOutcome == crInFactoryInCmdConfigParInconsistent)
			printf("Consistency check of InCommand parameters in InFactory failed\n");
		if (configCheckOutcome == crInFactoryInRepConfigParInconsistent)
			printf("Consistency check of InRepot parameters in InFactory failed\n");
		return EXIT_SUCCESS;
	}
	printf("S1: Consistency check of configuration parameters ran successfully.\n");

	/* Create In- and OutStreams */
	inStream1 = CrFwInStreamMake(0);
	inStream2 = CrFwInStreamMake(1);
	outStream1 = CrFwOutStreamMake(0);
	outStream2 = CrFwOutStreamMake(1);

	/* Set port number */
	CrDaServerSocketSetPort(CR_DA_SOCKET_PORT);

	/* Initialize the InStreams and OutStreams */
	CrFwCmpInit(outStream1);
	if (!CrFwCmpIsInInitialized(outStream1))
		return 0;
	CrFwCmpInit(outStream2);
	if (!CrFwCmpIsInInitialized(outStream2))
		return 0;
	CrFwCmpInit(inStream1);
	if (!CrFwCmpIsInInitialized(inStream1))
		return 0;
	CrFwCmpInit(inStream2);
	if (!CrFwCmpIsInInitialized(inStream2))
		return 0;

	printf("S1: Wait 5 seconds (to give time to the client sockets applications to start) and then continue\n");
	sleep(5);

	/* Configure the InStream and OutStream */
	CrFwCmpReset(inStream1);
	CrFwCmpReset(inStream2);
	CrFwCmpReset(outStream1);
	CrFwCmpReset(outStream2);
	if (!CrFwCmpIsInConfigured(inStream1))
		return 0;
	if (!CrFwCmpIsInConfigured(inStream2))
		return 0;
	if (!CrFwCmpIsInConfigured(outStream1))
		return 0;
	if (!CrFwCmpIsInConfigured(outStream2))
		return 0;

	/* Initialize and reset framework components */
	fwCmp[0] = CrFwOutFactoryMake();
	fwCmp[1] = CrFwInFactoryMake();
	fwCmp[2] = CrFwInLoaderMake();
	fwCmp[3] = CrFwInManagerMake(0);
	fwCmp[4] = CrFwInRegistryMake();
	fwCmp[5] = CrFwOutLoaderMake();
	fwCmp[6] = CrFwOutRegistryMake();
	fwCmp[7] = CrFwOutManagerMake(0);
	for (i=0; i<CR_S1_N_OF_FW_CMP; i++) {
		CrFwCmpInit(fwCmp[i]);
		if (!CrFwCmpIsInInitialized(fwCmp[i]))
			return 0;
		CrFwCmpReset(fwCmp[i]);
		if (!CrFwCmpIsInConfigured(fwCmp[i]))
			return 0;
	}

	/* Execute control cycles */
	for (i=1; i<100; i++) {
		printf("S1: Starting cycle %d\n",i);
		/* Set temperature value */
		if (i%10 != 0)
			temp = CR_S1_LOW_TEMP_VALUE;
		else
			temp = CR_S1_HIGH_TEMP_VALUE;
		/* Perform temperature monitoring action */
		CrDaTempMonitoringExec(temp, CR_FW_HOST_APP_ID);

		/* Poll socket for incoming reports */
		CrDaServerSocketPoll();

		/* Load packets from the two InStreams */
		CrFwInLoaderSetInStream(inStream1);
		FwSmExecute(CrFwInLoaderMake());
		CrFwInLoaderSetInStream(inStream2);
		FwSmExecute(CrFwInLoaderMake());

		/* Execute Managers */
		FwSmExecute(CrFwInManagerMake(0));
		FwSmExecute(CrFwOutManagerMake(0));

		/* Check application errors */
		if (CrFwGetAppErrCode() != crNoAppErr) {
			printf("S1: Application Error Code is set and is equal to: %d\n",CrFwGetAppErrCode());
		}

		/* Wait 1 second and then continue */
		sleep(1);
	}

	return EXIT_SUCCESS;
}
