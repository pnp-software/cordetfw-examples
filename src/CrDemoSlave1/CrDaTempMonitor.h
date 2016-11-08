/**
 * @file
 * @ingroup crDemoSlave1
 * Temperature monitoring logic in the slave applications.
 * The slave applications are responsible for monitoring a temperature measurement.
 * This module defines the functions through which:
 * - Temperature monitoring is enabled
 * - Temperature monitoring is disabled
 * - The limit against which monitoring is performed is defined
 * - Temperature monitoring is performed
 * .
 * Some of the functions defined in this module are used as progress actions for the commands
 * which the Slave Applications receive from the Master Application (see customization of
 * commands in <code>CrFwInFactoryUserPar.h</code>).
 * They are therefore defined to comply with the <code>::CrFwInCmdProgressAction_t</code> prototype.
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

#ifndef CRDA_TEMPMONITORING_H_
#define CRDA_TEMPMONITORING_H_

/* Include Framework Files */
#include "CrFwConstants.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

/**
 * Enable temperature monitoring.
 * This function is intended to be used as progress action for the
 * InCommand which enables temperature monitoring.
 * @param smDesc the InCommand state machine descriptor (this argument is
 * required for compatibility with the <code>::CrFwInCmdProgressAction_t</code> prototype)
 */
void CrDaTempMonitoringEnable(FwSmDesc_t smDesc);

/**
 * Disable temperature monitoring.
 * This function is intended to be used as progress action for the
 * InCommand which disables temperature monitoring.
 * @param smDesc the InCommand state machine descriptor (this argument is
 * required for compatibility with the <code>::CrFwInCmdProgressAction_t</code> prototype)
 */
void CrDaTempMonitoringDisable(FwSmDesc_t smDesc);

/**
 * Set the limit against the temperature is monitored.
 * This function is intended to be used as progress action for the
 * InCommand which set the temperature monitoring limit.
 * @param smDesc the InCommand state machine descriptor (this argument is
 * required for compatibility with the <code>::CrFwInCmdProgressAction_t</code> prototype)
 */
void CrDaTempMonitoringSetTempLimit(FwSmDesc_t smDesc);

/**
 * Execute a temperature monitoring action on the argument temperature.
 * If temperature monitoring is disabled, this function returns without doing anything.
 * If temperature monitoring is enabled, this function compares the argument temperature with
 * its temperature limit and if it finds that the argument temperature exceeds its limit,
 * it generates a "temperature limit violated" report to the Master Application.
 *
 * This function would normally be called periodically by the host application.
 * @param temp the temperature to be monitored (an integer in the range 0 to 127)
 * @param appId the identifier of the application which is performing the monitoring
 * (either Slave 1 or Slave 2)
 */
void CrDaTempMonitoringExec(char temp, CrFwDestSrc_t appId);

#endif /* CRDA_TEMPMONITORING_H_ */
