/**
 * @file
 * @ingroup crDemoMaster
 * Implementation of the command to set the temperature limit.
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

#include <stdlib.h>
/* Include configuration files */
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "OutCmp/CrFwOutCmp.h"
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
/* Include Demo Application files */
#include "CrMaOutCmpSetTempLimit.h"

/** The temperature limit */
static char cmdTempLimit = 0;

/*-----------------------------------------------------------------------------------------*/
void CrMaOutCmpSetTempLimitSerialize(FwSmDesc_t smDesc) {
	char* pcktPar = CrFwOutCmpGetParStart(smDesc);
	CrFwOutCmpDefSerialize(smDesc);
	CrFwOutCmpSetAckLevel(smDesc, 0, 1, 0, 0);
	pcktPar[0] = cmdTempLimit;
}

/*-----------------------------------------------------------------------------------------*/
void CrMaOutCmpSetTempLimitSetTempLimit(char tempLimit) {
	cmdTempLimit = tempLimit;
}
