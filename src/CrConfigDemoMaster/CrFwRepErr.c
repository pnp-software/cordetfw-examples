/**
 * @file
 * @ingroup crConfigDemoMaster
 * Implementation of the error reporting interface of <code>CrFwRepErr.h</code>
 * for the Master Application of the CORDET Demo.
 * This implementation writes the error reports to standard output.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Include Framework Files */
#include "CrFwConstants.h"
#include "CrFwRepErr.h"

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErr(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId) {
	printf("CrFwErrRep: error %d generated by component %d of type %d\n", errCode,instanceId,typeId);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrDestSrc(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                       CrFwDestSrc_t destSrc) {
	printf("CrFwRepErrDestSrc: error %d generated by component %d of type %d for dest/src %d\n",
	       errCode,instanceId,typeId,destSrc);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrInstanceIdAndDest(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                 CrFwInstanceId_t instanceId, CrFwInstanceId_t secondaryInstanceId, CrFwDestSrc_t dest) {
	printf("CrFwRepErrInstanceIdAndDest: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
	printf("                             secondary sequence identifier: %d, destination: %d\n",secondaryInstanceId,dest);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrSeqCnt(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                      CrFwSeqCnt_t expSeqCnt, CrFwSeqCnt_t actSeqCnt) {
	printf("CrFwRepErrSeqCnt: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
	printf("                  expected sequence counter: %d, actual sequence counter: %d\n",expSeqCnt,actSeqCnt);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrGroup(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                     CrFwGroup_t group) {
	printf("CrFwRepErrGroup: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
	printf("                  invalid group: %d\n",group);

}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrInstanceIdAndOutcome(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, CrFwInstanceId_t secondaryInstanceId, CrFwOutcome_t outcome) {
	printf("CrFwRepErrInstanceIdAndOutcome: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
	printf("                                secondary sequence identifier: %d, outcome: %d\n",secondaryInstanceId,outcome);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrPckt(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, CrFwPckt_t pckt) {
	printf("CrFwRepErrPckt: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
	printf("                pckt[0] : %d, pckt[1]: %d\n",pckt[0],pckt[1]);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrRep(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, FwSmDesc_t rep) {
	printf("CrFwRepErrRep: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrCmd(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, FwSmDesc_t cmd) {
	printf("CrFwRepErrCmd: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrKind(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, CrFwServType_t  servType,
									CrFwServSubType_t servSubType, CrFwDiscriminant_t disc) {
	printf("CrFwRepErrKind: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
}
