/**
 * @file
 * @ingroup crConfigDemoMaster
 * Header file to define all user-configurable constants and types for the Master
 * Application of the CORDET Demo.
 * The content of this file is taken over unchanged from the framework-provided default
 * with the exception of the following items:
 * - The value of the application identifier
 * - The maximum value of the service type, sub-type and discriminant attributes
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

#ifndef CRFW_USERCONSTANTS_H_
#define CRFW_USERCONSTANTS_H_

#include "CrMaConstants.h"
#include "FwPrConstants.h"

/** Type used for instance identifiers. */
typedef unsigned short CrFwInstanceId_t;

/** Type used for the identifier of a component type. */
typedef unsigned short int CrFwTypeId_t;

/** Type used for the outcome of a check (see <code>::CrFwCmpData</code>). */
typedef unsigned char CrFwOutcome_t;

/** Type used for the sequence counter of commands or reports. */
typedef unsigned int CrFwSeqCnt_t;

/** Type used for the application time. */
typedef float CrFwTime_t;

/** Type used for the time stamp of a command or report. */
typedef unsigned int CrFwTimeStamp_t;

/** Type used for the number of elapsed cycles.
 * Many applications operate on a cyclical basis and this
 * type is used for the number of elapsed execution cycles. */
typedef unsigned int CrFwTimeCyc_t;

/** Type used for the service type of a command or report. */
typedef unsigned char CrFwServType_t;

/** Type used for the command or report sub-type. */
typedef unsigned char CrFwServSubType_t;

/** Type used for the destination or source group of a packet. */
typedef unsigned char CrFwGroup_t;

/** Type used for the command or report destination and source. */
typedef unsigned char CrFwDestSrc_t;

/** Type used for the discriminant of a command or report. */
typedef unsigned short CrFwDiscriminant_t;

/** Type for the index used to track the state of a component. */
typedef unsigned short CrFwTrackingIndex_t;

/** Type for the index of a command or report kind. */
typedef unsigned short CrFwCmdRepKindIndex_t;

/** Type for the component kind key in <code>CrFwInFactory.c</code> and <code>CrFwOutFactory.c</code>. */
typedef unsigned int CrFwCmdRepKindKey_t;

/**
 * Type for the index in the pool of pre-allocated OutComponents in
 * the OutFactory (see <code>CrFwOutFactory.h</code>).
 */
typedef unsigned char CrFwOutFactoryPoolIndex_t;

/**
 * Type for the index in the pool of pre-allocated incoming components in
 * the InFactory (see <code>CrFwInFactory.h</code>).
 */
typedef unsigned char CrFwInFactoryPoolIndex_t;

/** Type used for unsigned integers with a "short" range. */
typedef unsigned char CrFwCounterU1_t;

/** Type used for signed integers with a "short" range. */
typedef signed char CrFwCounterS1_t;

/** Type used for unsigned integers with a "medium" range. */
typedef unsigned short CrFwCounterU2_t;

/** Type for the packet length. */
typedef unsigned short int CrFwPcktLength_t;

/**
 * Identifier for the errors reported through the error reporting interface of <code>CrFwRepErr.h</code>.
 * When a framework component encounters a non-nominal situation during its normal operation,
 * it reports it as an error using the services defined by the <code>CrFwRepErr.h</code>
 * interface.
 * Each error situation is characterized by an error code.
 * This enumerated type defines all the error codes.
 */
typedef enum {
	/** The packet queue of an OutStream is full (see <code>CrFwOutStream.h</code>) */
	crOutStreamPQFull =2,
	/** The packet queue of an InStream is full (see <code>CrFwInStream.h</code>) */
	crInStreamPQFull =3,
	/** An InStream has encountered a sequence counter error (see <code>CrFwInStream.h</code>) */
	crInStreamSCErr =4,
	/** An OutComponent has an invalid destination (see <code>CrFwOutCmp.h</code>) */
	crOutCmpSendPcktInvDest =5,
	/** The Pending OutComponent List (POCL) of an OutManager is full (see <code>CrFwOutManager.h</code>) */
	crOutManagerPoclFull =6,
	/** The Pending Command/Report List (PCRL) of an InManager is full (see <code>CrFwInManager.h</code>) */
	crInManagerPcrlFull =7,
	/** The InLoader has retrieved a packet with an invalid destination (see <code>CrFwInLoader.h</code>) */
	crInLoaderInvDest = 8,
	/** An InReport or InCommand has failed its acceptance check */
	crInLoaderAccFail = 9,
	/** An OutComponent has an illegal group */
	crOutStreamIllGroup = 10,
	/** An incoming command or report has an illegal group */
	crInStreamIllGroup = 11,
	/** An OutStream cannot buffer an out-going packet because no more packets are available (see <code>CrFwOutStream.h</code>) */
	crOutStreamNoMorePckt =12,
	/** An InReport could not be created due to insufficient resources or illegal type/sub-type/discriminant */
	crInLoaderCreFail = 13,
	/** An InReport could not be loaded in its InManager */
	crInLoaderLdFail = 14
} CrFwRepErrCode_t;

/**
 * Application error code for the framework components.
 * An application error is declared when a framework function has been called by the
 * application code with an illegal parameter values or in an illegal context and execution
 * of the function with the illegal values would cause an internal framework data structure
 * to be corrupted.
 *
 * Nominally, the application error code should be equal to: <code>::crNoAppErr</code>.
 * If the application error code has a different value, then an application error has been
 * encountered.
 * If multiple errors have been encountered, the application error code reflects the
 * most recent error.
 */
typedef enum {
	/** No application errors have been detected. */
	crNoAppErr = 0,
	/** An OutStream function was called on an object which is not an OutStream. */
	crNotOutStream = 1,
	/** A framework function has been called with an illegal OutStream identifier. */
	crOutStreamIllId = 2,
	/**
	 * A framework function has been called with a destination attribute which is not
	 * associated to any OutStream.
	 */
	crOutStreamUndefDest = 3,
	/**
	 * A framework function has been called with a source attribute which is not
	 * associated to any InStream.
	 */
	crInStreamUndefDest = 4,
	/** A packet allocation request has failed (see <code>::CrFwPcktMake</code>). */
	crPcktAllocationFail = 5,
	/** A packet release request has encountered an error (see <code>::CrFwPcktRelease</code>). */
	crPcktRelErr = 6,
	/** An InStream function was called on an object which is not an InStream. */
	crNotInStream = 7,
	/** A framework function has been called with an illegal InStream identifier. */
	crInStreamIllId = 8,
	/** An OutComponent function was called on an object which is not an OutComponent. */
	crNotOutCmp = 9,
	/** An OutComponent allocation request has failed (see <code>::CrFwOutFactoryMakeOutCmp</code>). */
	crOutCmpAllocationFail = 10,
	/** An OutComponent release request has encountered an error (see <code>::CrFwOutFactoryReleaseOutCmp</code>). */
	crOutCmpRelErr = 11,
	/** A framework function was called with an illegal service type */
	crIllServType = 12,
	/** A framework function was called with an illegal service sub-type */
	crIllServSubType = 13,
	/** A framework function was called with an illegal discriminant */
	crIllDiscriminant = 14,
	/** A framework function was called with an illegal type/sub-type pair for an OutComponent */
	crIllOutCmpType = 15,
	/** A framework function was called with an illegal type/sub-type/discriminant triplet for an OutComponent */
	crIllOutCmpKind = 16,
	/** A framework function has been called with an illegal OutManager identifier. */
	crOutManagerIllId = 17,
	/** A framework function was called with an illegal type/sub-type/discriminant triplet for an InCommand */
	crIllInCmdKind = 18,
	/** Allocation request for a packet for an InCommand has failed (see <code>::CrFwInFactoryMakeInCmd</code>). */
	crInCmdAllocationFail = 19,
	/** A framework function was called with an illegal type/sub-type/discriminant triplet for an InReport */
	crIllInRepKind = 20,
	/** Allocation request for an InReport has failed (see <code>::CrFwInFactoryMakeInRep</code>). */
	crInRepAllocationFail = 21,
	/** An InReport release request has encountered an error (see <code>::CrFwInFactoryReleaseInRep</code>). */
	crInRepRelErr = 22,
	/** An InCommand release request has encountered an error (see <code>::CrFwInFactoryReleaseInCmd</code>). */
	crInCmdRelErr = 23,
	/** A framework function has been called with an illegal InManager identifier. */
	crInManagerIllId = 24
} CrFwAppErrCode_t;

/**
 * The maximum number of packets which can be created with the default packet implementation.
 * The value of this constant must not exceed the range of the <code>CrFwCounterU2_t</code> type.
 */
#define CR_FW_MAX_NOF_PCKTS 12

/** The identifier of the Master Application of the CORDET Demo */
#define CR_FW_HOST_APP_ID 1

/** The number of bits reserved for the application identifier in a command or report identifier */
#define CR_FW_NBITS_APP_ID 4

/** Maximum value of the service type attribute of InReports and InCommands for the Master Application */
#define CR_FW_MAX_SERV_TYPE 64

/** Maximum value of the service sub-type attribute of InReports and InCommands for the Master Application */
#define CR_FW_MAX_SERV_SUBTYPE 4

/** Maximum value of the discriminant attribute of InReports and InCommands for the Master Application */
#define CR_FW_MAX_DISCRIMINANT 1

#endif /* CRFW_USERCONSTANTS_H_ */
