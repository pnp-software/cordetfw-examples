/**
 * @file
 * @ingroup crDemoMaster
 * Header file to define constants and types for the CORDET Demo.
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

#ifndef CRDA_CONSTANTS_H_
#define CRDA_CONSTANTS_H_

#include "FwPrConstants.h"

/** The identifier of the Master Application of the CORDET Demo */
#define CR_DA_MASTER 1

/** The identifier of the first Slave Application of the CORDET Demo */
#define CR_DA_SLAVE_1 2

/** The identifier of the first Slave Application of the CORDET Demo */
#define CR_DA_SLAVE_2 3

/** The port number for the socket port */
#define CR_DA_SOCKET_PORT 2002

/** The identifier of the service type supported by the demo application */
#define CR_DA_SERV_TYPE 64

/** The identifier of the service sub-type to enable temperature monitoring */
#define CR_DA_SERV_SUBTYPE_EN 1

/** The identifier of the service sub-type to disable temperature monitoring */
#define CR_DA_SERV_SUBTYPE_DIS 2

/** The identifier of the service sub-type to set the temperature limit */
#define CR_DA_SERV_SUBTYPE_SET 3

/** The identifier of the service sub-type to report a temperature violation */
#define CR_DA_SERV_SUBTYPE_REP 4

#endif /* CRFW_USERCONSTANTS_H_ */
