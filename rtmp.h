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


#ifndef __RTMP_H__
#define __RTMP_H__

#include "spectrum_def.h"

#include "rtmp_dot11.h"
#include "wpa_cmm.h"

#include "wsc.h"
#include "link_list.h"





#ifdef CLIENT_WDS
#include "client_wds_cmm.h"
#endif /* CLIENT_WDS */




#ifdef WFD_SUPPORT
#include "wfd_cmm.h"
#endif /* WFD_SUPPORT */

#include "drs_extr.h"

struct _RTMP_RA_LEGACY_TB;

typedef struct _RTMP_ADAPTER RTMP_ADAPTER;
typedef struct _RTMP_ADAPTER *PRTMP_ADAPTER;

typedef struct _RTMP_CHIP_OP_ RTMP_CHIP_OP;
typedef struct _RTMP_CHIP_CAP_ RTMP_CHIP_CAP;

typedef struct _UAPSD_INFO {
	unsigned char bAPSDCapable;
} UAPSD_INFO;

#include "mcu.h"


#ifdef CONFIG_ANDES_SUPPORT
#include "mcu_and.h"
#endif

#include "rtmp_chip.h"

#include "radar.h"

#ifdef CARRIER_DETECTION_SUPPORT
#include "cs.h"
#endif /* CARRIER_DETECTION_SUPPORT */

#ifdef DFS_SUPPORT
#include "dfs.h"
#endif /* DFS_SUPPORT */

#ifdef LED_CONTROL_SUPPORT
#include "rt_led.h"
#endif /* LED_CONTROL_SUPPORT */


#ifdef RALINK_ATE
#include "rt_ate.h"
#endif /* RALINK_ATE */


/*#define DBG		1 */

/*#define DBG_DIAGNOSE		1 */
#define ASIC_VERSION	0x0000

/*+++Used for merge MiniportMMRequest() and MiniportDataMMRequest() into one function */
#define MAX_DATAMM_RETRY	3
#define MGMT_USE_QUEUE_FLAG	0x80
/*---Used for merge MiniportMMRequest() and MiniportDataMMRequest() into one function */
/* The number of channels for per-channel Tx power offset */


#define	MAXSEQ		(0xFFF)

#ifdef DOT11N_SS3_SUPPORT
#define MAX_MCS_SET 24		/* From MCS 0 ~ MCS 23 */
#else
#define MAX_MCS_SET 16		/* From MCS 0 ~ MCS 15 */
#endif /* DOT11N_SS3_SUPPORT */


#define MAX_TXPOWER_ARRAY_SIZE	5

extern unsigned char CISCO_OUI[];
extern unsigned char BaSizeArray[4];

extern unsigned char BROADCAST_ADDR[MAC_ADDR_LEN];
extern unsigned char ZERO_MAC_ADDR[MAC_ADDR_LEN];
extern unsigned long BIT32[32];
extern char *CipherName[];
extern unsigned char RxwiMCSToOfdmRate[12];
extern unsigned char SNAP_802_1H[6];
extern unsigned char SNAP_BRIDGE_TUNNEL[6];
extern unsigned char EAPOL[2];
extern unsigned char IPX[2];
extern unsigned char TPID[];
extern unsigned char APPLE_TALK[2];
extern unsigned char OfdmRateToRxwiMCS[];
extern unsigned char MapUserPriorityToAccessCategory[8];

extern unsigned char RateIdToMbps[];
extern unsigned short RateIdTo500Kbps[];

extern unsigned char CipherSuiteWpaNoneTkip[];
extern unsigned char CipherSuiteWpaNoneTkipLen;

extern unsigned char CipherSuiteWpaNoneAes[];
extern unsigned char CipherSuiteWpaNoneAesLen;

extern unsigned char SsidIe;
extern unsigned char SupRateIe;
extern unsigned char ExtRateIe;

#ifdef DOT11_N_SUPPORT
extern unsigned char HtCapIe;
extern unsigned char AddHtInfoIe;
extern unsigned char NewExtChanIe;
extern unsigned char BssCoexistIe;
extern unsigned char ExtHtCapIe;
#ifdef CONFIG_STA_SUPPORT
extern unsigned char PRE_N_HT_OUI[];
#endif /* CONFIG_STA_SUPPORT */
#endif /* DOT11_N_SUPPORT */
extern unsigned char ExtCapIe;

extern unsigned char ErpIe;
extern unsigned char DsIe;
extern unsigned char TimIe;
extern unsigned char WpaIe;
extern unsigned char Wpa2Ie;
extern unsigned char IbssIe;
extern unsigned char WapiIe;

extern unsigned char WPA_OUI[];
extern unsigned char RSN_OUI[];
extern unsigned char WAPI_OUI[];
extern unsigned char WME_INFO_ELEM[];
extern unsigned char WME_PARM_ELEM[];
extern unsigned char RALINK_OUI[];
extern unsigned char PowerConstraintIE[];

typedef union _CAPTURE_MODE_PACKET_BUFFER {
	struct 
	{
		unsigned int       BYTE0:8;     
		unsigned int       BYTE1:8;
		unsigned int       BYTE2:8;
		unsigned int       BYTE3:8;
	} field;
	unsigned int                   Value;
}CAPTURE_MODE_PACKET_BUFFER, *PCAPTURE_MODE_PACKET_BUFFER;

typedef struct _RSSI_SAMPLE {
	char LastRssi0;		/* last received RSSI */
	char LastRssi1;		/* last received RSSI */
	char LastRssi2;		/* last received RSSI */
	char AvgRssi0;
	char AvgRssi1;
	char AvgRssi2;
	short AvgRssi0X8;
	short AvgRssi1X8;
	short AvgRssi2X8;
	char LastSnr0;
	char LastSnr1;
	char LastSnr2;
	char AvgSnr0;
	char AvgSnr1;
	char AvgSnr2;
	short AvgSnr0X8;
	short AvgSnr1X8;
	short AvgSnr2X8;
	char LastNoiseLevel0;
	char LastNoiseLevel1;
	char LastNoiseLevel2;
} RSSI_SAMPLE;

/* */
/*  Queue structure and macros */
/* */
#define InitializeQueueHeader(QueueHeader)              \
{                                                       \
	(QueueHeader)->Head = (QueueHeader)->Tail = NULL;   \
	(QueueHeader)->Number = 0;                          \
}

#define RemoveHeadQueue(QueueHeader)                \
(QueueHeader)->Head;                                \
{                                                   \
	PQUEUE_ENTRY pNext;                             \
	if ((QueueHeader)->Head != NULL)				\
	{												\
		pNext = (QueueHeader)->Head->Next;          \
		(QueueHeader)->Head->Next = NULL;		\
		(QueueHeader)->Head = pNext;                \
		if (pNext == NULL)                          \
			(QueueHeader)->Tail = NULL;             \
		(QueueHeader)->Number--;                    \
	}												\
}

#define InsertHeadQueue(QueueHeader, QueueEntry)            \
{                                                           \
		((PQUEUE_ENTRY)QueueEntry)->Next = (QueueHeader)->Head; \
		(QueueHeader)->Head = (PQUEUE_ENTRY)(QueueEntry);       \
		if ((QueueHeader)->Tail == NULL)                        \
			(QueueHeader)->Tail = (PQUEUE_ENTRY)(QueueEntry);   \
		(QueueHeader)->Number++;                                \
}

#define InsertTailQueue(QueueHeader, QueueEntry)				\
{                                                               \
	((PQUEUE_ENTRY)QueueEntry)->Next = NULL;                    \
	if ((QueueHeader)->Tail)                                    \
		(QueueHeader)->Tail->Next = (PQUEUE_ENTRY)(QueueEntry); \
	else                                                        \
		(QueueHeader)->Head = (PQUEUE_ENTRY)(QueueEntry);       \
	(QueueHeader)->Tail = (PQUEUE_ENTRY)(QueueEntry);           \
	(QueueHeader)->Number++;                                    \
}

#define InsertTailQueueAc(pAd, pEntry, QueueHeader, QueueEntry)			\
{																		\
	((PQUEUE_ENTRY)QueueEntry)->Next = NULL;							\
	if ((QueueHeader)->Tail)											\
		(QueueHeader)->Tail->Next = (PQUEUE_ENTRY)(QueueEntry);			\
	else																\
		(QueueHeader)->Head = (PQUEUE_ENTRY)(QueueEntry);				\
	(QueueHeader)->Tail = (PQUEUE_ENTRY)(QueueEntry);					\
	(QueueHeader)->Number++;											\
}
void DisplayTxAgg (RTMP_ADAPTER *pAd);


/* */
/*  Macros for flag and ref count operations */
/* */
#define RTMP_SET_FLAG(_M, _F)       ((_M)->Flags |= (_F))
#define RTMP_CLEAR_FLAG(_M, _F)     ((_M)->Flags &= ~(_F))
#define RTMP_CLEAR_FLAGS(_M)        ((_M)->Flags = 0)
#define RTMP_TEST_FLAG(_M, _F)      (((_M)->Flags & (_F)) != 0)
#define RTMP_TEST_FLAGS(_M, _F)     (((_M)->Flags & (_F)) == (_F))
/* Macro for power save flag. */
#define RTMP_SET_PSFLAG(_M, _F)       ((_M)->PSFlags |= (_F))
#define RTMP_CLEAR_PSFLAG(_M, _F)     ((_M)->PSFlags &= ~(_F))
#define RTMP_CLEAR_PSFLAGS(_M)        ((_M)->PSFlags = 0)
#define RTMP_TEST_PSFLAG(_M, _F)      (((_M)->PSFlags & (_F)) != 0)
#define RTMP_TEST_PSFLAGS(_M, _F)     (((_M)->PSFlags & (_F)) == (_F))

#define OPSTATUS_SET_FLAG(_pAd, _F)     ((_pAd)->CommonCfg.OpStatusFlags |= (_F))
#define OPSTATUS_CLEAR_FLAG(_pAd, _F)   ((_pAd)->CommonCfg.OpStatusFlags &= ~(_F))
#define OPSTATUS_TEST_FLAG(_pAd, _F)    (((_pAd)->CommonCfg.OpStatusFlags & (_F)) != 0)

#define WIFI_TEST_SET_FLAG(_pAd, _F)     ((_pAd)->CommonCfg.WiFiTestFlags |= (_F))
#define WIFI_TEST_CLEAR_FLAG(_pAd, _F)   ((_pAd)->CommonCfg.WiFiTestFlags &= ~(_F))
#define WIFI_TEST_CHECK_FLAG(_pAd, _F)    (((_pAd)->CommonCfg.WiFiTestFlags & (_F)) != 0)

#define CLIENT_STATUS_SET_FLAG(_pEntry,_F)      ((_pEntry)->ClientStatusFlags |= (_F))
#define CLIENT_STATUS_CLEAR_FLAG(_pEntry,_F)    ((_pEntry)->ClientStatusFlags &= ~(_F))
#define CLIENT_STATUS_TEST_FLAG(_pEntry,_F)     (((_pEntry)->ClientStatusFlags & (_F)) != 0)

#define RX_FILTER_SET_FLAG(_pAd, _F)    ((_pAd)->CommonCfg.PacketFilter |= (_F))
#define RX_FILTER_CLEAR_FLAG(_pAd, _F)  ((_pAd)->CommonCfg.PacketFilter &= ~(_F))
#define RX_FILTER_TEST_FLAG(_pAd, _F)   (((_pAd)->CommonCfg.PacketFilter & (_F)) != 0)

#define RTMP_SET_MORE_FLAG(_M, _F)       ((_M)->MoreFlags |= (_F))
#define RTMP_TEST_MORE_FLAG(_M, _F)      (((_M)->MoreFlags & (_F)) != 0)
#define RTMP_CLEAR_MORE_FLAG(_M, _F)     ((_M)->MoreFlags &= ~(_F))

#define SET_ASIC_CAP(_pAd, _caps)		((_pAd)->chipCap.asic_caps |= (_caps))
#define IS_ASIC_CAP(_pAd, _caps)			(((_pAd)->chipCap.asic_caps & (_caps)) != 0)
#define CLR_ASIC_CAP(_pAd, _caps)		((_pAd)->chipCap.asic_caps &= ~(_caps))


#ifdef CONFIG_STA_SUPPORT
#define STA_NO_SECURITY_ON(_p)          (_p->StaCfg.WepStatus == Ndis802_11EncryptionDisabled)
#define STA_WEP_ON(_p)                  (_p->StaCfg.WepStatus == Ndis802_11Encryption1Enabled)
#define STA_TKIP_ON(_p)                 (_p->StaCfg.WepStatus == Ndis802_11Encryption2Enabled)
#define STA_AES_ON(_p)                  (_p->StaCfg.WepStatus == Ndis802_11Encryption3Enabled)

#define STA_TGN_WIFI_ON(_p)             (_p->StaCfg.bTGnWifiTest == TRUE)
#endif /* CONFIG_STA_SUPPORT */

#define CKIP_KP_ON(_p)				((((_p)->StaCfg.CkipFlag) & 0x10) && ((_p)->StaCfg.bCkipCmicOn == TRUE))
#define CKIP_CMIC_ON(_p)			((((_p)->StaCfg.CkipFlag) & 0x08) && ((_p)->StaCfg.bCkipCmicOn == TRUE))

#define INC_RING_INDEX(_idx, _RingSize)    \
{                                          \
    (_idx) = (_idx+1) % (_RingSize);       \
}

#ifdef USB_BULK_BUF_ALIGMENT
#define CUR_WRITE_IDX_INC(_idx, _RingSize)    \
{                                          \
    (_idx) = (_idx+1) % (_RingSize);       \
}
#endif /* USB_BULK_BUF_ALIGMENT */

#ifdef DOT11_N_SUPPORT
/* StaActive.SupportedHtPhy.MCSSet is copied from AP beacon.  Don't need to update here. */
#define COPY_HTSETTINGS_FROM_MLME_AUX_TO_ACTIVE_CFG(_pAd)                                 \
{                                                                                       \
	_pAd->StaActive.SupportedHtPhy.ChannelWidth = _pAd->MlmeAux.HtCapability.HtCapInfo.ChannelWidth;      \
	_pAd->StaActive.SupportedHtPhy.MimoPs = _pAd->MlmeAux.HtCapability.HtCapInfo.MimoPs;      \
	_pAd->StaActive.SupportedHtPhy.GF = _pAd->MlmeAux.HtCapability.HtCapInfo.GF;      \
	_pAd->StaActive.SupportedHtPhy.ShortGIfor20 = _pAd->MlmeAux.HtCapability.HtCapInfo.ShortGIfor20;      \
	_pAd->StaActive.SupportedHtPhy.ShortGIfor40 = _pAd->MlmeAux.HtCapability.HtCapInfo.ShortGIfor40;      \
	_pAd->StaActive.SupportedHtPhy.TxSTBC = _pAd->MlmeAux.HtCapability.HtCapInfo.TxSTBC;      \
	_pAd->StaActive.SupportedHtPhy.RxSTBC = _pAd->MlmeAux.HtCapability.HtCapInfo.RxSTBC;      \
	_pAd->StaActive.SupportedHtPhy.ExtChanOffset = _pAd->MlmeAux.AddHtInfo.AddHtInfo.ExtChanOffset;      \
	_pAd->StaActive.SupportedHtPhy.RecomWidth = _pAd->MlmeAux.AddHtInfo.AddHtInfo.RecomWidth;      \
	_pAd->StaActive.SupportedHtPhy.OperaionMode = _pAd->MlmeAux.AddHtInfo.AddHtInfo2.OperaionMode;      \
	_pAd->StaActive.SupportedHtPhy.NonGfPresent = _pAd->MlmeAux.AddHtInfo.AddHtInfo2.NonGfPresent;      \
	NdisMoveMemory((_pAd)->MacTab.Content[BSSID_WCID].HTCapability.MCSSet, (_pAd)->StaActive.SupportedPhyInfo.MCSSet, sizeof(unsigned char) * 16);\
}

#define COPY_AP_HTSETTINGS_FROM_BEACON(_pAd, _pHtCapability)                                 \
{                                                                                       \
	_pAd->MacTab.Content[BSSID_WCID].AMsduSize = (unsigned char)(_pHtCapability->HtCapInfo.AMsduSize);	\
	_pAd->MacTab.Content[BSSID_WCID].MmpsMode= (unsigned char)(_pHtCapability->HtCapInfo.MimoPs);	\
	_pAd->MacTab.Content[BSSID_WCID].MaxRAmpduFactor = (unsigned char)(_pHtCapability->HtCapParm.MaxRAmpduFactor);	\
}
#endif /* DOT11_N_SUPPORT */

#ifdef DOT11_VHT_AC
#define COPY_VHT_FROM_MLME_AUX_TO_ACTIVE_CFG(_pAd)                                 \
{                                                                                       \
}
#endif /* DOT11_VHT_AC */


/*
	Common fragment list structure -  Identical to the scatter gather frag list structure
*/
#define NIC_MAX_PHYS_BUF_COUNT              8

typedef struct _RTMP_SCATTER_GATHER_ELEMENT {
	void *Address;
	unsigned long Length;
	unsigned long* Reserved;
} RTMP_SCATTER_GATHER_ELEMENT, *PRTMP_SCATTER_GATHER_ELEMENT;

typedef struct _RTMP_SCATTER_GATHER_LIST {
	unsigned long NumberOfElements;
	unsigned long* Reserved;
	RTMP_SCATTER_GATHER_ELEMENT Elements[NIC_MAX_PHYS_BUF_COUNT];
} RTMP_SCATTER_GATHER_LIST, *PRTMP_SCATTER_GATHER_LIST;


/*
	Some utility macros
*/
#ifndef min
#define min(_a, _b)     (((_a) < (_b)) ? (_a) : (_b))
#endif

#ifndef max
#define max(_a, _b)     (((_a) > (_b)) ? (_a) : (_b))
#endif

#define GET_LNA_GAIN(_pAd)	((_pAd->LatchRfRegs.Channel <= 14) ? (_pAd->BLNAGain) : ((_pAd->LatchRfRegs.Channel <= 64) ? (_pAd->ALNAGain0) : ((_pAd->LatchRfRegs.Channel <= 128) ? (_pAd->ALNAGain1) : (_pAd->ALNAGain2))))

#define INC_COUNTER64(Val)          (Val.QuadPart++)

#define INFRA_ON(_p)                (OPSTATUS_TEST_FLAG(_p, fOP_STATUS_INFRA_ON))
#define ADHOC_ON(_p)                (OPSTATUS_TEST_FLAG(_p, fOP_STATUS_ADHOC_ON))
#define MONITOR_ON(_p)              (((_p)->StaCfg.BssType) == BSS_MONITOR)
#define IDLE_ON(_p)                 (!INFRA_ON(_p) && !ADHOC_ON(_p))

/* Check LEAP & CCKM flags */
#define LEAP_ON(_p)                 (((_p)->StaCfg.LeapAuthMode) == CISCO_AuthModeLEAP)
#define LEAP_CCKM_ON(_p)            ((((_p)->StaCfg.LeapAuthMode) == CISCO_AuthModeLEAP) && ((_p)->StaCfg.LeapAuthInfo.CCKM == TRUE))

/* if orginal Ethernet frame contains no LLC/SNAP, then an extra LLC/SNAP encap is required */
#define EXTRA_LLCSNAP_ENCAP_FROM_PKT_START(_pBufVA, _pExtraLlcSnapEncap)		\
{																\
	if (((*(_pBufVA + 12) << 8) + *(_pBufVA + 13)) > 1500)		\
	{															\
		_pExtraLlcSnapEncap = SNAP_802_1H;						\
		if (NdisEqualMemory(IPX, _pBufVA + 12, 2) || 			\
			NdisEqualMemory(APPLE_TALK, _pBufVA + 12, 2))		\
		{														\
			_pExtraLlcSnapEncap = SNAP_BRIDGE_TUNNEL;			\
		}														\
	}															\
	else														\
	{															\
		_pExtraLlcSnapEncap = NULL;								\
	}															\
}

/* New Define for new Tx Path. */
#define EXTRA_LLCSNAP_ENCAP_FROM_PKT_OFFSET(_pBufVA, _pExtraLlcSnapEncap)	\
{																\
	if (((*(_pBufVA) << 8) + *(_pBufVA + 1)) > 1500)			\
	{															\
		_pExtraLlcSnapEncap = SNAP_802_1H;						\
		if (NdisEqualMemory(IPX, _pBufVA, 2) || 				\
			NdisEqualMemory(APPLE_TALK, _pBufVA, 2))			\
		{														\
			_pExtraLlcSnapEncap = SNAP_BRIDGE_TUNNEL;			\
		}														\
	}															\
	else														\
	{															\
		_pExtraLlcSnapEncap = NULL;								\
	}															\
}

#define MAKE_802_3_HEADER(_p, _pMac1, _pMac2, _pType)                   \
{                                                                       \
    NdisMoveMemory(_p, _pMac1, MAC_ADDR_LEN);                           \
    NdisMoveMemory((_p + MAC_ADDR_LEN), _pMac2, MAC_ADDR_LEN);          \
    NdisMoveMemory((_p + MAC_ADDR_LEN * 2), _pType, LENGTH_802_3_TYPE); \
}

/*
	if pData has no LLC/SNAP (neither RFC1042 nor Bridge tunnel),
		keep it that way.
	else if the received frame is LLC/SNAP-encaped IPX or APPLETALK,
		preserve the LLC/SNAP field
	else remove the LLC/SNAP field from the result Ethernet frame

	Patch for WHQL only, which did not turn on Netbios but use IPX within its payload
	Note:
		_pData & _DataSize may be altered (remove 8-byte LLC/SNAP) by this MACRO
		_pRemovedLLCSNAP: pointer to removed LLC/SNAP; NULL is not removed
*/
#define CONVERT_TO_802_3(_p8023hdr, _pDA, _pSA, _pData, _DataSize, _pRemovedLLCSNAP)      \
{                                                                       \
    char LLC_Len[2];                                                    \
                                                                        \
    _pRemovedLLCSNAP = NULL;                                            \
    if (NdisEqualMemory(SNAP_802_1H, _pData, 6)  ||                     \
        NdisEqualMemory(SNAP_BRIDGE_TUNNEL, _pData, 6))                 \
    {                                                                   \
        unsigned char* pProto = _pData + 6;                                     \
                                                                        \
        if ((NdisEqualMemory(IPX, pProto, 2) || NdisEqualMemory(APPLE_TALK, pProto, 2)) &&  \
            NdisEqualMemory(SNAP_802_1H, _pData, 6))                    \
        {                                                               \
            LLC_Len[0] = (unsigned char)(_DataSize >> 8);                       \
            LLC_Len[1] = (unsigned char)(_DataSize & (256 - 1));                \
            MAKE_802_3_HEADER(_p8023hdr, _pDA, _pSA, LLC_Len);          \
        }                                                               \
        else                                                            \
        {                                                               \
            MAKE_802_3_HEADER(_p8023hdr, _pDA, _pSA, pProto);           \
            _pRemovedLLCSNAP = _pData;                                  \
            _DataSize -= LENGTH_802_1_H;                                \
            _pData += LENGTH_802_1_H;                                   \
        }                                                               \
    }                                                                   \
    else                                                                \
    {                                                                   \
        LLC_Len[0] = (unsigned char)(_DataSize >> 8);                           \
        LLC_Len[1] = (unsigned char)(_DataSize & (256 - 1));                    \
        MAKE_802_3_HEADER(_p8023hdr, _pDA, _pSA, LLC_Len);              \
    }                                                                   \
}

/*
	Enqueue this frame to MLME engine
	We need to enqueue the whole frame because MLME need to pass data type
	information from 802.11 header
*/
#ifdef RTMP_MAC_USB
#define REPORT_MGMT_FRAME_TO_MLME(_pAd, Wcid, _pFrame, _FrameSize, _Rssi0, _Rssi1, _Rssi2, _MinSNR, _OpMode)        \
{                                                                                       \
    unsigned int High32TSF=0, Low32TSF=0;                                                          \
    MlmeEnqueueForRecv(_pAd, Wcid, High32TSF, Low32TSF, (unsigned char)_Rssi0, (unsigned char)_Rssi1,(unsigned char)_Rssi2,_FrameSize, _pFrame, (unsigned char)_MinSNR, _OpMode);   \
}
#endif /* RTMP_MAC_USB */

#define MAC_ADDR_EQUAL(pAddr1,pAddr2)           RTMPEqualMemory((void *)(pAddr1), (void *)(pAddr2), MAC_ADDR_LEN)
#define SSID_EQUAL(ssid1, len1, ssid2, len2)    ((len1==len2) && (RTMPEqualMemory(ssid1, ssid2, len1)))


#ifdef CONFIG_STA_SUPPORT
#define STA_EXTRA_SETTING(_pAd)

#define STA_PORT_SECURED(_pAd) \
{ \
	unsigned char	Cancelled; \
	(_pAd)->StaCfg.PortSecured = WPA_802_1X_PORT_SECURED; \
	RTMP_IndicateMediaState(_pAd, NdisMediaStateConnected); \
	NdisAcquireSpinLock(&((_pAd)->MacTabLock)); \
	(_pAd)->MacTab.Content[BSSID_WCID].PortSecured = (_pAd)->StaCfg.PortSecured; \
	(_pAd)->MacTab.Content[BSSID_WCID].PrivacyFilter = Ndis802_11PrivFilterAcceptAll;\
	NdisReleaseSpinLock(&(_pAd)->MacTabLock); \
	RTMPCancelTimer(&((_pAd)->Mlme.LinkDownTimer), &Cancelled);\
	STA_EXTRA_SETTING(_pAd); \
}
#endif /* CONFIG_STA_SUPPORT */

/* */
/*  Data buffer for DMA operation, the buffer must be contiguous physical memory */
/*  Both DMA to / from CPU use the same structure. */
/* */
typedef struct _RTMP_DMABUF {
	unsigned long AllocSize;
	void *AllocVa;		/* TxBuf virtual address */
	NDIS_PHYSICAL_ADDRESS AllocPa;	/* TxBuf physical address */
} RTMP_DMABUF, *PRTMP_DMABUF;

/* */
/* Control block (Descriptor) for all ring descriptor DMA operation, buffer must be */
/* contiguous physical memory. NDIS_PACKET stored the binding Rx packet descriptor */
/* which won't be released, driver has to wait until upper layer return the packet */
/* before giveing up this rx ring descriptor to ASIC. NDIS_BUFFER is assocaited pair */
/* to describe the packet buffer. For Tx, NDIS_PACKET stored the tx packet descriptor */
/* which driver should ACK upper layer when the tx is physically done or failed. */
/* */
typedef struct _RTMP_DMACB {
	unsigned long AllocSize;	/* Control block size */
	void *AllocVa;		/* Control block virtual address */
	NDIS_PHYSICAL_ADDRESS AllocPa;	/* Control block physical address */
	PNDIS_PACKET pNdisPacket;
	PNDIS_PACKET pNextNdisPacket;

	RTMP_DMABUF DmaBuf;	/* Associated DMA buffer structure */
#ifdef CACHE_LINE_32B
	RXD_STRUC LastBDInfo;
#endif /* CACHE_LINE_32B */
} RTMP_DMACB, *PRTMP_DMACB;

typedef struct _RTMP_TX_RING {
	RTMP_DMACB Cell[TX_RING_SIZE];
	unsigned int TxCpuIdx;
	unsigned int TxDmaIdx;
	unsigned int TxSwFreeIdx;	/* software next free tx index */
} RTMP_TX_RING, *PRTMP_TX_RING;

typedef struct _RTMP_RX_RING {
	RTMP_DMACB Cell[RX_RING_SIZE];
	unsigned int RxCpuIdx;
	unsigned int RxDmaIdx;
	int RxSwReadIdx;	/* software next read index */
} RTMP_RX_RING, *PRTMP_RX_RING;

typedef struct _RTMP_MGMT_RING {
	RTMP_DMACB Cell[MGMT_RING_SIZE];
	unsigned int TxCpuIdx;
	unsigned int TxDmaIdx;
	unsigned int TxSwFreeIdx;	/* software next free tx index */
} RTMP_MGMT_RING, *PRTMP_MGMT_RING;

typedef struct _RTMP_CTRL_RING {
	RTMP_DMACB Cell[16];
	unsigned int TxCpuIdx;
	unsigned int TxDmaIdx;
	unsigned int TxSwFreeIdx;	/* software next free tx index */
} RTMP_CTRL_RING, *PRTMP_CTRL_RING;

/* */
/*  Statistic counter structure */
/* */
typedef struct _COUNTER_802_3 {
	/* General Stats */
	unsigned long GoodTransmits;
	unsigned long GoodReceives;
	unsigned long TxErrors;
	unsigned long RxErrors;
	unsigned long RxNoBuffer;

	/* Ethernet Stats */
	unsigned long RcvAlignmentErrors;
	unsigned long OneCollision;
	unsigned long MoreCollisions;

} COUNTER_802_3, *PCOUNTER_802_3;

typedef struct _COUNTER_802_11 {
	unsigned long Length;
/*	unsigned long long   LastTransmittedFragmentCount; */
	unsigned long long TransmittedFragmentCount;
	unsigned long long MulticastTransmittedFrameCount;
	unsigned long long FailedCount;
	unsigned long long RetryCount;
	unsigned long long MultipleRetryCount;
	unsigned long long RTSSuccessCount;
	unsigned long long RTSFailureCount;
	unsigned long long ACKFailureCount;
	unsigned long long FrameDuplicateCount;
	unsigned long long ReceivedFragmentCount;
	unsigned long long MulticastReceivedFrameCount;
	unsigned long long FCSErrorCount;
	unsigned long long TransmittedFrameCount;
	unsigned long long WEPUndecryptableCount;
	unsigned long long TransmitCountFrmOs;
} COUNTER_802_11, *PCOUNTER_802_11;


#ifdef RT3290
typedef struct _ANT_DIVERSITY
{
	unsigned char		RateUp;
	unsigned long		TrainCounter;
	unsigned long		AntennaDiversityState;	// 0->Stable state 1->training state
	unsigned long		AntennaDiversityPER[2];  // 0 ->main 1->aux
	unsigned long		AntennaDiversityTxPacketCount[2];  // 0 ->main 1->aux	
	unsigned long		AntennaDiversityRxPacketCount[2];
	char		Rssi[2];
	unsigned long		AntennaDiversityCount;
	unsigned long		AntennaDiversityTrigger;	
}ANT_DIVERSITY, *PANT_DIVERSITY;
#endif /* RT3290 */

typedef struct _COUNTER_RALINK {
	unsigned int OneSecStart;	/* for one sec count clear use */
	unsigned int OneSecBeaconSentCnt;
	unsigned int OneSecFalseCCACnt;	/* CCA error count, for debug purpose, might move to global counter */
	unsigned int OneSecRxFcsErrCnt;	/* CRC error */
	unsigned int OneSecRxOkCnt;	/* RX without error */
	unsigned int OneSecTxFailCount;
	unsigned int OneSecTxNoRetryOkCount;
	unsigned int OneSecTxRetryOkCount;
	unsigned int OneSecRxOkDataCnt;	/* unicast-to-me DATA frame count */
	unsigned int OneSecTransmittedByteCount;	/* both successful and failure, used to calculate TX throughput */

	unsigned long OneSecOsTxCount[NUM_OF_TX_RING];
	unsigned long OneSecDmaDoneCount[NUM_OF_TX_RING];
	unsigned int OneSecTxDoneCount;
	unsigned long OneSecRxCount;
	unsigned int OneSecReceivedByteCount;
	unsigned int OneSecTxAggregationCount;
	unsigned int OneSecRxAggregationCount;
	unsigned int OneSecEnd;	/* for one sec count clear use */

	unsigned long TransmittedByteCount;	/* both successful and failure, used to calculate TX throughput */
	unsigned long ReceivedByteCount;	/* both CRC okay and CRC error, used to calculate RX throughput */
#ifdef RT3290
	// TODO: shiang, check the purpose of following parameter
	unsigned long OneSecRxOkCnt2; /* RX without error */
#endif /* RT3290 */
	unsigned long BadCQIAutoRecoveryCount;
	unsigned long PoorCQIRoamingCount;
	unsigned long MgmtRingFullCount;
	unsigned long RxCountSinceLastNULL;
	unsigned long RxCount;
	unsigned long KickTxCount;
	unsigned long long RealFcsErrCount;
	unsigned long PendingNdisPacketCount;
	unsigned long FalseCCACnt;                    /* CCA error count */

	unsigned int LastOneSecTotalTxCount;	/* OneSecTxNoRetryOkCount + OneSecTxRetryOkCount + OneSecTxFailCount */
	unsigned int LastOneSecRxOkDataCnt;	/* OneSecRxOkDataCnt */
	unsigned long DuplicateRcv;
	unsigned long TxAggCount;
	unsigned long TxNonAggCount;
	unsigned long TxAgg1MPDUCount;
	unsigned long TxAgg2MPDUCount;
	unsigned long TxAgg3MPDUCount;
	unsigned long TxAgg4MPDUCount;
	unsigned long TxAgg5MPDUCount;
	unsigned long TxAgg6MPDUCount;
	unsigned long TxAgg7MPDUCount;
	unsigned long TxAgg8MPDUCount;
	unsigned long TxAgg9MPDUCount;
	unsigned long TxAgg10MPDUCount;
	unsigned long TxAgg11MPDUCount;
	unsigned long TxAgg12MPDUCount;
	unsigned long TxAgg13MPDUCount;
	unsigned long TxAgg14MPDUCount;
	unsigned long TxAgg15MPDUCount;
	unsigned long TxAgg16MPDUCount;

	unsigned long long TransmittedOctetsInAMSDU;
	unsigned long long TransmittedAMSDUCount;
	unsigned long long ReceivedOctesInAMSDUCount;
	unsigned long long ReceivedAMSDUCount;
	unsigned long long TransmittedAMPDUCount;
	unsigned long long TransmittedMPDUsInAMPDUCount;
	unsigned long long TransmittedOctetsInAMPDUCount;
	unsigned long long MPDUInReceivedAMPDUCount;

	unsigned long PhyErrCnt;
	unsigned long PlcpErrCnt;
} COUNTER_RALINK, *PCOUNTER_RALINK;

typedef struct _COUNTER_DRS {
	/* to record the each TX rate's quality. 0 is best, the bigger the worse. */
	unsigned short TxQuality[MAX_TX_RATE_INDEX+1];
	unsigned char PER[MAX_TX_RATE_INDEX+1];
	unsigned char TxRateUpPenalty;	/* extra # of second penalty due to last unstable condition */
	unsigned long CurrTxRateStableTime;	/* # of second in current TX rate */
	/*unsigned char         fNoisyEnvironment; */
	unsigned char fLastSecAccordingRSSI;
	unsigned char LastSecTxRateChangeAction;	/* 0: no change, 1:rate UP, 2:rate down */
	unsigned char LastTimeTxRateChangeAction;	/*Keep last time value of LastSecTxRateChangeAction */
	unsigned long LastTxOkCount;
} COUNTER_DRS, *PCOUNTER_DRS;


#ifdef DOT11_N_SUPPORT
#ifdef TXBF_SUPPORT
typedef
    struct {
	unsigned long TxSuccessCount;
	unsigned long TxRetryCount;
	unsigned long TxFailCount;
	unsigned long ETxSuccessCount;
	unsigned long ETxRetryCount;
	unsigned long ETxFailCount;
	unsigned long ITxSuccessCount;
	unsigned long ITxRetryCount;
	unsigned long ITxFailCount;
} COUNTER_TXBF;
#endif /* TXBF_SUPPORT */
#endif /* DOT11_N_SUPPORT */


#ifdef STREAM_MODE_SUPPORT
typedef struct _STREAM_MODE_ENTRY_{
#define STREAM_MODE_STATIC		1
	unsigned short flag;
	unsigned char macAddr[MAC_ADDR_LEN];
}STREAM_MODE_ENTRY;
#endif /* STREAM_MODE_SUPPORT */

/***************************************************************************
  *	security key related data structure
  **************************************************************************/

/* structure to define WPA Group Key Rekey interval */
typedef struct __attribute__ ((packed)) _RT_802_11_WPA_REKEY {
	unsigned long ReKeyMethod;	/* mechanism for rekeying: 0:disable, 1: time-based, 2: packet-based */
	unsigned long ReKeyinterval;	/* time-based: seconds, packet-based: kilo-packets */
} RT_WPA_REKEY,*PRT_WPA_REKEY, RT_802_11_WPA_REKEY, *PRT_802_11_WPA_REKEY;


#ifdef RTMP_MAC_USB
/***************************************************************************
  *	RTUSB I/O related data structure
  **************************************************************************/

/* for USB interface, avoid in interrupt when write key */
typedef struct RT_ADD_PAIRWISE_KEY_ENTRY {
	unsigned char MacAddr[6];
	unsigned short MacTabMatchWCID;	/* ASIC */
	CIPHER_KEY CipherKey;
} RT_ADD_PAIRWISE_KEY_ENTRY,*PRT_ADD_PAIRWISE_KEY_ENTRY;


/* Cipher suite type for mixed mode group cipher, P802.11i-2004 */
typedef enum _RT_802_11_CIPHER_SUITE_TYPE {
	Cipher_Type_NONE,
	Cipher_Type_WEP40,
	Cipher_Type_TKIP,
	Cipher_Type_RSVD,
	Cipher_Type_CCMP,
	Cipher_Type_WEP104
} RT_802_11_CIPHER_SUITE_TYPE, *PRT_802_11_CIPHER_SUITE_TYPE;
#endif /* RTMP_MAC_USB */

typedef struct {
	unsigned char Addr[MAC_ADDR_LEN];
	unsigned char ErrorCode[2];	/*00 01-Invalid authentication type */
	/*00 02-Authentication timeout */
	/*00 03-Challenge from AP failed */
	/*00 04-Challenge to AP failed */
	unsigned char Reported;
} ROGUEAP_ENTRY, *PROGUEAP_ENTRY;

typedef struct {
	unsigned char RogueApNr;
	ROGUEAP_ENTRY RogueApEntry[MAX_LEN_OF_BSS_TABLE];
} ROGUEAP_TABLE, *PROGUEAP_TABLE;

/*
  *	Fragment Frame structure
  */
typedef struct _FRAGMENT_FRAME {
	PNDIS_PACKET pFragPacket;
	unsigned long RxSize;
	unsigned short Sequence;
	unsigned short LastFrag;
	unsigned long Flags;		/* Some extra frame information. bit 0: LLC presented */
} FRAGMENT_FRAME, *PFRAGMENT_FRAME;


/* */
/* Tkip Key structure which RC4 key & MIC calculation */
/* */
typedef struct _TKIP_KEY_INFO {
	unsigned int nBytesInM;		/* # bytes in M for MICKEY */
	unsigned long IV16;
	unsigned long IV32;
	unsigned long K0;		/* for MICKEY Low */
	unsigned long K1;		/* for MICKEY Hig */
	unsigned long L;		/* Current state for MICKEY */
	unsigned long R;		/* Current state for MICKEY */
	unsigned long M;		/* Message accumulator for MICKEY */
	unsigned char RC4KEY[16];
	unsigned char MIC[8];
} TKIP_KEY_INFO, *PTKIP_KEY_INFO;


/* */
/* Private / Misc data, counters for driver internal use */
/* */
typedef struct __PRIVATE_STRUC {
	unsigned int SystemResetCnt;	/* System reset counter */
	unsigned int TxRingFullCnt;	/* Tx ring full occurrance number */
	unsigned int PhyRxErrCnt;	/* PHY Rx error count, for debug purpose, might move to global counter */
	/* Variables for WEP encryption / decryption in rtmp_wep.c */
	/* Tkip stuff */
	TKIP_KEY_INFO Tx;
	TKIP_KEY_INFO Rx;
} PRIVATE_STRUC, *PPRIVATE_STRUC;


/***************************************************************************
  *	Channel and BBP related data structures
  **************************************************************************/
/* structure to tune BBP R66 (BBP TUNING) */
typedef struct _BBP_R66_TUNING {
	unsigned char bEnable;
	unsigned short FalseCcaLowerThreshold;	/* default 100 */
	unsigned short FalseCcaUpperThreshold;	/* default 512 */
	unsigned char R66Delta;
	unsigned char R66CurrentValue;
	unsigned char R66LowerUpperSelect;	/*Before LinkUp, Used LowerBound or UpperBound as R66 value. */
} BBP_R66_TUNING, *PBBP_R66_TUNING;


#ifdef DOT11_N_SUPPORT
#ifdef DOT11N_DRAFT3
#define EFFECTED_CH_SECONDARY 0x1
#define EFFECTED_CH_PRIMARY	0x2
#define EFFECTED_CH_LEGACY		0x4
#endif /* DOT11N_DRAFT3 */
#endif /* DOT11_N_SUPPORT */

/* structure to store channel TX power */
typedef struct _CHANNEL_TX_POWER {
	unsigned short RemainingTimeForUse;	/*unit: sec */
	unsigned char Channel;
#ifdef DOT11N_DRAFT3
	unsigned char bEffectedChannel;	/* For BW 40 operating in 2.4GHz , the "effected channel" is the channel that is covered in 40Mhz. */
#endif /* DOT11N_DRAFT3 */
	char Power;
	char Power2;
#ifdef DOT11N_SS3_SUPPORT
	char Power3;
#endif /* DOT11N_SS3_SUPPORT */
	unsigned char MaxTxPwr;
	unsigned char DfsReq;
	unsigned char RegulatoryDomain;

/*
	Channel property:
 
	CHANNEL_DISABLED: The channel is disabled.
	CHANNEL_PASSIVE_SCAN: Only passive scanning is allowed.
	CHANNEL_NO_IBSS: IBSS is not allowed.
	CHANNEL_RADAR: Radar detection is required.
	CHANNEL_NO_FAT_ABOVE: Extension channel above this channel is not allowed.
	CHANNEL_NO_FAT_BELOW: Extension channel below this channel is not allowed.
	CHANNEL_40M_CAP: 40 BW channel group
 */
#define CHANNEL_DEFAULT_PROP	0x00
#define CHANNEL_DISABLED		0x01	/* no use */
#define CHANNEL_PASSIVE_SCAN	0x02
#define CHANNEL_NO_IBSS			0x04
#define CHANNEL_RADAR			0x08
#define CHANNEL_NO_FAT_ABOVE	0x10
#define CHANNEL_NO_FAT_BELOW	0x20
#define CHANNEL_40M_CAP			0x40

	unsigned char Flags;

} CHANNEL_TX_POWER, *PCHANNEL_TX_POWER;

/* Channel list subset */
typedef struct _CHANNEL_LIST_SUB {
	unsigned char	Channel;
	unsigned char	IdxMap; /* Index mapping to original channel list */
} CHANNEL_LIST_SUB, *PCHANNEL_LIST_SUB;


typedef struct _SOFT_RX_ANT_DIVERSITY_STRUCT {
	unsigned char EvaluatePeriod;	/* 0:not evalute status, 1: evaluate status, 2: switching status */
	unsigned char EvaluateStableCnt;
	unsigned char Pair1PrimaryRxAnt;	/* 0:Ant-E1, 1:Ant-E2 */
	unsigned char Pair1SecondaryRxAnt;	/* 0:Ant-E1, 1:Ant-E2 */
#ifdef CONFIG_STA_SUPPORT
	short Pair1AvgRssi[2];	/* AvgRssi[0]:E1, AvgRssi[1]:E2 */
	short Pair2AvgRssi[2];	/* AvgRssi[0]:E3, AvgRssi[1]:E4 */
#endif /* CONFIG_STA_SUPPORT */
	short Pair1LastAvgRssi;	/* */
	short Pair2LastAvgRssi;	/* */
	unsigned long RcvPktNumWhenEvaluate;
	unsigned char FirstPktArrivedWhenEvaluate;
} SOFT_RX_ANT_DIVERSITY, *PSOFT_RX_ANT_DIVERSITY;

typedef enum _ABGBAND_STATE_ {
	UNKNOWN_BAND,
	BG_BAND,
	A_BAND,
} ABGBAND_STATE;

#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */
/***************************************************************************
  *	structure for MLME state machine
  **************************************************************************/
typedef struct _MLME_STRUCT {
#ifdef CONFIG_STA_SUPPORT
	/* STA state machines */
	STATE_MACHINE CntlMachine;
	STATE_MACHINE AssocMachine;
	STATE_MACHINE AuthMachine;
	STATE_MACHINE AuthRspMachine;
	STATE_MACHINE SyncMachine;
	STATE_MACHINE WpaPskMachine;
	STATE_MACHINE LeapMachine;
	STATE_MACHINE_FUNC AssocFunc[ASSOC_FUNC_SIZE];
	STATE_MACHINE_FUNC AuthFunc[AUTH_FUNC_SIZE];
	STATE_MACHINE_FUNC AuthRspFunc[AUTH_RSP_FUNC_SIZE];
	STATE_MACHINE_FUNC SyncFunc[SYNC_FUNC_SIZE];

#endif /* CONFIG_STA_SUPPORT */
	STATE_MACHINE_FUNC ActFunc[ACT_FUNC_SIZE];
	/* Action */
	STATE_MACHINE ActMachine;


#ifdef QOS_DLS_SUPPORT
	STATE_MACHINE DlsMachine;
	STATE_MACHINE_FUNC DlsFunc[DLS_FUNC_SIZE];
#endif /* QOS_DLS_SUPPORT */



	/* common WPA state machine */
	STATE_MACHINE WpaMachine;
	STATE_MACHINE_FUNC WpaFunc[WPA_FUNC_SIZE];


	unsigned long ChannelQuality;	/* 0..100, Channel Quality Indication for Roaming */
	unsigned long Now32;		/* latch the value of NdisGetSystemUpTime() */
	unsigned long LastSendNULLpsmTime;

	unsigned char bRunning;
	NDIS_SPIN_LOCK TaskLock;
	MLME_QUEUE Queue;

	unsigned int ShiftReg;

	RALINK_TIMER_STRUCT PeriodicTimer;
	RALINK_TIMER_STRUCT APSDPeriodicTimer;
	RALINK_TIMER_STRUCT LinkDownTimer;
	RALINK_TIMER_STRUCT LinkUpTimer;
	unsigned long PeriodicRound;
	unsigned long GPIORound;
	unsigned long OneSecPeriodicRound;

	unsigned char RealRxPath;
	unsigned char bLowThroughput;
	unsigned char bEnableAutoAntennaCheck;
	RALINK_TIMER_STRUCT RxAntEvalTimer;


#ifdef RTMP_MAC_USB
	RALINK_TIMER_STRUCT AutoWakeupTimer;
	unsigned char AutoWakeupTimerRunning;
#endif /* RTMP_MAC_USB */
} MLME_STRUCT, *PMLME_STRUCT;

#ifdef DOT11_N_SUPPORT
/***************************************************************************
  *	802.11 N related data structures
  **************************************************************************/
struct reordering_mpdu {
	struct reordering_mpdu *next;
	PNDIS_PACKET pPacket;	/* coverted to 802.3 frame */
	int Sequence;		/* sequence number of MPDU */
	unsigned char bAMSDU;
	unsigned char					OpMode;
};

struct reordering_list {
	struct reordering_mpdu *next;
	int qlen;
};

struct reordering_mpdu_pool {
	void *mem;
	NDIS_SPIN_LOCK lock;
	struct reordering_list freelist;
};

typedef enum _REC_BLOCKACK_STATUS {
	Recipient_NONE = 0,
	Recipient_USED,
	Recipient_HandleRes,
	Recipient_Accept
} REC_BLOCKACK_STATUS, *PREC_BLOCKACK_STATUS;

typedef enum _ORI_BLOCKACK_STATUS {
	Originator_NONE = 0,
	Originator_USED,
	Originator_WaitRes,
	Originator_Done
} ORI_BLOCKACK_STATUS, *PORI_BLOCKACK_STATUS;

typedef struct _BA_ORI_ENTRY {
	unsigned char Wcid;
	unsigned char TID;
	unsigned char BAWinSize;
	unsigned char Token;
/* Sequence is to fill every outgoing QoS DATA frame's sequence field in 802.11 header. */
	unsigned short Sequence;
	unsigned short TimeOutValue;
	ORI_BLOCKACK_STATUS ORI_BA_Status;
	RALINK_TIMER_STRUCT ORIBATimer;
	void *pAdapter;
} BA_ORI_ENTRY, *PBA_ORI_ENTRY;

typedef struct _BA_REC_ENTRY {
	unsigned char Wcid;
	unsigned char TID;
	unsigned char BAWinSize;	/* 7.3.1.14. each buffer is capable of holding a max AMSDU or MSDU. */
	/*unsigned char NumOfRxPkt; */
	/*unsigned char    Curindidx; // the head in the RX reordering buffer */
	unsigned short LastIndSeq;
/*	unsigned short		LastIndSeqAtTimer; */
	unsigned short TimeOutValue;
	RALINK_TIMER_STRUCT RECBATimer;
	unsigned long LastIndSeqAtTimer;
	unsigned long nDropPacket;
	unsigned long rcvSeq;
	REC_BLOCKACK_STATUS REC_BA_Status;
/*	unsigned char	RxBufIdxUsed; */
	/* corresponding virtual address for RX reordering packet storage. */
	/*RTMP_REORDERDMABUF MAP_RXBuf[MAX_RX_REORDERBUF]; */
	NDIS_SPIN_LOCK RxReRingLock;	/* Rx Ring spinlock */
/*	struct _BA_REC_ENTRY *pNext; */
	void *pAdapter;
	struct reordering_list list;
} BA_REC_ENTRY, *PBA_REC_ENTRY;


typedef struct {
	unsigned long numAsRecipient;	/* I am recipient of numAsRecipient clients. These client are in the BARecEntry[] */
	unsigned long numAsOriginator;	/* I am originator of   numAsOriginator clients. These clients are in the BAOriEntry[] */
	unsigned long numDoneOriginator;	/* count Done Originator sessions */
	BA_ORI_ENTRY BAOriEntry[MAX_LEN_OF_BA_ORI_TABLE];
	BA_REC_ENTRY BARecEntry[MAX_LEN_OF_BA_REC_TABLE];
} BA_TABLE, *PBA_TABLE;

/*For QureyBATableOID use; */
typedef struct __attribute__ ((packed)) _OID_BA_REC_ENTRY {
	unsigned char MACAddr[MAC_ADDR_LEN];
	unsigned char BaBitmap;		/* if (BaBitmap&(1<<TID)), this session with{MACAddr, TID}exists, so read BufSize[TID] for BufferSize */
	unsigned char rsv;
	unsigned char BufSize[8];
	REC_BLOCKACK_STATUS REC_BA_Status[8];
} OID_BA_REC_ENTRY, *POID_BA_REC_ENTRY;

/*For QureyBATableOID use; */
typedef struct __attribute__ ((packed)) _OID_BA_ORI_ENTRY {
	unsigned char MACAddr[MAC_ADDR_LEN];
	unsigned char BaBitmap;		/* if (BaBitmap&(1<<TID)), this session with{MACAddr, TID}exists, so read BufSize[TID] for BufferSize, read ORI_BA_Status[TID] for status */
	unsigned char rsv;
	unsigned char BufSize[8];
	ORI_BLOCKACK_STATUS ORI_BA_Status[8];
} OID_BA_ORI_ENTRY, *POID_BA_ORI_ENTRY;

typedef struct _QUERYBA_TABLE {
	OID_BA_ORI_ENTRY BAOriEntry[32];
	OID_BA_REC_ENTRY BARecEntry[32];
	unsigned char OriNum;		/* Number of below BAOriEntry */
	unsigned char RecNum;		/* Number of below BARecEntry */
} QUERYBA_TABLE, *PQUERYBA_TABLE;

typedef union _BACAP_STRUC {
#ifdef RT_BIG_ENDIAN
	struct {
		unsigned int:4;
		unsigned int b2040CoexistScanSup:1;	/*As Sta, support do 2040 coexistence scan for AP. As Ap, support monitor trigger event to check if can use BW 40MHz. */
		unsigned int bHtAdhoc:1;	/* adhoc can use ht rate. */
		unsigned int MMPSmode:2;	/* MIMO power save more, 0:static, 1:dynamic, 2:rsv, 3:mimo enable */
		unsigned int AmsduSize:1;	/* 0:3839, 1:7935 bytes. unsigned int  MSDUSizeToBytes[]        = { 3839, 7935}; */
		unsigned int AmsduEnable:1;	/*Enable AMSDU transmisstion */
		unsigned int MpduDensity:3;
		unsigned int Policy:2;	/* 0: DELAY_BA 1:IMMED_BA  (//BA Policy subfiled value in ADDBA frame)   2:BA-not use */
		unsigned int AutoBA:1;	/* automatically BA */
		unsigned int TxBAWinLimit:8;
		unsigned int RxBAWinLimit:8;
	} field;
#else
	struct {
		unsigned int RxBAWinLimit:8;
		unsigned int TxBAWinLimit:8;
		unsigned int AutoBA:1;	/* automatically BA */
		unsigned int Policy:2;	/* 0: DELAY_BA 1:IMMED_BA  (//BA Policy subfiled value in ADDBA frame)   2:BA-not use */
		unsigned int MpduDensity:3;
		unsigned int AmsduEnable:1;	/*Enable AMSDU transmisstion */
		unsigned int AmsduSize:1;	/* 0:3839, 1:7935 bytes. unsigned int  MSDUSizeToBytes[]        = { 3839, 7935}; */
		unsigned int MMPSmode:2;	/* MIMO power save more, 0:static, 1:dynamic, 2:rsv, 3:mimo enable */
		unsigned int bHtAdhoc:1;	/* adhoc can use ht rate. */
		unsigned int b2040CoexistScanSup:1;	/*As Sta, support do 2040 coexistence scan for AP. As Ap, support monitor trigger event to check if can use BW 40MHz. */
		 unsigned int:4;
	} field;
#endif
	unsigned int word;
} BACAP_STRUC, *PBACAP_STRUC;

typedef struct {
	unsigned char IsRecipient;
	unsigned char MACAddr[MAC_ADDR_LEN];
	unsigned char TID;
	unsigned char nMSDU;
	unsigned short TimeOut;
	unsigned char bAllTid;	/* If True, delete all TID for BA sessions with this MACaddr. */
} OID_ADD_BA_ENTRY, *POID_ADD_BA_ENTRY;

#ifdef DOT11N_DRAFT3
typedef enum _BSS2040COEXIST_FLAG {
	BSS_2040_COEXIST_DISABLE = 0,
	BSS_2040_COEXIST_TIMER_FIRED = 1,
	BSS_2040_COEXIST_INFO_SYNC = 2,
	BSS_2040_COEXIST_INFO_NOTIFY = 4,
} BSS2040COEXIST_FLAG;

typedef struct _BssCoexChRange_ {
	unsigned char primaryCh;
	unsigned char secondaryCh;
	unsigned char effectChStart;
	unsigned char effectChEnd;
} BSS_COEX_CH_RANGE;
#endif /* DOT11N_DRAFT3 */

#define IS_HT_STA(_pMacEntry)	\
	(_pMacEntry->MaxHTPhyMode.field.MODE >= MODE_HTMIX)

#define IS_HT_RATE(_pMacEntry)	\
	(_pMacEntry->HTPhyMode.field.MODE >= MODE_HTMIX)

#define PEER_IS_HT_RATE(_pMacEntry)	\
	(_pMacEntry->HTPhyMode.field.MODE >= MODE_HTMIX)

#endif /* DOT11_N_SUPPORT */

/*This structure is for all 802.11n card interOptibilityTest action. Reset all Num every n second.  (Details see MLMEPeriodic) */
typedef struct _IOT_STRUC {
	unsigned char bRTSLongProtOn;
#ifdef CONFIG_STA_SUPPORT
	unsigned char bLastAtheros;
	unsigned char bCurrentAtheros;
	unsigned char bNowAtherosBurstOn;
	unsigned char bNextDisableRxBA;
	unsigned char bToggle;
#endif /* CONFIG_STA_SUPPORT */
} IOT_STRUC, *PIOT_STRUC;

/* This is the registry setting for 802.11n transmit setting.  Used in advanced page. */
typedef union _REG_TRANSMIT_SETTING {
#ifdef RT_BIG_ENDIAN
	struct {
		unsigned int rsv:13;
		unsigned int EXTCHA:2;
		unsigned int HTMODE:1;
		unsigned int TRANSNO:2;
		unsigned int STBC:1;	/*SPACE */
		unsigned int ShortGI:1;
		unsigned int BW:1;	/*channel bandwidth 20MHz or 40 MHz */
		unsigned int TxBF:1;	/* 3*3 */
		unsigned int ITxBfEn:1;
		unsigned int rsv0:9;
		/*unsigned int  MCS:7;                 // MCS */
		/*unsigned int  PhyMode:4; */
	} field;
#else
	struct {
		/*unsigned int  PhyMode:4; */
		/*unsigned int  MCS:7;                 // MCS */
		unsigned int rsv0:9;
		unsigned int ITxBfEn:1;
		unsigned int TxBF:1;
		unsigned int BW:1;	/*channel bandwidth 20MHz or 40 MHz */
		unsigned int ShortGI:1;
		unsigned int STBC:1;	/*SPACE */
		unsigned int TRANSNO:2;
		unsigned int HTMODE:1;
		unsigned int EXTCHA:2;
		unsigned int rsv:13;
	} field;
#endif
	unsigned int word;
} REG_TRANSMIT_SETTING, *PREG_TRANSMIT_SETTING;


typedef union _DESIRED_TRANSMIT_SETTING {
#ifdef RT_BIG_ENDIAN
	struct {
		unsigned short rsv:3;
		unsigned short FixedTxMode:2;	/* If MCS isn't AUTO, fix rate in CCK, OFDM or HT mode. */
		unsigned short PhyMode:4;
		unsigned short MCS:7;	/* MCS */
	} field;
#else
	struct {
		unsigned short MCS:7;	/* MCS */
		unsigned short PhyMode:4;
		unsigned short FixedTxMode:2;	/* If MCS isn't AUTO, fix rate in CCK, OFDM or HT mode. */
		unsigned short rsv:3;
	} field;
#endif
	unsigned short word;
} DESIRED_TRANSMIT_SETTING, *PDESIRED_TRANSMIT_SETTING;


struct hw_setting{
	unsigned char prim_ch;
	unsigned char cent_ch;
	unsigned char bbp_bw;
	unsigned char rf_band;
	unsigned char cur_ch_pwr[3];
};


struct wifi_dev{
	NDIS_802_11_AUTHENTICATION_MODE AuthMode;
	NDIS_802_11_WEP_STATUS WepStatus;
	NDIS_802_11_WEP_STATUS GroupKeyWepStatus;
	WPA_MIX_PAIR_CIPHER WpaMixPairCipher;
	
	RT_PHY_INFO DesiredHtPhyInfo;
	DESIRED_TRANSMIT_SETTING DesiredTransmitSetting;	/* Desired transmit setting. this is for reading registry setting only. not useful. */
	unsigned char bAutoTxRateSwitch;

	unsigned char bWmmCapable;	/* 0:disable WMM, 1:enable WMM */
	
	HTTRANSMIT_SETTING HTPhyMode, MaxHTPhyMode, MinHTPhyMode;
};


#ifdef RTMP_MAC_USB
/***************************************************************************
  *	USB-based chip Beacon related data structures
  **************************************************************************/
#define BEACON_BITMAP_MASK		0xff
typedef struct _BEACON_SYNC_STRUCT_ {
	unsigned char BeaconBuf[HW_BEACON_MAX_NUM][HW_BEACON_OFFSET];
	unsigned char *BeaconTxWI[HW_BEACON_MAX_NUM];
	unsigned long TimIELocationInBeacon[HW_BEACON_MAX_NUM];
	unsigned long CapabilityInfoLocationInBeacon[HW_BEACON_MAX_NUM];
	unsigned char EnableBeacon;	/* trigger to enable beacon transmission. */
	unsigned char BeaconBitMap;	/* NOTE: If the MAX_MBSSID_NUM is larger than 8, this parameter need to change. */
	unsigned char DtimBitOn;	/* NOTE: If the MAX_MBSSID_NUM is larger than 8, this parameter need to change. */
} BEACON_SYNC_STRUCT;
#endif /* RTMP_MAC_USB */

/***************************************************************************
  *	Multiple SSID related data structures
  **************************************************************************/
#define WLAN_MAX_NUM_OF_TIM			((MAX_LEN_OF_MAC_TABLE >> 3) + 1)	/* /8 + 1 */
#define WLAN_CT_TIM_BCMC_OFFSET		0	/* unit: 32B */

/* clear bcmc TIM bit */
#define WLAN_MR_TIM_BCMC_CLEAR(apidx) \
	pAd->ApCfg.MBSSID[apidx].TimBitmaps[WLAN_CT_TIM_BCMC_OFFSET] &= ~NUM_BIT8[0];

/* set bcmc TIM bit */
#define WLAN_MR_TIM_BCMC_SET(apidx) \
	pAd->ApCfg.MBSSID[apidx].TimBitmaps[WLAN_CT_TIM_BCMC_OFFSET] |= NUM_BIT8[0];

/* clear a station PS TIM bit */
#define WLAN_MR_TIM_BIT_CLEAR(ad_p, apidx, wcid) \
	{	unsigned char tim_offset = wcid >> 3; \
		unsigned char bit_offset = wcid & 0x7; \
		ad_p->ApCfg.MBSSID[apidx].TimBitmaps[tim_offset] &= (~NUM_BIT8[bit_offset]); }

/* set a station PS TIM bit */
#define WLAN_MR_TIM_BIT_SET(ad_p, apidx, wcid) \
	{	unsigned char tim_offset = wcid >> 3; \
		unsigned char bit_offset = wcid & 0x7; \
		ad_p->ApCfg.MBSSID[apidx].TimBitmaps[tim_offset] |= NUM_BIT8[bit_offset]; }




/* configuration common to OPMODE_AP as well as OPMODE_STA */
typedef struct _COMMON_CONFIG {
	unsigned char bCountryFlag;
	unsigned char CountryCode[3];
#ifdef EXT_BUILD_CHANNEL_LIST
	unsigned char Geography;
	unsigned char DfsType;
	unsigned char* pChDesp;
#endif				/* EXT_BUILD_CHANNEL_LIST */
	unsigned char CountryRegion;	/* Enum of country region, 0:FCC, 1:IC, 2:ETSI, 3:SPAIN, 4:France, 5:MKK, 6:MKK1, 7:Israel */
	unsigned char CountryRegionForABand;	/* Enum of country region for A band */
	unsigned char PhyMode;
	unsigned char cfg_wmode;
	unsigned char SavedPhyMode;
	unsigned short Dsifs;		/* in units of usec */
	unsigned long PacketFilter;	/* Packet filter for receiving */
	unsigned char RegulatoryClass[MAX_NUM_OF_REGULATORY_CLASS];

	char Ssid[MAX_LEN_OF_SSID];	/* NOT NULL-terminated */
	unsigned char SsidLen;		/* the actual ssid length in used */
	unsigned char LastSsidLen;	/* the actual ssid length in used */
	char LastSsid[MAX_LEN_OF_SSID];	/* NOT NULL-terminated */
	unsigned char LastBssid[MAC_ADDR_LEN];

	unsigned char Bssid[MAC_ADDR_LEN];
	unsigned short BeaconPeriod;
	unsigned char Channel;
	unsigned char CentralChannel;	/* Central Channel when using 40MHz is indicating. not real channel. */

	unsigned char SupRate[MAX_LEN_OF_SUPPORTED_RATES];
	unsigned char SupRateLen;
	unsigned char ExtRate[MAX_LEN_OF_SUPPORTED_RATES];
	unsigned char ExtRateLen;
	unsigned char DesireRate[MAX_LEN_OF_SUPPORTED_RATES];	/* OID_802_11_DESIRED_RATES */
	unsigned char MaxDesiredRate;
	unsigned char ExpectedACKRate[MAX_LEN_OF_SUPPORTED_RATES];

	unsigned long BasicRateBitmap;	/* backup basic ratebitmap */
	unsigned long BasicRateBitmapOld;	/* backup basic ratebitmap */

	unsigned char bInServicePeriod;


	unsigned char bAPSDAC_BE;
	unsigned char bAPSDAC_BK;
	unsigned char bAPSDAC_VI;
	unsigned char bAPSDAC_VO;


	/* because TSPEC can modify the APSD flag, we need to keep the APSD flag
	   requested in association stage from the station;
	   we need to recover the APSD flag after the TSPEC is deleted. */
	unsigned char bACMAPSDBackup[4];	/* for delivery-enabled & trigger-enabled both */
	unsigned char bACMAPSDTr[4];	/* no use */
	unsigned char MaxSPLength;

	unsigned char bNeedSendTriggerFrame;
	unsigned char bAPSDForcePowerSave;	/* Force power save mode, should only use in APSD-STAUT */
	unsigned long TriggerTimerCount;
	unsigned char BBPCurrentBW;	/* BW_10, BW_20, BW_40, BW_80 */
	REG_TRANSMIT_SETTING RegTransmitSetting;	/*registry transmit setting. this is for reading registry setting only. not useful. */
	unsigned char TxRate;		/* Same value to fill in TXD. TxRate is 6-bit */
	unsigned char MaxTxRate;	/* RATE_1, RATE_2, RATE_5_5, RATE_11 */
	unsigned char TxRateIndex;	/* Tx rate index in Rate Switch Table */
	unsigned char MinTxRate;	/* RATE_1, RATE_2, RATE_5_5, RATE_11 */
	unsigned char RtsRate;		/* RATE_xxx */
	HTTRANSMIT_SETTING MlmeTransmit;	/* MGMT frame PHY rate setting when operatin at Ht rate. */
	unsigned char MlmeRate;		/* RATE_xxx, used to send MLME frames */
	unsigned char BasicMlmeRate;	/* Default Rate for sending MLME frames */

	unsigned short RtsThreshold;	/* in unit of BYTE */
	unsigned short FragmentThreshold;	/* in unit of BYTE */

	unsigned char TxPower;		/* in unit of mW */
	unsigned long TxPowerPercentage;	/* 0~100 % */
	unsigned long TxPowerDefault;	/* keep for TxPowerPercentage */
	unsigned char PwrConstraint;

#ifdef DOT11_N_SUPPORT
	BACAP_STRUC BACapability;	/*   NO USE = 0XFF  ;  IMMED_BA =1  ;  DELAY_BA=0 */
	BACAP_STRUC REGBACapability;	/*   NO USE = 0XFF  ;  IMMED_BA =1  ;  DELAY_BA=0 */
#endif /* DOT11_N_SUPPORT */

#ifdef DOT11_VHT_AC
	unsigned char force_vht;
	unsigned char vht_bw;
	unsigned char vht_sgi_80;
	unsigned char vht_stbc;
	unsigned char vht_bw_signal;
	unsigned char vht_cent_ch;
	unsigned char vht_cent_ch2;
#endif /* DOT11_VHT_AC */

	IOT_STRUC IOTestParm;	/* 802.11n interOpbility Test Parameter; */
	unsigned long TxPreamble;	/* Rt802_11PreambleLong, Rt802_11Preambleshort, Rt802_11PreambleAuto */
	unsigned char bUseZeroToDisableFragment;	/* Microsoft use 0 as disable */
	unsigned long UseBGProtection;	/* 0: auto, 1: always use, 2: always not use */
	unsigned char bUseShortSlotTime;	/* 0: disable, 1 - use short slot (9us) */
	unsigned char bEnableTxBurst;	/* 1: enble TX PACKET BURST (when BA is established or AP is not a legacy WMM AP), 0: disable TX PACKET BURST */
	unsigned char bAggregationCapable;	/* 1: enable TX aggregation when the peer supports it */
	unsigned char bPiggyBackCapable;	/* 1: enable TX piggy-back according MAC's version */
	unsigned char bIEEE80211H;	/* 1: enable IEEE802.11h spec. */
	unsigned char RDDurRegion; /* Region of radar detection */
	unsigned long DisableOLBCDetect;	/* 0: enable OLBC detect; 1 disable OLBC detect */

#ifdef DOT11_N_SUPPORT
	unsigned char bRdg;
#endif /* DOT11_N_SUPPORT */
	unsigned char bWmmCapable;	/* 0:disable WMM, 1:enable WMM */
	QOS_CAPABILITY_PARM APQosCapability;	/* QOS capability of the current associated AP */
	EDCA_PARM APEdcaParm;	/* EDCA parameters of the current associated AP */
	QBSS_LOAD_PARM APQbssLoad;	/* QBSS load of the current associated AP */
	unsigned char AckPolicy[4];	/* ACK policy of the specified AC. see ACK_xxx */
#ifdef CONFIG_STA_SUPPORT
	unsigned char bDLSCapable;	/* 0:disable DLS, 1:enable DLS */
#endif /* CONFIG_STA_SUPPORT */
	/* a bitmap of unsigned char flags. each bit represent an operation status of a particular */
	/* unsigned char control, either ON or OFF. These flags should always be accessed via */
	/* OPSTATUS_TEST_FLAG(), OPSTATUS_SET_FLAG(), OP_STATUS_CLEAR_FLAG() macros. */
	/* see fOP_STATUS_xxx in RTMP_DEF.C for detail bit definition */
	unsigned long OpStatusFlags;

	unsigned char NdisRadioStateOff;	/*For HCT 12.0, set this flag to TRUE instead of called MlmeRadioOff. */

#ifdef DFS_SUPPORT
	/* IEEE802.11H--DFS. */
	RADAR_DETECT_STRUCT RadarDetect;
#endif /* DFS_SUPPORT */
#ifdef CARRIER_DETECTION_SUPPORT
	CARRIER_DETECTION_STRUCT CarrierDetect;
#endif /* CARRIER_DETECTION_SUPPORT */

#ifdef DOT11_N_SUPPORT
	/* HT */
	RT_HT_CAPABILITY DesiredHtPhy;
	HT_CAPABILITY_IE HtCapability;
	ADD_HT_INFO_IE AddHTInfo;	/* Useful as AP. */
	/*This IE is used with channel switch announcement element when changing to a new 40MHz. */
	/*This IE is included in channel switch ammouncement frames 7.4.1.5, beacons, probe Rsp. */
	NEW_EXT_CHAN_IE NewExtChanOffset;	/*7.3.2.20A, 1 if extension channel is above the control channel, 3 if below, 0 if not present */

	EXT_CAP_INFO_ELEMENT ExtCapIE;	/* this is the extened capibility IE appreed in MGMT frames. Doesn't need to update once set in Init. */

#ifdef DOT11N_DRAFT3
	unsigned char bBssCoexEnable;
	/* 
	   Following two paramters now only used for the initial scan operation. the AP only do 
	   bandwidth fallback when BssCoexApCnt > BssCoexApCntThr
	   By default, the "BssCoexApCntThr" is set as 0 in "UserCfgInit()".
	 */
	unsigned char BssCoexApCntThr;
	unsigned char BssCoexApCnt;

	unsigned char Bss2040CoexistFlag;	/* bit 0: bBssCoexistTimerRunning, bit 1: NeedSyncAddHtInfo. */
	RALINK_TIMER_STRUCT Bss2040CoexistTimer;
	unsigned char Bss2040NeedFallBack; 	/* 1: Need Fall back to 20MHz */

	/*This IE is used for 20/40 BSS Coexistence. */
	BSS_2040_COEXIST_IE BSS2040CoexistInfo;

	unsigned short Dot11OBssScanPassiveDwell;	/* Unit : TU. 5~1000 */
	unsigned short Dot11OBssScanActiveDwell;	/* Unit : TU. 10~1000 */
	unsigned short Dot11BssWidthTriggerScanint;	/* Unit : Second */
	unsigned short Dot11OBssScanPassiveTotalPerChannel;	/* Unit : TU. 200~10000 */
	unsigned short Dot11OBssScanActiveTotalPerChannel;	/* Unit : TU. 20~10000 */
	unsigned short Dot11BssWidthChanTranDelayFactor;
	unsigned short Dot11OBssScanActivityThre;	/* Unit : percentage */

	unsigned long Dot11BssWidthChanTranDelay;	/* multiple of (Dot11BssWidthTriggerScanint * Dot11BssWidthChanTranDelayFactor) */
	unsigned long CountDownCtr;	/* CountDown Counter from (Dot11BssWidthTriggerScanint * Dot11BssWidthChanTranDelayFactor) */

	BSS_2040_COEXIST_IE LastBSSCoexist2040;
	BSS_2040_COEXIST_IE BSSCoexist2040;
	TRIGGER_EVENT_TAB TriggerEventTab;
	unsigned char ChannelListIdx;

	unsigned char bOverlapScanning;
	unsigned char bBssCoexNotify;
#endif /* DOT11N_DRAFT3 */

	unsigned char bHTProtect;
	unsigned char bMIMOPSEnable;
	unsigned char bBADecline;
	unsigned char bDisableReordering;
	unsigned char bForty_Mhz_Intolerant;
	unsigned char bExtChannelSwitchAnnouncement;
	unsigned char bRcvBSSWidthTriggerEvents;
	unsigned long LastRcvBSSWidthTriggerEventsTime;

	unsigned char TxBASize;

	unsigned char bRalinkBurstMode;
	unsigned int RestoreBurstMode;
#endif /* DOT11_N_SUPPORT */

#ifdef DOT11_VHT_AC
	unsigned int cfg_vht;
	VHT_CAP_INFO vht_info;
#endif /* DOT11_VHT_AC */

#ifdef SYSTEM_LOG_SUPPORT
	/* Enable wireless event */
	unsigned char bWirelessEvent;
#endif /* SYSTEM_LOG_SUPPORT */

	unsigned char bWiFiTest;	/* Enable this parameter for WiFi test */

	/* Tx & Rx Stream number selection */
	unsigned char TxStream;
	unsigned char RxStream;

	/* transmit phy mode, trasmit rate for Multicast. */
#ifdef MCAST_RATE_SPECIFIC
	unsigned char McastTransmitMcs;
	unsigned char McastTransmitPhyMode;
#endif /* MCAST_RATE_SPECIFIC */

	unsigned char bHardwareRadio;	/* Hardware controlled Radio enabled */

#ifdef RTMP_MAC_USB
	unsigned char bMultipleIRP;	/* Multiple Bulk IN flag */
	unsigned char NumOfBulkInIRP;	/* if bMultipleIRP == TRUE, NumOfBulkInIRP will be 4 otherwise be 1 */
	RT_HT_CAPABILITY SupportedHtPhy;
	unsigned long MaxPktOneTxBulk;
	unsigned char TxBulkFactor;
	unsigned char RxBulkFactor;

	unsigned char IsUpdateBeacon;
	BEACON_SYNC_STRUCT *pBeaconSync;
	RALINK_TIMER_STRUCT BeaconUpdateTimer;
	unsigned int BeaconAdjust;
	unsigned int BeaconFactor;
	unsigned int BeaconRemain;
#endif				/* RTMP_MAC_USB */



	NDIS_SPIN_LOCK MeasureReqTabLock;
	PMEASURE_REQ_TAB pMeasureReqTab;

	NDIS_SPIN_LOCK TpcReqTabLock;
	PTPC_REQ_TAB pTpcReqTab;

	/* transmit phy mode, trasmit rate for Multicast. */
#ifdef MCAST_RATE_SPECIFIC
	HTTRANSMIT_SETTING MCastPhyMode;
#endif /* MCAST_RATE_SPECIFIC */

#ifdef SINGLE_SKU
	unsigned short DefineMaxTxPwr;
	unsigned char bSKUMode;
	unsigned short AntGain;
	unsigned short BandedgeDelta;
	unsigned short ModuleTxpower;
#endif /* SINGLE_SKU */



	unsigned char HT_DisallowTKIP;	/* Restrict the encryption type in 11n HT mode */

	unsigned char HT_Disable;	/* 1: disable HT function; 0: enable HT function */


#ifdef PRE_ANT_SWITCH
	unsigned char PreAntSwitch;	/* Preamble Antenna Switch */
	short PreAntSwitchRSSI;	/* Preamble Antenna Switch RSSI threshold */
	short PreAntSwitchTimeout; /* Preamble Antenna Switch timeout in seconds */
#endif /* PRE_ANT_SWITCH */

#ifdef CFO_TRACK
	short	CFOTrack;	/* CFO Tracking. 0=>use default, 1=>track, 2-7=> track 8-n times, 8=>done tracking */
#endif /* CFO_TRACK */

#ifdef NEW_RATE_ADAPT_SUPPORT
	unsigned short	lowTrafficThrd;		/* Threshold for reverting to default MCS when traffic is low */
	unsigned char	TrainUpRule;		/* QuickDRS train up criterion: 0=>Throughput, 1=>PER, 2=> Throughput & PER */
	short	TrainUpRuleRSSI;	/* If TrainUpRule=2 then use Hybrid rule when RSSI < TrainUpRuleRSSI */
	unsigned short	TrainUpLowThrd;		/* QuickDRS Hybrid train up low threshold */
	unsigned short	TrainUpHighThrd;	/* QuickDRS Hybrid train up high threshold */
#endif /* NEW_RATE_ADAPT_SUPPORT */

#ifdef STREAM_MODE_SUPPORT
#define		STREAM_MODE_STA_NUM		4

	unsigned char	StreamMode; /* 0=disabled, 1=enable for 1SS, 2=enable for 2SS, 3=enable for 1,2SS */
	unsigned char	StreamModeMac[STREAM_MODE_STA_NUM][MAC_ADDR_LEN];
	unsigned short	StreamModeMCS;	/* Bit map for enabling Stream Mode based on MCS */
#endif /* STREAM_MODE_SUPPORT */

#ifdef DOT11_N_SUPPORT
#ifdef TXBF_SUPPORT
	unsigned long ITxBfTimeout;
	unsigned long ETxBfTimeout;
	unsigned long	ETxBfEnCond;		/* Enable sending of sounding and beamforming */
	unsigned char	ETxBfNoncompress;	/* Force non-compressed Sounding Response */
	unsigned char	ETxBfIncapable;		/* Report Incapable of BF in TX BF Capabilities */
#endif /* TXBF_SUPPORT */
#endif /* DOT11_N_SUPPORT */

#ifdef DBG_CTRL_SUPPORT
	unsigned long DebugFlags;	/* Temporary debug flags */
#endif /* DBG_CTRL_SUPPORT */



	//brian
	unsigned int nLoopBack_Count;
	unsigned int nWIFI_Info_Idx;
	
#ifdef CONFIG_WIFI_TEST
	unsigned long WiFiTestFlags;
#endif
} COMMON_CONFIG, *PCOMMON_CONFIG;

#ifdef DBG_CTRL_SUPPORT
/* DebugFlag definitions */
#define DBF_NO_BF_AWARE_RA		0x0001	/* Revert to older Rate Adaptation that is not BF aware */
#define DBF_SHOW_BF_STATS		0x0002	/* Display BF statistics in AP "iwpriv stat" display */
#define DBF_NO_TXBF_3SS			0x0004	/* Disable TXBF for MCS > 20 */
#define DBF_UNUSED0008			0x0008	/* Unused */
#define DBF_DBQ_RA_LOG			0x0010	/* Log RA information in DBQ */
#define DBF_INIT_MCS_MARGIN		0x0020	/* Use 6 dB margin when selecting initial MCS */
#define DBF_INIT_MCS_DIS1		0x0040	/* Disable highest MCSs when selecting initial MCS */
#define DBF_FORCE_QUICK_DRS		0x0080	/* Force Quick DRS even if rate didn't change */
#define DBF_FORCE_SGI			0x0100	/* Force short GI */
#define DBF_DBQ_NO_BCN			0x0200	/* Disable logging of RX Beacon frames */
#define DBF_LOG_VCO_CAL			0x0400	/* Log VCO cal */
#define DBF_DISABLE_CAL			0x0800	/* Disable Divider Calibration at channel change */
#ifdef INCLUDE_DEBUG_QUEUE
#define DBF_DBQ_TXFIFO			0x1000	/* Enable logging of TX information from FIFO */
#define DBF_DBQ_TXFRAME			0x2000	/* Enable logging of Frames queued for TX */
#define DBF_DBQ_RXWI_FULL		0x4000	/* Enable logging of full RXWI */
#define DBF_DBQ_RXWI			0x8000	/* Enable logging of partial RXWI */
#endif /* INCLUDE_DEBUG_QUEUE */

#define DBF_SHOW_RA_LOG			0x010000	/* Display concise Rate Adaptation information */
#define DBF_SHOW_ZERO_RA_LOG	0x020000	/* Include RA Log entries when TxCount is 0 */
#define DBF_FORCE_20MHZ			0x040000	/* Force 20 MHz TX */
#define DBF_FORCE_40MHZ 		0x080000	/* Force 40 MHz Tx */
#define DBF_DISABLE_CCK			0x100000	/* Disable CCK */
#define DBF_UNUSED200000		0x200000	/* Unused */
#define DBF_ENABLE_HT_DUP		0x400000	/* Allow HT Duplicate mode in TX rate table */
#define DBF_ENABLE_CCK_5G		0x800000	/* Enable CCK rates in 5G band */
#define DBF_UNUSED0100000		0x0100000	/* Unused */
#define DBF_ENABLE_20MHZ_MCS8	0x02000000	/* Substitute 20MHz MCS8 for 40MHz MCS8 */
#define DBF_DISABLE_20MHZ_MCS0	0x04000000	/* Disable substitution of 20MHz MCS0 for 40MHz MCS32 */
#define DBF_DISABLE_20MHZ_MCS1	0x08000000	/* Disable substitution of 20MHz MCS1 for 40MHz MCS0 */
#endif /* DBG_CTRL_SUPPORT */

#ifdef CONFIG_STA_SUPPORT

#ifdef CREDENTIAL_STORE
typedef struct _STA_CONNECT_INFO {
	unsigned char Changeable;
	unsigned char IEEE8021X;
	char Ssid[MAX_LEN_OF_SSID]; // NOT NULL-terminated
	unsigned char SsidLen; // the actual ssid length in used
	NDIS_802_11_AUTHENTICATION_MODE AuthMode; // This should match to whatever microsoft defined
	NDIS_802_11_WEP_STATUS WepStatus;
	unsigned char DefaultKeyId;
	unsigned char PMK[LEN_PMK]; // WPA PSK mode PMK
	unsigned char WpaPassPhrase[64]; // WPA PSK pass phrase
	unsigned int WpaPassPhraseLen; // the length of WPA PSK pass phrase
	unsigned char WpaState;
	CIPHER_KEY SharedKey[1][4]; // STA always use SharedKey[BSS0][0..3]
	NDIS_SPIN_LOCK Lock;
} STA_CONNECT_INFO, *P_STA_CONNECT_INFO;
#endif /* CREDENTIAL_STORE */


/* Modified by Wu Xi-Kun 4/21/2006 */
/* STA configuration and status */
typedef struct _STA_ADMIN_CONFIG {
	struct wifi_dev wdev;

	/*
		GROUP 1 -
		User configuration loaded from Registry, E2PROM or OID_xxx. These settings describe
		the user intended configuration, but not necessary fully equal to the final
		settings in ACTIVE BSS after negotiation/compromize with the BSS holder (either
		AP or IBSS holder).
		Once initialized, user configuration can only be changed via OID_xxx
	*/
	unsigned char BssType;		/* BSS_INFRA or BSS_ADHOC */

#ifdef MONITOR_FLAG_11N_SNIFFER_SUPPORT
#define MONITOR_FLAG_11N_SNIFFER		0x01
	unsigned char BssMonitorFlag;	/* Specific flag for monitor */
#endif				/* MONITOR_FLAG_11N_SNIFFER_SUPPORT */

	unsigned short AtimWin;		/* used when starting a new IBSS */

	/*
		GROUP 2 -
		User configuration loaded from Registry, E2PROM or OID_xxx. These settings describe
		the user intended configuration, and should be always applied to the final
		settings in ACTIVE BSS without compromising with the BSS holder.
		Once initialized, user configuration can only be changed via OID_xxx
	*/
	unsigned char RssiTrigger;
	unsigned char RssiTriggerMode;	/* RSSI_TRIGGERED_UPON_BELOW_THRESHOLD or RSSI_TRIGGERED_UPON_EXCCEED_THRESHOLD */
	unsigned short DefaultListenCount;	/* default listen count; */
	unsigned long WindowsPowerMode;	/* Power mode for AC power */
	unsigned long WindowsBatteryPowerMode;	/* Power mode for battery if exists */
	unsigned char bWindowsACCAMEnable;	/* Enable CAM power mode when AC on */
	unsigned char bAutoReconnect;	/* Set to TRUE when setting OID_802_11_SSID with no matching BSSID */
	unsigned long WindowsPowerProfile;	/* Windows power profile, for NDIS5.1 PnP */

	unsigned char	 FlgPsmCanNotSleep; /* TRUE: can not switch ASIC to sleep */
	/* MIB:ieee802dot11.dot11smt(1).dot11StationConfigTable(1) */
	unsigned short Psm;		/* power management mode   (PWR_ACTIVE|PWR_SAVE) */
	unsigned short DisassocReason;
	unsigned char DisassocSta[MAC_ADDR_LEN];
	unsigned short DeauthReason;
	unsigned char DeauthSta[MAC_ADDR_LEN];
	unsigned short AuthFailReason;
	unsigned char AuthFailSta[MAC_ADDR_LEN];

	NDIS_802_11_PRIVACY_FILTER PrivacyFilter;	/* PrivacyFilter enum for 802.1X */
	NDIS_802_11_AUTHENTICATION_MODE AuthMode;	/* This should match to whatever microsoft defined */
	NDIS_802_11_WEP_STATUS WepStatus;

	/* Add to support different cipher suite for WPA2/WPA mode */
	NDIS_802_11_ENCRYPTION_STATUS GroupCipher;	/* Multicast cipher suite */
	NDIS_802_11_ENCRYPTION_STATUS PairCipher;	/* Unicast cipher suite */
	unsigned char bMixCipher;	/* Indicate current Pair & Group use different cipher suites */
	unsigned short RsnCapability;

	NDIS_802_11_WEP_STATUS GroupKeyWepStatus;

	unsigned char WpaPassPhrase[64];	/* WPA PSK pass phrase */
	unsigned int WpaPassPhraseLen;	/* the length of WPA PSK pass phrase */
	unsigned char PMK[LEN_PMK];	/* WPA PSK mode PMK */
	unsigned char PTK[LEN_PTK];	/* WPA PSK mode PTK */
	unsigned char GMK[LEN_GMK];	/* WPA PSK mode GMK */
	unsigned char GTK[MAX_LEN_GTK];	/* GTK from authenticator */
	unsigned char GNonce[32];	/* GNonce for WPA2PSK from authenticator */
	CIPHER_KEY TxGTK;
	BSSID_INFO SavedPMK[PMKID_NO];
	unsigned int SavedPMKNum;	/* Saved PMKID number */

	unsigned char DefaultKeyId;


	/* WPA 802.1x port control, WPA_802_1X_PORT_SECURED, WPA_802_1X_PORT_NOT_SECURED */
	unsigned char PortSecured;

	/* For WPA countermeasures */
	unsigned long LastMicErrorTime;	/* record last MIC error time */
	unsigned long MicErrCnt;	/* Should be 0, 1, 2, then reset to zero (after disassoiciation). */
	unsigned char bBlockAssoc;	/* Block associate attempt for 60 seconds after counter measure occurred. */
	/* For WPA-PSK supplicant state */
	unsigned char WpaState;		/* Default is SS_NOTUSE and handled by microsoft 802.1x */
	unsigned char ReplayCounter[8];
	unsigned char ANonce[32];	/* ANonce for WPA-PSK from aurhenticator */
	unsigned char SNonce[32];	/* SNonce for WPA-PSK */

	unsigned char LastSNR0;		/* last received BEACON's SNR */
	unsigned char LastSNR1;		/* last received BEACON's SNR for 2nd  antenna */
#ifdef DOT11N_SS3_SUPPORT
	unsigned char LastSNR2;		/* last received BEACON's SNR for 3nd  antenna */
	int BF_SNR[3];	/* Last RXWI BF SNR. Units=0.25 dB */
#endif /* DOT11N_SS3_SUPPORT */
	RSSI_SAMPLE RssiSample;
	unsigned long NumOfAvgRssiSample;

	unsigned long LastBeaconRxTime;	/* OS's timestamp of the last BEACON RX time */
	unsigned long Last11bBeaconRxTime;	/* OS's timestamp of the last 11B BEACON RX time */
	unsigned long Last11gBeaconRxTime;	/* OS's timestamp of the last 11G BEACON RX time */
	unsigned long Last20NBeaconRxTime;	/* OS's timestamp of the last 20MHz N BEACON RX time */

	unsigned long LastScanTime;	/* Record last scan time for issue BSSID_SCAN_LIST */
	unsigned char bNotFirstScan;	/* Sam add for ADHOC flag to do first scan when do initialization */
	unsigned char bSwRadio;	/* Software controlled Radio On/Off, TRUE: On */
	unsigned char bHwRadio;	/* Hardware controlled Radio On/Off, TRUE: On */
	unsigned char bRadio;		/* Radio state, And of Sw & Hw radio state */
	unsigned char bHardwareRadio;	/* Hardware controlled Radio enabled */
	unsigned char bShowHiddenSSID;	/* Show all known SSID in SSID list get operation */

	/* New for WPA, windows want us to to keep association information and */
	/* Fixed IEs from last association response */
	NDIS_802_11_ASSOCIATION_INFORMATION AssocInfo;
	unsigned short ReqVarIELen;	/* Length of next VIE include EID & Length */
	unsigned char ReqVarIEs[MAX_VIE_LEN];	/* The content saved here should be little-endian format. */
	unsigned short ResVarIELen;	/* Length of next VIE include EID & Length */
	unsigned char ResVarIEs[MAX_VIE_LEN];

	unsigned char RSNIE_Len;
	unsigned char RSN_IE[MAX_LEN_OF_RSNIE];	/* The content saved here should be little-endian format. */

	unsigned long CLBusyBytes;	/* Save the total bytes received durning channel load scan time */
	unsigned short RPIDensity[8];	/* Array for RPI density collection */

	unsigned char RMReqCnt;		/* Number of measurement request saved. */
	unsigned char CurrentRMReqIdx;	/* Number of measurement request saved. */
	unsigned char ParallelReq;	/* Parallel measurement, only one request performed, */
	/* It must be the same channel with maximum duration */
	unsigned short ParallelDuration;	/* Maximum duration for parallel measurement */
	unsigned char ParallelChannel;	/* Only one channel with parallel measurement */
	unsigned short IAPPToken;	/* IAPP dialog token */
	/* Hack for channel load and noise histogram parameters */
	unsigned char NHFactor;		/* Parameter for Noise histogram */
	unsigned char CLFactor;		/* Parameter for channel load */

	RALINK_TIMER_STRUCT StaQuickResponeForRateUpTimer;
	unsigned char StaQuickResponeForRateUpTimerRunning;

	unsigned char DtimCount;	/* 0.. DtimPeriod-1 */
	unsigned char DtimPeriod;	/* default = 3 */

#ifdef QOS_DLS_SUPPORT
	RT_802_11_DLS DLSEntry[MAX_NUM_OF_DLS_ENTRY];
	unsigned char DlsReplayCounter[8];
#endif				/* QOS_DLS_SUPPORT */


	RALINK_TIMER_STRUCT WpaDisassocAndBlockAssocTimer;
	/* Fast Roaming */
	unsigned char bAutoRoaming;	/* 0:disable auto roaming by RSSI, 1:enable auto roaming by RSSI */
	char dBmToRoam;		/* the condition to roam when receiving Rssi less than this value. It's negative value. */

#ifdef WPA_SUPPLICANT_SUPPORT
	unsigned char IEEE8021X;
	unsigned char IEEE8021x_required_keys;
	CIPHER_KEY DesireSharedKey[4];	/* Record user desired WEP keys */
	unsigned char DesireSharedKeyId;

	/* 0x00: driver ignores wpa_supplicant */
	/* 0x01: wpa_supplicant initiates scanning and AP selection */
	/* 0x02: driver takes care of scanning, AP selection, and IEEE 802.11 association parameters */
	/* 0x80: wpa_supplicant trigger driver to do WPS */
	unsigned char WpaSupplicantUP;
	unsigned char WpaSupplicantScanCount;
	unsigned char bRSN_IE_FromWpaSupplicant;
	unsigned char bLostAp;
	unsigned char *pWpsProbeReqIe;
	unsigned int WpsProbeReqIeLen;
	unsigned char *pWpaAssocIe;
	unsigned int WpaAssocIeLen;
#endif /* WPA_SUPPLICANT_SUPPORT */

	char dev_name[16];
	unsigned short OriDevType;

	unsigned char bTGnWifiTest;
	unsigned char bSkipAutoScanConn;

	HTTRANSMIT_SETTING HTPhyMode, MaxHTPhyMode, MinHTPhyMode;	/* For transmit phy setting in TXWI. */
	DESIRED_TRANSMIT_SETTING DesiredTransmitSetting;
	RT_PHY_INFO DesiredHtPhyInfo;
	unsigned char bAutoTxRateSwitch;


#ifdef EXT_BUILD_CHANNEL_LIST
	unsigned char IEEE80211dClientMode;
	unsigned char StaOriCountryCode[3];
	unsigned char StaOriGeography;
#endif /* EXT_BUILD_CHANNEL_LIST */





	unsigned char bAutoConnectByBssid;
	unsigned long BeaconLostTime;	/* seconds */
	unsigned char bForceTxBurst;	/* 1: force enble TX PACKET BURST, 0: disable */
#ifdef XLINK_SUPPORT
	unsigned char PSPXlink;	/* 0: Disable. 1: Enable */
#endif /* XLINK_SUPPORT */
	unsigned char bAutoConnectIfNoSSID;
#ifdef DOT11_N_SUPPORT
#ifdef DOT11N_DRAFT3
	unsigned char RegClass;		/*IE_SUPP_REG_CLASS: 2009 PF#3: For 20/40 intolerant Channel Report */
#endif /* DOT11N_DRAFT3 */
	unsigned char bAdhocN;
#endif /* DOT11_N_SUPPORT */
	unsigned char bAdhocCreator;	/*TRUE indicates divice is Creator. */


	/*
	   Enhancement Scanning Mechanism
	   To decrease the possibility of ping loss
	 */
	unsigned char bImprovedScan;
	unsigned char BssNr;
	unsigned char ScanChannelCnt;	/* 0 at the beginning of scan, stop at 7 */
	unsigned char LastScanChannel;
	/************************************/

	unsigned char bFastConnect;

/*connectinfo  for tmp store connect info from UI*/
	unsigned char Connectinfoflag;
	unsigned char   ConnectinfoBssid[MAC_ADDR_LEN];
	unsigned char   ConnectinfoChannel;
	unsigned char   ConnectinfoSsidLen;
	char    ConnectinfoSsid[MAX_LEN_OF_SSID];
	unsigned char ConnectinfoBssType;
	



	/* UAPSD information: such as enable or disable, do not remove */
	UAPSD_INFO UapsdInfo;

#ifdef WFD_SUPPORT
	RT_WFD_CONFIG WfdCfg;
#endif /* WFD_SUPPORT */

#ifdef RT3290
	// TODO: shiang, check the purpose of following parameters
	unsigned long AntS;
	unsigned long AntSAuxDelta;
	unsigned long AntSRssiFactor;
	unsigned long AntSPERFactor;
	char Rssi[2];
#endif /* RT3290 */
} STA_ADMIN_CONFIG, *PSTA_ADMIN_CONFIG;


/*
	This data structure keep the current active BSS/IBSS's configuration that
	this STA had agreed upon joining the network. Which means these parameters
	are usually decided by the BSS/IBSS creator instead of user configuration.
	Data in this data structurre is valid only when either ADHOC_ON()/INFRA_ON()
	is TRUE. Normally, after SCAN or failed roaming attempts, we need to
	recover back to the current active settings
*/
typedef struct _STA_ACTIVE_CONFIG {
	unsigned short Aid;
	unsigned short AtimWin;		/* in kusec; IBSS parameter set element */
	unsigned short CapabilityInfo;
	EXT_CAP_INFO_ELEMENT ExtCapInfo;
	unsigned short CfpMaxDuration;
	unsigned short CfpPeriod;

	/* Copy supported rate from desired AP's beacon. We are trying to match */
	/* AP's supported and extended rate settings. */
	unsigned char SupRate[MAX_LEN_OF_SUPPORTED_RATES];
	unsigned char ExtRate[MAX_LEN_OF_SUPPORTED_RATES];
	unsigned char SupRateLen;
	unsigned char ExtRateLen;
	/* Copy supported ht from desired AP's beacon. We are trying to match */
	RT_PHY_INFO SupportedPhyInfo;
	RT_HT_CAPABILITY SupportedHtPhy;
	RT_VHT_CAP	SupVhtCap;
} STA_ACTIVE_CONFIG, *PSTA_ACTIVE_CONFIG;



#endif /* CONFIG_STA_SUPPORT */



/* Values of LastSecTxRateChangeAction */
#define RATE_NO_CHANGE	0		/* No change in rate */
#define RATE_UP			1		/* Trying higher rate or same rate with different BF */
#define RATE_DOWN		2		/* Trying lower rate */



#ifdef WFA_VHT_PF
#ifdef IP_ASSEMBLY
struct ip_frag_q{
	struct list_head ip_queue[4];
	int ip_id[4];
	int ip_id_FragSize[4];
	unsigned long ip_pkt_jiffies[4];
};
#endif /* IP_ASSEMBLY */
#endif /* WFA_VHT_PF */
typedef struct _QUEUE_ENTRY
{
    struct _QUEUE_ENTRY *Next;
} QUEUE_ENTRY, *PQUEUE_ENTRY;

/* Queue structure */
typedef struct _QUEUE_HEADER
{
    PQUEUE_ENTRY Head;
    PQUEUE_ENTRY Tail;
    unsigned long Number;
} QUEUE_HEADER, *PQUEUE_HEADER;


typedef struct _MAC_TABLE_ENTRY {
	/*
	   0:Invalid,
	   Bit 0: AsCli, Bit 1: AsWds, Bit 2: AsAPCLI,
	   Bit 3: AsMesh, Bit 4: AsDls, Bit 5: AsTDls
	 */
	unsigned int EntryType;

	unsigned char isCached;
	unsigned char bIAmBadAtheros;	/* Flag if this is Atheros chip that has IOT problem.  We need to turn on RTS/CTS protection. */
	unsigned char wcid;

	/* WPA/WPA2 4-way database */
	unsigned char EnqueueEapolStartTimerRunning;	/* Enqueue EAPoL-Start for triggering EAP SM */
	RALINK_TIMER_STRUCT EnqueueStartForPSKTimer;	/* A timer which enqueue EAPoL-Start for triggering PSK SM */

	/*jan for wpa */
	/* record which entry revoke MIC Failure , if it leaves the BSS itself, AP won't update aMICFailTime MIB */
	unsigned char CMTimerRunning;
	unsigned char apidx;		/* MBSS number */
	unsigned char RSNIE_Len;
	unsigned char RSN_IE[MAX_LEN_OF_RSNIE];
	unsigned char ANonce[LEN_KEY_DESC_NONCE];
	unsigned char SNonce[LEN_KEY_DESC_NONCE];
	unsigned char R_Counter[LEN_KEY_DESC_REPLAY];
	unsigned char PTK[64];
	unsigned char ReTryCounter;
	RALINK_TIMER_STRUCT RetryTimer;
#ifdef TXBF_SUPPORT
	RALINK_TIMER_STRUCT eTxBfProbeTimer;
#endif /* TXBF_SUPPORT */
	NDIS_802_11_AUTHENTICATION_MODE AuthMode;	/* This should match to whatever microsoft defined */
	NDIS_802_11_WEP_STATUS WepStatus;
	NDIS_802_11_WEP_STATUS GroupKeyWepStatus;
	unsigned char WpaState;
	unsigned char GTKState;
	unsigned short PortSecured;
	NDIS_802_11_PRIVACY_FILTER PrivacyFilter;	/* PrivacyFilter enum for 802.1X */
	CIPHER_KEY PairwiseKey;
	void *pAd;
	int PMKID_CacheIdx;
	unsigned char PMKID[LEN_PMKID];
	unsigned char NegotiatedAKM[LEN_OUI_SUITE];	/* It indicate the negotiated AKM suite */


	unsigned char Addr[MAC_ADDR_LEN];
	unsigned char HdrAddr1[MAC_ADDR_LEN];
	unsigned char HdrAddr2[MAC_ADDR_LEN];
	unsigned char HdrAddr3[MAC_ADDR_LEN];
	unsigned char PsMode;
	unsigned char FlgPsModeIsWakeForAWhile; /* wake up for a while until a condition */
	unsigned char VirtualTimeout; /* peer power save virtual timeout */
	SST Sst;
	AUTH_STATE AuthState;	/* for SHARED KEY authentication state machine used only */
	unsigned char IsReassocSta;	/* Indicate whether this is a reassociation procedure */
	unsigned short Aid;
	unsigned short CapabilityInfo;
	unsigned char LastRssi;
	unsigned long NoDataIdleCount;
	unsigned short StationKeepAliveCount;	/* unit: second */
	unsigned long PsQIdleCount;
	QUEUE_HEADER PsQueue;

	unsigned int StaConnectTime;	/* the live time of this station since associated with AP */
	unsigned int StaIdleTimeout;	/* idle timeout per entry */

#ifdef UAPSD_SUPPORT
	/* these UAPSD states are used on the fly */
	/* 0:AC_BK, 1:AC_BE, 2:AC_VI, 3:AC_VO */
	unsigned char bAPSDCapablePerAC[4];	/* for trigger-enabled */
	unsigned char bAPSDDeliverEnabledPerAC[4];	/* for delivery-enabled */


	unsigned char MaxSPLength;

	unsigned char bAPSDAllAC;	/* 1: all AC are delivery-enabled U-APSD */

	struct list_head UAPSDQueue[WMM_NUM_OF_AC];	/* queue for each U-APSD */
	unsigned short UAPSDQIdleCount;	/* U-APSD queue timeout */

	PQUEUE_ENTRY pUAPSDEOSPFrame;	/* the last U-APSD frame */
	unsigned short UAPSDTxNum;	/* total U-APSD frame number */
	unsigned char bAPSDFlagEOSPOK;	/* 1: EOSP frame is tx by ASIC */
	unsigned char bAPSDFlagSPStart;	/* 1: SP is started */

	/* need to use unsigned long, because time parameters in OS is defined as
	   unsigned long */
	unsigned long UAPSDTimeStampLast;	/* unit: 1000000/OS_HZ */
	unsigned char bAPSDFlagSpRoughUse;	/* 1: use rough SP (default: accurate) */

	/* we will set the flag when PS-poll frame is received and
	   clear it when statistics handle.
	   if the flag is set when PS-poll frame is received then calling
	   statistics handler to clear it. */
	unsigned char bAPSDFlagLegacySent;	/* 1: Legacy PS sent but
					   yet statistics handle */

#ifdef RTMP_MAC_USB
	unsigned int UAPSDTagOffset[WMM_NUM_OF_AC];
#endif /* RTMP_MAC_USB */
#endif /* UAPSD_SUPPORT */

#ifdef DOT11_N_SUPPORT
	unsigned char bSendBAR;
	unsigned short NoBADataCountDown;

	unsigned int CachedBuf[16];	/* unsigned int (4 bytes) for alignment */

#ifdef TXBF_SUPPORT
	COUNTER_TXBF TxBFCounters;		/* TxBF Statistics */
	unsigned int LastETxCount;		/* Used to compute %BF statistics */
	unsigned int LastITxCount;
	unsigned int LastTxCount;
#endif /* TXBF_SUPPORT */
#endif /* DOT11_N_SUPPORT */

#ifdef STREAM_MODE_SUPPORT
	unsigned int StreamModeMACReg;	/* MAC reg used to control stream mode for this client. 0=>No stream mode */
#endif // STREAM_MODE_SUPPORT //

	unsigned int FIFOCount;
	unsigned int DebugFIFOCount;
	unsigned int DebugTxCount;
	unsigned char bDlsInit;

/*==================================================== */
/* WDS entry needs these */
/* If ValidAsWDS==TRUE, MatchWDSTabIdx is the index in WdsTab.MacTab */
	unsigned int MatchWDSTabIdx;
	unsigned char MaxSupportedRate;
	unsigned char CurrTxRate;
	unsigned char CurrTxRateIndex;
	unsigned char lastRateIdx;
	unsigned char *pTable;	/* Pointer to this entry's Tx Rate Table */

#ifdef NEW_RATE_ADAPT_SUPPORT
	unsigned char lowTrafficCount;
	unsigned char fewPktsCnt;
	unsigned char perThrdAdj;
	unsigned char mcsGroup;/* the mcs group to be tried */
#endif /* NEW_RATE_ADAPT_SUPPORT */
	enum RATE_ADAPT_ALG rateAlg;

#ifdef MFB_SUPPORT
	unsigned char lastLegalMfb;	/* last legal mfb which is used to set rate */
	unsigned char isMfbChanged;	/* purpose: true when mfb has changed but the new mfb is not adopted for Tx */
	struct _RTMP_RA_LEGACY_TB *LegalMfbRS;
	unsigned char fLastChangeAccordingMfb;
	NDIS_SPIN_LOCK fLastChangeAccordingMfbLock;
/* Tx MRQ */
	unsigned char toTxMrq;
	unsigned char msiToTx, mrqCnt;	/*mrqCnt is used to count down the inverted-BF mrq to be sent */
/* Rx mfb */
	unsigned char pendingMfsi;
/* Tx MFB */
	unsigned char toTxMfb;
	unsigned char	mfbToTx;
	unsigned char	mfb0, mfb1;
#endif	/* MFB_SUPPORT */
#ifdef TXBF_SUPPORT
	unsigned char			TxSndgType;
	NDIS_SPIN_LOCK	TxSndgLock;

/* ETxBF */
	unsigned char		bfState;
	unsigned char		sndgMcs;
	unsigned char		sndgBW;
	int			sndg0Snr0, sndg0Snr1, sndg0Snr2;
	unsigned char		sndg0Mcs;
#ifdef ETXBF_EN_COND3_SUPPORT
	unsigned char		bestMethod;
	unsigned char		sndgRateIdx;
	unsigned char		bf0Mcs, sndg0RateIdx, bf0RateIdx;
	unsigned char		sndg1Mcs, bf1Mcs, sndg1RateIdx, bf1RateIdx;
	int			sndg1Snr0, sndg1Snr1, sndg1Snr2;
#endif /* ETXBF_EN_COND3_SUPPORT */
	unsigned char		noSndgCnt;
	unsigned char		eTxBfEnCond;
	unsigned char		noSndgCntThrd, ndpSndgStreams;
	unsigned char		iTxBfEn;

	unsigned char		phyETxBf;			/* True=>Set ETxBF bit in PHY rate */
	unsigned char		phyITxBf;			/* True=>Set ITxBF bit in PHY rate */
	unsigned char		lastNonBfRate;		/* Last good non-BF rate */
	unsigned char		lastRatePhyTxBf;	/* For Quick Check. True if last rate was BF */
	unsigned short      BfTxQuality[MAX_TX_RATE_INDEX + 1];	/* Beamformed TX Quality */
#endif /* TXBF_SUPPORT */

	/* to record the each TX rate's quality. 0 is best, the bigger the worse. */
	unsigned short      TxQuality[MAX_TX_RATE_INDEX + 1];
	unsigned int 	OneSecTxNoRetryOkCount;
	unsigned int      OneSecTxRetryOkCount;
	unsigned int      OneSecTxFailCount;
	unsigned int      OneSecRxLGICount;		/* unicast-to-me Long GI count */
	unsigned int      OneSecRxSGICount;      	/* unicast-to-me short GI count */

#ifdef FIFO_EXT_SUPPORT
	unsigned int 	fifoTxSucCnt;
	unsigned int 	fifoTxRtyCnt;
#endif /* FIFO_EXT_SUPPORT */


	unsigned char fLastSecAccordingRSSI;
	unsigned char LastSecTxRateChangeAction;	/* 0: no change, 1:rate UP, 2:rate down */
	char LastTimeTxRateChangeAction;	/* Keep last time value of LastSecTxRateChangeAction */
	unsigned long LastTxOkCount; /* TxSuccess count in last Rate Adaptation interval */
	unsigned char LastTxPER;	/* Tx PER in last Rate Adaptation interval */
	unsigned char PER[MAX_TX_RATE_INDEX + 1];

	unsigned int ContinueTxFailCnt;
	unsigned int CurrTxRateStableTime;	/* # of second in current TX rate */
	unsigned char TxRateUpPenalty;	/* extra # of second penalty due to last unstable condition */
#ifdef WDS_SUPPORT
	unsigned char LockEntryTx;	/* TRUE = block to WDS Entry traffic, FALSE = not. */
#endif /* WDS_SUPPORT */
	unsigned long TimeStamp_toTxRing;

/*==================================================== */



#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
	unsigned int MatchDlsEntryIdx;	/* indicate the index in pAd->StaCfg.DLSEntry */
#endif /* QOS_DLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

	/*
		A bitmap of unsigned char flags. each bit represent an operation status of a particular
		unsigned char control, either ON or OFF. These flags should always be accessed via
		CLIENT_STATUS_TEST_FLAG(), CLIENT_STATUS_SET_FLAG(), CLIENT_STATUS_CLEAR_FLAG() macros.
		see fOP_STATUS_xxx in RTMP_DEF.C for detail bit definition. fCLIENT_STATUS_AMSDU_INUSED
	*/
	unsigned long ClientStatusFlags;

	HTTRANSMIT_SETTING HTPhyMode, MaxHTPhyMode, MinHTPhyMode;	/* For transmit phy setting in TXWI. */

#ifdef DOT11_N_SUPPORT
	/* HT EWC MIMO-N used parameters */
	unsigned short RXBAbitmap;	/* fill to on-chip  RXWI_BA_BITMASK in 8.1.3RX attribute entry format */
	unsigned short TXBAbitmap;	/* This bitmap as originator, only keep in software used to mark AMPDU bit in TXWI */
	unsigned short TXAutoBAbitmap;
	unsigned short BADeclineBitmap;
	unsigned short BARecWcidArray[NUM_OF_TID];	/* The mapping wcid of recipient session. if RXBAbitmap bit is masked */
	unsigned short BAOriWcidArray[NUM_OF_TID];	/* The mapping wcid of originator session. if TXBAbitmap bit is masked */
	unsigned short BAOriSequence[NUM_OF_TID];	/* The mapping wcid of originator session. if TXBAbitmap bit is masked */

	/* 802.11n features. */
	unsigned char MpduDensity;
	unsigned char MaxRAmpduFactor;
	unsigned char AMsduSize;
	unsigned char MmpsMode;		/* MIMO power save more. */

	HT_CAPABILITY_IE HTCapability;

#ifdef DOT11N_DRAFT3
	unsigned char BSS2040CoexistenceMgmtSupport;
	unsigned char bForty_Mhz_intolerant;
#endif /* DOT11N_DRAFT3 */

#ifdef DOT11_VHT_AC
	VHT_CAP_IE vht_cap_ie;
#endif /* DOT11_VHT_AC */

#endif /* DOT11_N_SUPPORT */


	unsigned char bAutoTxRateSwitch;

	unsigned char RateLen;
	struct _MAC_TABLE_ENTRY *pNext;
	unsigned short TxSeq[NUM_OF_TID];
	unsigned short NonQosDataSeq;

	RSSI_SAMPLE RssiSample;
	unsigned int LastRxRate;
	short freqOffset;		/* Last RXWI FOFFSET */
	short freqOffsetValid;	/* Set when freqOffset field has been updated */


	unsigned char bWscCapable;
	unsigned char Receive_EapolStart_EapRspId;

	unsigned int TXMCSExpected[MAX_MCS_SET];
	unsigned int TXMCSSuccessful[MAX_MCS_SET];
	unsigned int TXMCSFailed[MAX_MCS_SET];
	unsigned int TXMCSAutoFallBack[MAX_MCS_SET][MAX_MCS_SET];

#ifdef CONFIG_STA_SUPPORT
	unsigned long LastBeaconRxTime;
#endif /* CONFIG_STA_SUPPORT */



	unsigned long AssocDeadLine;




	unsigned long ChannelQuality;	/* 0..100, Channel Quality Indication for Roaming */


#ifdef VENDOR_FEATURE1_SUPPORT
	/* total 128B, use unsigned int to avoid alignment problem */
	unsigned int HeaderBuf[32];	/* (total 128B) TempBuffer for TX_INFO + TX_WI + 802.11 Header + padding + AMSDU SubHeader + LLC/SNAP */

	unsigned char HdrPadLen;	/* recording Header Padding Length; */
	unsigned char MpduHeaderLen;
	unsigned short Protocol;
#endif /* VENDOR_FEATURE1_SUPPORT */

#ifdef AGS_SUPPORT
	AGS_CONTROL AGSCtrl;	/* AGS control */
#endif /* AGS_SUPPORT */

#ifdef WFD_SUPPORT
	unsigned char bWfdClient;
#endif /* WFD_SUPPORT */

unsigned char	SupportRateMode; /* 1: CCK 2:OFDM 4: HT, 8:VHT */
unsigned char SupportCCKMCS[MAX_LEN_OF_CCK_RATES];
unsigned char SupportOFDMMCS[MAX_LEN_OF_OFDM_RATES];
unsigned char SupportHTMCS[MAX_LEN_OF_HT_RATES];


#ifdef DOT11_VHT_AC
	unsigned char SupportVHTMCS[MAX_LEN_OF_VHT_RATES];
#endif /* DOT11_VHT_AC */

#ifdef WFA_VHT_PF
#ifdef IP_ASSEMBLY
	struct list_head ip_queue1[4];
	int ip_id1[4];
	int ip_id1_FragSize[4];
	unsigned long ip_pkt1_jiffies[4];

	struct list_head ip_queue2[4];
	int ip_id2[4];
	int ip_id2_FragSize[4];
	unsigned long ip_pkt2_jiffies[4];
	
	struct ip_frag_q ip_fragQ[2];
	unsigned char ip_queue_inited;
#endif /* IP_ASSEMBLY */
#endif /* WFA_VHT_PF */

#ifdef MAC_REPEATER_SUPPORT
	unsigned char ExtAid;
	unsigned char ClientType; /* 0x00: apcli, 0x01: wireless station, 0x02: ethernet entry */
	unsigned char bConnToRootAP;
#endif /* MAC_REPEATER_SUPPORT */
} MAC_TABLE_ENTRY, *PMAC_TABLE_ENTRY;


typedef struct _MAC_TABLE {
	MAC_TABLE_ENTRY *Hash[HASH_TABLE_SIZE];
	MAC_TABLE_ENTRY Content[MAX_LEN_OF_MAC_TABLE];
	unsigned short Size;
	QUEUE_HEADER McastPsQueue;
	unsigned long PsQIdleCount;
	unsigned char fAnyStationInPsm;
	unsigned char fAnyStationBadAtheros;	/* Check if any Station is atheros 802.11n Chip.  We need to use RTS/CTS with Atheros 802,.11n chip. */
	unsigned char fAnyTxOPForceDisable;	/* Check if it is necessary to disable BE TxOP */
	unsigned char fAllStationAsRalink;	/* Check if all stations are ralink-chipset */
#ifdef DOT11_N_SUPPORT
	unsigned char fAnyStationIsLegacy;	/* Check if I use legacy rate to transmit to my BSS Station/ */
	unsigned char fAnyStationNonGF;	/* Check if any Station can't support GF. */
	unsigned char fAnyStation20Only;	/* Check if any Station can't support GF. */
	unsigned char fAnyStationMIMOPSDynamic;	/* Check if any Station is MIMO Dynamic */
	unsigned char fAnyBASession;	/* Check if there is BA session.  Force turn on RTS/CTS */
	unsigned char fAnyStaFortyintolerant;	/* Check if still has any station set the intolerant bit on! */
	unsigned char fAllStationGainGoodMCS; /* Check if all stations more than MCS threshold */

#endif				/* DOT11_N_SUPPORT */

	unsigned short			MsduLifeTime; /* life time for PS packet */

} MAC_TABLE, *PMAC_TABLE;



#ifdef BLOCK_NET_IF
typedef struct _BLOCK_QUEUE_ENTRY {
	unsigned char SwTxQueueBlockFlag;
	struct list_head NetIfList;
} BLOCK_QUEUE_ENTRY, *PBLOCK_QUEUE_ENTRY;
#endif /* BLOCK_NET_IF */


struct wificonf {
	unsigned char bShortGI;
	unsigned char bGreenField;
};

typedef struct _RTMP_DEV_INFO_ {
	unsigned char chipName[16];
	RTMP_INF_TYPE infType;
} RTMP_DEV_INFO;

#ifdef DBG_DIAGNOSE
#define DIAGNOSE_TIME	10	/* 10 sec */
typedef struct _RtmpDiagStrcut_ {	/* Diagnosis Related element */
	unsigned char inited;
	unsigned char qIdx;
	unsigned char ArrayStartIdx;
	unsigned char ArrayCurIdx;
	/* Tx Related Count */
	unsigned short TxDataCnt[DIAGNOSE_TIME];
	unsigned short TxFailCnt[DIAGNOSE_TIME];
/*	unsigned short TxDescCnt[DIAGNOSE_TIME][16];		// TxDesc queue length in scale of 0~14, >=15 */
	unsigned short TxDescCnt[DIAGNOSE_TIME][24];	/* 3*3    // TxDesc queue length in scale of 0~14, >=15 */
/*	unsigned short TxMcsCnt[DIAGNOSE_TIME][16];			// TxDate MCS Count in range from 0 to 15, step in 1. */
	unsigned short TxMcsCnt[DIAGNOSE_TIME][MAX_MCS_SET];	/* 3*3 */
	unsigned short TxSWQueCnt[DIAGNOSE_TIME][9];	/* TxSwQueue length in scale of 0, 1, 2, 3, 4, 5, 6, 7, >=8 */

	unsigned short TxAggCnt[DIAGNOSE_TIME];
	unsigned short TxNonAggCnt[DIAGNOSE_TIME];
/*	unsigned short TxAMPDUCnt[DIAGNOSE_TIME][16];		// 10 sec, TxDMA APMDU Aggregation count in range from 0 to 15, in setp of 1. */
	unsigned short TxAMPDUCnt[DIAGNOSE_TIME][MAX_MCS_SET];	/* 3*3 // 10 sec, TxDMA APMDU Aggregation count in range from 0 to 15, in setp of 1. */
	unsigned short TxRalinkCnt[DIAGNOSE_TIME];	/* TxRalink Aggregation Count in 1 sec scale. */
	unsigned short TxAMSDUCnt[DIAGNOSE_TIME];	/* TxAMSUD Aggregation Count in 1 sec scale. */

	/* Rx Related Count */
	unsigned short RxDataCnt[DIAGNOSE_TIME];	/* Rx Total Data count. */
	unsigned short RxCrcErrCnt[DIAGNOSE_TIME];
/*	unsigned short			RxMcsCnt[DIAGNOSE_TIME][16];		// Rx MCS Count in range from 0 to 15, step in 1. */
	unsigned short RxMcsCnt[DIAGNOSE_TIME][MAX_MCS_SET];	/* 3*3 */
} RtmpDiagStruct;
#endif /* DBG_DIAGNOSE */

#if defined(RTMP_intERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 
/*
	The number of channels for per-channel Tx power offset
*/
#define NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET	14

/* The Tx power control using the internal ALC */
#ifdef RT8592
// TODO: shiang-6590, fix me for this ugly definition!
#define LOOKUP_TB_SIZE		45
#else
#define LOOKUP_TB_SIZE		33
#endif /* RT8592 */

typedef struct _TX_POWER_CONTROL {
	unsigned char binternalTxALC; /* internal Tx ALC */
	unsigned char bExtendedTssiMode; /* The extended TSSI mode (each channel has different Tx power if needed) */
	char PerChTxPwrOffset[NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET + 1]; /* Per-channel Tx power offset */
	char idxTxPowerTable; /* The index of the Tx power table for ant0 */
	char idxTxPowerTable2; /* The index of the Tx power table for ant1 */
	char RF_TX_ALC; /* 3390: RF R12[4:0]: Tx0 ALC, 3352: RF R47[4:0]: Tx0 ALC, 5390: RF R49[5:0]: Tx0 ALC */
	char MAC_PowerDelta; /* Tx power control over MAC 0x1314~0x1324 */
	char MAC_PowerDelta2; /* Tx power control for Tx1 */
	char TotalDeltaPower2; /* Tx power control for Tx1 */
#ifdef RTMP_TEMPERATURE_COMPENSATION
	int LookupTable[IEEE80211_BAND_NUMS][LOOKUP_TB_SIZE];
	int RefTemp[IEEE80211_BAND_NUMS];
	unsigned char TssiGain[IEEE80211_BAND_NUMS];
	/* Index offset, -7....25. */
	int LookupTableIndex;
#endif /* RTMP_TEMPERATURE_COMPENSATION */

} TX_POWER_CONTROL, *PTX_POWER_CONTROL;
#endif /* RTMP_intERNAL_TX_ALC || RTMP_TEMPERATURE_COMPENSATION */

/* */
/* The entry of transmit power control over MAC */
/* */
typedef struct _TX_POWER_CONTROL_OVER_MAC_ENTRY {
	unsigned short MACRegisterOffset;	/* MAC register offset */
	unsigned long RegisterValue;	/* Register value */
} TX_POWER_CONTROL_OVER_MAC_ENTRY, *PTX_POWER_CONTROL_OVER_MAC_ENTRY;

/* */
/* The maximum registers of transmit power control */
/* */
#define MAX_TX_PWR_CONTROL_OVER_MAC_REGISTERS 5



#ifdef MT76x0
#undef MAX_TX_PWR_CONTROL_OVER_MAC_REGISTERS
#define MAX_TX_PWR_CONTROL_OVER_MAC_REGISTERS	6
#endif /* MT76x0 */

/* */
/* The configuration of the transmit power control over MAC */
/* */
typedef struct _CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC {
	unsigned char NumOfEntries;	/* Number of entries */
	TX_POWER_CONTROL_OVER_MAC_ENTRY TxPwrCtrlOverMAC[MAX_TX_PWR_CONTROL_OVER_MAC_REGISTERS];
} CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC, *PCONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC;

/* */
/* The extension of the transmit power control over MAC */
/* */
typedef struct _TX_POWER_CONTROL_EXT_OVER_MAC {
	struct {
		unsigned long TxPwrCfg0;	/* MAC 0x1314 */
		unsigned long TxPwrCfg0Ext;	/* MAC 0x1390 */
		unsigned long TxPwrCfg1;	/* MAC 0x1318 */
		unsigned long TxPwrCfg1Ext;	/* MAC 0x1394 */
		unsigned long TxPwrCfg2;	/* MAC 0x131C */
		unsigned long TxPwrCfg2Ext;	/* MAC 0x1398 */
		unsigned long TxPwrCfg3;	/* MAC 0x1320 */
		unsigned long TxPwrCfg3Ext;	/* MAC 0x139C */
		unsigned long TxPwrCfg4;	/* MAC 0x1324 */
		unsigned long TxPwrCfg4Ext;	/* MAC 0x13A0 */
		unsigned long TxPwrCfg5;	/* MAC 0x1384 */
		unsigned long TxPwrCfg6;	/* MAC 0x1388 */
		unsigned long TxPwrCfg7;	/* MAC 0x13D4 */
		unsigned long TxPwrCfg8;	/* MAC 0x13D8 */
		unsigned long TxPwrCfg9;	/* MAC 0x13DC */
	} BW20Over2Dot4G;

	struct {
		unsigned long TxPwrCfg0;	/* MAC 0x1314 */
		unsigned long TxPwrCfg0Ext;	/* MAC 0x1390 */
		unsigned long TxPwrCfg1;	/* MAC 0x1318 */
		unsigned long TxPwrCfg1Ext;	/* MAC 0x1394 */
		unsigned long TxPwrCfg2;	/* MAC 0x131C */
		unsigned long TxPwrCfg2Ext;	/* MAC 0x1398 */
		unsigned long TxPwrCfg3;	/* MAC 0x1320 */
		unsigned long TxPwrCfg3Ext;	/* MAC 0x139C */
		unsigned long TxPwrCfg4;	/* MAC 0x1324 */
		unsigned long TxPwrCfg4Ext;	/* MAC 0x13A0 */
		unsigned long TxPwrCfg5;	/* MAC 0x1384 */
		unsigned long TxPwrCfg6;	/* MAC 0x1388 */
		unsigned long TxPwrCfg7;	/* MAC 0x13D4 */
		unsigned long TxPwrCfg8;	/* MAC 0x13D8 */
		unsigned long TxPwrCfg9;	/* MAC 0x13DC */
	} BW40Over2Dot4G;

	struct {
		unsigned long TxPwrCfg0;	/* MAC 0x1314 */
		unsigned long TxPwrCfg0Ext;	/* MAC 0x1390 */
		unsigned long TxPwrCfg1;	/* MAC 0x1318 */
		unsigned long TxPwrCfg1Ext;	/* MAC 0x1394 */
		unsigned long TxPwrCfg2;	/* MAC 0x131C */
		unsigned long TxPwrCfg2Ext;	/* MAC 0x1398 */
		unsigned long TxPwrCfg3;	/* MAC 0x1320 */
		unsigned long TxPwrCfg3Ext;	/* MAC 0x139C */
		unsigned long TxPwrCfg4;	/* MAC 0x1324 */
		unsigned long TxPwrCfg4Ext;	/* MAC 0x13A0 */
		unsigned long TxPwrCfg5;	/* MAC 0x1384 */
		unsigned long TxPwrCfg6;	/* MAC 0x1388 */
		unsigned long TxPwrCfg7;	/* MAC 0x13D4 */
		unsigned long TxPwrCfg8;	/* MAC 0x13D8 */
		unsigned long TxPwrCfg9;	/* MAC 0x13DC */
	} BW20Over5G;

	struct {
		unsigned long TxPwrCfg0;	/* MAC 0x1314 */
		unsigned long TxPwrCfg0Ext;	/* MAC 0x1390 */
		unsigned long TxPwrCfg1;	/* MAC 0x1318 */
		unsigned long TxPwrCfg1Ext;	/* MAC 0x1394 */
		unsigned long TxPwrCfg2;	/* MAC 0x131C */
		unsigned long TxPwrCfg2Ext;	/* MAC 0x1398 */
		unsigned long TxPwrCfg3;	/* MAC 0x1320 */
		unsigned long TxPwrCfg3Ext;	/* MAC 0x139C */
		unsigned long TxPwrCfg4;	/* MAC 0x1324 */
		unsigned long TxPwrCfg4Ext;	/* MAC 0x13A0 */
		unsigned long TxPwrCfg5;	/* MAC 0x1384 */
		unsigned long TxPwrCfg6;	/* MAC 0x1388 */
		unsigned long TxPwrCfg7;	/* MAC 0x13D4 */
		unsigned long TxPwrCfg8;	/* MAC 0x13D8 */
		unsigned long TxPwrCfg9;	/* MAC 0x13DC */
	} BW40Over5G;
} TX_POWER_CONTROL_EXT_OVER_MAC, *PTX_POWER_CONTROL_EXT_OVER_MAC;

/* For Wake on Wireless LAN */
#ifdef WOW_SUPPORT
#ifdef RTMP_MAC_USB
typedef struct _WOW_CFG_STRUCT {
	unsigned char			bEnable;		/* Enable WOW function*/
	unsigned char			bWOWFirmware;	/* Enable WOW function, trigger to reload WOW-support firmware */
	unsigned char			nSelectedGPIO;	/* Side band signal to wake up system */
	unsigned char			nDelay;			/* Delay number is multiple of 3 secs, and it used to postpone the WOW function */
	unsigned char           nHoldTime;      /* GPIO puls hold time, unit: 10ms */
} WOW_CFG_STRUCT, *PWOW_CFG_STRUCT;
#endif /* RTMP_MAC_USB */
#endif /* WOW_SUPPORT */

/*
	Packet drop reason code
*/
typedef enum{
	PKT_ATE_ON = 1 << 8,
	PKT_RADAR_ON = 2 << 8,
	PKT_RRM_QUIET = 3 << 8,
	PKT_TX_STOP = 4 <<8,
	PKT_TX_JAM = 5 << 8,

	PKT_NETDEV_DOWN = 6 < 8,
	PKT_NETDEV_NO_MATCH = 7 << 8,
	PKT_NOT_ALLOW_SEND = 8 << 8,

	PKT_INVALID_DST = 9<< 8,
	PKT_INVALID_SRC = 10 << 8,
	PKT_INVALID_PKT_DATA = 11 << 8,
	PKT_INVALID_PKT_LEN = 12 << 8,
	PKT_INVALID_ETH_TYPE = 13 << 8,
	PKT_INVALID_TXBLK_INFO = 14 << 8,
	PKT_INVALID_SW_ENCRYPT = 15 << 8,
	PKT_INVALID_PKT_TYPE = 16 << 8,
	PKT_INVALID_PKT_MIC = 17 << 8,
	
	PKT_PORT_NOT_SECURE = 18 << 8,
	PKT_TSPEC_NO_MATCH  = 19 << 8,
	PKT_NO_ASSOCED_STA = 20 << 8,
	PKT_INVALID_MAC_ENTRY = 21 << 8,
	
	PKT_TX_QUE_FULL = 22 << 8,
	PKT_TX_QUE_ADJUST = 23<<8,
		
	PKT_PS_QUE_TIME= 24 <<8,
	PKT_PS_QUE_CLEAN = 25 << 8,
	PKT_MCAST_PS_QUE_FULL = 26 << 8,
	PKT_UCAST_PS_QUE_FULL = 27 << 8,
	
	PKT_RX_EAPOL_SANITY_FAIL = 28 <<8,
	PKT_RX_NOT_TO_KERNEL = 29 << 8,
	PKT_RX_MESH_SIG_FAIL = 30 << 8,
	PKT_APCLI_FAIL = 31 << 8,
	PKT_ZERO_DATA = 32 <<8,
	PKT_SW_DECRYPT_FAIL = 33 << 8,
	PKT_TX_SW_ENC_FAIL = 34 << 8,

	PKT_ACM_FAIL = 35 << 8,
	PKT_IGMP_GRP_FAIL = 36 << 8,
	PKT_MGMT_FAIL = 37 << 8,
	PKT_AMPDU_OUT_ORDER = 38 << 8,
	PKT_UAPSD_EOSP = 39 << 8,
	PKT_UAPSD_Q_FULL = 40 << 8,

	PKT_DRO_REASON_MAX = 41,
}PKT_DROP_REASON;

/* Packet drop Direction code */
typedef enum{
	PKT_TX = 0,
	PKT_RX = 1 << 31,
}PKT_DROP_DIECTION;




typedef struct _BBP_RESET_CTL
{
#define BBP_RECORD_NUM	47
	RTMP_REG_PAIR BBPRegDB[BBP_RECORD_NUM];
	unsigned char	AsicCheckEn;
} BBP_RESET_CTL, *PBBP_RESET_CTL;


typedef struct tx_agc_ctrl{
	unsigned char bAutoTxAgc;	/* Enable driver auto Tx Agc control */
	unsigned char TssiRef;		/* Store Tssi reference value as 25 temperature. */
	unsigned char TssiPlusBoundary[5];	/* Tssi boundary for increase Tx power to compensate. */
	unsigned char TssiMinusBoundary[5];	/* Tssi boundary for decrease Tx power to compensate. */
	unsigned char TxAgcStep;	/* Store Tx TSSI delta increment / decrement value */
	char TxAgcComp;	/* Store the compensation (TxAgcStep * (idx-1)) */
}TX_AGC_CTRL;


/*
	The miniport adapter structure
*/
struct _RTMP_ADAPTER {
	void *OS_Cookie;	/* save specific structure relative to OS */
	struct net_device * net_dev;
	unsigned long VirtualIfCnt;

	//unsigned char PollIdle;

	RTMP_CHIP_OP chipOps;
	RTMP_CHIP_CAP chipCap;

#ifdef CONFIG_STA_SUPPORT
	unsigned short ThisTbttNumToNextWakeUp;
#endif /* CONFIG_STA_SUPPORT */

#ifdef HOSTAPD_SUPPORT
	unsigned int IoctlIF;
#endif /* HOSTAPD_SUPPORT */
#ifdef INF_PPA_SUPPORT
	unsigned int g_if_id;
	unsigned char PPAEnable;
	PPA_DIRECTPATH_CB *pDirectpathCb;
#endif /* INF_PPA_SUPPORT */


	NDIS_SPIN_LOCK irq_lock;

	/*======Cmd Thread in PCI/RBUS/USB */
	CmdQ CmdQ;
	NDIS_SPIN_LOCK CmdQLock;	/* CmdQLock spinlock */
	RTMP_OS_TASK cmdQTask;

#ifdef RTMP_MAC_USB
/*****************************************************************************************/
/*      USB related parameters                                                           */
/*****************************************************************************************/
/*	struct usb_config_descriptor		*config; */
	void*config;

	unsigned int NumberOfPipes;
	unsigned short BulkOutMaxPacketSize;
	unsigned short BulkInMaxPacketSize;
	unsigned char BulkOutEpAddr[6];
	unsigned char BulkInEpAddr[2]; 

	/*======Control Flags */
	unsigned long BulkFlags;
	unsigned char bUsbTxBulkAggre;	/* Flags for bulk out data priority */

	/*======Cmd Thread */
/*	CmdQ					CmdQ; */
/*	NDIS_SPIN_LOCK			CmdQLock;				// CmdQLock spinlock */
/*	RTMP_OS_TASK			cmdQTask; */

	/*======Semaphores (event) */
	RTMP_OS_SEM UsbVendorReq_semaphore;
	RTMP_OS_SEM reg_atomic;
	RTMP_OS_SEM hw_atomic;
	RTMP_OS_SEM cal_atomic;
	RTMP_OS_SEM wlan_en_atomic;
	RTMP_OS_SEM mcu_atomic;
	void *UsbVendorReqBuf;
/*	wait_queue_head_t	 *wait; */
	void*wait;

	/* lock for ATE */
#ifdef RALINK_ATE
	NDIS_SPIN_LOCK GenericLock;	/* ATE Tx/Rx generic spinlock */
#endif /* RALINK_ATE */

#endif /* RTMP_MAC_USB */

/*****************************************************************************************/
/*      RBUS related parameters                                                           								  */
/*****************************************************************************************/

/*****************************************************************************************/
/*      Both PCI/USB related parameters                                                  							  */
/*****************************************************************************************/
	/*RTMP_DEV_INFO                 chipInfo; */
	RTMP_INF_TYPE infType;

/*****************************************************************************************/
/*      Driver Mgmt related parameters                                                  							  */
/*****************************************************************************************/
	RTMP_OS_TASK mlmeTask;
#ifdef RTMP_TIMER_TASK_SUPPORT
	/* If you want use timer task to handle the timer related jobs, enable this. */
	RTMP_TIMER_TASK_QUEUE TimerQ;
	NDIS_SPIN_LOCK TimerQLock;
	RTMP_OS_TASK timerTask;
#endif /* RTMP_TIMER_TASK_SUPPORT */

/*****************************************************************************************/
/*      Tx related parameters                                                           */
/*****************************************************************************************/
	unsigned char DeQueueRunning[NUM_OF_TX_RING];	/* for ensuring RTUSBDeQueuePacket get call once */
	NDIS_SPIN_LOCK DeQueueLock[NUM_OF_TX_RING];

#ifdef RTMP_MAC_USB
	/* Data related context and AC specified, 4 AC supported */
	NDIS_SPIN_LOCK BulkOutLock[6];	/* BulkOut spinlock for 4 ACs */
	NDIS_SPIN_LOCK MLMEBulkOutLock;	/* MLME BulkOut lock */

	HT_TX_CONTEXT TxContext[NUM_OF_TX_RING];
	NDIS_SPIN_LOCK TxContextQueueLock[NUM_OF_TX_RING];	/* TxContextQueue spinlock */

	/* 4 sets of Bulk Out index and pending flag */
	/*
	   array size of NextBulkOutIndex must be larger than or equal to 5;
	   Or BulkOutPending[0] will be overwrited in NICInitTransmit().
	 */
	unsigned char NextBulkOutIndex[NUM_OF_TX_RING];	/* only used for 4 EDCA bulkout pipe */

	unsigned char BulkOutPending[6];	/* used for total 6 bulkout pipe */
	unsigned char bulkResetPipeid;
	unsigned char MgmtBulkPending;
	unsigned long bulkResetReq[6];
#ifdef INF_AMAZON_SE
	unsigned long BulkOutDataSizeCount[NUM_OF_TX_RING];
	unsigned char BulkOutDataFlag[NUM_OF_TX_RING];
	unsigned long BulkOutDataSizeLimit[NUM_OF_TX_RING];
	unsigned char RunningQueueNoCount;
	unsigned char LastRunningQueueNo;
#endif /* #ifdef INF_AMAZON_SE */

#ifdef CONFIG_STA_SUPPORT
	unsigned short CountDowntoPsm;
#endif /* CONFIG_STA_SUPPORT */

#endif /* RTMP_MAC_USB */

	/* resource for software backlog queues */
	QUEUE_HEADER TxSwQueue[NUM_OF_TX_RING];	/* 4 AC + 1 HCCA */
	NDIS_SPIN_LOCK TxSwQueueLock[NUM_OF_TX_RING];	/* TxSwQueue spinlock */

	/* Maximum allowed tx software Queue length */
	unsigned int 				TxSwQMaxLen;

	RTMP_DMABUF MgmtDescRing;	/* Shared memory for MGMT descriptors */
	RTMP_MGMT_RING MgmtRing;
	NDIS_SPIN_LOCK MgmtRingLock;	/* Prio Ring spinlock */

#ifdef CONFIG_ANDES_SUPPORT
	RTMP_CTRL_RING CtrlRing;
	NDIS_SPIN_LOCK CtrlRingLock;	/* Ctrl Ring spinlock */
#endif

	unsigned char LastMCUCmd;

/*****************************************************************************************/
/*      Rx related parameters                                                           */
/*****************************************************************************************/


#ifdef RTMP_MAC_USB
	RX_CONTEXT RxContext[RX_RING_SIZE];	/* 1 for redundant multiple IRP bulk in. */
	NDIS_SPIN_LOCK BulkInLock;	/* BulkIn spinlock for 4 ACs */
	NDIS_SPIN_LOCK CmdRspLock;
	unsigned char PendingRx;	/* The Maximum pending Rx value should be       RX_RING_SIZE. */
	unsigned char NextRxBulkInIndex;	/* Indicate the current RxContext Index which hold by Host controller. */
	unsigned char NextRxBulkInReadIndex;	/* Indicate the current RxContext Index which driver can read & process it. */
	unsigned long NextRxBulkInPosition;	/* Want to contatenate 2 URB buffer while 1st is bulkin failed URB. This Position is 1st URB TransferLength. */
	unsigned long TransferBufferLength;	/* current length of the packet buffer */
	unsigned long ReadPosition;	/* current read position in a packet buffer */

	CMD_RSP_CONTEXT CmdRspEventContext;
#endif /* RTMP_MAC_USB */

/*****************************************************************************************/
/*      ASIC related parameters                                                          */
/*****************************************************************************************/
	unsigned int MACVersion;	/* MAC version. Record rt2860C(0x28600100) or rt2860D (0x28600101).. */
	unsigned int MacIcVersion;

	/* --------------------------- */
	/* E2PROM */
	/* --------------------------- */
	unsigned long EepromVersion;	/* byte 0: version, byte 1: revision, byte 2~3: unused */
	unsigned long FirmwareVersion;	/* byte 0: Minor version, byte 1: Major version, otherwise unused. */
	unsigned short EEPROMDefaultValue[NUM_EEPROM_BBP_PARMS];
#ifdef TXBF_SUPPORT
	unsigned short EEPROMITxBFCalParams[6];
#endif /* TXBF_SUPPORT */
	unsigned char EEPROMAddressNum;	/* 93c46=6  93c66=8 */
	unsigned char EepromAccess;
	unsigned char EFuseTag;

	/* --------------------------- */
	/* BBP Control */
	/* --------------------------- */
	unsigned char BbpWriteLatch[MAX_BBP_ID + 1];	/* record last BBP register value written via BBP_IO_WRITE/BBP_IO_WRITE_VY_REG_ID */
	char BbpRssiToDbmDelta;	/* change from unsigned char to char for high power */
	BBP_R66_TUNING BbpTuning;

	/* ---------------------------- */
	/* RFIC control */
	/* ---------------------------- */
	unsigned char RfIcType;		/* RFIC_xxx */
	unsigned long RfFreqOffset;	/* Frequency offset for channel switching */


	RTMP_RF_REGS LatchRfRegs;	/* latch th latest RF programming value since RF IC doesn't support READ */

	EEPROM_ANTENNA_STRUC Antenna;	/* Since ANtenna definition is different for a & g. We need to save it for future reference. */
	EEPROM_NIC_CONFIG2_STRUC NicConfig2;
#if defined(BT_COEXISTENCE_SUPPORT) || defined(RT3290) || defined(RT8592)
	EEPROM_NIC_CONFIG3_STRUC NicConfig3;
#endif /* defined(BT_COEXISTENCE_SUPPORT) || defined(RT3290) || defined(RT8592) */

	/* This soft Rx Antenna Diversity mechanism is used only when user set */
	/* RX Antenna = DIVERSITY ON */
	SOFT_RX_ANT_DIVERSITY RxAnt;

	CHANNEL_TX_POWER TxPower[MAX_NUM_OF_CHANNELS];	/* Store Tx power value for all channels. */
	CHANNEL_TX_POWER ChannelList[MAX_NUM_OF_CHANNELS];	/* list all supported channels for site survey */



	unsigned char ChannelListNum;	/* number of channel in ChannelList[] */
	unsigned char Bbp94;
	unsigned char BbpForCCK;
	unsigned long Tx20MPwrCfgABand[MAX_TXPOWER_ARRAY_SIZE];
	unsigned long Tx20MPwrCfgGBand[MAX_TXPOWER_ARRAY_SIZE];
	unsigned long Tx40MPwrCfgABand[MAX_TXPOWER_ARRAY_SIZE];
	unsigned long Tx40MPwrCfgGBand[MAX_TXPOWER_ARRAY_SIZE];
#ifdef DOT11_VHT_AC
	unsigned long Tx80MPwrCfgABand[MAX_TXPOWER_ARRAY_SIZE]; // Per-rate Tx power control for VHT BW80 (5GHz only)
#endif /* DOT11_VHT_AC */


	unsigned char bAutoTxAgcA;	/* Enable driver auto Tx Agc control */
	unsigned char TssiRefA;		/* Store Tssi reference value as 25 temperature. */
	unsigned char TssiPlusBoundaryA[2][8];	/* Tssi boundary for increase Tx power to compensate. [Group][Boundary Index]*/
	unsigned char TssiMinusBoundaryA[2][8];	/* Tssi boundary for decrease Tx power to compensate. [Group][Boundary Index]*/
	unsigned char TxAgcStepA;	/* Store Tx TSSI delta increment / decrement value */
	char TxAgcCompensateA;	/* Store the compensation (TxAgcStep * (idx-1)) */

	unsigned char bAutoTxAgcG;	/* Enable driver auto Tx Agc control */
	unsigned char TssiRefG;		/* Store Tssi reference value as 25 temperature. */
	unsigned char TssiPlusBoundaryG[8];	/* Tssi boundary for increase Tx power to compensate. */
	unsigned char TssiMinusBoundaryG[8];	/* Tssi boundary for decrease Tx power to compensate. */
	unsigned char TxAgcStepG;	/* Store Tx TSSI delta increment / decrement value */
	char TxAgcCompensateG;	/* Store the compensation (TxAgcStep * (idx-1)) */

#ifdef RTMP_TEMPERATURE_TX_ALC
	char TssiCalibratedOffset;	/* reference temperature(e2p[D1h]) */  
	unsigned char ChBndryIdx;			/* 5G Channel Group Boundary Index for Temperature Compensation */

	char mp_delta_pwr;			 /* calculated by MP ATE temperature */
	char CurrTemperature;
	char DeltaPwrBeforeTempComp;
	char LastTempCompDeltaPwr;
#endif /* RTMP_TEMPERATURE_TX_ALC */

#if defined(RTMP_intERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 
	TX_POWER_CONTROL TxPowerCtrl;	/* The Tx power control using the internal ALC */
	char curr_temp;
	char rx_temp_base[2];	/* initial VGA value for chain 0/1,  used for base of rx temp compensation power base */
#endif /* RTMP_intERNAL_TX_ALC || RTMP_TEMPERATURE_COMPENSATION */


	signed char BGRssiOffset[3]; /* Store B/G RSSI #0/1/2 Offset value on EEPROM 0x46h */
	signed char ARssiOffset[3]; /* Store A RSSI 0/1/2 Offset value on EEPROM 0x4Ah */

	char BLNAGain;		/* Store B/G external LNA#0 value on EEPROM 0x44h */
	char ALNAGain0;		/* Store A external LNA#0 value for ch36~64 */
	char ALNAGain1;		/* Store A external LNA#1 value for ch100~128 */
	char ALNAGain2;		/* Store A external LNA#2 value for ch132~165 */


#ifdef LED_CONTROL_SUPPORT
	/* LED control */
	LED_CONTROL LedCntl;
#endif /* LED_CONTROL_SUPPORT */

	/* ---------------------------- */
	/* MAC control */
	/* ---------------------------- */

#ifdef RT8592
	char bw_cal[3];	// bw cal value for RF_R32, 0:20M, 1:40M, 2:80M
// TODO: shiang-6590, temporary get from windows and need to revise it!!
	/* IQ Calibration */
	unsigned char IQGaintx[3][4];
	unsigned char IQPhaseTx[3][4];
	unsigned short IQControl;
#endif /* RT8592 */

#if defined(RT3290) || defined(RT65xx)

	WLAN_FUN_CTRL_STRUC WlanFunCtrl;
#endif /* defined(RT3290) || defined(RT65xx) */
#ifdef RT3290
	// TODO: shiang, check about the purpose of this parameter
	CMB_CTRL_STRUC	CmbCtrl;
	WLAN_FUN_INFO_STRUC WlanFunInfo;
	BT_FUN_CTRL_STRUC BtFunCtrl;
	WLAN_BT_COEX_SETTING WlanBTCoexInfo;
	unsigned char RateUp;
	unsigned long AntennaDiversityState;/* 0->Stable state 1->training state */
	unsigned long AntennaDiversityPER[2];  // 0 ->main 1->aux
	unsigned long AntennaDiversityTxPacketCount[2];  // 0 ->main 1->aux	
	unsigned long AntennaDiversityRxPacketCount[2];
	unsigned long AntennaDiversityTrigger;
	unsigned long AntennaDiversityCount;
	unsigned long TrainCounter;
	ANT_DIVERSITY AntennaDiversityInfo;
#endif /* RT3290 */

	struct hw_setting hw_cfg;

/*****************************************************************************************/
/*      802.11 related parameters                                                        */
/*****************************************************************************************/
	/* outgoing BEACON frame buffer and corresponding TXD */
	TXWI_STRUC BeaconTxWI;
	unsigned char* BeaconBuf;
	unsigned short BeaconOffset[HW_BEACON_MAX_NUM];

	/* pre-build PS-POLL and NULL frame upon link up. for efficiency purpose. */
#ifdef CONFIG_STA_SUPPORT
	PSPOLL_FRAME PsPollFrame;
#endif /* CONFIG_STA_SUPPORT */
	HEADER_802_11 NullFrame;

#ifdef RTMP_MAC_USB
	TX_CONTEXT NullContext;
	TX_CONTEXT PsPollContext;
#endif /* RTMP_MAC_USB */


#ifdef UAPSD_SUPPORT
	NDIS_SPIN_LOCK UAPSDEOSPLock;	/* EOSP frame access lock use */
	unsigned char bAPSDFlagSPSuspend;	/* 1: SP is suspended; 0: SP is not */
#endif /* UAPSD_SUPPORT */

/*=========AP=========== */


#ifdef CONFIG_AP_SUPPORT
	/* ----------------------------------------------- */
	/* AP specific configuration & operation status */
	/* used only when pAd->OpMode == OPMODE_AP */
	/* ----------------------------------------------- */
	AP_ADMIN_CONFIG ApCfg;	/* user configuration when in AP mode */
	AP_MLME_AUX ApMlmeAux;



#ifdef MBSS_SUPPORT
	unsigned char FlgMbssInit;
#endif /* MBSS_SUPPORT */


#ifdef APCLI_SUPPORT
	unsigned char flg_apcli_init;
#endif /* APCLI_SUPPORT */

/*#ifdef AUTO_CH_SELECT_ENHANCE */
	PBSSINFO pBssInfoTab;
	PCHANNELINFO pChannelInfo;
/*#endif // AUTO_CH_SELECT_ENHANCE */


#endif /* CONFIG_AP_SUPPORT */



/*=======STA=========== */
#ifdef CONFIG_STA_SUPPORT
	/* ----------------------------------------------- */
	/* STA specific configuration & operation status */
	/* used only when pAd->OpMode == OPMODE_STA */
	/* ----------------------------------------------- */
	STA_ADMIN_CONFIG StaCfg;	/* user desired settings */
	STA_ACTIVE_CONFIG StaActive;	/* valid only when ADHOC_ON(pAd) || INFRA_ON(pAd) */
	char nickname[IW_ESSID_MAX_SIZE + 1];	/* nickname, only used in the iwconfig i/f */
	int PreMediaState;
#endif /* CONFIG_STA_SUPPORT */

/*=======Common=========== */
	/* OP mode: either AP or STA */
	unsigned char OpMode;		/* OPMODE_STA, OPMODE_AP */

	enum RATE_ADAPT_ALG rateAlg;		/* Rate adaptation algorithm */
	
	int IndicateMediaState;	/* Base on Indication state, default is NdisMediaStateDisConnected */

#ifdef PROFILE_STORE
	RTMP_OS_TASK 	WriteDatTask;
	unsigned char			bWriteDat;
#endif /* PROFILE_STORE */

#ifdef CREDENTIAL_STORE	
	STA_CONNECT_INFO StaCtIf;
#endif /* CREDENTIAL_STORE */



	/* MAT related parameters */


	/* 
		Frequency setting for rate adaptation 
			@ra_interval: 		for baseline time interval
			@ra_fast_interval:	for quick response time interval
	*/
	unsigned int 		ra_interval;
	unsigned int 		ra_fast_interval;

	/* configuration: read from Registry & E2PROM */
	unsigned char bLocalAdminMAC;	/* Use user changed MAC */
	unsigned char PermanentAddress[MAC_ADDR_LEN];	/* Factory default MAC address */
	unsigned char CurrentAddress[MAC_ADDR_LEN];	/* User changed MAC address */

	/* ------------------------------------------------------ */
	/* common configuration to both OPMODE_STA and OPMODE_AP */
	/* ------------------------------------------------------ */
	COMMON_CONFIG CommonCfg;
	MLME_STRUCT Mlme;

	/* AP needs those vaiables for site survey feature. */
	MLME_AUX MlmeAux;	/* temporary settings used during MLME state machine */
#if defined(AP_SCAN_SUPPORT) || defined(CONFIG_STA_SUPPORT)
	BSS_TABLE ScanTab;	/* store the latest SCAN result */
#endif /* defined(AP_SCAN_SUPPORT) || defined(CONFIG_STA_SUPPORT) */

	/*About MacTab, the sta driver will use #0 and #1 for multicast and AP. */
	MAC_TABLE MacTab;	/* ASIC on-chip WCID entry table.  At TX, ASIC always use key according to this on-chip table. */
	NDIS_SPIN_LOCK MacTabLock;

#ifdef DOT11_N_SUPPORT
	BA_TABLE BATable;
	NDIS_SPIN_LOCK BATabLock;
	RALINK_TIMER_STRUCT RECBATimer;
#endif /* DOT11_N_SUPPORT */

	/* DOT11_H */
	DOT11_H Dot11_H;

	/* encryption/decryption KEY tables */
	CIPHER_KEY SharedKey[HW_BEACON_MAX_NUM + MAX_P2P_NUM][4];	/* STA always use SharedKey[BSS0][0..3] */

	/* RX re-assembly buffer for fragmentation */
	FRAGMENT_FRAME FragFrame;	/* Frame storage for fragment frame */

	/* various Counters */
	COUNTER_802_3 Counters8023;	/* 802.3 counters */
	COUNTER_802_11 WlanCounters;	/* 802.11 MIB counters */
	COUNTER_RALINK RalinkCounters;	/* Ralink propriety counters */
	/* COUNTER_DRS DrsCounters;	*/ /* counters for Dynamic TX Rate Switching */
	PRIVATE_STRUC PrivateInfo;	/* Private information & counters */

	/* flags, see fRTMP_ADAPTER_xxx flags */
	unsigned long Flags;		/* Represent current device status */
	unsigned long PSFlags;		/* Power Save operation flag. */
	unsigned long MoreFlags;	/* Represent specific requirement */

	/* current TX sequence # */
	unsigned short Sequence;

	/* Control disconnect / connect event generation */
	/*+++Didn't used anymore */
	unsigned long LinkDownTime;
	/*--- */
	unsigned long LastRxRate;
	unsigned long LastTxRate;
	/*+++Used only for Station */
	unsigned char bConfigChanged;	/* Config Change flag for the same SSID setting */
	/*--- */

	unsigned long ExtraInfo;	/* Extra information for displaying status */
	unsigned long SystemErrorBitmap;	/* b0: E2PROM version error */

#ifdef SYSTEM_LOG_SUPPORT
	/* --------------------------- */
	/* System event log */
	/* --------------------------- */
	RT_802_11_EVENT_TABLE EventTab;
#endif /* SYSTEM_LOG_SUPPORT */

	unsigned char HTCEnable;

	/*****************************************************************************************/
	/*      Statistic related parameters                                                     */
	/*****************************************************************************************/
#ifdef RTMP_MAC_USB
	unsigned long BulkOutDataOneSecCount;
	unsigned long BulkInDataOneSecCount;
	unsigned long BulkLastOneSecCount;	/* BulkOutDataOneSecCount + BulkInDataOneSecCount */
	unsigned long watchDogRxCnt;
	unsigned long watchDogRxOverFlowCnt;
	unsigned long watchDogTxPendingCnt[NUM_OF_TX_RING];
#endif /* RTMP_MAC_USB */

	unsigned char bUpdateBcnCntDone;

	unsigned long macwd;
	/* ---------------------------- */
	/* DEBUG paramerts */
	/* ---------------------------- */

	/* ---------------------------- */
	/* rt2860c emulation-use Parameters */
	/* ---------------------------- */
	/*unsigned long         rtsaccu[30]; */
	/*unsigned long         ctsaccu[30]; */
	/*unsigned long         cfendaccu[30]; */
	/*unsigned long         bacontent[16]; */
	/*unsigned long         rxint[RX_RING_SIZE+1]; */
	/*unsigned char         rcvba[60]; */
	unsigned char bLinkAdapt;
	unsigned char bForcePrintTX;
	unsigned char bForcePrintRX;
	/*unsigned char               bDisablescanning;               //defined in RT2870 USB */
	unsigned char bStaFifoTest;
	unsigned char bProtectionTest;
	unsigned char bHCCATest;
	unsigned char bGenOneHCCA;
	unsigned char bBroadComHT;
	/*+++Following add from RT2870 USB. */
	unsigned long BulkOutReq;
	unsigned long BulkOutComplete;
	unsigned long BulkOutCompleteOther;
	unsigned long BulkOutCompleteCancel;	/* seems not use now? */
	unsigned long BulkInReq;
	unsigned long BulkInComplete;
	unsigned long BulkInCompleteFail;
	/*--- */

	struct wificonf WIFItestbed;

	unsigned char		TssiGain;
#ifdef RALINK_ATE
	ATE_INFO ate;
#ifdef RTMP_MAC_USB
	unsigned char ContinBulkOut;	/*ATE bulk out control */
	unsigned char ContinBulkIn;	/*ATE bulk in control */
	RTMP_OS_ATOMIC BulkOutRemained;
	RTMP_OS_ATOMIC BulkInRemained;
#endif /* RTMP_MAC_USB */
#endif /* RALINK_ATE */

#ifdef DOT11_N_SUPPORT
	struct reordering_mpdu_pool mpdu_blk_pool;
#endif /* DOT11_N_SUPPORT */

	/* statistics count */

	void*iw_stats;
	void*stats;

#ifdef BLOCK_NET_IF
	BLOCK_QUEUE_ENTRY blockQueueTab[NUM_OF_TX_RING];
#endif /* BLOCK_NET_IF */



#ifdef MULTIPLE_CARD_SUPPORT
	int MC_RowID;
	char MC_FileName[256];
#endif /* MULTIPLE_CARD_SUPPORT */

	unsigned long TbttTickCount;	/* beacon timestamp work-around */
#ifdef PCI_MSI_SUPPORT
	unsigned char HaveMsi;
#endif /* PCI_MSI_SUPPORT */


	/* for detect_wmm_traffic() BE TXOP use */
	unsigned long OneSecondnonBEpackets;	/* record non BE packets per second */
	unsigned char is_on;

	/* for detect_wmm_traffic() BE/BK TXOP use */
#define TIME_BASE			(1000000/OS_HZ)
#define TIME_ONE_SECOND		(1000000/TIME_BASE)
	unsigned char flg_be_adjust;
	unsigned long be_adjust_last_time;

#ifdef NintENDO_AP
	NINDO_CTRL_BLOCK nindo_ctrl_block;
#endif /* NintENDO_AP */


#ifdef IKANOS_VX_1X0
	struct IKANOS_TX_INFO IkanosTxInfo;
	struct IKANOS_TX_INFO IkanosRxInfo[HW_BEACON_MAX_NUM + MAX_WDS_ENTRY +
					   MAX_APCLI_NUM + MAX_MESH_NUM];
#endif /* IKANOS_VX_1X0 */


#ifdef DBG_DIAGNOSE
	RtmpDiagStruct DiagStruct;
#endif /* DBG_DIAGNOSE */


	unsigned char FlgCtsEnabled;
	unsigned char PM_FlgSuspend;

#ifdef RTMP_EFUSE_SUPPORT
	unsigned char bUseEfuse;
	unsigned char bEEPROMFile;
	unsigned char bFroceEEPROMBuffer;
	unsigned char EEPROMImage[1024];
#endif /* RTMP_EFUSE_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */

	EXT_CAP_INFO_ELEMENT ExtCapInfo;


#ifdef VENDOR_FEATURE1_SUPPORT
	unsigned char FifoUpdateDone, FifoUpdateRx;
#endif /* VENDOR_FEATURE1_SUPPORT */

	unsigned char RFICType;

#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
	void*pCfgDev;
	void*pCfg80211_CB;

	unsigned char FlgCfg80211Scanning;
	unsigned char FlgCfg80211Connecting;
	unsigned char Cfg80211_Alpha2[2];
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */

#ifdef OS_ABL_SUPPORT
#endif /* OS_ABL_SUPPORT */

	unsigned int ContinueMemAllocFailCount;

	struct {
		int IeLen;
		unsigned char *pIe;
	} ProbeRespIE[MAX_LEN_OF_BSS_TABLE];

	/* purpose: We free all kernel resources when module is removed */
	LIST_HEADER RscTimerMemList;	/* resource timers memory */
	LIST_HEADER RscTaskMemList;	/* resource tasks memory */
	LIST_HEADER RscLockMemList;	/* resource locks memory */
	LIST_HEADER RscTaskletMemList;	/* resource tasklets memory */
	LIST_HEADER RscSemMemList;	/* resource semaphore memory */
	LIST_HEADER RscAtomicMemList;	/* resource atomic memory */

	/* purpose: Cancel all timers when module is removed */
	LIST_HEADER RscTimerCreateList;	/* timers list */

#ifdef OS_ABL_SUPPORT
#endif /* OS_ABL_SUPPORT */





#ifdef WOW_SUPPORT
#ifdef RTMP_MAC_USB
	WOW_CFG_STRUCT WOW_Cfg; /* data structure for wake on wireless */
#endif /* RTMP_MAC_USB */
#endif /* WOW_SUPPORT */

#ifdef WLAN_SKB_RECYCLE
    struct sk_buff_head rx0_recycle;
#endif /* WLAN_SKB_RECYCLE */

#ifdef CONFIG_FPGA_MODE
	struct fpga_ctrl fpga_ctl;
#ifdef CAPTURE_MODE
	unsigned char cap_support;	/* 0: no cap mode; 1: cap mode enable */
	unsigned char cap_type;			/* 1: ADC6, 2: ADC8, 3: FEQ */
	unsigned char cap_trigger;		/* 1: manual trigger, 2: auto trigger */
	unsigned char do_cap;			/* 1: start to do cap, if auto, will triggered depends on trigger condition, if manual, start immediately */
	unsigned char cap_done;		/* 1: capture done, 0: capture not finish yet */
	unsigned int trigger_offset;	/* in unit of bytes */
	unsigned char *cap_buf;
#endif /* CAPTURE_MODE */
#endif /* CONFIG_FPGA_MODE */
#ifdef WFA_VHT_PF
	unsigned char force_amsdu;
	unsigned char force_noack;
	unsigned char vht_force_sgi;
	unsigned char vht_force_tx_stbc;
#ifdef IP_ASSEMBLY
	unsigned char ip_assemble;
#endif /* IP_ASSEMBLY */
#endif /* WFA_VHT_PF */

	unsigned char bloopBackTest;
	unsigned char bHwTxLookupRate;
	TXWI_STRUC NullTxWI;
	unsigned char TestMulMac;

	struct MCU_CTRL MCUCtrl;

#ifdef SINGLE_SKU_V2
	DL_LIST SingleSkuPwrList;
	char DefaultTargetPwr;
	char SingleSkuRatePwrDiff[19];
#endif /* SINGLE_SKU_V2 */
};

#if defined(RTMP_intERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 
/* The offset of the Tx power tuning entry (zero-based array) */
#define TX_POWER_TUNING_ENTRY_OFFSET			30

/* The lower-bound of the Tx power tuning entry */
#define LOWERBOUND_TX_POWER_TUNING_ENTRY		-30

/* The upper-bound of the Tx power tuning entry in G band */
#define UPPERBOUND_TX_POWER_TUNING_ENTRY(__pAd)		((__pAd)->chipCap.TxAlcTxPowerUpperBound_2G)

#ifdef A_BAND_SUPPORT
/* The upper-bound of the Tx power tuning entry in A band */
#define UPPERBOUND_TX_POWER_TUNING_ENTRY_5G(__pAd)		((__pAd)->chipCap.TxAlcTxPowerUpperBound_5G)
#endif /* A_BAND_SUPPORT */

/* Temperature compensation lookup table */

#define TEMPERATURE_COMPENSATION_LOOKUP_TABLE_OFFSET	7

/* The lower/upper power delta index for the TSSI rate table */

#define LOWER_POWER_DELTA_INDEX		0
#define UPPER_POWER_DELTA_INDEX		24

/* The offset of the TSSI rate table */

#define TSSI_RATIO_TABLE_OFFSET	12


/* Get the power delta bound */

#define GET_TSSI_RATE_TABLE_INDEX(x) (((x) > UPPER_POWER_DELTA_INDEX) ? (UPPER_POWER_DELTA_INDEX) : (((x) < LOWER_POWER_DELTA_INDEX) ? (LOWER_POWER_DELTA_INDEX) : ((x))))

/* 802.11b CCK TSSI information */

typedef union _CCK_TSSI_INFO
{
#ifdef RT_BIG_ENDIAN
	struct
	{
		unsigned char	Reserved:1;
		unsigned char	shortPreamble:1;
		unsigned char	Rate:2;
		unsigned char	Tx40MSel:2;
		unsigned char	TxType:2;
	} field;
#else
	struct
	{
		unsigned char	TxType:2;
		unsigned char	Tx40MSel:2;
		unsigned char	Rate:2;
		unsigned char	shortPreamble:1;
		unsigned char	Reserved:1;
	} field;
#endif /* RT_BIG_ENDIAN */

	unsigned char	value;
} CCK_TSSI_INFO, *PCCK_TSSI_INFO;


/* 802.11a/g OFDM TSSI information */

typedef union _OFDM_TSSI_INFO
{
#ifdef RT_BIG_ENDIAN
	struct
	{
		unsigned char	Rate:4;
		unsigned char	Tx40MSel:2;
		unsigned char	TxType:2;
	} field;
#else
	struct
	{
		unsigned char	TxType:2;
		unsigned char	Tx40MSel:2;
		unsigned char	Rate:4;
	} field;
#endif /* RT_BIG_ENDIAN */

	unsigned char	value;
} OFDM_TSSI_INFO, *POFDM_TSSI_INFO;


/* 802.11n HT TSSI information */

typedef struct _HT_TSSI_INFO {
	union {
#ifdef RT_BIG_ENDIAN
		struct {
			unsigned char SGI:1;
			unsigned char STBC:2;
			unsigned char Aggregation:1;
			unsigned char Tx40MSel:2;
			unsigned char TxType:2;
		} field;
#else	
		struct {
			unsigned char TxType:2;
			unsigned char Tx40MSel:2;
			unsigned char Aggregation:1;
			unsigned char STBC:2;
			unsigned char SGI:1;
		} field;
#endif /* RT_BIG_ENDIAN */

		unsigned char value;
	} PartA;

	union {
#ifdef RT_BIG_ENDIAN
		struct {
			unsigned char BW:1;
			unsigned char MCS:7;
		} field;
#else	
		struct {
			unsigned char MCS:7;
			unsigned char BW:1;
		} field;
#endif /* RT_BIG_ENDIAN */
		unsigned char	value;
	} PartB;
} HT_TSSI_INFO, *PHT_TSSI_INFO;

typedef struct _TSSI_INFO_{
	unsigned char tssi_info_0;
	union {
		CCK_TSSI_INFO cck_tssi_info;
		OFDM_TSSI_INFO ofdm_tssi_info;
		HT_TSSI_INFO ht_tssi_info_1;
		unsigned char byte;
	}tssi_info_1;
	HT_TSSI_INFO ht_tssi_info_2;
}TSSI_INFO;

#endif /* RTMP_intERNAL_TX_ALC || RTMP_TEMPERATURE_COMPENSATION */


/***************************************************************************
  *	Rx Path software control block related data structures
  **************************************************************************/
typedef struct _RX_BLK_
{
	unsigned char hw_rx_info[RXD_SIZE]; /* include "RXD_STRUC RxD" and "RXINFO_STRUC rx_info " */
	RXINFO_STRUC *pRxInfo;
#ifdef RLT_MAC
	RXFCE_INFO *pRxFceInfo;
#endif /* RLT_MAC */
	RXWI_STRUC *pRxWI;
	PHEADER_802_11 pHeader;
	PNDIS_PACKET pRxPacket;
	unsigned char *pData;
	unsigned short DataSize;
	unsigned short Flags;
	unsigned char UserPriority;	/* for calculate TKIP MIC using */
	unsigned char OpMode;	/* 0:OPMODE_STA 1:OPMODE_AP */
	unsigned char wcid;		/* copy of pRxWI->RxWIWirelessCliID */
	unsigned char mcs;
	unsigned char U2M;
#ifdef HDR_TRANS_SUPPORT
	unsigned char	bHdrRxTrans;	/* this packet's header is translated to 802.3 by HW  */
	unsigned char bHdrVlanTaged;	/* VLAN tag is added to this header */
	unsigned char *pTransData;
	unsigned short TransDataSize;
#endif /* HDR_TRANS_SUPPORT */
} RX_BLK;


#define RX_BLK_SET_FLAG(_pRxBlk, _flag)		(_pRxBlk->Flags |= _flag)
#define RX_BLK_TEST_FLAG(_pRxBlk, _flag)		(_pRxBlk->Flags & _flag)
#define RX_BLK_CLEAR_FLAG(_pRxBlk, _flag)	(_pRxBlk->Flags &= ~(_flag))


#define fRX_WDS			0x0001
#define fRX_AMSDU		0x0002
#define fRX_ARALINK		0x0004
#define fRX_HTC			0x0008
#define fRX_PAD			0x0010
#define fRX_AMPDU		0x0020
#define fRX_QOS			0x0040
#define fRX_INFRA		0x0080
#define fRX_EAP			0x0100
#define fRX_MESH		0x0200
#define fRX_APCLI		0x0400
#define fRX_DLS			0x0800
#define fRX_WPI			0x1000
#define fRX_P2PGO		0x2000
#define fRX_P2PCLI		0x4000

#define LENGTH_AMSDU_SUBFRAMEHEAD	14
#define LENGTH_ARALINK_SUBFRAMEHEAD	14
#define LENGTH_ARALINK_HEADER_FIELD	 2


/***************************************************************************
  *	Tx Path software control block related data structures
  **************************************************************************/
#define TX_UNKOWN_FRAME		0x00
#define TX_MCAST_FRAME			0x01
#define TX_LEGACY_FRAME		0x02
#define TX_AMPDU_FRAME		0x04
#define TX_AMSDU_FRAME		0x08
#define TX_RALINK_FRAME		0x10
#define TX_FRAG_FRAME			0x20


/*	Currently the sizeof(TX_BLK) is 148 bytes. */
typedef struct _TX_BLK_
{
	unsigned char				QueIdx;
	unsigned char				TxFrameType;				/* Indicate the Transmission type of the all frames in one batch */
	unsigned char				TotalFrameNum;				/* Total frame number want to send-out in one batch */
	unsigned short				TotalFragNum;				/* Total frame fragments required in one batch */
	unsigned short				TotalFrameLen;				/* Total length of all frames want to send-out in one batch */

	QUEUE_HEADER				TxPacketList;
	MAC_TABLE_ENTRY	*pMacEntry;					/* NULL: packet with 802.11 RA field is multicast/broadcast address */
	HTTRANSMIT_SETTING	*pTransmit;
	
	/* Following structure used for the characteristics of a specific packet. */
	PNDIS_PACKET		pPacket;
	unsigned char*				pSrcBufHeader;				/* Reference to the head of sk_buff->data */
	unsigned char*				pSrcBufData;				/* Reference to the sk_buff->data, will changed depends on hanlding progresss */
	unsigned int				SrcBufLen;					/* Length of packet payload which not including Layer 2 header */

	unsigned char*				pExtraLlcSnapEncap;			/* NULL means no extra LLC/SNAP is required */
#ifndef VENDOR_FEATURE1_SUPPORT
	/*
		Note: Can not insert any other new parameters
		between pExtraLlcSnapEncap & HeaderBuf; Or
		the start address of HeaderBuf will not be aligned by 4.

		But we can not change HeaderBuf[128] to HeaderBuf[32] because
		many codes use HeaderBuf[index].
	*/
	unsigned char				HeaderBuf[128];				/* TempBuffer for TX_INFO + TX_WI + TSO_INFO + 802.11 Header + padding + AMSDU SubHeader + LLC/SNAP */
#else
	unsigned int 			HeaderBuffer[32];			/* total 128B, use unsigned int to avoid alignment problem */
	unsigned char				*HeaderBuf;
#endif /* VENDOR_FEATURE1_SUPPORT */
	unsigned char				MpduHeaderLen;				/* 802.11 header length NOT including the padding */
	unsigned char				HdrPadLen;					/* recording Header Padding Length; */
	unsigned char				apidx;						/* The interface associated to this packet */
	unsigned char				Wcid;						/* The MAC entry associated to this packet */
	unsigned char				UserPriority;				/* priority class of packet */
	unsigned char				FrameGap;					/* what kind of IFS this packet use */
	unsigned char				MpduReqNum;					/* number of fragments of this frame */
	unsigned char				TxRate;						/* TODO: Obsoleted? Should change to MCS? */
	unsigned char				CipherAlg;					/* cipher alogrithm */
	PCIPHER_KEY			pKey;
	unsigned char				KeyIdx;						/* Indicate the transmit key index */


	unsigned int 			Flags;						/*See following definitions for detail. */

	/*YOU SHOULD NOT TOUCH IT! Following parameters are used for hardware-depended layer. */
	unsigned long				Priv;						/* Hardware specific value saved in here. */


#ifdef TXBF_SUPPORT
	unsigned char				TxSndgPkt; /* 1: sounding 2: NDP sounding */
	unsigned char				TxNDPSndgBW;
	unsigned char				TxNDPSndgMcs;
#endif /* TXBF_SUPPORT */

	unsigned char				naf_type;
#ifdef TX_PKT_SG
	PACKET_INFO pkt_info;
#endif /* TX_PKT_SG */
	unsigned char				OpMode;

#ifdef HDR_TRANS_SUPPORT
	unsigned char				NeedTrans;	/* indicate the packet needs to do hw header translate */
#endif /* HDR_TRANS_SUPPORT */

} TX_BLK, *PTX_BLK;


#define fTX_bRtsRequired			0x0001	/* Indicate if need send RTS frame for protection. Not used in RT2860/RT2870. */
#define fTX_bAckRequired			0x0002	/* the packet need ack response */
#define fTX_bPiggyBack			0x0004	/* Legacy device use Piggback or not */
#define fTX_bHTRate				0x0008	/* allow to use HT rate */
#define fTX_bForceNonQoS		0x0010	/* force to transmit frame without WMM-QoS in HT mode */
#define fTX_bAllowFrag			0x0020	/* allow to fragment the packet, A-MPDU, A-MSDU, A-Ralink is not allowed to fragment */
#define fTX_bMoreData			0x0040	/* there are more data packets in PowerSave Queue */
#define fTX_bWMM				0x0080	/* QOS Data */
#define fTX_bClearEAPFrame		0x0100

#define	fTX_bSwEncrypt			0x0400	/* this packet need to be encrypted by software before TX */

#ifdef UAPSD_SUPPORT
#define	fTX_bWMM_UAPSD_EOSP	0x0800	/* Used when UAPSD_SUPPORT */
#endif /* UAPSD_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */



#ifdef CLIENT_WDS
#define fTX_bClientWDSFrame		0x10000
#endif /* CLIENT_WDS */


#define TX_BLK_SET_FLAG(_pTxBlk, _flag)		(_pTxBlk->Flags |= _flag)
#define TX_BLK_TEST_FLAG(_pTxBlk, _flag)	(((_pTxBlk->Flags & _flag) == _flag) ? 1 : 0)
#define TX_BLK_CLEAR_FLAG(_pTxBlk, _flag)	(_pTxBlk->Flags &= ~(_flag))
	



#ifdef RT_BIG_ENDIAN
/***************************************************************************
  *	Endian conversion related functions
  **************************************************************************/
/*
	========================================================================

	Routine Description:
		Endian conversion of Tx/Rx descriptor .

	Arguments:
		pAd 	Pointer to our adapter
		pData			Pointer to Tx/Rx descriptor
		DescriptorType	Direction of the frame

	Return Value:
		None

	Note:
		Call this function when read or update descriptor
	========================================================================
*/
static inline void RTMPWIEndianChange(
PRTMP_ADAPTER	pAd,
unsigned char*			pData,
unsigned long			DescriptorType)
{
	int size;
	int i;
	unsigned char TXWISize = pAd->chipCap.TXWISize;
	unsigned char RXWISize = pAd->chipCap.RXWISize;
	
	size = ((DescriptorType == TYPE_TXWI) ? TXWISize : RXWISize);
	
	if(DescriptorType == TYPE_TXWI)
	{
		*((unsigned int *)(pData)) = SWAP32(*((unsigned int *)(pData)));		/* Byte 0~3 */
		*((unsigned int *)(pData + 4)) = SWAP32(*((unsigned int *)(pData+4)));	/* Byte 4~7 */
	} 
	else
	{
		for(i=0; i < size/4 ; i++)
			*(((unsigned int *)pData) +i) = SWAP32(*(((unsigned int *)pData)+i));
	}
}




/*
	========================================================================

	Routine Description:
		Endian conversion of Tx/Rx descriptor .

	Arguments:
		pAd 	Pointer to our adapter
		pData			Pointer to Tx/Rx descriptor
		DescriptorType	Direction of the frame

	Return Value:
		None

	Note:
		Call this function when read or update descriptor
	========================================================================
*/

#ifdef RTMP_MAC_USB
static inline void RTMPDescriptorEndianChange(unsigned char *pData, unsigned long DescType)
{	
	*((unsigned int *)(pData)) = SWAP32(*((unsigned int *)(pData)));
}
#endif /* RTMP_MAC_USB */
/*
	========================================================================

	Routine Description:
		Endian conversion of all kinds of 802.11 frames .

	Arguments:
		pAd 	Pointer to our adapter
		pData			Pointer to the 802.11 frame structure
		Dir 			Direction of the frame
		FromRxDoneint	Caller is from RxDone interrupt

	Return Value:
		None

	Note:
		Call this function when read or update buffer data
	========================================================================
*/
static inline void RTMPFrameEndianChange(
PRTMP_ADAPTER	pAd, 
unsigned char*			pData, 
unsigned long			Dir,
unsigned char 		FromRxDoneint)
{
	PHEADER_802_11 pFrame;
	unsigned char*	pMacHdr;

	/* swab 16 bit fields - Frame Control field */
	if(Dir == DIR_READ)
	{
		*(unsigned short *)pData = SWAP16(*(unsigned short *)pData);
	}

	pFrame = (PHEADER_802_11) pData;
	pMacHdr = (unsigned char*) pFrame;

	/* swab 16 bit fields - Duration/ID field */
	*(unsigned short *)(pMacHdr + 2) = SWAP16(*(unsigned short *)(pMacHdr + 2));

	if (pFrame->FC.Type != BTYPE_CNTL)
	{
		/* swab 16 bit fields - Sequence Control field */
		*(unsigned short *)(pMacHdr + 22) = SWAP16(*(unsigned short *)(pMacHdr + 22));
	}

	if(pFrame->FC.Type == BTYPE_MGMT)
	{
		switch(pFrame->FC.SubType)
		{
			case SUBTYPE_ASSOC_REQ:
			case SUBTYPE_REASSOC_REQ:
				/* swab 16 bit fields - CapabilityInfo field */
				pMacHdr += sizeof(HEADER_802_11);
				*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);

				/* swab 16 bit fields - Listen interval field */
				pMacHdr += 2;
				*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);
				break;

			case SUBTYPE_ASSOC_RSP:
			case SUBTYPE_REASSOC_RSP:
				/* swab 16 bit fields - CapabilityInfo field */
				pMacHdr += sizeof(HEADER_802_11);
				*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);

				/* swab 16 bit fields - Status Code field */
				pMacHdr += 2;
				*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);

				/* swab 16 bit fields - AID field */
				pMacHdr += 2;
				*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);
				break;

			case SUBTYPE_AUTH:
				 /* When the WEP bit is on, don't do the conversion here.
					This is only shared WEP can hit this condition. 
					For AP, it shall do conversion after decryption. 
					For STA, it shall do conversion before encryption. */
				if (pFrame->FC.Wep == 1)
					break;
				else
				{
					/* swab 16 bit fields - Auth Alg No. field */
					pMacHdr += sizeof(HEADER_802_11);
					*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);

					/* swab 16 bit fields - Auth Seq No. field */
					pMacHdr += 2;
					*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);

					/* swab 16 bit fields - Status Code field */
					pMacHdr += 2;
					*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);
				}
				break;

			case SUBTYPE_BEACON:
			case SUBTYPE_PROBE_RSP:
				/* swab 16 bit fields - Beaconinterval field */
				pMacHdr += (sizeof(HEADER_802_11) + TIMESTAMP_LEN);
				*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);

				/* swab 16 bit fields - CapabilityInfo field */
				pMacHdr += sizeof(unsigned short);
				*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);
				break;

			case SUBTYPE_DEAUTH:
			case SUBTYPE_DISASSOC:
				/* If the PMF is negotiated, those frames shall be encrypted */
				if(!FromRxDoneint && pFrame->FC.Wep == 1)
					break;
				else
				{
					/* swab 16 bit fields - Reason code field */
					pMacHdr += sizeof(HEADER_802_11);
					*(unsigned short *)pMacHdr = SWAP16(*(unsigned short *)pMacHdr);
				}
				break;
		}
	}
	else if( pFrame->FC.Type == BTYPE_DATA )
	{
	}
	else if(pFrame->FC.Type == BTYPE_CNTL)
	{
		switch(pFrame->FC.SubType)
		{
			case SUBTYPE_BLOCK_ACK_REQ:
				{
					PFRAME_BA_REQ pBAReq = (PFRAME_BA_REQ)pFrame;
					*(unsigned short *)(&pBAReq->BARControl) = SWAP16(*(unsigned short *)(&pBAReq->BARControl));
					pBAReq->BAStartingSeq.word = SWAP16(pBAReq->BAStartingSeq.word);
				}
				break;
			case SUBTYPE_BLOCK_ACK:
				/* For Block Ack packet, the HT_CONTROL field is in the same offset with Addr3 */
				*(unsigned int *)(&pFrame->Addr3[0]) = SWAP32(*(unsigned int *)(&pFrame->Addr3[0]));
				break;

			case SUBTYPE_ACK:
				/*For ACK packet, the HT_CONTROL field is in the same offset with Addr2 */
				*(unsigned int *)(&pFrame->Addr2[0])=	SWAP32(*(unsigned int *)(&pFrame->Addr2[0]));
				break;
		}
	}
	else
	{
		DBGPRint(RT_DEBUG_ERROR,("Invalid Frame Type!!!\n"));
	}

	/* swab 16 bit fields - Frame Control */
	if(Dir == DIR_WRITE)
	{
		*(unsigned short *)pData = SWAP16(*(unsigned short *)pData);
	}
}
#endif /* RT_BIG_ENDIAN */


/***************************************************************************
  *	Other static inline function definitions
  **************************************************************************/
static inline void ConvertMulticastIP2MAC(
unsigned char* pIpAddr,
unsigned char* *ppMacAddr, 
unsigned short ProtoType)
{
	if (pIpAddr == NULL)
		return;

	if (ppMacAddr == NULL || *ppMacAddr == NULL)
		return;

	switch (ProtoType)
	{
		case ETH_P_IPV6:
/*			memset(*ppMacAddr, 0, ETH_LENGTH_OF_ADDRESS); */
			*(*ppMacAddr) = 0x33;
			*(*ppMacAddr + 1) = 0x33;
			*(*ppMacAddr + 2) = pIpAddr[12];
			*(*ppMacAddr + 3) = pIpAddr[13];
			*(*ppMacAddr + 4) = pIpAddr[14];
			*(*ppMacAddr + 5) = pIpAddr[15];
			break;

		case ETH_P_IP:
		default:
/*			memset(*ppMacAddr, 0, ETH_LENGTH_OF_ADDRESS); */
			*(*ppMacAddr) = 0x01;
			*(*ppMacAddr + 1) = 0x00;
			*(*ppMacAddr + 2) = 0x5e;
			*(*ppMacAddr + 3) = pIpAddr[1] & 0x7f;
			*(*ppMacAddr + 4) = pIpAddr[2];
			*(*ppMacAddr + 5) = pIpAddr[3];
			break;
	}

	return;
}


char *get_phymode_str(int phy_mode);
char *get_bw_str(int bandwidth);


unsigned char RTMPCheckForHang(
 NDIS_HANDLE MiniportAdapterContext);

/*
	Private routines in rtmp_init.c
*/
NDIS_STATUS RTMPAllocTxRxRingMemory(
 PRTMP_ADAPTER   pAd);

#ifdef RESOURCE_PRE_ALLOC
NDIS_STATUS RTMPInitTxRxRingMemory(
RTMP_ADAPTER *pAd);
#endif /* RESOURCE_PRE_ALLOC */

NDIS_STATUS	RTMPReadParametersHook(
PRTMP_ADAPTER pAd);

NDIS_STATUS	RTMPSetProfileParameters(
RTMP_ADAPTER *pAd,
char *		pBuffer);

NDIS_STATUS	RTMPSetDefaultProfileParameters(
RTMP_ADAPTER *pAd);

#ifdef SINGLE_SKU_V2
NDIS_STATUS	RTMPSetSingleSKUParameters(
RTMP_ADAPTER *pAd);
#endif /* SINGLE_SKU_V2 */

int RTMPGetKeyParameter(
    IN char * key,
    char * dest,
    IN int destsize,
    IN char * buffer,
    IN unsigned char bTrimSpace);




#ifdef RLT_RF
NDIS_STATUS rlt_rf_write(
RTMP_ADAPTER *pAd,
unsigned char bank,
unsigned char regID,
unsigned char value);

NDIS_STATUS rlt_rf_read(
RTMP_ADAPTER *pAd,
unsigned char bank,
unsigned char regID,
unsigned char *pValue);
#endif /* RLT_RF */

void NICReadEEPROMParameters(
 PRTMP_ADAPTER       pAd,
char *				mac_addr);

void NICInitAsicFromEEPROM(
 PRTMP_ADAPTER       pAd);

NDIS_STATUS NICInitializeAdapter(
 PRTMP_ADAPTER   pAd,
  unsigned char    bHardReset);

NDIS_STATUS NICInitializeAsic(
 PRTMP_ADAPTER   pAd,
 unsigned char		bHardReset);


void RTMPRingCleanUp(
 PRTMP_ADAPTER   pAd,
 unsigned char           RingType);

void UserCfgExit(	
 RTMP_ADAPTER *pAd);

void UserCfgInit(
 PRTMP_ADAPTER   pAd);

NDIS_STATUS NICLoadFirmware(
 PRTMP_ADAPTER   pAd);

void NICEraseFirmware(
PRTMP_ADAPTER pAd);

void NICUpdateFifoStaCounters(
PRTMP_ADAPTER pAd);

void NICUpdateRawCounters(
 PRTMP_ADAPTER   pAd);

#ifdef FIFO_EXT_SUPPORT
unsigned char NicGetMacFifoTxCnt(
RTMP_ADAPTER *pAd,
MAC_TABLE_ENTRY *pEntry);

void AsicFifoExtSet(
RTMP_ADAPTER *pAd);

void AsicFifoExtEntryClean(
RTMP_ADAPTER * pAd, 
MAC_TABLE_ENTRY *pEntry);
#endif /* FIFO_EXT_SUPPORT */

void NicResetRawCounters(RTMP_ADAPTER *pAd);

void NicGetTxRawCounters(
RTMP_ADAPTER *pAd,
TX_STA_CNT0_STRUC *pStaTxCnt0,
TX_STA_CNT1_STRUC *pStaTxCnt1);
	
void RTMPZeroMemory(
 void *  pSrc,
 unsigned long   Length);

unsigned long RTMPCompareMemory(
 void *  pSrc1,
 void *  pSrc2,
 unsigned long   Length);

void RTMPMoveMemory(
	void *  pDest,
 void *  pSrc,
 unsigned long   Length);

void AtoH(
	char *	src,
	unsigned char* dest,
	int		destlen);

unsigned char BtoH(
	char ch);

void RTMP_TimerListAdd(
PRTMP_ADAPTER			pAd,
void				*pRsc);

void RTMP_TimerListRelease(
PRTMP_ADAPTER			pAd);

void RTMPInitTimer(
 PRTMP_ADAPTER           pAd,
 PRALINK_TIMER_STRUCT    pTimer,
 void *                  pTimerFunc,
void *				pData,
 unsigned char                 Repeat);

void RTMPSetTimer(
 PRALINK_TIMER_STRUCT    pTimer,
 unsigned long                   Value);


void RTMPModTimer(
PRALINK_TIMER_STRUCT	pTimer,
unsigned long					Value);

void RTMPCancelTimer(
 PRALINK_TIMER_STRUCT    pTimer,
	unsigned char                 *pCancelled);

void RTMPReleaseTimer(
 PRALINK_TIMER_STRUCT    pTimer,
	unsigned char                 *pCancelled);

void RTMPEnableRxTx(
PRTMP_ADAPTER	pAd);

void AntCfgInit(
 PRTMP_ADAPTER   pAd);

/* */
/* prototype in action.c */
/* */
void ActionStateMachineInit(
    IN	PRTMP_ADAPTER	pAd, 
    IN  STATE_MACHINE *S, 
    STATE_MACHINE_FUNC Trans[]);

void MlmeADDBAAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

void MlmeDELBAAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

void MlmeDLSAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

void MlmeInvalidAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

void MlmeQOSAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

#ifdef DOT11_N_SUPPORT
void PeerAddBAReqAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);

void PeerAddBARspAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);

void PeerDelBAAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);

void PeerBAAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);
#endif /* DOT11_N_SUPPORT */

void SendPSMPAction(
PRTMP_ADAPTER	pAd,
unsigned char			Wcid,
unsigned char			Psmp);
				   

void PeerRMAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);

void PeerPublicAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);

#ifdef CONFIG_STA_SUPPORT
void StaPublicAction(
PRTMP_ADAPTER pAd, 
BSS_2040_COEXIST_IE *pBss2040CoexIE);
#endif /* CONFIG_STA_SUPPORT */


void PeerBSSTranAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);

#ifdef DOT11_N_SUPPORT
void PeerHTAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);
#endif /* DOT11_N_SUPPORT */

void PeerQOSAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

#ifdef QOS_DLS_SUPPORT
void PeerDLSAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);
#endif /* QOS_DLS_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
void DlsParmFill(
PRTMP_ADAPTER pAd, 
MLME_DLS_REQ_STRUCT *pDlsReq,
PRT_802_11_DLS pDls,
unsigned short reason);
#endif /* QOS_DLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

#ifdef DOT11_N_SUPPORT
void RECBATimerTimeout(
    IN void *SystemSpecific1, 
    IN void *FunctionContext, 
    IN void *SystemSpecific2, 
    IN void *SystemSpecific3);

void ORIBATimerTimeout(
PRTMP_ADAPTER	pAd);

void SendRefreshBAR(
PRTMP_ADAPTER	pAd,
MAC_TABLE_ENTRY	*pEntry);

#ifdef DOT11N_DRAFT3
void RTMP_11N_D3_TimerInit(
PRTMP_ADAPTER pAd);

void SendBSS2040CoexistMgmtAction(
PRTMP_ADAPTER	pAd,
unsigned char	Wcid,
unsigned char	apidx,
unsigned char	InfoReq);

void SendNotifyBWActionFrame(
PRTMP_ADAPTER pAd,
unsigned char  Wcid,
unsigned char apidx);
	
unsigned char ChannelSwitchSanityCheck(
PRTMP_ADAPTER	pAd,
   unsigned char  Wcid,
   unsigned char  NewChannel,
   unsigned char  Secondary);

void ChannelSwitchAction(
PRTMP_ADAPTER	pAd,
   unsigned char  Wcid,
   unsigned char  Channel,
   unsigned char  Secondary);

unsigned long BuildintolerantChannelRep(
PRTMP_ADAPTER	pAd,
   unsigned char*  pDest); 

void Update2040CoexistFrameAndNotify(
PRTMP_ADAPTER	pAd,
   unsigned char  Wcid,
unsigned char	bAddintolerantCha);
	
void Send2040CoexistAction(
PRTMP_ADAPTER	pAd,
   unsigned char  Wcid,
unsigned char	bAddintolerantCha);

void UpdateBssScanParm(
PRTMP_ADAPTER pAd,
OVERLAP_BSS_SCAN_IE APBssScan);
#endif /* DOT11N_DRAFT3 */

void AsicEnableRalinkBurstMode(
PRTMP_ADAPTER pAd);

void AsicDisableRalinkBurstMode(
PRTMP_ADAPTER pAd);
#endif /* DOT11_N_SUPPORT */
	
void ActHeaderInit(
    IN	PRTMP_ADAPTER	pAd, 
    IN PHEADER_802_11 pHdr80211, 
    IN unsigned char* Addr1, 
    IN unsigned char* Addr2,
    IN unsigned char* Addr3);

void BarHeaderInit(
PRTMP_ADAPTER	pAd, 
PFRAME_BAR pCntlBar, 
unsigned char* pDA,
unsigned char* pSA);

void InsertActField(
PRTMP_ADAPTER pAd,
	unsigned char* pFrameBuf,
	unsigned long* pFrameLen,
unsigned char Category,
unsigned char ActCode);

unsigned char QosBADataParse(
PRTMP_ADAPTER	pAd, 
unsigned char bAMSDU,
unsigned char* p8023Header,
unsigned char	WCID,
unsigned char	TID,
unsigned short Sequence,
unsigned char DataOffset, 
unsigned short Datasize,
unsigned int   CurRxIndex);

#ifdef DOT11_N_SUPPORT
unsigned char CntlEnqueueForRecv(
    IN	PRTMP_ADAPTER	pAd, 
unsigned long Wcid, 
    IN unsigned long MsgLen, 
PFRAME_BA_REQ pMsg);

void BaAutoManSwitch(
PRTMP_ADAPTER	pAd);
#endif /* DOT11_N_SUPPORT */

void HTIOTCheck(
PRTMP_ADAPTER	pAd,
   unsigned char     BatRecIdx);

/* */
/* Private routines in rtmp_data.c */
/* */
unsigned char RTMPHandleTxRingDmaDoneinterrupt(
PRTMP_ADAPTER pAd,
unsigned intint_reg);

void RTMPHandleMgmtRingDmaDoneinterrupt(
PRTMP_ADAPTER pAd);

void RTMPHandleTBTTinterrupt(
PRTMP_ADAPTER pAd);

void RTMPHandlePreTBTTinterrupt(
PRTMP_ADAPTER pAd);

void RTMPHandleTwakeupinterrupt(
PRTMP_ADAPTER pAd);

void RTMPHandleRxCoherentinterrupt(
PRTMP_ADAPTER pAd);



NDIS_STATUS STASendPacket(
 PRTMP_ADAPTER   pAd,
 PNDIS_PACKET    pPacket);

void STASendPackets(
 NDIS_HANDLE     MiniportAdapterContext,
 PPNDIS_PACKET   ppPacketArray,
 unsigned int            NumberOfPackets);

void RTMPDeQueuePacket(
RTMP_ADAPTER *pAd,
   	IN unsigned char bintContext,
unsigned char QueIdx,
int Max_Tx_Packets);

NDIS_STATUS	RTMPHardTransmit(
PRTMP_ADAPTER	pAd,
PNDIS_PACKET		pPacket,
 unsigned char			QueIdx,
	OUT	unsigned long*			pFreeTXDLeft);

NDIS_STATUS	STAHardTransmit(
PRTMP_ADAPTER	pAd,
TX_BLK			*pTxBlk,
 unsigned char			QueIdx);

void STARxEAPOLFrameIndicate(
PRTMP_ADAPTER	pAd,
MAC_TABLE_ENTRY	*pEntry,
RX_BLK			*pRxBlk,
unsigned char			FromWhichBSSID);

NDIS_STATUS RTMPFreeTXDRequest(
 PRTMP_ADAPTER   pAd,
 unsigned char           RingType,
 unsigned char           NumberRequired,
	unsigned char*          FreeNumberIs);

NDIS_STATUS MlmeHardTransmit(
 PRTMP_ADAPTER   pAd,
 unsigned char	QueIdx,
 PNDIS_PACKET    pPacket,
unsigned char			FlgDataQForce,
unsigned char			FlgIsLocked);

NDIS_STATUS MlmeHardTransmitMgmtRing(
 PRTMP_ADAPTER   pAd,
 unsigned char	QueIdx,
 PNDIS_PACKET    pPacket);


unsigned short RTMPCalcDuration(
RTMP_ADAPTER *pAd,
unsigned char Rate,
unsigned long Size);

void RTMPWriteTxWI(
RTMP_ADAPTER *pAd,
TXWI_STRUC *pTxWI,
unsigned char FRAG,
unsigned char CFACK,
unsigned char InsTimestamp,
unsigned char AMPDU,
unsigned char Ack,
unsigned char NSeq, /* HW new a sequence. */
unsigned char BASize,
unsigned char WCID,
unsigned long Length,
unsigned char PID,
unsigned char TID,
unsigned char TxRate,
unsigned char Txopmode,
unsigned char CfAck,
HTTRANSMIT_SETTING *pTransmit);


void RTMPWriteTxWI_Data(
RTMP_ADAPTER *pAd,
	TXWI_STRUC *pTxWI,
TX_BLK *pTxBlk);

	
void RTMPWriteTxWI_Cache(
RTMP_ADAPTER *pAd,
	TXWI_STRUC *pTxWI,
TX_BLK *pTxBlk);

void RTMPSuspendMsduTransmission(
RTMP_ADAPTER *pAd);

void RTMPResumeMsduTransmission(
RTMP_ADAPTER *pAd);

NDIS_STATUS MiniportMMRequest(
RTMP_ADAPTER *pAd,
unsigned char QueIdx,
unsigned char *pData,
unsigned int Length);

void RTMPSendNullFrame(
RTMP_ADAPTER *pAd,
unsigned char TxRate,
unsigned char bQosNull,
unsigned short PwrMgmt);

#ifdef CONFIG_STA_SUPPORT
void RTMPReportMicError(
 PRTMP_ADAPTER   pAd, 
 PCIPHER_KEY     pWpaKey);

void WpaMicFailureReportFrame(
 PRTMP_ADAPTER    pAd, 
 MLME_QUEUE_ELEM *Elem);

void   WpaDisassocApAndBlockAssoc(
    IN  void *SystemSpecific1, 
    IN  void *FunctionContext, 
    IN  void *SystemSpecific2, 
    IN  void *SystemSpecific3);

void WpaStaPairwiseKeySetting(
PRTMP_ADAPTER	pAd);

void WpaStaGroupKeySetting(
PRTMP_ADAPTER	pAd);

void   WpaSendEapolStart(
PRTMP_ADAPTER	pAdapter,
 unsigned char*          pBssid);

#endif /* CONFIG_STA_SUPPORT */



unsigned char RTMPFreeTXDUponTxDmaDone(
PRTMP_ADAPTER    pAd, 
unsigned char            QueIdx);

unsigned char RTMPCheckEtherType(
PRTMP_ADAPTER	pAd, 
PNDIS_PACKET	pPacket,
PMAC_TABLE_ENTRY pMacEntry,
unsigned char			OpMode,
	unsigned char* pUserPriority,
	unsigned char* pQueIdx);


void RTMPCckBbpTuning(
PRTMP_ADAPTER	pAd, 
unsigned int			TxRate);
/* */
/* MLME routines */
/* */

/* Asic/RF/BBP related functions */
void AsicGetTxPowerOffset(
PRTMP_ADAPTER 			pAd,
unsigned long*					TxPwr);

void AsicGetAutoAgcOffsetForExternalTxAlc(
PRTMP_ADAPTER 		pAd,
char * 				pDeltaPwr,
char * 				pTotalDeltaPwr,
char * 				pAgcCompensate,
char * 				pDeltaPowerByBbpR1);
	
void AsicExtraPowerOverMAC(RTMP_ADAPTER *pAd);

#ifdef RTMP_TEMPERATURE_COMPENSATION
void AsicGetAutoAgcOffsetForTemperatureSensor(
PRTMP_ADAPTER 		pAd,
char *				pDeltaPwr,
char *				pTotalDeltaPwr,
char *				pAgcCompensate,
char * 				pDeltaPowerByBbpR1);
#endif /* RTMP_TEMPERATURE_COMPENSATION */

#ifdef SINGLE_SKU
void GetSingleSkuDeltaPower(
		PRTMP_ADAPTER 	pAd,
		char * 			pTotalDeltaPower,
	IN	unsigned long*			pSingleSKUTotalDeltaPwr,
	IN 	unsigned char*              	pSingleSKUBbpR1Offset);
#endif /* SINGLE_SKU*/

void AsicPercentageDeltaPower(
		PRTMP_ADAPTER 		pAd,
	char				Rssi,
	INOUT	char *				pDeltaPwr,
	INOUT	char *				pDeltaPowerByBbpR1);

void AsicCompensatePowerViaBBP(
		PRTMP_ADAPTER 		pAd,
	INOUT	char *				pTotalDeltaPower);

void AsicAdjustTxPower(
PRTMP_ADAPTER pAd);

void	AsicUpdateProtect(
	PRTMP_ADAPTER	pAd,
		unsigned short			OperaionMode,
		unsigned char			SetMask,
	unsigned char			bDisableBGProtect,
	unsigned char			bNonGFExist);

void AsicBBPAdjust(
RTMP_ADAPTER *pAd);

void AsicSwitchChannel(
 PRTMP_ADAPTER   pAd, 
unsigned char			Channel,
unsigned char			bScan);

int AsicSetChannel(
RTMP_ADAPTER *pAd,
unsigned char ch,
unsigned char bw,
unsigned char ext_ch,
unsigned char bScan);

void AsicLockChannel(
PRTMP_ADAPTER pAd, 
unsigned char Channel) ;

void AsicAntennaSelect(
 PRTMP_ADAPTER   pAd,
 unsigned char           Channel);

void AsicResetBBPAgent(
PRTMP_ADAPTER pAd);

#ifdef CONFIG_STA_SUPPORT
void AsicSleepThenAutoWakeup(
 PRTMP_ADAPTER   pAd, 
 unsigned short TbttNumToNextWakeUp);

void AsicForceSleep(
PRTMP_ADAPTER pAd);

void AsicForceWakeup(
PRTMP_ADAPTER pAd,
unsigned char    bFromTx);
#endif /* CONFIG_STA_SUPPORT */

void AsicSetBssid(
 PRTMP_ADAPTER   pAd, 
 unsigned char* pBssid);

void AsicDelWcidTab(
PRTMP_ADAPTER pAd,
unsigned char	Wcid);

#ifdef RLT_MAC
void AsicSetApCliBssid(
PRTMP_ADAPTER pAd, 
unsigned char* pBssid,
unsigned char index);

#ifdef MAC_REPEATER_SUPPORT
void AsicSetExtendedMacAddr(
PRTMP_ADAPTER pAd, 
unsigned char* pMacAddr,
unsigned intIdx);
#endif /* MAC_REPEATER_SUPPORT */
#endif /* RLT_MAC */

#ifdef DOT11_N_SUPPORT
void AsicEnableRDG(
PRTMP_ADAPTER pAd);

void AsicDisableRDG(
PRTMP_ADAPTER pAd);
#endif /* DOT11_N_SUPPORT */

void AsicDisableSync(
 PRTMP_ADAPTER   pAd);

void AsicEnableBssSync(
 PRTMP_ADAPTER   pAd);

void AsicEnableIbssSync(
 PRTMP_ADAPTER   pAd);

void AsicSetEdcaParm(
PRTMP_ADAPTER pAd,
PEDCA_PARM    pEdcaParm);

void AsicSetSlotTime(
PRTMP_ADAPTER pAd,
unsigned char bUseshortSlotTime);

void AsicAddSharedKeyEntry(
PRTMP_ADAPTER pAd,
unsigned char         BssIndex,
unsigned char         KeyIdx,
PCIPHER_KEY	 pCipherKey);

void AsicRemoveSharedKeyEntry(
PRTMP_ADAPTER pAd,
unsigned char         BssIndex,
unsigned char         KeyIdx);

void AsicUpdateWCIDIVEIV(
PRTMP_ADAPTER pAd,
unsigned short		WCID,
unsigned long        uIV,
unsigned long        uEIV);

void AsicUpdateRxWCIDTable(
PRTMP_ADAPTER pAd,
unsigned short		WCID,
unsigned char*        pAddr);

void AsicUpdateWcidAttributeEntry(
PRTMP_ADAPTER	pAd,
unsigned char			BssIdx,
	unsigned char		 	KeyIdx,
	unsigned char		 	CipherAlg,
unsigned char				Wcid,
unsigned char				KeyTabFlag);

void AsicAddPairwiseKeyEntry(
PRTMP_ADAPTER 	pAd,
unsigned char			WCID,
PCIPHER_KEY		pCipherKey);

void AsicRemovePairwiseKeyEntry(
PRTMP_ADAPTER  pAd,
unsigned char		 Wcid);

unsigned char AsicSendCommandToMcu(
PRTMP_ADAPTER pAd,
unsigned char         Command,
unsigned char         Token,
unsigned char         Arg0,
unsigned char         Arg1,
unsigned char in_atomic);

unsigned char AsicSendCommandToMcuBBP(
PRTMP_ADAPTER pAd,
unsigned char		 Command,
unsigned char		 Token,
unsigned char		 Arg0,
unsigned char		 Arg1,
unsigned char		FlgIsNeedLocked);





#ifdef STREAM_MODE_SUPPORT
unsigned intStreamModeRegVal(
RTMP_ADAPTER *pAd);

void AsicSetStreamMode(
RTMP_ADAPTER *pAd,
unsigned char* pMacAddr,
int chainIdx,
unsigned char bEnabled);

void RtmpStreamModeInit(
RTMP_ADAPTER *pAd);

/*
	Update the Tx chain address
	Parameters
		pAd: The adapter data structure
		pMacAddress: The MAC address of the peer STA

	Return Value:
		None
*/
void AsicUpdateTxChainAddress(
PRTMP_ADAPTER pAd, 
unsigned char* pMacAddress);

int Set_StreamMode_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *         arg);

int Set_StreamModeMac_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);

int Set_StreamModeMCS_Proc(
    IN  PRTMP_ADAPTER   pAd,
    IN  char *         arg);
#endif /* STREAM_MODE_SUPPORT */

#ifdef WOW_SUPPORT
#ifdef RTMP_MAC_USB
/* For WOW, 8051 MUC send full frame */
void AsicWOWSendNullFrame(
    IN PRTMP_ADAPTER pAd,
    IN unsigned char TxRate,
    IN unsigned char bQosNull);
 
void AsicLoadWOWFirmware(
    IN PRTMP_ADAPTER pAd,
    IN unsigned char WOW);
#endif /* RTMP_MAC_USB */
#endif /* WOW_SUPPORT */

void MacAddrRandomBssid(
 PRTMP_ADAPTER   pAd, 
	unsigned char* pAddr);

void MgtMacHeaderInit(
 PRTMP_ADAPTER     pAd, 
PHEADER_802_11 pHdr80211, 
unsigned char SubType, 
unsigned char ToDs, 
unsigned char* pDA, 
unsigned char* pBssid);

void MlmeRadioOff(
PRTMP_ADAPTER pAd);

void MlmeRadioOn(
PRTMP_ADAPTER pAd);


void BssTableInit(
BSS_TABLE *Tab);

#ifdef DOT11_N_SUPPORT
void BATableInit(
PRTMP_ADAPTER pAd,
    IN BA_TABLE *Tab);

void BATableExit(	
RTMP_ADAPTER *pAd);
#endif /* DOT11_N_SUPPORT */

unsigned long BssTableSearch(
BSS_TABLE *Tab, 
unsigned char* pBssid,
unsigned char Channel);

unsigned long BssSsidTableSearch(
BSS_TABLE *Tab, 
unsigned char*    pBssid,
unsigned char*    pSsid,
unsigned char     SsidLen,
unsigned char     Channel);

unsigned long BssTableSearchWithSSID(
BSS_TABLE *Tab, 
unsigned char*    Bssid,
unsigned char*    pSsid,
unsigned char     SsidLen,
unsigned char     Channel);

unsigned long BssSsidTableSearchBySSID(
BSS_TABLE *Tab,
unsigned char*	 pSsid,
unsigned char	 SsidLen);

void BssTableDeleteEntry(
 PBSS_TABLE pTab, 
     unsigned char* pBssid,
     unsigned char Channel);

unsigned long BssTableSetEntry(
PRTMP_ADAPTER pAd, 
	BSS_TABLE *Tab, 
BCN_IE_LIST *ie_list,
char Rssi,
unsigned short LengthVIE,	
PNDIS_802_11_VARIABLE_IEs pVIE);


#ifdef DOT11_N_SUPPORT
void BATableInsertEntry(
    IN	PRTMP_ADAPTER	pAd, 
unsigned short Aid,    
    IN unsigned short		TimeOutValue,
unsigned short		StartingSeq,
    IN unsigned char TID, 
unsigned char BAWinSize, 
unsigned char OriginatorStatus, 
    IN unsigned char IsRecipient);

#ifdef DOT11N_DRAFT3
void Bss2040CoexistTimeOut(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);


void TriEventInit(
PRTMP_ADAPTER	pAd);

int TriEventTableSetEntry(
PRTMP_ADAPTER	pAd, 
	TRIGGER_EVENT_TAB *Tab, 
unsigned char* pBssid, 
HT_CAPABILITY_IE *pHtCapability,
unsigned char			HtCapabilityLen,
unsigned char			RegClass,
unsigned char ChannelNo);

#endif /* DOT11N_DRAFT3 */
#endif /* DOT11_N_SUPPORT */

void BssTableSsidSort(
 PRTMP_ADAPTER   pAd, 
	BSS_TABLE *OutTab, 
 char Ssid[], 
 unsigned char SsidLen);

void BssTableSortByRssi(
BSS_TABLE *OutTab);

void BssCipherParse(
 PBSS_ENTRY  pBss);

NDIS_STATUS  MlmeQueueInit(
PRTMP_ADAPTER pAd,
MLME_QUEUE *Queue);

void MlmeQueueDestroy(
MLME_QUEUE *Queue);

unsigned char MlmeEnqueue(
PRTMP_ADAPTER pAd, 
unsigned long Machine, 
unsigned long MsgType, 
unsigned long MsgLen, 
void*Msg,
unsigned long Priv);

unsigned char MlmeEnqueueForRecv(
 PRTMP_ADAPTER   pAd, 
unsigned long Wcid, 
unsigned long TimeStampHigh, 
unsigned long TimeStampLow, 
unsigned char Rssi0, 
unsigned char Rssi1, 
unsigned char Rssi2, 
unsigned long MsgLen, 
void *Msg,
unsigned char Signal,
unsigned char OpMode);


unsigned char MlmeDequeue(
MLME_QUEUE *Queue, 
	MLME_QUEUE_ELEM **Elem);

void   MlmeRestartStateMachine(
 PRTMP_ADAPTER   pAd);

unsigned char  MlmeQueueEmpty(
MLME_QUEUE *Queue);

unsigned char  MlmeQueueFull(
MLME_QUEUE *Queue,
unsigned char SendId);

unsigned char  MsgTypeSubst(
PRTMP_ADAPTER pAd, 
PFRAME_802_11 pFrame, 
	int *Machine, 
	int *MsgType);

void StateMachineInit(
STATE_MACHINE *Sm, 
STATE_MACHINE_FUNC Trans[], 
unsigned long StNr, 
unsigned long MsgNr, 
STATE_MACHINE_FUNC DefFunc, 
unsigned long InitState, 
unsigned long Base);

void StateMachineSetAction(
STATE_MACHINE *S, 
unsigned long St, 
	unsigned long Msg, 
STATE_MACHINE_FUNC F);

void StateMachinePerformAction(
 PRTMP_ADAPTER   pAd, 
STATE_MACHINE *S, 
MLME_QUEUE_ELEM *Elem,
unsigned long CurrState);

void Drop(
 PRTMP_ADAPTER   pAd, 
MLME_QUEUE_ELEM *Elem);

void AssocStateMachineInit(
 PRTMP_ADAPTER   pAd, 
 STATE_MACHINE *Sm, 
	STATE_MACHINE_FUNC Trans[]);

void ReassocTimeout(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void AssocTimeout(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void DisassocTimeout(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

/*---------------------------------------------- */
void MlmeDisassocReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void MlmeAssocReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void MlmeReassocReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void MlmeDisassocReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerAssocRspAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerReassocRspAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerDisassocAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void DisassocTimeoutAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void AssocTimeoutAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void ReassocTimeoutAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void Cls3errAction(
 PRTMP_ADAPTER   pAd, 
 unsigned char* pAddr);

void InvalidStateWhenAssoc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void InvalidStateWhenReassoc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void InvalidStateWhenDisassociate(
 PRTMP_ADAPTER pAd, 
 MLME_QUEUE_ELEM *Elem);

#ifdef RTMP_MAC_USB
void MlmeCntlConfirm(
PRTMP_ADAPTER pAd, 
unsigned long MsgType, 
unsigned short Msg);
#endif /* RTMP_MAC_USB */

void ComposePsPoll(
 PRTMP_ADAPTER   pAd);

void ComposeNullFrame(
 PRTMP_ADAPTER pAd);

void AssocPostProc(
 PRTMP_ADAPTER pAd, 
 unsigned char* pAddr2, 
 unsigned short CapabilityInfo, 
 unsigned short Aid, 
 unsigned char SupRate[], 
 unsigned char SupRateLen,
 unsigned char ExtRate[],
 unsigned char ExtRateLen,
PEDCA_PARM pEdcaParm,
IE_LISTS *ie_list,
HT_CAPABILITY_IE *pHtCapability,
 unsigned char HtCapabilityLen,
ADD_HT_INFO_IE *pAddHtInfo);

void AuthStateMachineInit(
 PRTMP_ADAPTER   pAd, 
PSTATE_MACHINE sm, 
	STATE_MACHINE_FUNC Trans[]);

void AuthTimeout(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void MlmeAuthReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerAuthRspAtSeq2Action(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerAuthRspAtSeq4Action(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void AuthTimeoutAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void Cls2errAction(
 PRTMP_ADAPTER   pAd, 
 unsigned char* pAddr);

void MlmeDeauthReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void InvalidStateWhenAuth(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

/*============================================= */

void AuthRspStateMachineInit(
 PRTMP_ADAPTER   pAd, 
 PSTATE_MACHINE Sm, 
 STATE_MACHINE_FUNC Trans[]);

void PeerDeauthAction(
PRTMP_ADAPTER pAd, 
MLME_QUEUE_ELEM *Elem);

void PeerAuthSimpleRspGenAndSend(
 PRTMP_ADAPTER   pAd, 
 PHEADER_802_11  pHdr80211, 
 unsigned short Alg, 
 unsigned short Seq, 
 unsigned short Reason, 
 unsigned short Status);

/* */
/* Private routines in dls.c */
/* */

#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
void DlsStateMachineInit(
    IN PRTMP_ADAPTER pAd, 
    IN STATE_MACHINE *Sm, 
    STATE_MACHINE_FUNC Trans[]);

void MlmeDlsReqAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

void PeerDlsReqAction(
    IN PRTMP_ADAPTER	pAd, 
    IN MLME_QUEUE_ELEM	*Elem);

void PeerDlsRspAction(
    IN PRTMP_ADAPTER	pAd, 
    IN MLME_QUEUE_ELEM	*Elem);

void MlmeDlsTearDownAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem);

void PeerDlsTearDownAction(
    IN PRTMP_ADAPTER	pAd, 
    IN MLME_QUEUE_ELEM	*Elem);

void RTMPCheckDLSTimeOut(
PRTMP_ADAPTER	pAd);

unsigned char RTMPRcvFrameDLSCheck(
RTMP_ADAPTER *pAd,
PHEADER_802_11 pHeader,
unsigned long Len,
RXD_STRUC *pRxD);

int	RTMPCheckDLSFrame(
RTMP_ADAPTER *pAd,
unsigned char *pDA);

void RTMPSendDLSTearDownFrame(
PRTMP_ADAPTER	pAd,
 unsigned char*          pDA);

NDIS_STATUS RTMPSendSTAKeyRequest(
PRTMP_ADAPTER	pAd,
unsigned char*			pDA);

NDIS_STATUS RTMPSendSTAKeyHandShake(
PRTMP_ADAPTER	pAd,
unsigned char*			pDA);

void DlsTimeoutAction(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

unsigned char MlmeDlsReqSanity(
PRTMP_ADAPTER pAd, 
    IN void*Msg, 
    IN unsigned long MsgLen,
    PRT_802_11_DLS *pDLS,
    Punsigned short pReason);

int Set_DlsEntryInfo_Display_Proc(
PRTMP_ADAPTER pAd, 
unsigned char* arg);

MAC_TABLE_ENTRY *MacTableInsertDlsEntry(
 PRTMP_ADAPTER   pAd, 
 unsigned char*	pAddr,
 unsigned int	DlsEntryIdx);

unsigned char MacTableDeleteDlsEntry(
PRTMP_ADAPTER pAd,
unsigned short wcid,
unsigned char* pAddr);

MAC_TABLE_ENTRY *DlsEntryTableLookup(
PRTMP_ADAPTER pAd,
unsigned char*	pAddr,
unsigned char	bResetIdelCount);

MAC_TABLE_ENTRY *DlsEntryTableLookupByWcid(
PRTMP_ADAPTER pAd,
unsigned char	wcid,
unsigned char*	pAddr,
unsigned char	bResetIdelCount);

int	Set_DlsAddEntry_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_DlsTearDownEntry_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);
#endif /* QOS_DLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

#ifdef QOS_DLS_SUPPORT
unsigned char PeerDlsReqSanity(
    IN PRTMP_ADAPTER pAd, 
    IN void*Msg, 
    IN unsigned long MsgLen,
    unsigned char* pDA,
    unsigned char* pSA,
    unsigned short *pCapabilityInfo, 
    unsigned short *pDlsTimeout,
    unsigned char *pRatesLen,
    unsigned char Rates[],
    unsigned char *pHtCapabilityLen,
    HT_CAPABILITY_IE *pHtCapability);

unsigned char PeerDlsRspSanity(
    IN PRTMP_ADAPTER pAd, 
    IN void*Msg, 
    IN unsigned long MsgLen,
    unsigned char* pDA,
    unsigned char* pSA,
    unsigned short *pCapabilityInfo, 
    unsigned short *pStatus,
    unsigned char *pRatesLen,
    unsigned char Rates[],
    unsigned char *pHtCapabilityLen,
    HT_CAPABILITY_IE *pHtCapability);

unsigned char PeerDlsTearDownSanity(
    IN PRTMP_ADAPTER pAd, 
    IN void*Msg, 
    IN unsigned long MsgLen,
    unsigned char* pDA,
    unsigned char* pSA,
    unsigned short *pReason);
#endif /* QOS_DLS_SUPPORT */

unsigned char PeerProbeReqSanity(
    IN PRTMP_ADAPTER pAd, 
    IN void*Msg, 
    IN unsigned long MsgLen, 
    unsigned char* pAddr2,
    char Ssid[], 
    unsigned char *SsidLen,
    unsigned char *bRequestRssi);

/*======================================== */

void SyncStateMachineInit(
 PRTMP_ADAPTER   pAd, 
 STATE_MACHINE *Sm, 
	STATE_MACHINE_FUNC Trans[]);

void BeaconTimeout(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void ScanTimeout(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void MlmeScanReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void InvalidStateWhenScan(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void InvalidStateWhenJoin(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void InvalidStateWhenStart(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerBeacon(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void EnqueueProbeRequest(
PRTMP_ADAPTER pAd);

unsigned char ScanRunning(
		IN PRTMP_ADAPTER pAd);
/*========================================= */

void MlmeCntlInit(
 PRTMP_ADAPTER   pAd, 
 STATE_MACHINE *S, 
	STATE_MACHINE_FUNC Trans[]);

void MlmeCntlMachinePerformAction(
 PRTMP_ADAPTER   pAd, 
 STATE_MACHINE *S, 
 MLME_QUEUE_ELEM *Elem);

void CntlIdleProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void CntlOidScanProc(
 PRTMP_ADAPTER pAd,
 MLME_QUEUE_ELEM *Elem);

void CntlOidSsidProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM * Elem);

void CntlOidRTBssidProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM * Elem);

void CntlMlmeRoamingProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM * Elem);

void CntlWaitDisassocProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void CntlWaitJoinProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void CntlWaitReassocProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void CntlWaitStartProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void CntlWaitAuthProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void CntlWaitAuthProc2(
 PRTMP_ADAPTER pAd, 
 MLME_QUEUE_ELEM *Elem);

void CntlWaitAssocProc(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

#ifdef QOS_DLS_SUPPORT
void CntlOidDLSSetupProc(
PRTMP_ADAPTER pAd,
MLME_QUEUE_ELEM *Elem);
#endif /* QOS_DLS_SUPPORT */


void LinkUp(
 PRTMP_ADAPTER   pAd,
 unsigned char BssType);

void LinkDown(
 PRTMP_ADAPTER   pAd,
 unsigned char         IsReqFromAP);

void IterateOnBssTab(
 PRTMP_ADAPTER   pAd);

void IterateOnBssTab2(
 PRTMP_ADAPTER   pAd);;

void JoinParmFill(
 PRTMP_ADAPTER   pAd, 
 MLME_JOIN_REQ_STRUCT *JoinReq, 
 unsigned long BssIdx);

void AssocParmFill(
 PRTMP_ADAPTER   pAd, 
MLME_ASSOC_REQ_STRUCT *AssocReq, 
 unsigned char* pAddr, 
 unsigned short CapabilityInfo, 
 unsigned long Timeout, 
 unsigned short Listenintv);

void ScanParmFill(
 PRTMP_ADAPTER   pAd, 
 MLME_SCAN_REQ_STRUCT *ScanReq, 
 char Ssid[], 
 unsigned char SsidLen, 
 unsigned char BssType, 
 unsigned char ScanType); 

void DisassocParmFill(
 PRTMP_ADAPTER   pAd, 
 MLME_DISASSOC_REQ_STRUCT *DisassocReq, 
 unsigned char* pAddr, 
 unsigned short Reason);

void StartParmFill(
 PRTMP_ADAPTER   pAd, 
 MLME_START_REQ_STRUCT *StartReq, 
 char Ssid[], 
 unsigned char SsidLen);

void AuthParmFill(
 PRTMP_ADAPTER   pAd, 
 MLME_AUTH_REQ_STRUCT *AuthReq, 
 unsigned char* pAddr, 
 unsigned short Alg);

void EnqueuePsPoll(
 PRTMP_ADAPTER   pAd);

void EnqueueBeaconFrame(
 PRTMP_ADAPTER   pAd); 

void MlmeJoinReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void MlmeScanReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void MlmeStartReqAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void MlmeForceJoinReqAction(
PRTMP_ADAPTER pAd,
MLME_QUEUE_ELEM *Elem);

void MlmeForceScanReqAction(
PRTMP_ADAPTER pAd,
MLME_QUEUE_ELEM *Elem);

void ScanTimeoutAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void BeaconTimeoutAtJoinAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerBeaconAtScanAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerBeaconAtJoinAction(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerBeacon(
 PRTMP_ADAPTER   pAd, 
 MLME_QUEUE_ELEM *Elem);

void PeerProbeReqAction(
 PRTMP_ADAPTER pAd, 
 MLME_QUEUE_ELEM *Elem);

void ScanNextChannel(
 PRTMP_ADAPTER   pAd,
unsigned char	OpMode);


unsigned long MakeIbssBeacon(
 PRTMP_ADAPTER   pAd);

#ifdef CONFIG_STA_SUPPORT
void InitChannelRelatedValue(
 PRTMP_ADAPTER   pAd);

void AdjustChannelRelatedValue(
PRTMP_ADAPTER pAd,
	unsigned char *pBwFallBack,
unsigned short ifIndex,
unsigned char BandWidth,
unsigned char PriCh,
unsigned char ExtraCh);
#endif /* CONFIG_STA_SUPPORT */

unsigned char MlmeScanReqSanity(
 PRTMP_ADAPTER   pAd, 
 void*Msg, 
 unsigned long MsgLen, 
	unsigned char *BssType, 
	char ssid[], 
	unsigned char *SsidLen, 
	unsigned char *ScanType);


unsigned char PeerBeaconAndProbeRspSanity_Old(
 PRTMP_ADAPTER   pAd, 
 void*Msg, 
 unsigned long MsgLen, 
 unsigned char MsgChannel,
	unsigned char* pAddr2, 
	unsigned char* pBssid, 
	char Ssid[], 
	unsigned char *pSsidLen, 
	unsigned char *pBssType, 
	unsigned short *pBeaconPeriod, 
	unsigned char *pChannel, 
	unsigned char *pNewChannel, 
	unsigned long long Timestamp, 
	CF_PARM *pCfParm, 
	unsigned short *pAtimWin, 
	unsigned short *pCapabilityInfo, 
	unsigned char *pErp,
	unsigned char *pDtimCount, 
	unsigned char *pDtimPeriod, 
	unsigned char *pBcastFlag, 
	unsigned char *pMessageToMe, 
	unsigned char SupRate[],
	unsigned char *pSupRateLen,
	unsigned char ExtRate[],
	unsigned char *pExtRateLen,
	OUT	unsigned char *pCkipFlag,
	OUT	unsigned char *pAironetCellPowerLimit,
	PEDCA_PARM       pEdcaParm,
	PQBSS_LOAD_PARM  pQbssLoad,
	PQOS_CAPABILITY_PARM pQosCapability,
	unsigned long *pRalinkIe,
	unsigned char		 *pHtCapabilityLen,
#ifdef CONFIG_STA_SUPPORT
	unsigned char		 *pPreNHtCapabilityLen,
#endif /* CONFIG_STA_SUPPORT */
	HT_CAPABILITY_IE *pHtCapability,
	EXT_CAP_INFO_ELEMENT *pExtCapInfo,
	unsigned char		 *AddHtInfoLen,
	ADD_HT_INFO_IE *AddHtInfo,
	unsigned char *NewExtChannel,
	unsigned short *LengthVIE,
	PNDIS_802_11_VARIABLE_IEs pVIE);


unsigned char PeerBeaconAndProbeRspSanity(
PRTMP_ADAPTER pAd,
void*Msg, 
unsigned long MsgLen, 
unsigned char  MsgChannel,
	BCN_IE_LIST *ie_list,
	unsigned short *LengthVIE,	
	PNDIS_802_11_VARIABLE_IEs pVIE);


#ifdef DOT11_N_SUPPORT
#ifdef DOT11N_DRAFT3
unsigned char PeerBeaconAndProbeRspSanity2(
PRTMP_ADAPTER pAd, 
void*Msg, 
unsigned long MsgLen, 
OVERLAP_BSS_SCAN_IE *BssScan,
	unsigned char 	*RegClass);
#endif /* DOT11N_DRAFT3 */
#endif /* DOT11_N_SUPPORT */

unsigned char PeerAddBAReqActionSanity(
    IN PRTMP_ADAPTER pAd, 
    IN void*pMsg, 
    IN unsigned long MsgLen,
	unsigned char* pAddr2);

unsigned char PeerAddBARspActionSanity(
    IN PRTMP_ADAPTER pAd, 
    IN void*pMsg, 
    IN unsigned long MsgLen);

unsigned char PeerDelBAActionSanity(
    IN PRTMP_ADAPTER pAd, 
    IN unsigned char Wcid, 
    IN void*pMsg, 
    IN unsigned long MsgLen);

unsigned char MlmeAssocReqSanity(
 PRTMP_ADAPTER   pAd, 
 void*Msg, 
 unsigned long MsgLen, 
	unsigned char* pApAddr, 
	unsigned short *CapabilityInfo, 
	unsigned long *Timeout, 
	unsigned short *Listenintv);

unsigned char MlmeAuthReqSanity(
 PRTMP_ADAPTER   pAd, 
 void*Msg, 
 unsigned long MsgLen, 
	unsigned char* pAddr, 
	unsigned long *Timeout, 
	unsigned short *Alg);

unsigned char MlmeStartReqSanity(
 PRTMP_ADAPTER   pAd, 
 void*Msg, 
 unsigned long MsgLen, 
	char Ssid[], 
	unsigned char *Ssidlen);

unsigned char PeerAuthSanity(
 PRTMP_ADAPTER   pAd, 
 void*Msg, 
 unsigned long MsgLen, 
	unsigned char* pAddr, 
	unsigned short *Alg, 
	unsigned short *Seq, 
	unsigned short *Status, 
	char ChlgText[]);

unsigned char PeerAssocRspSanity(
 PRTMP_ADAPTER   pAd, 
    IN void*pMsg, 
 unsigned long MsgLen, 
	unsigned char* pAddr2, 
	unsigned short *pCapabilityInfo, 
	unsigned short *pStatus, 
	unsigned short *pAid, 
	unsigned char SupRate[], 
	unsigned char *pSupRateLen,
	unsigned char ExtRate[],
	unsigned char *pExtRateLen,
    HT_CAPABILITY_IE		*pHtCapability,
    ADD_HT_INFO_IE		*pAddHtInfo,	/* AP might use this additional ht info IE */
    unsigned char			*pHtCapabilityLen,
    unsigned char			*pAddHtInfoLen,
    unsigned char			*pNewExtChannelOffset,
	PEDCA_PARM pEdcaParm,
	EXT_CAP_INFO_ELEMENT *pExtCapInfo,
	unsigned char *pCkipFlag,
	IE_LISTS *ie_list);

unsigned char PeerDisassocSanity(
 PRTMP_ADAPTER   pAd, 
 void*Msg, 
 unsigned long MsgLen, 
	unsigned char* pAddr2, 
	unsigned short *Reason);

unsigned char PeerDeauthSanity(
 PRTMP_ADAPTER   pAd, 
 void*Msg, 
 unsigned long MsgLen, 
	unsigned char* pAddr1,
	unsigned char* pAddr2, 
	unsigned char* pAddr3, 
	unsigned short *Reason);

unsigned char GetTimBit(
 char *Ptr, 
 unsigned short Aid, 
	unsigned char *TimLen, 
	unsigned char *BcastFlag, 
	unsigned char *DtimCount, 
	unsigned char *DtimPeriod, 
	unsigned char *MessageToMe);

unsigned char ChannelSanity(
PRTMP_ADAPTER pAd, 
unsigned char channel);

NDIS_802_11_NETWORK_TYPE NetworkTypeInUseSanity(
PBSS_ENTRY pBss);

unsigned char MlmeDelBAReqSanity(
    IN PRTMP_ADAPTER pAd, 
    IN void*Msg, 
    IN unsigned long MsgLen);

unsigned char MlmeAddBAReqSanity(
    IN PRTMP_ADAPTER pAd, 
    IN void*Msg, 
    IN unsigned long MsgLen, 
    unsigned char* pAddr2);

unsigned long MakeOutgoingFrame(
	unsigned char *Buffer, 
	unsigned long *Length, ...);

unsigned char RandomByte(
 PRTMP_ADAPTER   pAd);

unsigned char RandomByte2(
 PRTMP_ADAPTER   pAd);

void AsicUpdateAutoFallBackTable(
PRTMP_ADAPTER	pAd,
unsigned char*			pTxRate);



void MlmePeriodicExec(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void LinkDownExec(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void LinkUpExec(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void STAMlmePeriodicExec(
	PRTMP_ADAPTER pAd);

void MlmeAutoScan(
PRTMP_ADAPTER pAd);

void MlmeAutoReconnectLastSSID(
PRTMP_ADAPTER pAd);

unsigned char MlmeValidateSSID(
unsigned char* pSsid,
unsigned char  SsidLen); 

void MlmeCheckForRoaming(
PRTMP_ADAPTER pAd,
unsigned long    Now32);

unsigned char MlmeCheckForFastRoaming(
 PRTMP_ADAPTER   pAd);

#ifdef TXBF_SUPPORT
unsigned char MlmeTxBfAllowed(
PRTMP_ADAPTER 		pAd,
PMAC_TABLE_ENTRY		pEntry,
struct _RTMP_RA_LEGACY_TB *pTxRate);
#endif /* TXBF_SUPPORT */

#ifdef AGS_SUPPORT
int Show_AGS_Proc(
    IN  PRTMP_ADAPTER	pAd, 
    IN  char *			arg);

#ifdef CONFIG_STA_SUPPORT
void MlmeDynamicTxRateSwitchingAGS(
PRTMP_ADAPTER pAd, 
PMAC_TABLE_ENTRY pEntry, 
unsigned char* pTable, 
unsigned char TableSize, 
PAGS_STATISTICS_INFO pAGSStatisticsInfo,
unsigned char InitTxRateIdx);

void StaQuickResponeForRateUpExecAGS(
PRTMP_ADAPTER pAd, 
PMAC_TABLE_ENTRY pEntry, 
unsigned char* pTable, 
unsigned char TableSize, 
PAGS_STATISTICS_INFO pAGSStatisticsInfo,
unsigned char InitTxRateIdx);
#endif /* CONFIG_STA_SUPPORT */

#endif /* AGS_SUPPORT */

void MlmeCalculateChannelQuality(
PRTMP_ADAPTER pAd,
PMAC_TABLE_ENTRY pMacEntry,
unsigned long Now);

void MlmeCheckPsmChange(
PRTMP_ADAPTER pAd,
unsigned long    Now32);

void MlmeSetPsmBit(
PRTMP_ADAPTER pAd, 
unsigned short psm);

void MlmeSetTxPreamble(
PRTMP_ADAPTER pAd, 
unsigned short TxPreamble);

void UpdateBasicRateBitmap(
PRTMP_ADAPTER	pAd);

void MlmeUpdateTxRates(
PRTMP_ADAPTER 	pAd,
	unsigned char		 	bLinkUp,
unsigned char			apidx);

#ifdef DOT11_N_SUPPORT
void MlmeUpdateHtTxRates(
PRTMP_ADAPTER 		pAd,
unsigned char				apidx);
#endif /* DOT11_N_SUPPORT */

void   RTMPCheckRates(
     PRTMP_ADAPTER   pAd,
 unsigned char           SupRate[],
 unsigned char           *SupRateLen);

#ifdef CONFIG_STA_SUPPORT
unsigned char RTMPCheckChannel(
PRTMP_ADAPTER pAd,
unsigned char		CentralChannel,
unsigned char		Channel);
#endif /* CONFIG_STA_SUPPORT */

unsigned char RTMPCheckHt(
RTMP_ADAPTER *pAd,
unsigned char Wcid,
	HT_CAPABILITY_IE *pHtCapability,
	ADD_HT_INFO_IE *pAddHtInfo);

#ifdef DOT11_VHT_AC
unsigned char RTMPCheckVht(
RTMP_ADAPTER *pAd,
unsigned char Wcid,
VHT_CAP_IE *vht_cap,
VHT_OP_IE *vht_op);
#endif /* DOT11_VHT_AC */

void RTMPUpdateMlmeRate(
PRTMP_ADAPTER	pAd);

char RTMPMaxRssi(
PRTMP_ADAPTER	pAd,
char				Rssi0,
char				Rssi1,
char				Rssi2);

char RTMPAvgRssi(
        IN PRTMP_ADAPTER	pAd,
        IN RSSI_SAMPLE		*pRssi);


char RTMPMinSnr(
PRTMP_ADAPTER	pAd,
char				Snr0,
char				Snr1);

void AsicSetRxAnt(
PRTMP_ADAPTER	pAd,
unsigned char			Ant);

#ifdef RTMP_EFUSE_SUPPORT
int set_eFuseGetFreeBlockCount_Proc(  
   	IN	PRTMP_ADAPTER	pAd,
char *			arg);

int set_eFusedump_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

int set_eFuseLoadFromBin_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

void EFusePhysicalReadRegisters( 
PRTMP_ADAPTER	pAd, 
unsigned short Offset, 
unsigned short Length, 
	OUT	unsigned short* pData);

int RtmpEfuseSupportCheck(
RTMP_ADAPTER *pAd);

#ifdef RALINK_ATE
int set_eFuseBufferModeWriteBack_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);
#endif /* RALINK_ATE */
#endif /* RTMP_EFUSE_SUPPORT */





void AsicEvaluateRxAnt(
PRTMP_ADAPTER	pAd);

void AsicRxAntEvalTimeout(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void APSDPeriodicExec(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

unsigned char RTMPCheckEntryEnableAutoRateSwitch(
PRTMP_ADAPTER    pAd,
PMAC_TABLE_ENTRY	pEntry);

unsigned char RTMPStaFixedTxMode(
PRTMP_ADAPTER    pAd,
PMAC_TABLE_ENTRY	pEntry);

void RTMPUpdateLegacyTxSetting(
		unsigned char				fixed_tx_mode,
		PMAC_TABLE_ENTRY	pEntry);

unsigned char RTMPAutoRateSwitchCheck(
PRTMP_ADAPTER    pAd);

NDIS_STATUS MlmeInit(
 PRTMP_ADAPTER   pAd);


#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */

#ifdef RTMP_TEMPERATURE_COMPENSATION
void InitLookupTable(
PRTMP_ADAPTER pAd);
#endif /* RTMP_TEMPERATURE_COMPENSATION */

void MlmeHandler(
 PRTMP_ADAPTER   pAd);

void MlmeHalt(
 PRTMP_ADAPTER   pAd);

void MlmeResetRalinkCounters(
 PRTMP_ADAPTER   pAd);

void BuildChannelList(
PRTMP_ADAPTER pAd);

unsigned char FirstChannel(
 PRTMP_ADAPTER   pAd);

unsigned char NextChannel(
 PRTMP_ADAPTER   pAd, 
 unsigned char channel);

void ChangeToCellPowerLimit(
PRTMP_ADAPTER pAd,
unsigned char         AironetCellPowerLimit);

/* */
/* Prototypes of function definition in cmm_tkip.c */
/* */
void   RTMPInitMICEngine(
 PRTMP_ADAPTER   pAd,    
 unsigned char*          pKey,
 unsigned char*          pDA,
 unsigned char*          pSA,
 unsigned char           UserPriority,
 unsigned char*          pMICKey);

unsigned char RTMPTkipCompareMICValue(
 PRTMP_ADAPTER   pAd,
 unsigned char*          pSrc,
 unsigned char*          pDA,
 unsigned char*          pSA,
 unsigned char*          pMICKey,
unsigned char			UserPriority,
 unsigned int            Len);

void   RTMPCalculateMICValue(
 PRTMP_ADAPTER   pAd,
 PNDIS_PACKET    pPacket,
 unsigned char*          pEncap,
 PCIPHER_KEY     pKey,
unsigned char			apidx);

void   RTMPTkipAppendByte( 
 PTKIP_KEY_INFO  pTkip,  
 unsigned char           uChar);

void   RTMPTkipAppend( 
 PTKIP_KEY_INFO  pTkip,  
 unsigned char*          pSrc,
 unsigned int            nBytes);

void   RTMPTkipGetMIC( 
 PTKIP_KEY_INFO  pTkip);

/* */
/* Prototypes of function definition in cmm_cfg.c */
/* */
int RT_CfgSetCountryRegion(
PRTMP_ADAPTER	pAd, 
char *			arg,
int				band);

int RT_CfgSetWirelessMode(
PRTMP_ADAPTER	pAd, 
char *			arg);

unsigned char cfgmode_2_wmode(unsigned char cfg_mode);
unsigned char *wmode_2_str(unsigned char wmode);


int RT_CfgSetShortSlot(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	RT_CfgSetWepKey(
PRTMP_ADAPTER	pAd, 
char *			keyString,
CIPHER_KEY		*pSharedKey,
int				keyIdx);

int RT_CfgSetWPAPSKKey(
RTMP_ADAPTER	*pAd, 
char *		keyString,
int			keyStringLen,
unsigned char		*pHashStr,
int			hashStrLen,
	unsigned char*		pPMKBuf);

int	RT_CfgSetFixedTxPhyMode(
char *			arg);

int	RT_CfgSetMacAddress(
	PRTMP_ADAPTER 	pAd,
char *			arg);

int	RT_CfgSetTxMCSProc(
char *			arg,
	OUT	unsigned char			*pAutoRate);

int	RT_CfgSetAutoFallBack(
	PRTMP_ADAPTER 	pAd,
char *			arg);


int	Set_Antenna_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);


/* */
/* Prototypes of function definition in cmm_info.c */
/* */
NDIS_STATUS RTMPWPARemoveKeyProc(
 PRTMP_ADAPTER   pAd,
 void *          pBuf);

void   RTMPWPARemoveAllKeys(
 PRTMP_ADAPTER   pAd);

unsigned char RTMPCheckStrPrintAble(
    IN  char *pInPutStr, 
    IN  unsigned char strLen);
    
void   RTMPSetPhyMode(
 PRTMP_ADAPTER   pAd,
 unsigned long phymode);

void RTMPUpdateHTIE(
RT_HT_CAPABILITY	*pRtHt,
	unsigned char				*pMcsSet,
	OUT		HT_CAPABILITY_IE *pHtCapability,
	OUT		ADD_HT_INFO_IE		*pAddHtInfo);

void RTMPAddWcidAttributeEntry(
PRTMP_ADAPTER	pAd,
unsigned char			BssIdx,
	unsigned char		 	KeyIdx,
	unsigned char		 	CipherAlg,
	MAC_TABLE_ENTRY *pEntry);

char * GetEncryptType(
	char enc);

char * GetAuthMode(
	char auth);

#ifdef DOT11_N_SUPPORT
void RTMPSetHT(
PRTMP_ADAPTER	pAd,
OID_SET_HT_PHYMODE *pHTPhyMode);

void RTMPSetIndividualHT(
PRTMP_ADAPTER		pAd,
unsigned char				apidx);

unsigned char get_cent_ch_by_htinfo(
	RTMP_ADAPTER *pAd,
	ADD_HT_INFO_IE *ht_op,
	HT_CAPABILITY_IE *ht_cap);

int get_ht_cent_ch(RTMP_ADAPTER *pAd, unsigned char *rf_bw, unsigned char *ext_ch);
int ht_mode_adjust(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry, HT_CAPABILITY_IE *peer, RT_HT_CAPABILITY *my);
int set_ht_fixed_mcs(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry, unsigned char fixed_mcs, unsigned char mcs_bound);
int get_ht_max_mcs(RTMP_ADAPTER *pAd, unsigned char *desire_mcs, unsigned char *cap_mcs);
#endif /* DOT11_N_SUPPORT */

void RTMPDisableDesiredHtInfo(
PRTMP_ADAPTER	pAd);

#ifdef SYSTEM_LOG_SUPPORT
void RtmpDrvSendWirelessEvent(
void		*pAdSrc,
unsigned short			Event_flag,
unsigned char* 			pAddr,
 unsigned char			BssIdx,
char			Rssi);
#else
#define RtmpDrvSendWirelessEvent(_pAd, _Event_flag, _pAddr, _BssIdx, _Rssi)
#endif /* SYSTEM_LOG_SUPPORT */
	
char    ConvertToRssi(
PRTMP_ADAPTER  pAd,
char				Rssi,
unsigned char    RssiNumber);

char    ConvertToSnr(
PRTMP_ADAPTER  pAd,
unsigned char				Snr);

#ifdef DOT11N_DRAFT3
void BuildEffectedChannelList(
PRTMP_ADAPTER pAd);


void DeleteEffectedChannelList(
PRTMP_ADAPTER pAd);

void CntlChannelWidth(
PRTMP_ADAPTER	pAd,
unsigned char			PrimaryChannel,
unsigned char			CentralChannel,	
unsigned char			ChannelWidth,
unsigned char			SecondaryChannelOffset);

#endif /* DOT11N_DRAFT3 */


void APAsicEvaluateRxAnt(
PRTMP_ADAPTER	pAd);


void APAsicRxAntEvalTimeout(
PRTMP_ADAPTER	pAd);


/* */
/* function prototype in ap_wpa.c */
/* */
void RTMPGetTxTscFromAsic(
 PRTMP_ADAPTER   pAd,
unsigned char			apidx,
	OUT	unsigned char*			pTxTsc);

MAC_TABLE_ENTRY *PACInquiry(
 PRTMP_ADAPTER   pAd, 
 unsigned long           Wcid);

unsigned int	APValidateRSNIE(
PRTMP_ADAPTER    pAd,
PMAC_TABLE_ENTRY pEntry,
unsigned char*			pRsnIe,
unsigned char			rsnie_len);

void HandleCounterMeasure(
PRTMP_ADAPTER pAd, 
MAC_TABLE_ENTRY  *pEntry);

void WPAStart4WayHS(
 PRTMP_ADAPTER   pAd, 
 MAC_TABLE_ENTRY *pEntry,
unsigned long			Timeinterval);

void WPAStart2WayGroupHS(
 PRTMP_ADAPTER   pAd, 
 MAC_TABLE_ENTRY *pEntry);

void PeerPairMsg1Action(
PRTMP_ADAPTER pAd, 
MAC_TABLE_ENTRY  *pEntry,
MLME_QUEUE_ELEM *Elem);

void PeerPairMsg2Action(
PRTMP_ADAPTER pAd, 
MAC_TABLE_ENTRY  *pEntry,
MLME_QUEUE_ELEM *Elem);

void PeerPairMsg3Action(
PRTMP_ADAPTER pAd, 
MAC_TABLE_ENTRY  *pEntry,
MLME_QUEUE_ELEM *Elem);

void PeerPairMsg4Action(
PRTMP_ADAPTER pAd, 
MAC_TABLE_ENTRY  *pEntry,
MLME_QUEUE_ELEM *Elem);

void PeerGroupMsg1Action(
 PRTMP_ADAPTER    pAd, 
 PMAC_TABLE_ENTRY pEntry,
    IN  MLME_QUEUE_ELEM  *Elem);

void PeerGroupMsg2Action(
 PRTMP_ADAPTER    pAd, 
 PMAC_TABLE_ENTRY pEntry,
 void            *Msg,
 unsigned int             MsgLen);

void CMTimerExec(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void WPARetryExec(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

#ifdef TXBF_SUPPORT
void ETxBfProbeTimerExec(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2,
void *SystemSpecific3);
#endif /* TXBF_SUPPORT */

void EnqueueStartForPSKExec(
    IN void *SystemSpecific1, 
    IN void *FunctionContext, 
    IN void *SystemSpecific2, 
    IN void *SystemSpecific3); 


void RTMPHandleSTAKey(
    IN PRTMP_ADAPTER    pAdapter, 
    IN MAC_TABLE_ENTRY  *pEntry,
    IN MLME_QUEUE_ELEM  *Elem);

void MlmeDeAuthAction(
 PRTMP_ADAPTER    pAd, 
 PMAC_TABLE_ENTRY pEntry,
 unsigned short           Reason,
 unsigned char          bDataFrameFirst);


void GREKEYPeriodicExec(
 void *  SystemSpecific1, 
 void *  FunctionContext, 
 void *  SystemSpecific2, 
 void *  SystemSpecific3);

void AES_128_CMAC(
unsigned char*	key,
unsigned char*	input,
int		len,
	OUT	unsigned char*	mac);

#ifdef DOT1X_SUPPORT
void   WpaSend(
    IN  PRTMP_ADAPTER   pAdapter,
    IN  unsigned char*          pPacket,
    IN  unsigned long           Len);

void RTMPAddPMKIDCache(
 PRTMP_ADAPTER   		pAd,
int						apidx,
unsigned char*				pAddr,
unsigned char					*PMKID,
unsigned char					*PMK);

int RTMPSearchPMKIDCache(
 PRTMP_ADAPTER   pAd,
int				apidx,
unsigned char*		pAddr);

void RTMPDeletePMKIDCache(
 PRTMP_ADAPTER   pAd,
int				apidx,
 int				idx);

void RTMPMaintainPMKIDCache(
 PRTMP_ADAPTER   pAd);
#else
#define RTMPMaintainPMKIDCache(_pAd)
#endif /* DOT1X_SUPPORT */

#ifdef RESOURCE_PRE_ALLOC
void RTMPResetTxRxRingMemory(
 RTMP_ADAPTER   *pAd);
#endif /* RESOURCE_PRE_ALLOC */

void RTMPFreeTxRxRingMemory(
    IN  PRTMP_ADAPTER   pAd);

unsigned char RTMP_FillTxBlkInfo(
RTMP_ADAPTER *pAd,
TX_BLK *pTxBlk);

 void announce_802_3_packet(
void		*pAdSrc,
PNDIS_PACKET	pPacket,
unsigned char			OpMode);

#ifdef DOT11_N_SUPPORT
unsigned int BA_Reorder_AMSDU_Annnounce(
PRTMP_ADAPTER	pAd, 	
PNDIS_PACKET	pPacket,
unsigned char			OpMode);
#endif /* DOT11_N_SUPPORT */

struct net_device * get_netdev_from_bssid(
PRTMP_ADAPTER	pAd,
unsigned char			FromWhichBSSID);


#ifdef DOT11_N_SUPPORT
void ba_flush_reordering_timeout_mpdus(
PRTMP_ADAPTER	pAd, 
PBA_REC_ENTRY	pBAEntry,
unsigned long			Now32);


void BAOriSessionSetUp(
			IN PRTMP_ADAPTER    pAd, 
			IN MAC_TABLE_ENTRY	*pEntry,
			IN unsigned char			TID,
			IN unsigned short			TimeOut,
			IN unsigned long			DelayTime,
			IN unsigned char		isForced);

void BASessionTearDownALL(
OUT	PRTMP_ADAPTER pAd, 
	unsigned char Wcid);

void BAOriSessionTearDown(
OUT	PRTMP_ADAPTER	pAd, 
	unsigned char			Wcid,
	unsigned char			TID,
	unsigned char			bPassive,
	unsigned char			bForceSend);

void BARecSessionTearDown(
OUT	PRTMP_ADAPTER	pAd, 
	unsigned char			Wcid,
	unsigned char			TID,
	unsigned char			bPassive);
#endif /* DOT11_N_SUPPORT */

unsigned char ba_reordering_resource_init(PRTMP_ADAPTER pAd, int num);
void ba_reordering_resource_release(PRTMP_ADAPTER pAd);

int ComputeChecksum(
unsigned int PIN);

unsigned int GenerateWpsPinCode(
PRTMP_ADAPTER	pAd,
    IN  unsigned char         bFromApcli,
unsigned char	apidx);




#ifdef NintENDO_AP
void InitNintENDO_TABLE(
PRTMP_ADAPTER pAd);

unsigned char	CheckNintENDO_TABLE(
PRTMP_ADAPTER pAd, 
	char * pDS_Ssid, 
	unsigned char DS_SsidLen, 
	unsigned char* pDS_Addr);

unsigned char	DelNintENDO_ENTRY(
PRTMP_ADAPTER pAd,
	unsigned char * pDS_Addr);

void RTMPIoctlNintendoCapable(
PRTMP_ADAPTER	pAd, 
RTMP_IOCTL_INPUT_STRUCT			*wrq);

void RTMPIoctlNintendoGetTable(
PRTMP_ADAPTER	pAd, 
RTMP_IOCTL_INPUT_STRUCT			*wrq);

void RTMPIoctlNintendoSetTable(
PRTMP_ADAPTER	pAd, 
RTMP_IOCTL_INPUT_STRUCT			*wrq);

#endif /* NintENDO_AP */

unsigned char rtstrmactohex(
char * s1,
char * s2);

unsigned char rtstrcasecmp(
char * s1,
char * s2);

char * rtstrstruncasecmp(
char * s1,
char * s2);

char * rtstrstr(
char * s1,
const char * s2);

char * rstrtok(
char * s,
const char * ct);
	
int rtinet_aton(
	const char * cp, 
	unsigned int *addr);
	
/*//////// common ioctl functions ////////*/
int Set_DriverVersion_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Set_CountryRegion_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Set_CountryRegionABand_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Set_WirelessMode_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Set_MBSS_WirelessMode_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Set_Channel_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);
int	Set_ShortSlot_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

int	Set_TxPower_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

int Set_BGProtection_Proc(
 PRTMP_ADAPTER		pAd, 
 char *			arg);

int Set_TxPreamble_Proc(
 PRTMP_ADAPTER		pAd,
 char *			arg);

int Set_RTSThreshold_Proc(
 PRTMP_ADAPTER		pAd,
 char *			arg);

int Set_FragThreshold_Proc(
 PRTMP_ADAPTER		pAd,
 char *			arg);

int Set_TxBurst_Proc(
 PRTMP_ADAPTER		pAd,
 char *			arg);


#ifdef AGGREGATION_SUPPORT
int	Set_PktAggregate_Proc(
 PRTMP_ADAPTER		pAd,
 char *			arg);
#endif /* AGGREGATION_SUPPORT */

#ifdef INF_PPA_SUPPORT
int	Set_INF_AMAZON_SE_PPA_Proc(
PRTMP_ADAPTER	pAd, 
unsigned char*			arg);

int ifx_ra_start_xmit (
struct net_device *rx_dev, 
struct net_device *tx_dev,
struct sk_buff *skb,
int len);
#endif /* INF_PPA_SUPPORT */

int	Set_IEEE80211H_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

#ifdef EXT_BUILD_CHANNEL_LIST
int Set_ExtCountryCode_Proc(
    IN  PRTMP_ADAPTER   pAdapter,
    IN  char *          arg);

int Set_ExtDfsType_Proc(
    IN      PRTMP_ADAPTER   pAd,
    IN      char *         arg);

int Set_ChannelListAdd_Proc(
    IN      PRTMP_ADAPTER   pAd,
    IN      char *         arg);

int Set_ChannelListShow_Proc(
    IN      PRTMP_ADAPTER	pAd,
    IN      char *			arg);
int Set_ChannelListDel_Proc(
    IN      PRTMP_ADAPTER	pAd,
    IN      char *			arg);
#endif /* EXT_BUILD_CHANNEL_LIST */

#ifdef DBG
int	Set_Debug_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_DebugFunc_Proc(
RTMP_ADAPTER *pAd, 
char * arg);
#endif

#ifdef TXBF_SUPPORT
int	Set_ReadITxBf_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_ReadETxBf_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_WriteITxBf_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_WriteETxBf_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_StatITxBf_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_StatETxBf_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_TxBfTag_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Set_ITxBfTimeout_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);

int Set_ETxBfTimeout_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);

int	Set_InvTxBfTag_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_ITxBfCal_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_ITxBfDivCal_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_ITxBfLnaCal_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

int	Set_ETxBfEnCond_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Set_ETxBfCodebook_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);

int Set_ETxBfCoefficient_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);

int Set_ETxBfGrouping_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);

int Set_ETxBfNoncompress_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);

int Set_ETxBfIncapable_Proc(
    IN  PRTMP_ADAPTER   pAd,
    IN  char *          arg);

int	Set_NoSndgCntThrd_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_NdpSndgStreams_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_Trigger_Sounding_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_ITxBfEn_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

#endif /* TXBF_SUPPORT */

int Set_RateAdaptinterval(
RTMP_ADAPTER *pAd,
char * arg);


#ifdef PRE_ANT_SWITCH
int Set_PreAntSwitch_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *         arg);

int Set_PreAntSwitchRSSI_Proc(
    IN  PRTMP_ADAPTER   pAd,
    IN  char *         arg);

int Set_PreAntSwitchTimeout_Proc(
    IN  PRTMP_ADAPTER   pAd,
    IN  char *         arg);

#endif /* PRE_ANT_SWITCH */


#ifdef CFO_TRACK
int Set_CFOTrack_Proc(
    IN  PRTMP_ADAPTER   pAd,
    IN  char *         arg);

#ifdef CFO_TRACK
#endif /* CFO_TRACK */

#endif // CFO_TRACK //

#ifdef DBG_CTRL_SUPPORT
int Set_DebugFlags_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);

#ifdef INCLUDE_DEBUG_QUEUE
int Set_DebugQueue_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *         arg);

void dbQueueEnqueue(
unsigned char type,
unsigned char *data);

void dbQueueEnqueueTxFrame(
unsigned char *pTxWI,
unsigned char *pHeader_802_11);

void dbQueueEnqueueRxFrame(
unsigned char *pRxWI,
unsigned char *pHeader_802_11,
unsigned long flags);
#endif /* INCLUDE_DEBUG_QUEUE */
#endif /* DBG_CTRL_SUPPORT */

int	Show_DescInfo_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Show_MacTable_Proc(RTMP_ADAPTER *pAd, char * *arg);
int show_devinfo_proc(RTMP_ADAPTER *pAd, char * arg);
int show_trinfo_proc(RTMP_ADAPTER *pAd, char * arg);

int	Set_ResetStatCounter_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

#ifdef DOT11_N_SUPPORT
int	Set_BASetup_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_BADecline_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_BAOriTearDown_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_BARecTearDown_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtBw_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtMcs_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtGi_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtOpMode_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtStbc_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtHtc_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtExtcha_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtMpduDensity_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtBaWinSize_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtRdg_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtLinkAdapt_Proc(																																																																																																																																																																																																																																									
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtAmsdu_Proc(																																																																																																																																																																																																																																																																																																																			
PRTMP_ADAPTER	pAd, 
char *			arg);
	
int	Set_HtAutoBa_Proc(																																																																																																																																																																																																																																																																																																																			
PRTMP_ADAPTER	pAd, 
char *			arg);
					
int	Set_HtProtect_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

int	Set_HtMimoPs_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

#ifdef DOT11N_DRAFT3
int Set_HT_BssCoex_Proc(
PRTMP_ADAPTER		pAd,
char *				pParam);

int Set_HT_BssCoexApCntThr_Proc(
PRTMP_ADAPTER		pAd,
char *				pParam);
#endif /* DOT11N_DRAFT3 */



int	Set_ForceShortGI_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

int	Set_ForceGF_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);

int	SetCommonHT(RTMP_ADAPTER *pAd);

int	Set_SendPSMPAction_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

void convert_reordering_packet_to_preAMSDU_or_802_3_packet(
PRTMP_ADAPTER	pAd, 
RX_BLK			*pRxBlk,
 unsigned char			FromWhichBSSID);

int	Set_HtMIMOPSmode_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);


int	Set_HtTxBASize_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_HtDisallowTKIP_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int	Set_BurstMode_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);
#endif /* DOT11_N_SUPPORT */


#ifdef DOT11_VHT_AC
int Set_VhtBw_Proc(RTMP_ADAPTER *pAd, char * arg);
int Set_VhtStbc_Proc(RTMP_ADAPTER *pAd, char * arg);
int Set_VhtBwSignal_Proc(RTMP_ADAPTER *pAd, char * arg);
#endif /* DOT11_VHT_AC */


#ifdef APCLI_SUPPORT
int RTMPIoctlConnStatus(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

#endif /*APCLI_SUPPORT*/




#ifdef CONFIG_STA_SUPPORT
void RTMPSendDLSTearDownFrame(
PRTMP_ADAPTER	pAd,
unsigned char*			pDA);

#ifdef DOT11_N_SUPPORT
void QueryBATABLE(
 PRTMP_ADAPTER pAd,
	PQUERYBA_TABLE pBAT);
#endif /* DOT11_N_SUPPORT */

#ifdef WPA_SUPPLICANT_SUPPORT
int	    WpaCheckEapCode(
 PRTMP_ADAPTER   	pAd,
 unsigned char*				pFrame,
 unsigned short				FrameLen,
 unsigned short				OffSet);
#endif /* WPA_SUPPLICANT_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */



#ifdef DOT11_N_SUPPORT
void Handle_BSS_Width_Trigger_Events(RTMP_ADAPTER *pAd);

void build_ext_channel_switch_ie(
RTMP_ADAPTER *pAd,
HT_EXT_CHANNEL_SWITCH_ANNOUNCEMENT_IE *pIE);

void assoc_ht_info_debugshow(
RTMP_ADAPTER *pAd,
MAC_TABLE_ENTRY *pEntry,
unsigned char ht_cap_len,
HT_CAPABILITY_IE *pHTCapability);
#endif /* DOT11_N_SUPPORT */

unsigned char APRxDoneInterruptHandle(RTMP_ADAPTER *pAd);
unsigned char STARxDoneInterruptHandle(RTMP_ADAPTER *pAd, unsigned char argc);
unsigned char RxDoneInterruptHandle(RTMP_ADAPTER *pAd);

#ifdef DOT11_N_SUPPORT
/* AMPDU packet indication */
void Indicate_AMPDU_Packet(
PRTMP_ADAPTER	pAd,
RX_BLK			*pRxBlk,
unsigned char			FromWhichBSSID);

#ifdef HDR_TRANS_SUPPORT
void Indicate_AMPDU_Packet_Hdr_Trns(
PRTMP_ADAPTER	pAd,
RX_BLK			*pRxBlk,
unsigned char			FromWhichBSSID);
#endif /* HDR_TRANS_SUPPORT */

/* AMSDU packet indication */
void Indicate_AMSDU_Packet(
PRTMP_ADAPTER	pAd,
RX_BLK			*pRxBlk,
unsigned char			FromWhichBSSID);

void BaReOrderingBufferMaintain(
    IN PRTMP_ADAPTER pAd);
#endif /* DOT11_N_SUPPORT */

/* Normal legacy Rx packet indication */
void Indicate_Legacy_Packet(
PRTMP_ADAPTER	pAd,
RX_BLK			*pRxBlk,
unsigned char			FromWhichBSSID);

#ifdef HDR_TRANS_SUPPORT
void Indicate_Legacy_Packet_Hdr_Trns(
PRTMP_ADAPTER	pAd,
RX_BLK			*pRxBlk,
unsigned char			FromWhichBSSID);
#endif /* HDR_TRANS_SUPPORT */

void Indicate_EAPOL_Packet(
PRTMP_ADAPTER	pAd,
RX_BLK			*pRxBlk,
unsigned char			FromWhichBSSID);

unsigned int deaggregate_AMSDU_announce(
PRTMP_ADAPTER	pAd,
	PNDIS_PACKET		pPacket,
unsigned char*			pData,
unsigned long			DataSize,
unsigned char			OpMode);

#ifdef TXBF_SUPPORT
unsigned char clientSupportsETxBF(RTMP_ADAPTER *pAd, HT_BF_CAP *pTxBFCap);
void setETxBFCap(RTMP_ADAPTER *pAd, HT_BF_CAP *pTxBFCap);

#ifdef ETXBF_EN_COND3_SUPPORT
voidtxSndgSameMcs(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY * pEnt, unsigned char smoothMfb);
voidtxSndgOtherGroup(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry);
voidtxMrqInvTxBF(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry);
void ChooseBestMethod(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry, unsigned char mfb);
void RxBestSndg(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry);
#endif /* ETXBF_EN_COND3_SUPPORT */

void HandleBfFb(RTMP_ADAPTER *pAd, RX_BLK *pRxBlk);

voidTxBFInit(
PRTMP_ADAPTER 	pAd,
MAC_TABLE_ENTRY	*pEntry,
unsigned char			supportsETxBF);

void ETxBFProbing(
 	IN PRTMP_ADAPTER 	pAd,
MAC_TABLE_ENTRY	*pEntry);

voidTrigger_Sounding_Packet(
PRTMP_ADAPTER	pAd,
unsigned char			SndgType,
unsigned char			SndgBW,
unsigned char			SndgMcs,
 MAC_TABLE_ENTRY *pEntry);

void Rtmp_asic_set_bf(
RTMP_ADAPTER *pAd);

unsigned char rtmp_chk_itxbf_calibration(
RTMP_ADAPTER *pAd);

#endif /* TXBF_SUPPORT */

unsigned char CmdRspEventCallbackHandle(PRTMP_ADAPTER pAd, unsigned char* pRspBuffer);	


#ifdef CONFIG_STA_SUPPORT
/* remove LLC and get 802_3 Header */
#define  RTMP_802_11_REMOVE_LLC_AND_CONVERT_TO_802_3(_pRxBlk, _pHeader802_3)	\
{																				\
	unsigned char* _pRemovedLLCSNAP = NULL, *_pDA, *_pSA;                                 \
																				\
	if (RX_BLK_TEST_FLAG(_pRxBlk, fRX_WDS) || RX_BLK_TEST_FLAG(_pRxBlk, fRX_MESH)) \
	{                                                                           \
		_pDA = _pRxBlk->pHeader->Addr3;                                         \
		_pSA = (unsigned char*)_pRxBlk->pHeader + sizeof(HEADER_802_11);                \
	}                                                                           \
	else                                                                        \
	{                                                                           \
		if (RX_BLK_TEST_FLAG(_pRxBlk, fRX_INFRA))                              	\
		{                                                                       \
			_pDA = _pRxBlk->pHeader->Addr1;                                     \
		if (RX_BLK_TEST_FLAG(_pRxBlk, fRX_DLS))									\
			_pSA = _pRxBlk->pHeader->Addr2;										\
		else																	\
			_pSA = _pRxBlk->pHeader->Addr3;                                     \
		}                                                                       \
		else                                                                    \
		{                                                                       \
			_pDA = _pRxBlk->pHeader->Addr1;                                     \
			_pSA = _pRxBlk->pHeader->Addr2;                                     \
		}                                                                       \
	}                                                                           \
																				\
	CONVERT_TO_802_3(_pHeader802_3, _pDA, _pSA, _pRxBlk->pData, 				\
		_pRxBlk->DataSize, _pRemovedLLCSNAP);                                   \
}
#endif /* CONFIG_STA_SUPPORT */


unsigned char APFowardWirelessStaToWirelessSta(
PRTMP_ADAPTER	pAd,
PNDIS_PACKET	pPacket,
unsigned long			FromWhichBSSID);

void Announce_or_Forward_802_3_Packet(
PRTMP_ADAPTER	pAd,
PNDIS_PACKET	pPacket,
unsigned char			FromWhichBSSID);

void Sta_Announce_or_Forward_802_3_Packet(
PRTMP_ADAPTER	pAd,
PNDIS_PACKET	pPacket,
unsigned char			FromWhichBSSID);


#ifdef CONFIG_STA_SUPPORT
#define ANNOUNCE_OR_FORWARD_802_3_PACKET(_pAd, _pPacket, _FromWhichBSS)\
			Sta_Announce_or_Forward_802_3_Packet(_pAd, _pPacket, _FromWhichBSS);
			/*announce_802_3_packet(_pAd, _pPacket); */
#endif /* CONFIG_STA_SUPPORT */




/* Normal, AMPDU or AMSDU */
void CmmRxnonRalinkFrameIndicate(
RTMP_ADAPTER *pAd,
RX_BLK *pRxBlk,
unsigned char FromWhichBSSID);

#ifdef HDR_TRANS_SUPPORT
void CmmRxnonRalinkFrameIndicate_Hdr_Trns(
RTMP_ADAPTER *pAd,
RX_BLK *pRxBlk,
unsigned char FromWhichBSSID);
#endif /* HDR_TRANS_SUPPORT */

void CmmRxRalinkFrameIndicate(
RTMP_ADAPTER *pAd,
MAC_TABLE_ENTRY *pEntry,
RX_BLK *pRxBlk,
unsigned char FromWhichBSSID);

void Update_Rssi_Sample(
RTMP_ADAPTER *pAd,
RSSI_SAMPLE *pRssi,
RXWI_STRUC *pRxWI);

PNDIS_PACKET GetPacketFromRxRing(
RTMP_ADAPTER *pAd,
	RX_BLK *pRxBlk,
	unsigned char	 *pbReschedule,
	unsigned int *pRxPending,
	unsigned char *bCmdRspPacket);

PNDIS_PACKET RTMPDeFragmentDataFrame(
RTMP_ADAPTER *pAd,
RX_BLK *pRxBlk);

/*////////////////////////////////////*/

#if defined (AP_SCAN_SUPPORT) || defined (CONFIG_STA_SUPPORT)
void RTMPIoctlGetSiteSurvey(
PRTMP_ADAPTER	pAdapter, 
RTMP_IOCTL_INPUT_STRUCT *wrq);
#endif





#ifdef SNMP_SUPPORT
/*for snmp */
typedef struct _DefaultKeyIdxValue
{
	unsigned char	KeyIdx;
	unsigned char	Value[16];
} DefaultKeyIdxValue, *PDefaultKeyIdxValue;
#endif


#ifdef CONFIG_STA_SUPPORT

/* The radio capture header precedes the 802.11 header. */
typedef struct __attribute__ ((packed)) _ieee80211_radiotap_header {
    unsigned char	it_version;	/* Version 0. Only increases
				 * for drastic changes,
				 * introduction of compatible
				 * new fields does not count.
				 */
    unsigned char	it_pad;
    unsigned short     it_len;         /* length of the whole
				 * header in bytes, including
				 * it_version, it_pad,
				 * it_len, and data fields.
				 */
    unsigned int   it_present;	/* A bitmap telling which
					 * fields are present. Set bit 31
					 * (0x80000000) to extend the
					 * bitmap by another 32 bits.
					 * Additional extensions are made
					 * by setting bit 31.
					 */
}ieee80211_radiotap_header ;

enum ieee80211_radiotap_type {
    IEEE80211_RADIOTAP_TSFT = 0,
    IEEE80211_RADIOTAP_FLAGS = 1,
    IEEE80211_RADIOTAP_RATE = 2,
    IEEE80211_RADIOTAP_CHANNEL = 3,
    IEEE80211_RADIOTAP_FHSS = 4,
    IEEE80211_RADIOTAP_DBM_ANTSIGNAL = 5,
    IEEE80211_RADIOTAP_DBM_ANTNOISE = 6,
    IEEE80211_RADIOTAP_LOCK_QUALITY = 7,
    IEEE80211_RADIOTAP_TX_ATTENUATION = 8,
    IEEE80211_RADIOTAP_DB_TX_ATTENUATION = 9,
    IEEE80211_RADIOTAP_DBM_TX_POWER = 10,
    IEEE80211_RADIOTAP_ANTENNA = 11,
    IEEE80211_RADIOTAP_DB_ANTSIGNAL = 12,
    IEEE80211_RADIOTAP_DB_ANTNOISE = 13
};

#define WLAN_RADIOTAP_PRESENT (			\
	(1 << IEEE80211_RADIOTAP_TSFT)	|	\
	(1 << IEEE80211_RADIOTAP_FLAGS) |	\
	(1 << IEEE80211_RADIOTAP_RATE)  | 	\
	 0)

typedef struct _wlan_radiotap_header {
	ieee80211_radiotap_header wt_ihdr;
	long wt_tsft;
	unsigned char wt_flags;	
	unsigned char wt_rate;
} wlan_radiotap_header;
/* Definition from madwifi */


void STA_MonPktSend(
PRTMP_ADAPTER	pAd, 
RX_BLK			*pRxBlk);

void   RTMPSetDesiredRates(
    PRTMP_ADAPTER   pAdapter,
    long            Rates);

#ifdef XLINK_SUPPORT
int Set_XlinkMode_Proc(
PRTMP_ADAPTER	pAdapter, 
char *			arg);
#endif /* XLINK_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

int	Set_FixedTxMode_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

#ifdef CONFIG_APSTA_MIXED_SUPPORT
int	Set_OpMode_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);
#endif /* CONFIG_APSTA_MIXED_SUPPORT */

int Set_LongRetryLimit_Proc(
PRTMP_ADAPTER	pAdapter, 
char *			arg);

int Set_ShortRetryLimit_Proc(
PRTMP_ADAPTER	pAdapter, 
char *			arg);

int Set_AutoFallBack_Proc(
PRTMP_ADAPTER	pAdapter, 
char *			arg);


void RT28XXDMADisable(
RTMP_ADAPTER 		*pAd);

void RT28XXDMAEnable(
RTMP_ADAPTER 		*pAd);
	
void RT28xx_UpdateBeaconToAsic(
RTMP_ADAPTER * pAd, 
int apidx,
unsigned long BeaconLen,
unsigned long UpdatePos);

void CfgInitHook(PRTMP_ADAPTER pAd);


NDIS_STATUS RtmpNetTaskInit(
RTMP_ADAPTER *pAd);

void RtmpNetTaskExit(
PRTMP_ADAPTER pAd);

NDIS_STATUS RtmpMgmtTaskInit(
RTMP_ADAPTER *pAd);
	
void RtmpMgmtTaskExit(
RTMP_ADAPTER *pAd);

void tbtt_tasklet(unsigned long data);


	
	

#ifdef CONFIG_STA_SUPPORT
#ifdef CREDENTIAL_STORE
NDIS_STATUS RecoverConnectInfo(
 RTMP_ADAPTER *pAd);

NDIS_STATUS StoreConnectInfo(
 RTMP_ADAPTER *pAd);
#endif /* CREDENTIAL_STORE */
#endif /* CONFIG_STA_SUPPORT */

void AsicTurnOffRFClk(
PRTMP_ADAPTER    pAd, 
unsigned char           Channel);



#ifdef RTMP_TIMER_TASK_SUPPORT
int RtmpTimerQThread(
unsigned long Context);

RTMP_TIMER_TASK_ENTRY *RtmpTimerQInsert(
RTMP_ADAPTER *pAd, 
RALINK_TIMER_STRUCT *pTimer);

unsigned char RtmpTimerQRemove(
RTMP_ADAPTER *pAd, 
RALINK_TIMER_STRUCT *pTimer);

void RtmpTimerQExit(
RTMP_ADAPTER *pAd);

void RtmpTimerQInit(
RTMP_ADAPTER *pAd);
#endif /* RTMP_TIMER_TASK_SUPPORT */


#ifdef RTMP_MAC_USB

int RTUSBMultiRead(
PRTMP_ADAPTER	pAd,
unsigned short			Offset,
unsigned char*			pData,
unsigned short			length);

int RTUSBMultiWrite(
PRTMP_ADAPTER	pAd,
unsigned short			Offset,
unsigned char*			pData,
unsigned short			length,
unsigned char			bWriteHigh);

int RTUSBMultiWrite_nBytes(
PRTMP_ADAPTER   pAd,
unsigned short                  Offset,
unsigned char*                  pData,
unsigned short                  length,
unsigned short                  batchLen);

int RTUSBMultiWrite_OneByte(
PRTMP_ADAPTER	pAd,
unsigned short			Offset,
unsigned char*			pData);

int RTUSBReadBBPRegister(
PRTMP_ADAPTER	pAd,
unsigned char			Id,
unsigned char*			pValue);

int RTUSBWriteBBPRegister(
PRTMP_ADAPTER	pAd,
unsigned char			Id,
unsigned char			Value);

int RTUSBWriteRFRegister(
PRTMP_ADAPTER	pAd,
unsigned int		Value);
	
int RTUSB_VendorRequest(
PRTMP_ADAPTER	pAd,
unsigned int		TransferFlags,
unsigned char			ReservedBits,
unsigned char			Request,
unsigned short			Value,
unsigned short			Index,
void *		TransferBuffer,
unsigned int		TransferBufferLength);

int RTUSBReadEEPROM(
PRTMP_ADAPTER	pAd,
unsigned short			Offset,
	OUT	unsigned char*			pData,
unsigned short			length);

int RTUSBWriteEEPROM(
PRTMP_ADAPTER	pAd,
unsigned short			Offset,
unsigned char*			pData,
unsigned short			length);

void RTUSBPutToSleep(
PRTMP_ADAPTER	pAd);

int RTUSBWakeUp(
PRTMP_ADAPTER	pAd);

NDIS_STATUS	RTUSBEnqueueCmdFromNdis(
PRTMP_ADAPTER	pAd,
NDIS_OID		Oid,
unsigned char			SetInformation,
void *		pInformationBuffer,
unsigned int		InformationBufferLength);

void RTUSBDequeueCmd(
PCmdQ		cmdq,
	OUT	PCmdQElmt	*pcmdqelmt);

int RTUSBCmdThread(
unsigned long Context);

void RTUSBBssBeaconExit(
RTMP_ADAPTER *pAd);

void RTUSBBssBeaconStop(
RTMP_ADAPTER *pAd);

void RTUSBBssBeaconStart(
RTMP_ADAPTER * pAd);

void RTUSBBssBeaconInit(
RTMP_ADAPTER *pAd);

void RTUSBWatchDog(
RTMP_ADAPTER *pAd);
	
int RTUSBWriteMACRegister(
PRTMP_ADAPTER	pAd,
unsigned short			Offset,
unsigned int		Value,
unsigned char			bWriteHigh);

int RTUSBReadMACRegister(
PRTMP_ADAPTER	pAd,
unsigned short			Offset,
	unsigned int* 		pValue);

int RTUSBSingleWrite(
	RTMP_ADAPTER 	*pAd,
unsigned short			Offset,
unsigned short			Value,
unsigned char			bWriteHigh);

int RTUSBFirmwareWrite(
PRTMP_ADAPTER pAd,
unsigned char*		pFwImage,
unsigned long		FwLen);

int	RTUSBVenderReset(
PRTMP_ADAPTER	pAd);

int RTUSBSetHardWareRegister(
PRTMP_ADAPTER	pAdapter,
void *		pBuf);

int RTUSBQueryHardWareRegister(
PRTMP_ADAPTER	pAdapter,
void *		pBuf);

/*void CMDHandler( */
/*    IN PRTMP_ADAPTER pAd); */

NDIS_STATUS	RTUSBWriteHWMACAddress(
RTMP_ADAPTER *pAd);

void MlmeSetPsm(
RTMP_ADAPTER *pAd, 
unsigned short psm);

NDIS_STATUS RTMPWPAAddKeyProc(
RTMP_ADAPTER *pAd,
void*pBuf);

void AsicRxAntEvalAction(
RTMP_ADAPTER *pAd);

void append_pkt(
RTMP_ADAPTER *pAd, 
unsigned char *pHeader802_3,
unsigned int HdrLen,
unsigned char *pData,
unsigned long DataSize,
	PNDIS_PACKET *ppPacket);


void RTUSBMlmeHardTransmit(
RTMP_ADAPTER *pAd,
MGMT_STRUC *pMgmt);

int MlmeThread(unsigned long Context);


/*
	Function Prototype in rtusb_data.c
*/
NDIS_STATUS	RTUSBFreeDescRequest(
RTMP_ADAPTER *pAd,
unsigned char BulkOutPipeId,
unsigned intreq_cnt);


unsigned char	RTUSBNeedQueueBackForAgg(
RTMP_ADAPTER *pAd, 
unsigned char		BulkOutPipeId);


/* Function Prototype in cmm_data_usb.c */
unsigned short RtmpUSB_WriteSubTxResource(
PRTMP_ADAPTER	pAd,
TX_BLK			*pTxBlk,
unsigned char			bIsLast,
	OUT	unsigned short			*FreeNumber);

unsigned short RtmpUSB_WriteSingleTxResource(
PRTMP_ADAPTER	pAd,
TX_BLK			*pTxBlk,
unsigned char			bIsLast,
	OUT	unsigned short			*FreeNumber);

unsigned short	RtmpUSB_WriteFragTxResource(
PRTMP_ADAPTER	pAd,
TX_BLK			*pTxBlk,
unsigned char			fragNum,
	OUT	unsigned short			*FreeNumber);
	
unsigned short RtmpUSB_WriteMultiTxResource(
PRTMP_ADAPTER	pAd,
TX_BLK			*pTxBlk,
unsigned char			frameNum,
	OUT	unsigned short			*FreeNumber);

void RtmpUSB_FinalWriteTxResource(
PRTMP_ADAPTER	pAd,
TX_BLK			*pTxBlk,
unsigned short			totalMPDUSize,
unsigned short			TxIdx);

void RtmpUSBDataLastTxIdx(
PRTMP_ADAPTER	pAd,
unsigned char			QueIdx,
unsigned short			TxIdx);

void RtmpUSBDataKickOut(
PRTMP_ADAPTER	pAd,
TX_BLK			*pTxBlk,
unsigned char			QueIdx);

int RtmpUSBMgmtKickOut(
RTMP_ADAPTER 	*pAd, 
unsigned char 			QueIdx,
PNDIS_PACKET		pPacket,
unsigned char*			pSrcBufVA,
unsigned int 			SrcBufLen);

void RtmpUSBNullFrameKickOut(
RTMP_ADAPTER *pAd,
unsigned char		QueIdx,
unsigned char		*pNullFrame,
unsigned int	frameLen);
	
void RtmpUsbStaAsicForceWakeupTimeout(
void *SystemSpecific1, 
void *FunctionContext, 
void *SystemSpecific2, 
void *SystemSpecific3);

void RT28xxUsbStaAsicForceWakeup(
PRTMP_ADAPTER pAd,
unsigned char       bFromTx);

void RT28xxUsbStaAsicSleepThenAutoWakeup(
PRTMP_ADAPTER pAd, 
unsigned short TbttNumToNextWakeUp);

void RT28xxUsbMlmeRadioOn(
PRTMP_ADAPTER pAd);

void RT28xxUsbMlmeRadioOFF(
PRTMP_ADAPTER pAd);

void RT28xxUsbAsicRadioOff(
PRTMP_ADAPTER pAd);

void RT28xxUsbAsicRadioOn(
PRTMP_ADAPTER pAd);

unsigned char AsicCheckCommandOk(
PRTMP_ADAPTER pAd,
unsigned char		 Command);

void RT28xxUsbAsicWOWEnable(
PRTMP_ADAPTER pAd);

void RT28xxUsbAsicWOWDisable(
PRTMP_ADAPTER pAd);

#endif /* RTMP_MAC_USB */

NDIS_STATUS RTMPCheckRxError(
RTMP_ADAPTER *pAd, 
PHEADER_802_11 pHeader,
RXWI_STRUC *pRxWI,
RXINFO_STRUC *pRxInfo);


/*////////////////////////////////////*/

#ifdef AP_QLOAD_SUPPORT
void QBSS_LoadInit(
 	IN		RTMP_ADAPTER	*pAd);

void QBSS_LoadAlarmReset(
 	IN		RTMP_ADAPTER	*pAd);

void QBSS_LoadAlarmResume(
 	IN		RTMP_ADAPTER	*pAd);

unsigned intQBSS_LoadBusyTimeGet(
 	IN		RTMP_ADAPTER	*pAd);

unsigned char QBSS_LoadIsAlarmIssued(
 	IN		RTMP_ADAPTER	*pAd);

unsigned char QBSS_LoadIsBusyTimeAccepted(
 	IN		RTMP_ADAPTER	*pAd,
	unsigned int 		BusyTime);

unsigned intQBSS_LoadElementAppend(
 	IN		RTMP_ADAPTER	*pAd,
	OUT		unsigned char			*buf_p);

unsigned intQBSS_LoadElementParse(
 	IN		RTMP_ADAPTER	*pAd,
	unsigned char			*pElement,
	OUT		unsigned short			*pStationCount,
	OUT		unsigned char			*pChanUtil,
	OUT		unsigned short			*pAvalAdmCap);

void QBSS_LoadUpdate(
 	IN		RTMP_ADAPTER	*pAd,
	unsigned long			UpTime);

void QBSS_LoadStatusClear(
 	IN		RTMP_ADAPTER	*pAd);

int	Show_QoSLoad_Proc(
PRTMP_ADAPTER	pAd,
char *			arg);
#endif /* AP_QLOAD_SUPPORT */

/*///////////////////////////////////*/
int RTMPShowCfgValue(
PRTMP_ADAPTER	pAd, 
char *			pName,
char *			pBuf,
unsigned int		MaxLen);

char * RTMPGetRalinkAuthModeStr(
    IN  NDIS_802_11_AUTHENTICATION_MODE authMode);

char * RTMPGetRalinkEncryModeStr(
    IN  unsigned short encryMode);
/*//////////////////////////////////*/

#ifdef CONFIG_STA_SUPPORT
void AsicStaBbpTuning(
PRTMP_ADAPTER pAd);

unsigned char StaAddMacTableEntry(
 PRTMP_ADAPTER		pAd,
 PMAC_TABLE_ENTRY	pEntry,
 unsigned char				MaxSupportedRateIn500Kbps,
 HT_CAPABILITY_IE	*pHtCapability,
 unsigned char				HtCapabilityLen,
 ADD_HT_INFO_IE		*pAddHtInfo,
 unsigned char				AddHtInfoLen,
IE_LISTS *ie_list,
 unsigned short        		CapabilityInfo);


unsigned char	AUTH_ReqSend(
 PRTMP_ADAPTER 		pAd,
 PMLME_QUEUE_ELEM	pElem,
 PRALINK_TIMER_STRUCT pAuthTimer,
 char *				pSMName,
 unsigned short				SeqNo,
 unsigned char*				pNewElement,
 unsigned long				ElementLen);
#endif /* CONFIG_STA_SUPPORT */ 


void ReSyncBeaconTime(RTMP_ADAPTER *pAd);
void RTMPSetAGCInitValue(RTMP_ADAPTER *pAd, unsigned char BandWidth);

#ifdef TXBF_SUPPORT
void HandleHtcField(
PRTMP_ADAPTER	pAd,
RX_BLK			*pRxBlk);
#endif /* TXBF_SUPPORT */

#ifdef MFB_SUPPORT
void MFB_PerPareMRQ(
PRTMP_ADAPTER	pAd,
	OUT	VOID* pBuf,
PMAC_TABLE_ENTRY pEntry);

void MFB_PerPareMFB(
PRTMP_ADAPTER	pAd,
	OUT	VOID* pBuf,
PMAC_TABLE_ENTRY pEntry);
#endif /* MFB_SUPPORT */

#define VIRTUAL_IF_INC(__pAd) ((__pAd)->VirtualIfCnt++)
#define VIRTUAL_IF_DEC(__pAd) ((__pAd)->VirtualIfCnt--)
#define VIRTUAL_IF_NUM(__pAd) ((__pAd)->VirtualIfCnt)



#ifdef RTMP_USB_SUPPORT
/*
 * Function Prototype in rtusb_bulk.c
 */
 
#ifdef INF_AMAZON_SE
void SoftwareFlowControl(
PRTMP_ADAPTER pAd) ;
#endif /* INF_AMAZON_SE */


void RTUSBInitTxDesc(
PRTMP_ADAPTER	pAd,
PTX_CONTEXT		pTxContext,
unsigned char			BulkOutPipeId,
usb_complete_t	Func);

void RTUSBInitHTTxDesc(
PRTMP_ADAPTER	pAd,
PHT_TX_CONTEXT	pTxContext,
unsigned char			BulkOutPipeId,
unsigned long			BulkOutSize,
usb_complete_t	Func);

void RTUSBInitRxDesc(
PRTMP_ADAPTER	pAd,
PRX_CONTEXT		pRxContext);

void RTUSBCleanUpDataBulkOutQueue(
PRTMP_ADAPTER	pAd);

void RTUSBCancelPendingBulkOutIRP(
PRTMP_ADAPTER	pAd);

void RTUSBBulkOutDataPacket(
PRTMP_ADAPTER	pAd,
unsigned char			BulkOutPipeId,
unsigned char			Index);

void RTUSBBulkOutNullFrame(
PRTMP_ADAPTER	pAd);

void RTUSBBulkOutRTSFrame(
PRTMP_ADAPTER	pAd);

void RTUSBCancelPendingBulkInIRP(
PRTMP_ADAPTER	pAd);

void RTUSBCancelPendingIRPs(
PRTMP_ADAPTER	pAd);

void RTUSBBulkOutMLMEPacket(
PRTMP_ADAPTER	pAd,
unsigned char			Index);

void RTUSBBulkOutPsPoll(
PRTMP_ADAPTER	pAd);

void RTUSBCleanUpMLMEBulkOutQueue(
PRTMP_ADAPTER	pAd);

void RTUSBKickBulkOut(
PRTMP_ADAPTER pAd);

void RTUSBBulkReceive(
PRTMP_ADAPTER	pAd);

void RTUSBBulkCmdRspEventReceive(
PRTMP_ADAPTER pAd);

void DoBulkIn(
RTMP_ADAPTER *pAd);

void RTUSBInitRxDesc(
PRTMP_ADAPTER	pAd,
 PRX_CONTEXT		pRxContext);

void RTUSBBulkRxHandle(
unsigned long data);	
#endif /* RTMP_USB_SUPPORT */


#ifdef SOFT_ENCRYPT
unsigned char RTMPExpandPacketForSwEncrypt(
 PRTMP_ADAPTER   pAd,
PTX_BLK			pTxBlk);

void RTMPUpdateSwCacheCipherInfo(	
 PRTMP_ADAPTER   pAd,
PTX_BLK			pTxBlk,
unsigned char*			pHdr);
#endif /* SOFT_ENCRYPT */


/*
	OS Related funciton prototype definitions.
	TODO: Maybe we need to move these function prototypes to other proper place.
*/

void RTInitializeCmdQ(
PCmdQ	cmdq);

int RTPCICmdThread(
unsigned long Context);

void CMDHandler(
    IN PRTMP_ADAPTER pAd);

void RTThreadDequeueCmd(
PCmdQ		cmdq,
	OUT	PCmdQElmt	*pcmdqelmt);

int RTEnqueueInternalCmd(
PRTMP_ADAPTER	pAd,
NDIS_OID			Oid,
void *		pInformationBuffer,
unsigned int		InformationBufferLength);

#ifdef HOSTAPD_SUPPORT
void Ieee80211_notify_michael_failure(
PRTMP_ADAPTER    pAd,
PHEADER_802_11   pHeader,
unsigned int            keyix,
int              report);

const char* ether_sprintf(const unsigned char *mac);
#endif/*HOSTAPD_SUPPORT*/

#ifdef VENDOR_FEATURE3_SUPPORT
void RTMP_IO_WRITE32(
	PRTMP_ADAPTER pAd,
	unsigned int Offset,
	unsigned int Value);

void RTMP_BBP_IO_READ8_BY_REG_ID(
	PRTMP_ADAPTER pAd,
	unsigned int Offset,
	unsigned char *pValue);

void RTMP_BBP_IO_READ8(
	PRTMP_ADAPTER pAd,
	unsigned char Offset,
	unsigned char *pValue,
	unsigned char FlgValidMCR);

void RTMP_BBP_IO_WRITE8_BY_REG_ID(
	PRTMP_ADAPTER pAd,
	unsigned int Offset,
	unsigned char Value);

void RTMP_BBP_IO_WRITE8(
	PRTMP_ADAPTER pAd,
	unsigned char Offset,
	unsigned char Value,
	unsigned char FlgValidMCR);
#endif /* VENDOR_FEATURE3_SUPPORT */


int AsicGetMacVersion(
RTMP_ADAPTER *pAd);

int WaitForAsicReady(
RTMP_ADAPTER *pAd);

unsigned char CHAN_PropertyCheck(
PRTMP_ADAPTER	pAd,
unsigned int		ChanNum,
unsigned char			Property);

#ifdef CONFIG_STA_SUPPORT

/* command */
int Set_SSID_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

#ifdef WMM_SUPPORT
int	Set_WmmCapable_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);
#endif

int Set_NetworkType_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

int Set_AuthMode_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

int Set_EncrypType_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

int Set_DefaultKeyID_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

int Set_Wep_Key_Proc(RTMP_ADAPTER  *pAd, char * Key, int KeyLen, int KeyId);

int Set_Key1_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

int Set_Key2_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

int Set_Key3_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

int Set_Key4_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

int Set_WPAPSK_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);


int Set_PSMode_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);

#ifdef WPA_SUPPLICANT_SUPPORT
int Set_Wpa_Support(
    IN	PRTMP_ADAPTER	pAd, 
char *			arg);
#endif /* WPA_SUPPLICANT_SUPPORT */

#ifdef DBG

void RTMPIoctlMAC(
PRTMP_ADAPTER	pAdapter, 
RTMP_IOCTL_INPUT_STRUCT	*wrq);

void RTMPIoctlE2PROM(
    IN  PRTMP_ADAPTER   pAdapter,
    IN  RTMP_IOCTL_INPUT_STRUCT *wrq);
#endif /* DBG */


NDIS_STATUS RTMPWPANoneAddKeyProc(
    IN  PRTMP_ADAPTER   pAd,
    IN	void *		pBuf);
	
int Set_FragTest_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);
	
#ifdef DOT11_N_SUPPORT	
int Set_TGnWifiTest_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *          arg);
#endif /* DOT11_N_SUPPORT */

int Set_LongRetryLimit_Proc(
PRTMP_ADAPTER	pAdapter, 
char *			arg);

int Set_ShortRetryLimit_Proc(
PRTMP_ADAPTER	pAdapter, 
char *			arg);

#ifdef EXT_BUILD_CHANNEL_LIST
int Set_Ieee80211dClientMode_Proc(
    IN  PRTMP_ADAPTER   pAdapter, 
    IN  char *          arg);
#endif /* EXT_BUILD_CHANNEL_LIST */

int	Show_Adhoc_MacTable_Proc(
PRTMP_ADAPTER	pAd, 
char *			extra,
unsigned int		size);



int Set_BeaconLostTime_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *         arg);

int Set_AutoRoaming_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *         arg);

int Set_SiteSurvey_Proc(
PRTMP_ADAPTER	pAd, 
char *			arg);

int Set_ForceTxBurst_Proc(
    IN  PRTMP_ADAPTER   pAd, 
    IN  char *         arg);

void RTMPAddKey(
PRTMP_ADAPTER	    pAd, 
PNDIS_802_11_KEY    pKey);


void StaSiteSurvey(
PRTMP_ADAPTER  		pAd,
PNDIS_802_11_SSID	pSsid,
unsigned char				ScanType);

void MaintainBssTable(
 PRTMP_ADAPTER pAd,
OUT	BSS_TABLE *Tab,
 unsigned long	MaxRxTimeDiff,
 unsigned char	MaxSameRxTimeCount);
#endif /* CONFIG_STA_SUPPORT */

void  getRate(
    IN HTTRANSMIT_SETTING HTSetting, 
    unsigned long* fLastTxRxRate);


#ifdef APCLI_SUPPORT
#ifdef APCLI_WPA_SUPPLICANT_SUPPORT
void   ApcliSendAssocIEsToWpaSupplicant( 
    IN  PRTMP_ADAPTER pAd,
    IN unsigned int ifIndex);

int	    ApcliWpaCheckEapCode(
 PRTMP_ADAPTER   		pAd,
 unsigned char*				pFrame,
 unsigned short				FrameLen,
 unsigned short				OffSet);

void   ApcliWpaSendEapolStart(
PRTMP_ADAPTER	pAd,
 unsigned char*          pBssid,
 PMAC_TABLE_ENTRY pMacEntry,
PAPCLI_STRUCT pApCliEntry);


void ApCliRTMPSendNullFrame(
PRTMP_ADAPTER	pAd,
unsigned char			TxRate,
unsigned char 		bQosNull,
PMAC_TABLE_ENTRY pMacEntry);

#endif/*APCLI_WPA_SUPPLICANT_SUPPORT*/
#endif/*APCLI_SUPPORT*/


void RTMP_IndicateMediaState(	
PRTMP_ADAPTER		pAd,
 int	media_state);

#if defined(RT3350) || defined(RT33xx)
void RTMP_TxEvmCalibration(
PRTMP_ADAPTER pAd);
#endif /* defined(RT3350) || defined(RT33xx) */

int RTMPSetInformation(
    RTMP_ADAPTER *pAd,
    RTMP_IOCTL_INPUT_STRUCT *rq,
    int cmd);

int RTMPQueryInformation(
    RTMP_ADAPTER *pAd,
    RTMP_IOCTL_INPUT_STRUCT *rq,
    int cmd);

void RTMPIoctlShow(
RTMP_ADAPTER *pAd,
RTMP_IOCTL_INPUT_STRUCT *rq,
unsigned intsubcmd,
void*pData,
unsigned long Data);

int RTMP_COM_IoctlHandle(
void*pAdSrc,
RTMP_IOCTL_INPUT_STRUCT *wrq,
int cmd,
unsigned short subcmd,
void*pData,
unsigned long Data);



int Set_VcoPeriod_Proc(
RTMP_ADAPTER *pAd,
char * arg);

int	Set_RateAlg_Proc(
RTMP_ADAPTER *pAd,
char * arg);

#ifdef SINGLE_SKU
int Set_ModuleTxpower_Proc(
RTMP_ADAPTER *pAd, 
char * arg);
#endif /* SINGLE_SKU */

void RtmpEnqueueNullFrame(
PRTMP_ADAPTER pAd,
unsigned char*        pAddr,
unsigned char         TxRate,
unsigned char         PID,
unsigned char         apidx,
    IN unsigned char       bQosNull,
    IN unsigned char       bEOSP,
    IN unsigned char         OldUP);

void RtmpCleanupPsQueue(
 PRTMP_ADAPTER   pAd,
 QUEUE_HEADER   *pQueue);

#ifdef CONFIG_STA_SUPPORT
unsigned char RtmpPktPmBitCheck(
    IN  PRTMP_ADAPTER       pAd);

void RtmpPsActiveExtendCheck(
PRTMP_ADAPTER		pAd);

void RtmpPsModeChange(
PRTMP_ADAPTER		pAd,
unsigned int			PsMode);
#endif /* CONFIG_STA_SUPPORT */

unsigned char dot11_2_ra_rate(unsigned char MaxSupportedRateIn500Kbps);
unsigned char dot11_max_sup_rate(int SupRateLen, unsigned char *SupRate, int ExtRateLen, unsigned char *ExtRate);

void Mgmt_tb_set_mcast_entry(RTMP_ADAPTER *pAd);
void set_entry_phy_cfg(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry);
void MacTableReset(RTMP_ADAPTER *pAd);
MAC_TABLE_ENTRY *MacTableLookup(RTMP_ADAPTER *pAd, unsigned char *pAddr);
unsigned char MacTableDeleteEntry(RTMP_ADAPTER *pAd, unsigned short wcid, unsigned char *pAddr);
MAC_TABLE_ENTRY *MacTableInsertEntry(
    IN RTMP_ADAPTER *pAd,
    IN unsigned char *pAddr,
unsigned char apidx,
unsigned char OpMode,
unsigned char CleanAll);

#ifdef MAC_REPEATER_SUPPORT
MAC_TABLE_ENTRY *InsertMacRepeaterEntry(
 PRTMP_ADAPTER   pAd,
 unsigned char*			pAddr,
 unsigned char			IfIdx);
#endif /* MAC_REPEATER_SUPPORT */

void dumpTxWI(RTMP_ADAPTER *pAd, TXWI_STRUC *pTxWI);
void dump_rxwi(RTMP_ADAPTER *pAd, RXWI_STRUC *pRxWI);
void dump_txinfo(RTMP_ADAPTER *pAd, TXINFO_STRUC *pTxInfo);
void dump_rxinfo(RTMP_ADAPTER *pAd, RXINFO_STRUC *pRxInfo);
void dumpRxFCEInfo(RTMP_ADAPTER *pAd, RXFCE_INFO *pRxFceInfo);



#ifdef CONFIG_FPGA_MODE
int set_tr_stop(RTMP_ADAPTER *pAd, char * arg);
int set_tx_kickcnt(RTMP_ADAPTER *pAd, char * arg);
int set_data_phy_mode(RTMP_ADAPTER *pAd, char * arg);
int set_data_bw(RTMP_ADAPTER *pAd, char * arg);
int set_data_ldpc(RTMP_ADAPTER *pAd, char * arg);
int set_data_mcs(RTMP_ADAPTER *pAd, char * arg);
int set_data_gi(RTMP_ADAPTER *pAd, char * arg);
int set_data_basize(RTMP_ADAPTER *pAd, char * arg);
int set_fpga_mode(RTMP_ADAPTER *pAd, char * arg);

#ifdef CAPTURE_MODE
void Cap_mode_init(RTMP_ADAPTER *pAd);
void Cap_mode_deinit(RTMP_ADAPTER *pAd);
int set_cap_start(RTMP_ADAPTER *pAd, char * arg);
int set_cap_trigger(RTMP_ADAPTER *pAd, char * arg);
int asic_cap_start(RTMP_ADAPTER *pAd);
int asic_cap_stop(RTMP_ADAPTER *pAd);
int cap_status_chk_and_get(RTMP_ADAPTER *pAd);
int set_cap_dump(RTMP_ADAPTER *pAd, char * arg);
void Cap_dump(RTMP_ADAPTER *pAd, char *bank1, char *bank2, int len);
#endif /* CAPTURE_MODE */
#endif /* CONFIG_FPGA_MODE */

#ifdef WFA_VHT_PF
int set_force_amsdu(RTMP_ADAPTER *pAd, char * arg);
int set_force_noack(RTMP_ADAPTER *pAd, char * arg);
int set_force_vht_sgi(RTMP_ADAPTER *pAd, char * arg);
int set_force_vht_tx_stbc(RTMP_ADAPTER *pAd, char * arg);
int set_force_ext_cca(RTMP_ADAPTER *pAd, char * arg);
#ifdef IP_ASSEMBLY
int set_force_ip_assemble(RTMP_ADAPTER *pAd, char * arg);
#endif /* IP_ASSEMBLY */
#endif /* WFA_VHT_PF */



#ifdef RLT_RF
int set_rf(RTMP_ADAPTER *pAd, char * arg);
#endif /* RLT_RF */

#ifdef RTMP_MAC_USB
unsigned char CmdRspEventHandle(RTMP_ADAPTER *pAd);
#endif /* RTMP_MAC_USB */

#endif  /* __RTMP_H__ */

#ifdef MT76x0
int set_temp_sensor_proc(
RTMP_ADAPTER		*pAd,
char *			arg);
#endif /* MT76x0 */
