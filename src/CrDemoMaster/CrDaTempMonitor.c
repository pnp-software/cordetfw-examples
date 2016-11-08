/**
 * @file
 * @ingroup crDemoMaster
 * Implementation of temperature monitoring module.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 * @version GPLv3_0.7.1
 *
 * This file is part of CORDET Framework.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdio.h>
#include "CrDaServerSocket.h"
#include "CrDaConstants.h"
#include "CrDaOutCmpTempViolation.h"
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
#include "OutLoader/CrFwOutLoader.h"
#include "OutFactory/CrFwOutFactory.h"
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

/** The temperature limit */
static int tempLimit = 0;

/** The enable status of temperature monitoring */
static CrFwBool_t isTempMonitoringEnabled = 0;

/* ---------------------------------------------------------------------- */
void CrDaTempMonitoringEnable(FwSmDesc_t smDesc) {
	isTempMonitoringEnabled = 1;
}

/* ---------------------------------------------------------------------- */
void CrDaTempMonitoringDisable(FwSmDesc_t smDesc) {
	isTempMonitoringEnabled = 0;
}

/* ---------------------------------------------------------------------- */
void CrDaTempMonitoringSetTempLimit(FwSmDesc_t smDesc) {
	char* pcktPar = CrFwInCmdGetParStart(smDesc);
	tempLimit = pcktPar[0];
}

/* ---------------------------------------------------------------------- */
void CrDaTempMonitoringExec(char temp, CrFwDestSrc_t appId) {
	FwSmDesc_t rep;
	if (isTempMonitoringEnabled == 1) {
		if (temp > tempLimit) {
			if (appId == CR_DA_SLAVE_1)
				printf("S1: Temperature violation detected -- Sending report to Master Application\n");
			else
				printf("S2: Temperature violation detected -- Sending report to Master Application\n");
			/* Create outReport reporting temperature violation */
			rep = CrFwOutFactoryMakeOutCmp(CR_DA_SERV_TYPE,CR_DA_SERV_SUBTYPE_REP,0,0);
			CrDaOutCmpTempViolationSetTemp(temp);
			CrFwOutCmpSetDest(rep,CR_DA_MASTER);
			/* Request outReport to be sent out */
			CrFwOutLoaderLoad(rep);
		}
	}
	return;
}
