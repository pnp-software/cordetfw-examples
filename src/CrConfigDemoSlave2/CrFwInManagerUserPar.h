/**
 * @file
 * @ingroup crConfigDemoSlave2
 * User-modifiable parameters for the InManager components (see <code>CrFwInManager.h</code>)
 * of the Slave Application of the CORDET Demo.
 *
 * The parameters defined in this file determine the configuration of the InManager Components.
 * The value of these parameters cannot be changed dynamically.
 *
 * The Slave Application only needs one InManager for incoming commands.
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

#ifndef CR_FW_INMANAGER_USERPAR_H_
#define CR_FW_INMANAGER_USERPAR_H_

/**
 * The number of InManager components in the application.
 * The value of this constant must be smaller than the range of the <code>::CrFwCounterU1_t</code>
 * integer type.
 */
#define CR_FW_NOF_INMANAGER 1

/**
 * The sizes of the Pending Command/Report List (PCRL) of the InManager components.
 * Each InManager has one PCRL.
 * This constant defines the size of the PCRL of the i-th InManager.
 * The size of a PCRL must be a positive integer (i.e. it is not legal
 * to define a zero-size PCRL) in the range of the <code>#CrFwCounterU2_t</code> type.
 */
#define CR_FW_INMANAGER_PCRLSIZE {10}

#endif /* CR_FW_INMANAGER_USERPAR_H_ */
