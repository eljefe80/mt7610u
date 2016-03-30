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


#ifndef __AP_H__
#define __AP_H__




/* ============================================================= */
/*      Common definition */
/* ============================================================= */
#define MBSS_VLAN_INFO_GET(												\
	__pAd, __VLAN_VID, __VLAN_Priority, __FromWhichBSSID) 				\
{																		\
	if ((__FromWhichBSSID < __pAd->ApCfg.BssidNum) &&					\
		(__FromWhichBSSID < HW_BEACON_MAX_NUM) &&						\
		(__pAd->ApCfg.MBSSID[__FromWhichBSSID].VLAN_VID != 0))			\
	{																	\
		__VLAN_VID = __pAd->ApCfg.MBSSID[__FromWhichBSSID].VLAN_VID;	\
		__VLAN_Priority = __pAd->ApCfg.MBSSID[__FromWhichBSSID].VLAN_Priority; \
	}																	\
}

/* ============================================================= */
/*      Function Prototypes */
/* ============================================================= */

/* ap_data.c */

unsigned char APBridgeToWirelessSta(
    PRTMP_ADAPTER   pAd,
    unsigned char*          pHeader,
    unsigned int            HdrLen,
    unsigned char*          pData,
    unsigned int            DataLen,
    unsigned long           fromwdsidx);

void RTMP_BASetup(
PRTMP_ADAPTER pAd,
PMAC_TABLE_ENTRY pMacEntry,
unsigned char UserPriority);

void APSendPackets(
NDIS_HANDLE		MiniportAdapterContext,
PPNDIS_PACKET	ppPacketArray,
unsigned int			NumberOfPackets);

int APSendPacket(
    PRTMP_ADAPTER   pAd,
    PNDIS_PACKET    pPacket);

int APInsertPsQueue(
PRTMP_ADAPTER pAd,
PNDIS_PACKET pPacket,
MAC_TABLE_ENTRY *pMacEntry,
unsigned char QueIdx);

int APHardTransmit(
PRTMP_ADAPTER	pAd,
TX_BLK			*pTxBlk,
unsigned char			QueIdx);

void APRxEAPOLFrameIndicate(
PRTMP_ADAPTER	pAd,
MAC_TABLE_ENTRY	*pEntry,
RX_BLK			*pRxBlk,
unsigned char			FromWhichBSSID);

int APCheckRxError(
RTMP_ADAPTER *pAd,
RXINFO_STRUC *pRxInfo,
unsigned char Wcid);

unsigned char APCheckClass2Class3Error(
    PRTMP_ADAPTER   pAd,
unsigned long Wcid, 
 PHEADER_802_11  pHeader);

void APHandleRxPsPoll(
PRTMP_ADAPTER	pAd,
unsigned char*			pAddr,
unsigned short			Aid,
   unsigned char			isActive);

void    RTMPDescriptorEndianChange(
    unsigned char*          pData,
    unsigned long           DescriptorType);
    
void    RTMPFrameEndianChange(
    PRTMP_ADAPTER   pAd,
    unsigned char*          pData,
    unsigned long           Dir,
    unsigned char         FromRxDoneint);

/* ap_assoc.c */

void APAssocStateMachineInit(
    PRTMP_ADAPTER   pAd, 
    STATE_MACHINE *S, 
   STATE_MACHINE_FUNC Trans[]);


void MbssKickOutStas(
PRTMP_ADAPTER pAd,
int apidx,
unsigned short Reason);

void APMlmeKickOutSta(
   PRTMP_ADAPTER pAd, 
unsigned char* pStaAddr, 
unsigned char Wcid,
unsigned short Reason);



void APCls3errAction(
    PRTMP_ADAPTER   pAd, 
	unsigned long Wcid,
   PHEADER_802_11	pHeader);

/*
void RTMPAddClientSec(
PRTMP_ADAPTER	pAd,
unsigned char	BssIdx,
unsigned char		 KeyIdx,
unsigned char		 CipherAlg,
unsigned char*		 pKey,
unsigned char*		 pTxMic,
unsigned char*		 pRxMic,
MAC_TABLE_ENTRY *pEntry);
*/

/* ap_auth.c */

void APAuthStateMachineInit(
   PRTMP_ADAPTER pAd, 
   STATE_MACHINE *Sm, 
   STATE_MACHINE_FUNC Trans[]);

void APCls2errAction(
   PRTMP_ADAPTER pAd, 
	unsigned long Wcid,
   PHEADER_802_11	pHeader);

/* ap_connect.c */


void APMakeBssBeacon(
    PRTMP_ADAPTER   pAd,
int				apidx);

void APUpdateBeaconFrame(
    PRTMP_ADAPTER   pAd,
int				apidx);

void APMakeAllBssBeacon(
    PRTMP_ADAPTER   pAd);

void APUpdateAllBeaconFrame(
    PRTMP_ADAPTER   pAd);


/* ap_sync.c */

void APSyncStateMachineInit(
   PRTMP_ADAPTER pAd,
   STATE_MACHINE *Sm,
   STATE_MACHINE_FUNC Trans[]);

void APScanTimeout(
void*SystemSpecific1,
void*FunctionContext,
void*SystemSpecific2,
void*SystemSpecific3);

void APInvalidStateWhenScan(
PRTMP_ADAPTER pAd,
MLME_QUEUE_ELEM *Elem);

void APScanTimeoutAction(
PRTMP_ADAPTER pAd,
MLME_QUEUE_ELEM *Elem);

void APPeerProbeReqAction(
    PRTMP_ADAPTER pAd, 
    MLME_QUEUE_ELEM *Elem);

void APPeerBeaconAction(
   PRTMP_ADAPTER pAd, 
   MLME_QUEUE_ELEM *Elem);

void APMlmeScanReqAction(
PRTMP_ADAPTER pAd,
MLME_QUEUE_ELEM *Elem);

void APPeerBeaconAtScanAction(
PRTMP_ADAPTER pAd,
MLME_QUEUE_ELEM *Elem);

void APScanCnclAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);

void ApSiteSurvey(
PRTMP_ADAPTER  		pAd,
PNDIS_802_11_SSID	pSsid,
unsigned char				ScanType,
unsigned char				ChannelSel);

void SupportRate(
unsigned char* SupRate,
unsigned char SupRateLen,
unsigned char* ExtRate,
unsigned char ExtRateLen,
unsigned char* *Rates,
unsigned char* RatesLen,
unsigned char* pMaxSupportRate);


unsigned char ApScanRunning(
PRTMP_ADAPTER pAd);
	
#ifdef DOT11N_DRAFT3
void APOverlappingBSSScan(
RTMP_ADAPTER *pAd);

int GetBssCoexEffectedChRange(
RTMP_ADAPTER *pAd,
BSS_COEX_CH_RANGE *pCoexChRange);

#endif /* DOT11N_DRAFT3 */

/* ap_wpa.c */
void WpaStateMachineInit(
    PRTMP_ADAPTER   pAd, 
    STATE_MACHINE *Sm, 
   STATE_MACHINE_FUNC Trans[]);

/* ap_mlme.c */
void APMlmePeriodicExec(
    PRTMP_ADAPTER   pAd);

unsigned char APMsgTypeSubst(
   PRTMP_ADAPTER pAd,
   PFRAME_802_11 pFrame, 
   int *Machine, 
   int *MsgType);

void APQuickResponeForRateUpExec(
   void*SystemSpecific1, 
   void*FunctionContext, 
   void*SystemSpecific2, 
   void*SystemSpecific3);

#ifdef RTMP_MAC_USB
void BeaconUpdateExec(
   void*SystemSpecific1, 
   void*FunctionContext, 
   void*SystemSpecific2, 
   void*SystemSpecific3);
#endif /* RTMP_MAC_USB */

void RTMPSetPiggyBack(
PRTMP_ADAPTER	pAd,
unsigned char			bPiggyBack);

void APAsicEvaluateRxAnt(
PRTMP_ADAPTER	pAd);

void APAsicRxAntEvalTimeout(
PRTMP_ADAPTER	pAd);

/* ap.c */
int APInitialize(
    PRTMP_ADAPTER   pAd);

void APShutdown(
   PRTMP_ADAPTER    pAd);

void APStartUp(
    PRTMP_ADAPTER   pAd);

void APStop(
    PRTMP_ADAPTER   pAd);

void APCleanupPsQueue(
    PRTMP_ADAPTER   pAd,
    struct list_head*   pQueue);


void MacTableMaintenance(
   PRTMP_ADAPTER pAd);

unsigned intMacTableAssocStaNumGet(
PRTMP_ADAPTER pAd);

MAC_TABLE_ENTRY *APSsPsInquiry(
    PRTMP_ADAPTER   pAd, 
    unsigned char*          pAddr, 
   SST             *Sst, 
   unsigned short          *Aid,
   unsigned char           *PsMode,
   unsigned char           *Rate); 

unsigned char APPsIndicate(
    PRTMP_ADAPTER   pAd, 
    unsigned char*          pAddr, 
unsigned long Wcid, 
    unsigned char           Psm);

#ifdef SYSTEM_LOG_SUPPORT
void ApLogEvent(
   PRTMP_ADAPTER    pAd,
   unsigned char*           pAddr,
   unsigned short           Event);
#else
#define ApLogEvent(_pAd, _pAddr, _Event)
#endif /* SYSTEM_LOG_SUPPORT */

#ifdef DOT11_N_SUPPORT
void APUpdateOperationMode(
   PRTMP_ADAPTER pAd);
#endif /* DOT11_N_SUPPORT */

void APUpdateCapabilityAndErpIe(
PRTMP_ADAPTER pAd);

unsigned char ApCheckAccessControlList(
PRTMP_ADAPTER pAd,
unsigned char*        pAddr,
unsigned char         Apidx);

void ApUpdateAccessControlList(
   PRTMP_ADAPTER pAd,
   unsigned char         Apidx);

void ApEnqueueNullFrame(
PRTMP_ADAPTER pAd,
unsigned char*        pAddr,
unsigned char         TxRate,
unsigned char         PID,
unsigned char         apidx,
   unsigned char       bQosNull,
   unsigned char       bEOSP,
   unsigned char         OldUP);

/* ap_sanity.c */


unsigned char PeerAssocReqCmmSanity(
   PRTMP_ADAPTER pAd, 
unsigned char isRessoc,
   void*Msg, 
   int MsgLen,
   IE_LISTS *ie_lists);


unsigned char PeerDisassocReqSanity(
   PRTMP_ADAPTER pAd, 
   void*Msg, 
   unsigned long MsgLen, 
   unsigned char* pAddr2, 
   unsigned short	*SeqNum,
   unsigned short *Reason);

unsigned char PeerDeauthReqSanity(
   PRTMP_ADAPTER pAd, 
   void*Msg, 
   unsigned long MsgLen, 
   unsigned char* pAddr2, 
   unsigned short	*SeqNum,    
   unsigned short *Reason);

unsigned char APPeerAuthSanity(
   PRTMP_ADAPTER pAd, 
   void*Msg, 
   unsigned long MsgLen, 
unsigned char* pAddr1, 
   unsigned char* pAddr2, 
   unsigned short *Alg, 
   unsigned short *Seq, 
   unsigned short *Status, 
   char *ChlgText
	);


#ifdef DOT1X_SUPPORT
/* ap_cfg.h */
int	Set_OwnIPAddr_Proc(
PRTMP_ADAPTER	pAd, 
char*			arg);

int	Set_EAPIfName_Proc(
PRTMP_ADAPTER	pAd, 
char*			arg);

int	Set_PreAuthIfName_Proc(
PRTMP_ADAPTER	pAd, 
char*			arg);

/* Define in ap.c */
unsigned char DOT1X_internalCmdAction(
    PRTMP_ADAPTER	pAd,
    MAC_TABLE_ENTRY *pEntry,
   unsigned char			cmd);

unsigned char DOT1X_EapTriggerAction(
    PRTMP_ADAPTER	pAd,
    MAC_TABLE_ENTRY *pEntry);
#endif /* DOT1X_SUPPORT */
#endif  /* __AP_H__ */

void AP_E2PROM_IOCTL_PostCtrl(
RTMP_IOCTL_INPUT_STRUCT	*wrq,
char*					msg);

void IAPP_L2_UpdatePostCtrl(
PRTMP_ADAPTER	pAd,
   unsigned char *mac_p,
   int  bssid);
