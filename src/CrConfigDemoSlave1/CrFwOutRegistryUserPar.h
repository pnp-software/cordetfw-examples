/**
 * @file
 * @ingroup crConfigDemoSlave1
 * User-modifiable parameters for the OutRegistry component (see <code>CrFwOutRegistry.h</code>).
 * This header file defines the set of services to be provided by the Slave Application of the
 * CORDET Demo.
 * A service is defined in terms of the following characteristics:
 * - The service type identifier
 * - The service sub-type identifier
 * - The range of discriminant values for that service type and sub-type
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

#ifndef CRFW_OUTREGISTRY_USERPAR_H_
#define CRFW_OUTREGISTRY_USERPAR_H_

/**
 * The maximum number of commands or reports which can be tracked by the OutRegistry.
 * This constant must be smaller than the range of <code>::CrFwTrackingIndex_t</code>.
 */
#define CR_FW_OUTREGISTRY_N 64

/**
 * The total number of out-going service types/sub-types offered by the application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * This constant defines the total number of [service type, service sub-type] pairs supported
 * by the application.
 * This constant must be smaller than the range of: <code>CrFwCmdRepIndex_t</code>.
 */
#define CR_FW_OUTREGISTRY_NSERV 1

/**
 * Definition of the range of out-going services supported by the application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * Each line in this initializer describes one [service type, service sub-type] pair which is
 * supported by the application.
 * The elements in each line are as follows:
 * - The service type
 * - The service sub-type
 * - The maximum value of the discriminant for commands or reports of that type and
 *   sub-type. A value of zero indicates that no discriminant is associated to commands
 *   or report of that type and sub-type.
 * .
 * The list of service descriptors must satisfy the following constraints:
 * - The number of lines must be the same as <code>#CR_FW_OUTREGISTRY_NSERV</code>.
 * - The service types must be listed in increasing order.
 * - The service sub-types within a service type must be listed in increasing order.
 * - The set of service type and sub-types must be consistent with the service types and
 *   sub-types declared in the <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer.
 * .
 * Compliance with the last three constraints is checked by
 * <code>::CrFwAuxOutRegistryConfigCheck</code>.
 */
#define CR_FW_OUTREGISTRY_INIT_SERV_DESC \
	{ {64, 4, 0}, \
	}

#endif /* CRFW_OUTREGISTRY_USERPAR_H_ */
