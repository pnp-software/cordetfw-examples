/**
 * @file
 * @ingroup crConfigDemoSlave2
 * User-modifiable parameters for the InLoader components (see <code>CrFwInLoader.h</code>) for
 * the Slave 2 Application of the CORDET Demo.
 * This file defines all the user-modifiable parameters for the InLoader.
 *
 * The parameters defined in this file determine the configuration of the InLoader singleton
 * component.
 * The value of these parameters cannot be changed dynamically.
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

#ifndef CR_MA_INLOADER_USERPAR_H_
#define CR_MA_INLOADER_USERPAR_H_

#include "InLoader/CrFwInLoader.h"

/**
 * The function which determines the re-routing destination of a packet.
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetReroutingDest_t</code>.
 * The function specified here is one of the default re-routing destination functions defined in
 * <code>CrFwInLoader.h</code>.
 * Use of this re-routing function implies that the Slave 2 Application has no re-routing capabilities.
 */
#define CR_FW_INLOADER_DET_REROUTING_DEST CrFwInLoaderDefNoRerouting;

/**
 * The function which determines the InManager into which an InReport or InCommand must be loaded.
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetInManager_t</code>.
 * The function specified here is the default re-routing destination function defined in
 * <code>CrFwInLoader.h</code>.
 */
#define CR_FW_INLOADER_SEL_INMANAGER CrFwInLoaderDefGetInManager;

#endif /* CR_MA_INLOADER_USERPAR_H_ */
