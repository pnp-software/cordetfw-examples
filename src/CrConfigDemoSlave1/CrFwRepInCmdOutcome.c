/**
 * @file
 * @ingroup crConfigDemoSlave1
 * Implementation of the error reporting interface of <code>CrFwRepErr.h</code>
 * for the Slave 1 Application of the CORDET Demo.
 * This implementation writes the InCommand Outcome Reports to standard output.
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
/* Include Framework Files */
#include "CrFwConstants.h"
#include "CrFwRepInCmdOutcome.h"

/*-----------------------------------------------------------------------------------------*/
void CrFwRepInCmdOutcome(CrFwRepInCmdOutcome_t outcome, CrFwInstanceId_t instanceId, CrFwServType_t servType,
                         CrFwServSubType_t servSubType, CrFwDiscriminant_t disc, CrFwOutcome_t failCode, FwSmDesc_t inCmd) {
	if (outcome == crCmdAckStrSucc) {
		if ((servType == CR_DA_SERV_TYPE) && (servSubType == CR_DA_SERV_SUBTYPE_EN))
			printf("S1: successful start for InCommand to enable temperature monitoring\n");
		else if ((servType == CR_DA_SERV_TYPE) && (servSubType == CR_DA_SERV_SUBTYPE_DIS))
			printf("S1: successful start for InCommand to disable temperature monitoring\n");
		else if ((servType == CR_DA_SERV_TYPE) && (servSubType == CR_DA_SERV_SUBTYPE_SET))
			printf("S1: successful start for InCommand to set temperature limit\n");
		return;
	}

	if (outcome == crCmdAckPrgSucc) {
		printf("S1: unexpected progress report for InCommand %d, service type %d,\n",instanceId,servType);
		printf("    service sub-type %d, and discriminant %d\n",servSubType,disc);
	} else if (outcome == crCmdAckTrmSucc) {
		printf("S1: unexpected termination report for InCommand %d, service type %d,\n",instanceId,servType);
		printf("    service sub-type %d, and discriminant %d\n",servSubType,disc);
	} else if (outcome == crCmdAckAccFail) {
		printf("S1: unexpected acceptance failure report for InCommand %d, service type %d,\n",instanceId,servType);
		printf("    service sub-type %d, and discriminant %d; fail code: %d\n",servSubType,disc,failCode);
	} else if (outcome == crCmdAckStrFail) {
		printf("S1: unexpected start failure report for InCommand %d, service type %d,\n",instanceId,servType);
		printf("    service sub-type %d, and discriminant %d; fail code: %d\n",servSubType,disc,failCode);
	} else if (outcome == crCmdAckPrgFail) {
		printf("S1: unexpected progress failure report for InCommand %d, service type %d,\n",instanceId,servType);
		printf("    service sub-type %d, and discriminant %d; fail code: %d\n",servSubType,disc,failCode);
	} else if (outcome == crCmdAckTrmFail) {
		printf("S1: unexpected termination failure report for InCommand %d, service type %d,\n",instanceId,servType);
		printf("    service sub-type %d, and discriminant %d; fail code: %d\n",servSubType,disc,failCode);
	}
}
