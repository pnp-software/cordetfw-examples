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
