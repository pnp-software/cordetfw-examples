/**
 * @file
 * @ingroup crDemoMaster
 * OutComponent encapsulating a command to enable or disable temperature monitoring in
 * a Slave Application.
 * An OutComponent is defined by defining the functions which override its
 * adaptation points, namely (see <code>CrFwOutCmp.h</code>):
 * - The Enable Check Operation
 * - The Ready Check Operation
 * - The Serialize Operation
 * .
 * These operations are defined as follows for the command to enable/disable temperature
 * monitoring:
 * - Enable Check Operation: the default Enable Check Operation of
 *   <code>CrFwOutCmpDefEnableCheck.h</code> is used.
 * - Ready Check Operation: the default Ready Check Operation of
 *   <code>CrFwSmCheckAlwaysTrue.h</code> is used.
 * - Serialize Operation: this operation calls the default Serialize Operation of
 *   <code>CrFwOutCmpDefSerialize.h</code> and then it sets
 *   the command destination (either Slave 1 or Slave 2) and it sets the acknowledge
 *   level to acknowledge execution start.
 * .
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

#ifndef CRMA_OUTCMP_ENABLE_DISABLE_H_
#define CRMA_OUTCMP_ENABLE_DISABLE_H_

/* Include framework components */
#include "CrFwConstants.h"
/* Include FW Profile components */
#include "FwSmCore.h"

/**
 * Implementation of the Serialize Operation for the command to enable or disable
 * temperature monitoring.
 * This operation calls the default Serialize Operation of
 * <code>CrFwOutCmpDefSerialize.h</code> and then it sets the
 * destination (either Slave 1 or Slave 2) and it sets the acknowledge level to acknowledge
 * execution start.
 * The value of the temperature limit is set through function
 * <code>::CrMaOutCmpSetTempLimitSetTempLimit</code>.
 * @param smDesc the descriptor of the OutComponent state machine
 * @return the value of the Enable Flag
 */
void CrMaOutCmpEnableDisableSerialize(FwSmDesc_t smDesc);

#endif /* CRMA_OUTCMP_ENABLE_DISABLE_H_ */
