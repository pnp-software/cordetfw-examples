/**
 * @file
 * @ingroup crConfigDemoSlave1
 * User-modifiable parameters for the InFactory component (see <code>CrFwInFactory.h</code>)
 * of the Slave Application of the CORDET Demo.
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

#ifndef CRMA_INFACTORY_USERPAR_H_
#define CRMA_INFACTORY_USERPAR_H_

#include "CrDaTempMonitor.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/**
 * The maximum number of components representing an incoming command which may be allocated
 * at any one time.
 * This constant must be a positive integer smaller than the range of
 * <code>::CrFwInFactoryPoolIndex_t</code>.
 */
#define CR_FW_INFACTORY_MAX_NOF_INCMD 10

/**
 * The maximum number of InReports which may be allocated at any one time.
 * This constant must be smaller than the range of <code>::CrFwInFactoryPoolIndex_t</code>.
 */
#define CR_FW_INFACTORY_MAX_NOF_INREP 10

/**
 * The total number of kinds of incoming commands supported by the application.
 * An incoming command kind is defined by the triplet: [service type, service sub-type,
 * discriminant value].
 * The value of this constant must be the same as the number of rows of the
 * initializer <code>#CR_FW_INCMD_INIT_KIND_DESC</code> and it must be smaller
 * than the range of the <code>::CrFwCmdRepKindIndex_t</code> type.
 *
 * The Slave Application receives three kinds of InCommand.
 */
#define CR_FW_INCMD_NKINDS 3

/**
 * The total number of kinds of incoming reports supported by the application.
 * An incoming report kind is defined by the triplet: [service type, service sub-type,
 * discriminant value].
 * The value of this constant must be the same as the number of rows of the
 * initializer <code>#CR_FW_INREP_INIT_KIND_DESC</code> and it must be smaller
 * than the range of the <code>::CrFwCmdRepKindIndex_t</code> type.
 *
 * The Slave Application receives no InReports and hence this constant
 * should be equal to zero.
 * However, this constant is used as the size of an array.
 * Zero-sized arrays are not allowed in all versions of C.
 * Hence, in order to ensure compatibility with a wide range of C compilers, a value of 1
 * is used for this constant.
 */
#define CR_FW_INREP_NKINDS 1

/**
 * Definition of the incoming command kinds supported by the application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * An incoming command kind is defined by the triplet: [service type, service sub-type,
 * discriminant].
 *
 * Each line in this initializer describes one incoming command kind.
 * The elements in each line are as follows:
 * - The service type.
 * - The service sub-type.
 * - The discriminant value. A value of zero indicates either that no discriminant is
 *   associated to commands/reports of that type and sub-type or else that all commands/reports of
 *   this type and sub-type have the same characteristics.
 * - The function implementing the Validity Check Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdValidityCheck_t</code>;
 *   function <code>::CrFwPrCheckAlwaysTrue</code> can be used as a default).
 * - The function implementing the Ready Check Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdReadyCheck_t</code>;
 *   function <code>::CrFwSmCheckAlwaysTrue</code> can be used as a default).
 * - The function implementing the Start Action Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdStartAction_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as a default).
 * - The function implementing the Progress Action Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdProgressAction_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as a default).
 * - The function implementing the Termination Action Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdTerminationAction_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as a default).
 * - The function implementing the Abort Action Operation for this kind of incoming command
 *   (this must be a function pointer of type <code>::CrFwInCmdAbortAction_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as a default).
 * .
 * The list of service descriptors must satisfy the following constraints:
 * - The number of lines must be the same as <code>::CR_FW_INCMD_NKINDS</code>.
 * - The values of the service types, sub-types and discriminant must be lower than
 * 	 <code>#CR_FW_MAX_SERV_TYPE</code>, <code>#CR_FW_MAX_SERV_SUBTYPE</code> and
 * 	 <code>#CR_FW_MAX_DISCRIMINANT</code>.
 * - The service types must be listed in increasing order.
 * - The service sub-types within a service type must be listed in increasing order.
 * - The discriminant values within a service type/sub-type must be listed in increasing order.
 * .
 * The last four constraints are checked by the auxiliary function
 * <code>::CrFwAuxInFactoryInCmdConfigCheck</code>.
 *
 * The initializer values defined below are those which are used for the Slave Applications.
 * The non-default function pointers for the Progress Actions are defined in
 * <code>CrDaTempMonitoring.h</code>.
 */
#define CR_FW_INCMD_INIT_KIND_DESC \
	{ {64, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
						&CrDaTempMonitoringEnable, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
      {64, 2, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
						&CrDaTempMonitoringDisable, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
      {64, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
						&CrDaTempMonitoringSetTempLimit, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
	}

/**
 * Definition of the incoming report kinds supported by an application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * An incoming report kind is defined by the triplet: [service type, service sub-type,
 * discriminant].
 *
 * Each line in this initializer describes one incoming report kind.
 * The elements in each line are as follows:
 * - The service type.
 * - The service sub-type.
 * - The discriminant value. A value of zero indicates either that no discriminant is
 *   associated to commands/reports of that type and sub-type or else that all commands/reports of
 *   this type and sub-type have the same characteristics.
 * - The function implementing the Update Action Operation for this kind of incoming report
 *   (this must be a function pointer of type <code>::CrFwInRepUpdateAction_t</code>;
 *   function <code>::CrFwPrEmptyAction</code> can be used as a default).
 * - The function implementing the Validity Check Operation for this kind of incoming report
 *   (this must be a function pointer of type <code>::CrFwInRepValidityCheck_t</code>;
 *   function <code>::CrFwPrCheckAlwaysTrue</code> can be used as a default).
 * .
 * The list of service descriptors must satisfy the following constraints:
 * - The number of lines must be the same as <code>::CR_FW_INREP_NKINDS</code>.
 * - The values of the service types, sub-types and discriminant must be lower than
 * 	 <code>#CR_FW_MAX_SERV_TYPE</code>, <code>#CR_FW_MAX_SERV_SUBTYPE</code> and
 * 	 <code>#CR_FW_MAX_DISCRIMINANT</code>.
 *   maximum values defined in <code>CrFwUserConstants.h</code> (TBC).
 * - The service types must be listed in increasing order.
 * - The service sub-types within a service type must be listed in increasing order.
 * - The discriminant values within a service type/sub-type must be listed in increasing order.
 * .
 * The last four constraints are checked by the auxiliary function
 * <code>::CrFwAuxInFactoryInRepConfigCheck</code>.
 *
 * The initializer values defined below are those which are used for the Slave Applications.
 * The Slave Applications do not receive any reports but a dummy report is defined all the
 * same to avoid use of zero-sized array.
 */
#define CR_FW_INREP_INIT_KIND_DESC \
	{ {64, 4, 0, &CrFwPrEmptyAction, &CrFwPrCheckAlwaysTrue}, \
	}

#endif /* CRFW_INFACTORY_USERPAR_H_ */
