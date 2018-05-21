/**
 * @file
 * @ingroup crConfigDemoMaster
 * Implementation of the error reporting interface of <code>CrFwRepErr.h</code>
 * for the Master Application of the CORDET Demo.
 * This implementation writes the InCommand Outcome Reports to standard output.
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
/* Include Framework Files */
#include "CrFwConstants.h"
#include "CrFwRepInCmdOutcome.h"

/*-----------------------------------------------------------------------------------------*/
void CrFwRepInCmdOutcome(CrFwRepInCmdOutcome_t outcome, CrFwInstanceId_t instanceId, CrFwServType_t servType,
                         CrFwServSubType_t servSubType, CrFwDiscriminant_t disc, CrFwOutcome_t failCode, FwSmDesc_t inCmd) {

	printf("CrFwRepInCmdOutcome: unexpected outcome for InCommand %d, service type %d,\n",instanceId,servType);
	printf("                     service sub-type %d, and discriminant %d\n",servSubType,disc);

}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepInCmdOutcomeCreFail(CrFwRepInCmdOutcome_t outcome, CrFwOutcome_t failCode, CrFwPckt_t pckt) {

	printf("CrFwRepInCmdOutcomeCreFailt: failure to create InCommand component\n");
}

