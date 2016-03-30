/*
 *************************************************************************
 * Ralink Tech Inc.
 * 5F., No.36, Taiyuan St., Jhubei City,
 * Hsinchu County 302,
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                       *
 *************************************************************************/


#ifndef __SPECTRUM_H__
#define __SPECTRUM_H__

#include "spectrum_def.h"


unsigned char GetRegulatoryMaxTxPwr(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char channel);

char RTMP_GetTxPwr(
	IN PRTMP_ADAPTER pAd,
	IN HTTRANSMIT_SETTING HTTxMode);

/*
	==========================================================================
	Description:
		Prepare Measurement request action frame and enqueue it into
		management queue waiting for transmition.
		
	Parametrs:
		1. the destination mac address of the frame.
	
	Return	: None.
	==========================================================================
 */
void MakeMeasurementReqFrame(
	IN PRTMP_ADAPTER pAd,
	unsigned char* pOutBuffer,
	unsigned long* pFrameLen,
	IN unsigned char TotalLen,
	IN unsigned char Category,
	IN unsigned char Action,
	IN unsigned char MeasureToken, 
	IN unsigned char MeasureReqMode,
	IN unsigned char MeasureReqType,
	IN unsigned short NumOfRepetitions);

/*
	==========================================================================
	Description:
		Prepare Measurement report action frame and enqueue it into
		management queue waiting for transmition.
		
	Parametrs:
		1. the destination mac address of the frame.
	
	Return	: None.
	==========================================================================
 */
void EnqueueMeasurementRep(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pDA,
	IN unsigned char DialogToken,
	IN unsigned char MeasureToken, 
	IN unsigned char MeasureReqMode,
	IN unsigned char MeasureReqType,
	IN unsigned char ReportInfoLen,
	IN unsigned char* pReportInfo);

/*
	==========================================================================
	Description:
		Prepare TPC Request action frame and enqueue it into
		management queue waiting for transmition.
		
	Parametrs:
		1. the destination mac address of the frame.
	
	Return	: None.
	==========================================================================
 */
void EnqueueTPCReq(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pDA,
	IN unsigned char DialogToken);

/*
	==========================================================================
	Description:
		Prepare TPC Report action frame and enqueue it into
		management queue waiting for transmition.
		
	Parametrs:
		1. the destination mac address of the frame.
	
	Return	: None.
	==========================================================================
 */
void EnqueueTPCRep(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pDA,
	IN unsigned char DialogToken,
	IN unsigned char TxPwr,
	IN unsigned char LinkMargin);

#ifdef WDS_SUPPORT
/*
	==========================================================================
	Description:
		Prepare Channel Switch Announcement action frame and enqueue it into
		management queue waiting for transmition.
		
	Parametrs:
		1. the destination mac address of the frame.
		2. Channel switch announcement mode.
		2. a New selected channel.
	
	Return	: None.
	==========================================================================
 */
void EnqueueChSwAnn(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pDA, 
	IN unsigned char ChSwMode,
	IN unsigned char NewCh);
#endif /* WDS_SUPPORT */

/*
	==========================================================================
	Description:
		Spectrun action frames Handler such as channel switch annoucement,
		measurement report, measurement request actions frames.
		
	Parametrs:
		Elme - MLME message containing the received frame
	
	Return	: None.
	==========================================================================
 */
void PeerSpectrumAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

/*
	==========================================================================
	Description:
		
	Parametrs:
	
	Return	: None.
	==========================================================================
 */
int Set_MeasureReq_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	unsigned char*			arg);

int Set_TpcReq_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	unsigned char*			arg);

int Set_PwrConstraint(
	IN	PRTMP_ADAPTER	pAd, 
	IN	unsigned char*			arg);


NDIS_STATUS	MeasureReqTabInit(
	IN PRTMP_ADAPTER pAd);

void MeasureReqTabExit(
	IN PRTMP_ADAPTER pAd);

PMEASURE_REQ_ENTRY MeasureReqLookUp(
	IN PRTMP_ADAPTER	pAd,
	IN unsigned char			DialogToken);

PMEASURE_REQ_ENTRY MeasureReqInsert(
	IN PRTMP_ADAPTER	pAd,
	IN unsigned char			DialogToken);

void MeasureReqDelete(
	IN PRTMP_ADAPTER	pAd,
	IN unsigned char			DialogToken);

void InsertChannelRepIE(
	IN PRTMP_ADAPTER pAd,
	unsigned char* pFrameBuf,
	unsigned long* pFrameLen,
	IN unsigned char* pCountry,
	IN unsigned char RegulatoryClass);

void InsertTpcReportIE(
	IN PRTMP_ADAPTER pAd,
	unsigned char* pFrameBuf,
	unsigned long* pFrameLen,
	IN unsigned char TxPwr,
	IN unsigned char LinkMargin);

void InsertDialogToken(
	IN PRTMP_ADAPTER pAd,
	unsigned char* pFrameBuf,
	unsigned long* pFrameLen,
	IN unsigned char DialogToken);

NDIS_STATUS	TpcReqTabInit(
	IN PRTMP_ADAPTER pAd);

void TpcReqTabExit(
	IN PRTMP_ADAPTER pAd);

void NotifyChSwAnnToPeerAPs(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pRA,
	IN unsigned char* pTA,
	IN unsigned char ChSwMode,
	IN unsigned char Channel);

void RguClass_BuildBcnChList(
	IN PRTMP_ADAPTER pAd,
	unsigned char* pBuf,
	OUT	unsigned long* pBufLen);
#endif /* __SPECTRUM_H__ */

