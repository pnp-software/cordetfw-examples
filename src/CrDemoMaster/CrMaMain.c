/**
 * @file
 * @ingroup crDemoMaster
 * Main program for the Master Application of the CORDET Demo.
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
#include "CrMaConstants.h"
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
 * Main program for the Master Application.
 * This Main Program performs the following actions:
 * - It checks the consistency of the configuration parameters using
 *   <code>::CrFwAuxConfigCheck</code>.
 * - It initializes and configures the InStreams and OutStreams components
 *   (note that their initialization action initializes the client socket and
 *   this must be synchronized with the initialization of the server socket
 *   in the Slave 1 Application).
 * - It initializes and configures all framework components used by the
 *   Master Application.
 * - It executes a loop and in every cycle of the loop commands may be
 *   sent to the Slave Applications and reports may be received from them.
 * .
 * The schedule for sending commands to the Slave Applications is as follows:
 * - In cycles which are multiples of 5, the command to set the temperature limit
 *   in Slave 1 is sent
 * - In cycles which are multiples of 6, the command to enable temperature monitoring
 *   in Slave 1 is sent
 * - In cycles which are multiples of 90, the command to disable temperature
 *   monitoring in Slave 1 is sent
 * .
 * In all control cycles, the client socket waiting for reports from the two
 * slave applications is polled through a call to <code>::CrDaClientSocketPoll</code>.
 * @return always returns EXIT_SUCCESS
 */
int main() {
	FwSmDesc_t fwCmp[CR_MA_N_OF_FW_CMP];
	FwSmDesc_t inStreamSlave1, inStreamSlave2;
	FwSmDesc_t outStreamSlave1, outStreamSlave2;
	CrFwConfigCheckOutcome_t configCheckOutcome;
	FwSmDesc_t outCmd;
	int i;

	/* User warning about order in which demo applications are started */
	printf("MA: The Slave 1 Application (Server Socket) must be started before the Master Application\n");

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
	printf("MA: Consistency check of configuration parameters ran successfully.\n");

	/* Create In- and OutStreams */
	inStreamSlave1 = CrFwInStreamMake(0);
	inStreamSlave2 = CrFwInStreamMake(1);
	outStreamSlave1 = CrFwOutStreamMake(0);
	outStreamSlave2 = CrFwOutStreamMake(1);

	/* Set port number and host name */
	CrDaClientSocketSetPort(CR_DA_SOCKET_PORT);
	CrDaClientSocketSetHost("localhost");

	/* Initialize the InStreams and OutStreams */
	CrFwCmpInit(outStreamSlave1);
	if (!CrFwCmpIsInInitialized(outStreamSlave1))
		return 0;
	CrFwCmpInit(outStreamSlave2);
	if (!CrFwCmpIsInInitialized(outStreamSlave2))
		return 0;
	CrFwCmpInit(inStreamSlave1);
	if (!CrFwCmpIsInInitialized(inStreamSlave1))
		return 0;
	CrFwCmpInit(inStreamSlave2);
	if (!CrFwCmpIsInInitialized(inStreamSlave2))
		return 0;

	/* Configure the InStream and OutStream */
	CrFwCmpReset(inStreamSlave1);
	CrFwCmpReset(inStreamSlave2);
	CrFwCmpReset(outStreamSlave1);
	CrFwCmpReset(outStreamSlave2);
	if (!CrFwCmpIsInConfigured(inStreamSlave1))
		return 0;
	if (!CrFwCmpIsInConfigured(inStreamSlave2))
		return 0;
	if (!CrFwCmpIsInConfigured(outStreamSlave1))
		return 0;
	if (!CrFwCmpIsInConfigured(outStreamSlave2))
		return 0;

	/* Initialize and reset framework components */
	fwCmp[0] = CrFwOutFactoryMake();
	fwCmp[1] = CrFwInFactoryMake();
	fwCmp[2] = CrFwInLoaderMake();
	fwCmp[3] = CrFwInManagerMake(0);
	fwCmp[4] = CrFwInManagerMake(1);
	fwCmp[5] = CrFwInRegistryMake();
	fwCmp[6] = CrFwOutLoaderMake();
	fwCmp[7] = CrFwOutRegistryMake();
	fwCmp[8] = CrFwOutManagerMake(0);
	for (i=0; i<CR_MA_N_OF_FW_CMP; i++) {
		CrFwCmpInit(fwCmp[i]);
		if (!CrFwCmpIsInInitialized(fwCmp[i]))
			return 0;
		CrFwCmpReset(fwCmp[i]);
		if (!CrFwCmpIsInConfigured(fwCmp[i]))
			return 0;
	}

	/* Execute control cycles */
	for (i=1; i<100; i++) {
		printf("MA: Starting cycle %d\n",i);
		/* Set temperature limit in Slave 1 */
		if (i == 10) {
			CrMaOutCmpSetTempLimitSetTempLimit(TEMP_LIMIT);
			outCmd = CrFwOutFactoryMakeOutCmp(CR_DA_SERV_TYPE,CR_DA_SERV_SUBTYPE_SET,0,0);
			CrFwOutCmpSetDest(outCmd,CR_DA_SLAVE_1);
			CrFwOutLoaderLoad(outCmd);
			printf("MA: Sending command to set the temperature limit in Slave 1 to %d degC\n",TEMP_LIMIT);
		}
		/* Set temperature limit in Slave 2 */
		if (i == 11) {
			CrMaOutCmpSetTempLimitSetTempLimit(TEMP_LIMIT);
			outCmd = CrFwOutFactoryMakeOutCmp(CR_DA_SERV_TYPE,CR_DA_SERV_SUBTYPE_SET,0,0);
			CrFwOutCmpSetDest(outCmd,CR_DA_SLAVE_2);
			CrFwOutLoaderLoad(outCmd);
			printf("MA: Sending command to set the temperature limit in Slave 2 to %d degC\n",TEMP_LIMIT);
		}
		/* Enable temperature monitoring in Slave 1 in cycles which are multiples of 12 */
		if ((i % 12) == 0) {
			outCmd = CrFwOutFactoryMakeOutCmp(CR_DA_SERV_TYPE,CR_DA_SERV_SUBTYPE_EN,0,0);
			CrFwOutCmpSetDest(outCmd,CR_DA_SLAVE_1);
			CrFwOutLoaderLoad(outCmd);
			printf("MA: Sending command to enable temperature monitoring in Slave 1\n");
		}
		/* Enable temperature monitoring in Slave 2 in cycles which are multiples of 15 */
		if ((i % 15) == 0) {
			outCmd = CrFwOutFactoryMakeOutCmp(CR_DA_SERV_TYPE,CR_DA_SERV_SUBTYPE_EN,0,0);
			CrFwOutCmpSetDest(outCmd,CR_DA_SLAVE_2);
			CrFwOutLoaderLoad(outCmd);
			printf("MA: Sending command to enable temperature monitoring in Slave 2\n");
		}
		/* Disable temperature monitoring in Slave 1 in cycles which are multiples of 18 */
		if ((i % 18) == 0) {
			outCmd = CrFwOutFactoryMakeOutCmp(CR_DA_SERV_TYPE,CR_DA_SERV_SUBTYPE_DIS,0,0);
			CrFwOutCmpSetDest(outCmd,CR_DA_SLAVE_1);
			CrFwOutLoaderLoad(outCmd);
			printf("MA: Sending command to disable temperature monitoring in Slave 1\n");
		}
		/* Disable temperature monitoring in Slave 2 in cycles which are multiples of 60 */
		if ((i % 60) == 0) {
			outCmd = CrFwOutFactoryMakeOutCmp(CR_DA_SERV_TYPE,CR_DA_SERV_SUBTYPE_DIS,0,0);
			CrFwOutCmpSetDest(outCmd,CR_DA_SLAVE_2);
			CrFwOutLoaderLoad(outCmd);
			printf("MA: Sending command to disable temperature monitoring in Slave 2\n");
		}
		/* Poll socket for incoming reports */
		CrDaClientSocketPoll();

		/* Load packets from the two InStreams */
		CrFwInLoaderSetInStream(inStreamSlave1);
		FwSmExecute(CrFwInLoaderMake());
		CrFwInLoaderSetInStream(inStreamSlave2);
		FwSmExecute(CrFwInLoaderMake());

		/* Execute Managers */
		FwSmExecute(CrFwInManagerMake(1));	/* The first InManager is not used */
		FwSmExecute(CrFwOutManagerMake(0));

		/* Check application errors */
		if (CrFwGetAppErrCode() != crNoAppErr) {
			printf("MA: Application Error Code is set and is equal to: %d\n",CrFwGetAppErrCode());
		}

		/* Wait 1 second and then continue */
		sleep(1);
	}

	return EXIT_SUCCESS;
}

