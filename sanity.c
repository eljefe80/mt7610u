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


#include "rt_config.h"

extern unsigned char CISCO_OUI[];

extern unsigned char WPA_OUI[];
extern unsigned char RSN_OUI[];
extern unsigned char WME_INFO_ELEM[];
extern unsigned char WME_PARM_ELEM[];
extern unsigned char RALINK_OUI[];
extern unsigned char BROADCOM_OUI[];

/* 
    ==========================================================================
    Description:
        MLME message sanity check
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
 */
unsigned char MlmeStartReqSanity(
	IN PRTMP_ADAPTER pAd,
	IN void *Msg,
	IN unsigned long MsgLen,
	char Ssid[],
	unsigned char *pSsidLen)
{
	MLME_START_REQ_STRUCT *Info;

	Info = (MLME_START_REQ_STRUCT *) (Msg);

	if (Info->SsidLen > MAX_LEN_OF_SSID) {
		DBGPRINT(RT_DEBUG_TRACE, ("%s(): fail - wrong SSID length\n",
									__FUNCTION__));
		return FALSE;
	}

	*pSsidLen = Info->SsidLen;
	NdisMoveMemory(Ssid, Info->Ssid, *pSsidLen);

	return TRUE;
}

/* 
    ==========================================================================
    Description:
        MLME message sanity check
    Return:
        TRUE if all parameters are OK, FALSE otherwise
        
    IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
unsigned char PeerAssocRspSanity(
	IN PRTMP_ADAPTER pAd,
	IN void *pMsg,
	IN unsigned long MsgLen,
	unsigned char* pAddr2,
	unsigned short *pCapabilityInfo,
	unsigned short *pStatus,
	unsigned short *pAid,
	unsigned char SupRate[],
	unsigned char *pSupRateLen,
	unsigned char ExtRate[],
	unsigned char *pExtRateLen,
	HT_CAPABILITY_IE *pHtCapability,
	ADD_HT_INFO_IE *pAddHtInfo,	/* AP might use this additional ht info IE */
	unsigned char *pHtCapabilityLen,
	unsigned char *pAddHtInfoLen,
	unsigned char *pNewExtChannelOffset,
	PEDCA_PARM pEdcaParm,
	EXT_CAP_INFO_ELEMENT *pExtCapInfo,
	unsigned char *pCkipFlag,
	IE_LISTS *ie_list)
{
	char IeType, *Ptr;
	PFRAME_802_11 pFrame = (PFRAME_802_11) pMsg;
	PEID_STRUCT pEid;
	unsigned long Length = 0;

	*pNewExtChannelOffset = 0xff;
	*pHtCapabilityLen = 0;
	*pAddHtInfoLen = 0;
	COPY_MAC_ADDR(pAddr2, pFrame->Hdr.Addr2);
	Ptr = (char*) pFrame->Octet;
	Length += LENGTH_802_11;

	NdisMoveMemory(pCapabilityInfo, &pFrame->Octet[0], 2);
	Length += 2;
	NdisMoveMemory(pStatus, &pFrame->Octet[2], 2);
	Length += 2;
	*pCkipFlag = 0;
	*pExtRateLen = 0;
	pEdcaParm->bValid = FALSE;

	if (*pStatus != MLME_SUCCESS)
		return TRUE;

	NdisMoveMemory(pAid, &pFrame->Octet[4], 2);
	Length += 2;

	/* Aid already swaped byte order in RTMPFrameEndianChange() for big endian platform */
	*pAid = (*pAid) & 0x3fff;	/* AID is low 14-bit */

	/* -- get supported rates from payload and advance the pointer */
	IeType = pFrame->Octet[6];
	*pSupRateLen = pFrame->Octet[7];
	if ((IeType != IE_SUPP_RATES)
	    || (*pSupRateLen > MAX_LEN_OF_SUPPORTED_RATES)) {
		DBGPRINT(RT_DEBUG_TRACE, ("%s(): fail - wrong SupportedRates IE\n", __FUNCTION__));
		return FALSE;
	} else
		NdisMoveMemory(SupRate, &pFrame->Octet[8], *pSupRateLen);


	Length = Length + 2 + *pSupRateLen;

	/*
	   many AP implement proprietary IEs in non-standard order, we'd better
	   tolerate mis-ordered IEs to get best compatibility
	 */
	pEid = (PEID_STRUCT) & pFrame->Octet[8 + (*pSupRateLen)];

	/* get variable fields from payload and advance the pointer */
	while ((Length + 2 + pEid->Len) <= MsgLen) {
		switch (pEid->Eid) {
		case IE_EXT_SUPP_RATES:
			if (pEid->Len <= MAX_LEN_OF_SUPPORTED_RATES) {
				NdisMoveMemory(ExtRate, pEid->Octet, pEid->Len);
				*pExtRateLen = pEid->Len;
			}
			break;

#ifdef DOT11_N_SUPPORT
		case IE_HT_CAP:
		case IE_HT_CAP2:
			if (pEid->Len >= SIZE_HT_CAP_IE) {	/* Note: allow extension.!! */
				NdisMoveMemory(pHtCapability, pEid->Octet, SIZE_HT_CAP_IE);

				*(unsigned short *) (&pHtCapability->HtCapInfo) = cpu2le16(*(unsigned short *)(&pHtCapability->HtCapInfo));
				*(unsigned short *) (&pHtCapability->ExtHtCapInfo) = cpu2le16(*(unsigned short *)(&pHtCapability->ExtHtCapInfo));

				*pHtCapabilityLen = SIZE_HT_CAP_IE;
			} else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_HT_CAP\n", __FUNCTION__));
			}

			break;

		case IE_ADD_HT:
		case IE_ADD_HT2:
			if (pEid->Len >= sizeof (ADD_HT_INFO_IE)) {
				/*
				   This IE allows extension, but we can ignore extra bytes beyond our knowledge , so only
				   copy first sizeof(ADD_HT_INFO_IE)
				 */
				NdisMoveMemory(pAddHtInfo, pEid->Octet, sizeof (ADD_HT_INFO_IE));

				*(unsigned short *) (&pAddHtInfo->AddHtInfo2) = cpu2le16(*(unsigned short *)(&pAddHtInfo->AddHtInfo2));
				*(unsigned short *) (&pAddHtInfo->AddHtInfo3) = cpu2le16(*(unsigned short *)(&pAddHtInfo->AddHtInfo3));

				*pAddHtInfoLen = SIZE_ADD_HT_INFO_IE;
			} else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_ADD_HT\n", __FUNCTION__));
			}

			break;
		case IE_SECONDARY_CH_OFFSET:
			if (pEid->Len == 1) {
				*pNewExtChannelOffset = pEid->Octet[0];
			} else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_SECONDARY_CH_OFFSET\n", __FUNCTION__));
			}
			break;

#ifdef DOT11_VHT_AC
		case IE_VHT_CAP:
			if (pEid->Len == sizeof(VHT_CAP_IE)) {
				NdisMoveMemory(&ie_list->vht_cap, pEid->Octet, sizeof(VHT_CAP_IE));
				ie_list->vht_cap_len = sizeof(VHT_CAP_IE);
			} else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_VHT_CAP\n", __FUNCTION__));
			}
			break;

		case IE_VHT_OP:
			if (pEid->Len == sizeof(VHT_OP_IE)) {
				NdisMoveMemory(&ie_list->vht_op, pEid->Octet, sizeof(VHT_OP_IE));
				ie_list->vht_op_len = sizeof(VHT_OP_IE);
			}else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_VHT_OP\n", __FUNCTION__));
			}
			break;
#endif /* DOT11_VHT_AC */
#endif /* DOT11_N_SUPPORT */

		case IE_VENDOR_SPECIFIC:
			/* handle WME PARAMTER ELEMENT */
			if (NdisEqualMemory(pEid->Octet, WME_PARM_ELEM, 6)
			    && (pEid->Len == 24)) {
				unsigned char* ptr;
				int i;

				/* parsing EDCA parameters */
				pEdcaParm->bValid = TRUE;
				pEdcaParm->bQAck = FALSE;	/* pEid->Octet[0] & 0x10; */
				pEdcaParm->bQueueRequest = FALSE;	/* pEid->Octet[0] & 0x20; */
				pEdcaParm->bTxopRequest = FALSE;	/* pEid->Octet[0] & 0x40; */
				pEdcaParm->EdcaUpdateCount =
				    pEid->Octet[6] & 0x0f;
				pEdcaParm->bAPSDCapable =
				    (pEid->Octet[6] & 0x80) ? 1 : 0;
				ptr = (unsigned char*) & pEid->Octet[8];
				for (i = 0; i < 4; i++) {
					unsigned char aci = (*ptr & 0x60) >> 5;	/* b5~6 is AC INDEX */
					pEdcaParm->bACM[aci] = (((*ptr) & 0x10) == 0x10);	/* b5 is ACM */
					pEdcaParm->Aifsn[aci] = (*ptr) & 0x0f;	/* b0~3 is AIFSN */
					pEdcaParm->Cwmin[aci] = *(ptr + 1) & 0x0f;	/* b0~4 is Cwmin */
					pEdcaParm->Cwmax[aci] = *(ptr + 1) >> 4;	/* b5~8 is Cwmax */
					pEdcaParm->Txop[aci] = *(ptr + 2) + 256 * (*(ptr + 3));	/* in unit of 32-us */
					ptr += 4;	/* point to next AC */
				}
			}
			break;
		case IE_EXT_CAPABILITY:
			if (pEid->Len >= 1)
			{
				unsigned char MaxSize;
				unsigned char MySize = sizeof(EXT_CAP_INFO_ELEMENT);

				MaxSize = min(pEid->Len, MySize);
				NdisMoveMemory(pExtCapInfo, &pEid->Octet[0], MaxSize);
				DBGPRINT(RT_DEBUG_WARN, ("PeerAssocReqSanity - IE_EXT_CAPABILITY!\n"));
			}
			break;

		default:
			DBGPRINT(RT_DEBUG_TRACE,
				 ("%s():ignore unrecognized EID = %d\n", __FUNCTION__, pEid->Eid));
			break;
		}

		Length = Length + 2 + pEid->Len;
		pEid = (PEID_STRUCT) ((unsigned char *) pEid + 2 + pEid->Len);
	}


	return TRUE;
}


/* 
    ==========================================================================
    Description:
        
	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
unsigned char GetTimBit(
	IN char *Ptr,
	IN unsigned short Aid,
	unsigned char *TimLen,
	unsigned char *BcastFlag,
	unsigned char *DtimCount,
	unsigned char *DtimPeriod,
	unsigned char *MessageToMe)
{
	unsigned char BitCntl, N1, N2, MyByte, MyBit;
	char *IdxPtr;

	IdxPtr = Ptr;

	IdxPtr++;
	*TimLen = *IdxPtr;

	/* get DTIM Count from TIM element */
	IdxPtr++;
	*DtimCount = *IdxPtr;

	/* get DTIM Period from TIM element */
	IdxPtr++;
	*DtimPeriod = *IdxPtr;

	/* get Bitmap Control from TIM element */
	IdxPtr++;
	BitCntl = *IdxPtr;

	if ((*DtimCount == 0) && (BitCntl & 0x01))
		*BcastFlag = TRUE;
	else
		*BcastFlag = FALSE;

	/* Parse Partial Virtual Bitmap from TIM element */
	N1 = BitCntl & 0xfe;	/* N1 is the first bitmap byte# */
	N2 = *TimLen - 4 + N1;	/* N2 is the last bitmap byte# */

	if ((Aid < (N1 << 3)) || (Aid >= ((N2 + 1) << 3)))
		*MessageToMe = FALSE;
	else {
		MyByte = (Aid >> 3) - N1;	/* my byte position in the bitmap byte-stream */
		MyBit = Aid % 16 - ((MyByte & 0x01) ? 8 : 0);

		IdxPtr += (MyByte + 1);

		if (*IdxPtr & (0x01 << MyBit))
			*MessageToMe = TRUE;
		else
			*MessageToMe = FALSE;
	}

	return TRUE;
}
