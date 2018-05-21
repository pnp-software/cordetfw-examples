/**
 * @file
 * @ingroup crConfigDemoMaster
 * User-modifiable parameters for the OutFactory component (see <code>CrFwOutFactory.h</code>)
 * of the Master Application of the CORDET Demo.
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

#include "CrMaOutCmpEnableDisable.h"
#include "CrMaOutCmpSetTempLimit.h"

#ifndef CRFW_OUTFACTORY_USERPAR_H_
#define CRFW_OUTFACTORY_USERPAR_H_

/**
 * The maximum number of OutComponents which may be allocated at any one time.
 * This constant must be smaller than the range of <code>::CrFwOutFactoryPoolIndex_t</code>.
 */
#define CR_FW_OUTFACTORY_MAX_NOF_OUTCMP 10

/**
 * The total number of kinds of OutComponents supported by the application.
 * An OutComponent kind is defined by the triplet: [service type, service sub-type,
 * discriminant value].
 * The value of this constant must be the same as the number of rows of the
 * initializer <code>#CR_FW_OUTCMP_INIT_KIND_DESC</code> and it must be smaller
 * than the range of the <code>::CrFwCmdRepKindIndex_t</code> type.
 */
#define CR_FW_OUTCMP_NKINDS 3

/**
 * Definition of the OutComponent kinds supported by an application.
 * An application supports a number of service types and, for each service type, it supports
 * a number of sub-types.
 * Each sub-type may support a range of discriminant values.
 * An OutComponent kind is defined by the triplet: [service type, service sub-type, discriminant].
 *
 * Each line in this initializer describes one OutComponent kind.
 * If the discriminant field is different from zero, then the line describes the characteristics
 * of the reports/commands of that specific kind (as identified by the triplet
 * [service type, service sub-type, discriminant]).
 * If, instead, the discriminant is equal to zero, then the line describes the default characteristics
 * of all reports/commands of the given type and sub-type.
 *
 * The elements in each line are as follows:
 * - The service type.
 * - The service sub-type.
 * - The discriminant value.
 * - The command/report flag. A value of 1 indicates that the OutComponent is a command and
 *   a value of 2 indicates that it is a report,
 * - The length (in number of bytes) of the packet (see <code>CrFwPckt.h</code>) to which
 *   this kind of OutComponent is serialized.
 * - The function implementing the Enable Check Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpEnableCheck_t</code>;
 *   function <code>CrFwOutCmpDefEnableCheck</code> can be used as default).
 * - The function implementing the Ready Check Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpReadyCheck_t</code>;
 *   function <code>CrFwSmCheckAlwaysTrue</code> can be used as default).
 * - The function implementing the Repeat Check Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpRepeatCheck_t</code>;
 *   function <code>::CrFwSmCheckAlwaysFalse</code> can be used as default).
 * - The function implementing the Update Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpUpdate_t</code>;
 *   function <code>::CrFwSmEmptyAction</code> can be used as default).
 * - The function implementing the Serialize Operation for this kind of component
 *   (this must be a function pointer of type <code>::CrFwOutCmpSerialize_t</code>;
 *   function <code>CrFwOutCmpDefSerialize</code> can be used as default).
 * .
 * The list of service descriptors must satisfy the following constraints:
 * - The number of lines must be the same as <code>::CR_FW_OUTCMP_NKINDS</code>.
 * - The set of service types and sub-types and their discriminants must be consistent
 *   with the definition of <code>::CR_FW_OUTREGISTRY_INIT_SERV_DESC</code>.
 * - The service types must be listed in increasing order.
 * - The service sub-types within a service type must be listed in increasing order.
 * - The discriminant values within a service type/sub-type must be listed in increasing order.
 * .
 * The last four constraints are checked by the auxiliary function
 * <code>::CrFwAuxOutFactoryConfigCheck</code>.
 *
 * The initializer values defined below are which are used for the Master Application.
 * The function pointers for the serialize operations are defined in
 * <code>CrMaOutCmpEnableDisable.h</code> and in <code>CrMaOutCmpSetTempLimit.h</code>.
 */
#define CR_FW_OUTCMP_INIT_KIND_DESC \
	{ {64, 1, 0, 1, 100, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
							&CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrMaOutCmpEnableDisableSerialize}, \
	  {64, 2, 0, 1, 100, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
							&CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrMaOutCmpEnableDisableSerialize}, \
	  {64, 3, 0, 1, 100, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
							&CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrMaOutCmpSetTempLimitSerialize}, \
	}

#endif /* CRFW_OUTFACTORY_USERPAR_H_ */
