/**
 * @file
 * @ingroup crDemoMaster
 * Implementation of the Temperature Limit Violation InReport.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CrDaConstants.h"
/* Include configuration files */
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "InRep/CrFwInRep.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "OutFactory/CrFwOutFactory.h"
#include "Pckt/CrFwPckt.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrMaInRepTempViolationValidityCheck(FwPrDesc_t prDesc) {
	return 1;
}

/*-----------------------------------------------------------------------------------------*/
void CrMaInRepTempViolationUpdateAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInRepData_t* cmpSpecificData = (CrFwInRepData_t*)(cmpData->cmpSpecificData);
	CrFwPckt_t pckt = cmpSpecificData->pckt; /* the incoming packet */
	char* pcktPar = CrFwPcktGetParStart(pckt);	/* the parameter area of the incoming packet */
	if (CrFwPcktGetSrc(pckt) == CR_DA_SLAVE_1) {
		printf("MA: Seq. Counter %d - Limit Violation in Slave 1, Temperature = %d\n", CrFwPcktGetSeqCnt(pckt),
		       pcktPar[0]);
		cmpData->outcome = 1;
		return;
	}
	if (CrFwPcktGetSrc(pckt) == CR_DA_SLAVE_2) {
		printf("MA: Seq. Counter %d - Limit Violation in Slave 2, Temperature = %d\n", CrFwPcktGetSeqCnt(pckt),
		       pcktPar[0]);
		cmpData->outcome = 1;
		return;
	}
	cmpData->outcome = 0;
}
