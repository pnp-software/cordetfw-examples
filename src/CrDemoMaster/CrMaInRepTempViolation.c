/**
 * @file
 * @ingroup crDemoMaster
 * Implementation of the Temperature Limit Violation InReport.
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
