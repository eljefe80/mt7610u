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


#ifndef	__WPA_H__
#define	__WPA_H__

#ifndef ROUND_UP
#define ROUND_UP(__x, __y) \
	(((unsigned long)((__x)+((__y)-1))) & ((unsigned long)~((__y)-1)))
#endif

#define	SET_UINT16_TO_ARRARY(_V, _LEN)		\
{											\
	_V[0] = ((unsigned short)_LEN) >> 8;			\
	_V[1] = ((unsigned short)_LEN & 0xFF);					\
}

#define	INC_UINT16_TO_ARRARY(_V, _LEN)			\
{												\
	unsigned short	var_len;							\
												\
	var_len = (_V[0]<<8) | (_V[1]);				\
	var_len += _LEN;							\
												\
	_V[0] = (var_len & 0xFF00) >> 8;			\
	_V[1] = (var_len & 0xFF);					\
}

#define	CONV_ARRARY_TO_UINT16(_V)	((_V[0]<<8) | (_V[1]))

#define	ADD_ONE_To_64BIT_VAR(_V)		\
{										\
	unsigned char	cnt = LEN_KEY_DESC_REPLAY;	\
	do									\
	{									\
		cnt--;							\
		_V[cnt]++;						\
		if (cnt == 0)					\
			break;						\
	}while (_V[cnt] == 0);				\
}

#define INC_TX_TSC(_tsc, _cnt)                          \
{                                                       \
    int i=0;                                            \
	while (++_tsc[i] == 0x0)                            \
    {                                                   \
        i++;                                            \
		if (i == (_cnt))                                \
			break;                                      \
	}                                                   \
}

#define IS_WPA_CAPABILITY(a)       (((a) >= Ndis802_11AuthModeWPA) && ((a) <= Ndis802_11AuthModeWPA1PSKWPA2PSK))

/* 	
	WFA recommend to restrict the encryption type in 11n-HT mode.
 	So, the WEP and TKIP shall not be allowed to use HT rate. 
 */
#define IS_INVALID_HT_SECURITY(_mode)		\
	(((_mode) == Ndis802_11Encryption1Enabled) || \
	 ((_mode) == Ndis802_11Encryption2Enabled))

#define MIX_CIPHER_WPA_TKIP_ON(x)       (((x) & 0x08) != 0)
#define MIX_CIPHER_WPA_AES_ON(x)        (((x) & 0x04) != 0)
#define MIX_CIPHER_WPA2_TKIP_ON(x)      (((x) & 0x02) != 0)
#define MIX_CIPHER_WPA2_AES_ON(x)       (((x) & 0x01) != 0)

/* Some definition are different between Keneral mode and Daemon mode */
#ifdef WPA_DAEMON_MODE
/* The definition for Daemon mode */
#define WPA_GET_BSS_NUM(_pAd)		(_pAd)->mbss_num

#define WPA_GET_PMK(_pAd, _pEntry, _pmk)					\
{															\
	_pmk = _pAd->MBSS[_pEntry->apidx].PMK;					\
}

#define WPA_GET_GTK(_pAd, _pEntry, _gtk)					\
{															\
	_gtk = _pAd->MBSS[_pEntry->apidx].GTK;					\
}

#define WPA_GET_GROUP_CIPHER(_pAd, _pEntry, _cipher)		\
{															\
	_cipher = (_pAd)->MBSS[_pEntry->apidx].GroupEncrypType;	\
}

#define WPA_GET_DEFAULT_KEY_ID(_pAd, _pEntry, _idx)			\
{															\
	_idx = (_pAd)->MBSS[_pEntry->apidx].DefaultKeyId;		\
}

#define WPA_GET_BMCST_TSC(_pAd, _pEntry, _tsc)				\
{															\
	_tsc = 1;												\
}

#define WPA_BSSID(_pAd, _apidx)		(_pAd)->MBSS[_apidx].wlan_addr

#define WPA_OS_MALLOC(_p, _s)		\
{									\
	_p = os_malloc(_s);			\
}

#define WPA_OS_FREE(_p)		\
{								\
	os_free(_p);				\
}

#define WPA_GET_CURRENT_TIME(_time)		\
{										\
	struct timeval tv;					\
	gettimeofday(&tv, NULL);			\
	*(_time) = tv.tv_sec;					\
}

#else
/* The definition for Driver mode */

#if defined(CONFIG_AP_SUPPORT) && defined(CONFIG_STA_SUPPORT)
#define WPA_GET_BSS_NUM(_pAd)		(((_pAd)->OpMode == OPMODE_AP) ? (_pAd)->ApCfg.BssidNum : 1)
#define WPA_GET_GROUP_CIPHER(_pAd, _pEntry, _cipher)					\
	{																	\
	_cipher = Ndis802_11WEPDisabled;								\
		if ((_pAd)->OpMode == OPMODE_AP)								\
		{																\
		if (IS_ENTRY_APCLI(_pEntry) && 								\
			((_pEntry)->MatchAPCLITabIdx < MAX_APCLI_NUM))			\
			_cipher = (_pAd)->ApCfg.ApCliTab[(_pEntry)->MatchAPCLITabIdx].GroupCipher;	\
			else if ((_pEntry)->apidx < (_pAd)->ApCfg.BssidNum)			\
				_cipher = (_pAd)->ApCfg.MBSSID[_pEntry->apidx].GroupKeyWepStatus;\
		}																\
		else															\
			_cipher = (_pAd)->StaCfg.GroupCipher;						\
	}

#define WPA_BSSID(_pAd, _apidx) 	(((_pAd)->OpMode == OPMODE_AP) ?\
									(_pAd)->ApCfg.MBSSID[_apidx].Bssid :\
									(_pAd)->CommonCfg.Bssid)
#elif defined(CONFIG_AP_SUPPORT)
#define WPA_GET_BSS_NUM(_pAd)		(_pAd)->ApCfg.BssidNum
#define WPA_GET_GROUP_CIPHER(_pAd, _pEntry, _cipher)				\
	{																\
	_cipher = Ndis802_11WEPDisabled;							\
	if (IS_ENTRY_APCLI(_pEntry) && 								\
		((_pEntry)->MatchAPCLITabIdx < MAX_APCLI_NUM))			\
		_cipher = (_pAd)->ApCfg.ApCliTab[(_pEntry)->MatchAPCLITabIdx].GroupCipher;	\
		else if ((_pEntry)->apidx < (_pAd)->ApCfg.BssidNum)			\
			_cipher = (_pAd)->ApCfg.MBSSID[_pEntry->apidx].GroupKeyWepStatus;\
	}

#define WPA_BSSID(_pAd, _apidx) 	(_pAd)->ApCfg.MBSSID[_apidx].Bssid

#elif defined(CONFIG_STA_SUPPORT)
#define WPA_GET_BSS_NUM(_pAd)		1
#define WPA_GET_GROUP_CIPHER(_pAd, _pEntry, _cipher)				\
	{																\
		_cipher = (_pAd)->StaCfg.GroupCipher;						\
	}
#define WPA_BSSID(_pAd, _apidx) 	(_pAd)->CommonCfg.Bssid
#endif /* defined(CONFIG_STA_SUPPORT) */

#define WPA_OS_MALLOC(_p, _s)		\
{									\
	os_alloc_mem(NULL, (unsigned char* *)&_p, _s);		\
}

#define WPA_OS_FREE(_p)		\
{							\
	os_free_mem(NULL, _p);	\
}

#define WPA_GET_CURRENT_TIME(_time)		NdisGetSystemUpTime(_time);

#endif /* End of Driver Mode */


/*========================================
	The prototype is defined in cmm_wpa.c
  ========================================*/
void inc_iv_byte(
	unsigned char *iv,
	unsigned int len,
	unsigned int cnt);

unsigned char WpaMsgTypeSubst(
	IN unsigned char EAPType,
	int *MsgType);

void PRF(
	IN unsigned char *key,
	IN int key_len,
	IN unsigned char *prefix,
	IN int prefix_len,
	IN unsigned char *data,
	IN int data_len,
	unsigned char *output,
	IN int len);

int RtmpPasswordHash(
	char *password,
	unsigned char *ssid,
	int ssidlength,
	unsigned char *output);

	void KDF(
	IN unsigned char* key,
	IN int key_len,
	IN unsigned char* label,
	IN int label_len,
	IN unsigned char* data,
	IN int data_len,
	unsigned char* output,
	IN unsigned short len);

unsigned char* WPA_ExtractSuiteFromRSNIE(
	IN unsigned char* rsnie,
	IN unsigned int rsnie_len,
	IN unsigned char type,
	unsigned char *count);

void WpaShowAllsuite(
	IN unsigned char* rsnie,
	IN unsigned int rsnie_len);

void RTMPInsertRSNIE(
	IN unsigned char* pFrameBuf,
	unsigned long* pFrameLen,
	IN unsigned char* rsnie_ptr,
	IN unsigned char rsnie_len,
	IN unsigned char* pmkid_ptr,
	IN unsigned char pmkid_len);

/* 
 =====================================	
 	function prototype in cmm_wpa.c
 =====================================	
*/
void RTMPToWirelessSta(
	IN PRTMP_ADAPTER pAd,
	IN PMAC_TABLE_ENTRY pEntry,
	IN unsigned char* pHeader802_3,
	IN unsigned int HdrLen,
	IN unsigned char* pData,
	IN unsigned int DataLen,
	IN unsigned char bClearFrame);

void WpaDerivePTK(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char *PMK,
	IN unsigned char *ANonce,
	IN unsigned char *AA,
	IN unsigned char *SNonce,
	IN unsigned char *SA,
	unsigned char *output,
	IN unsigned int len);

void WpaDeriveGTK(
	IN unsigned char *PMK,
	IN unsigned char *GNonce,
	IN unsigned char *AA,
	unsigned char *output,
	IN unsigned int len);

void GenRandom(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char *macAddr,
	unsigned char *random);

unsigned char RTMPCheckWPAframe(
	IN PRTMP_ADAPTER pAd,
	IN PMAC_TABLE_ENTRY pEntry,
	IN unsigned char* pData,
	IN unsigned long DataByteCount,
	IN unsigned char FromWhichBSSID);

#ifdef HDR_TRANS_SUPPORT
unsigned char RTMPCheckWPAframe_Hdr_Trns(
	IN PRTMP_ADAPTER pAd,
	IN PMAC_TABLE_ENTRY pEntry,
	IN unsigned char* pData,
	IN unsigned long DataByteCount,
	IN unsigned char FromWhichBSSID);
#endif /* HDR_TRANS_SUPPORT */

unsigned char RTMPParseEapolKeyData(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pKeyData,
	IN unsigned char KeyDataLen,
	IN unsigned char GroupKeyIndex,
	IN unsigned char MsgType,
	IN unsigned char bWPA2,
	IN MAC_TABLE_ENTRY *pEntry);

void WPA_ConstructKdeHdr(
	IN unsigned char data_type,
	IN unsigned char data_len,
	unsigned char* pBuf);

void ConstructEapolMsg(
	IN PMAC_TABLE_ENTRY pEntry,
	IN unsigned char GroupKeyWepStatus,
	IN unsigned char MsgType,
	IN unsigned char DefaultKeyIdx,
	IN unsigned char *KeyNonce,
	IN unsigned char *TxRSC,
	IN unsigned char *GTK,
	IN unsigned char *RSNIE,
	IN unsigned char RSNIE_Len,
	PEAPOL_PACKET pMsg);

PCIPHER_KEY RTMPSwCipherKeySelection(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pIV,
	IN RX_BLK *pRxBlk,
	IN PMAC_TABLE_ENTRY pEntry);

NDIS_STATUS RTMPSoftDecryptionAction(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pHdr,
	IN unsigned char UserPriority,
	IN PCIPHER_KEY pKey,
	unsigned char* pData,
	unsigned short *DataByteCnt);

void RTMPSoftConstructIVHdr(
	IN unsigned char CipherAlg,
	IN unsigned char key_id,
	IN unsigned char* pTxIv,
	unsigned char* pHdrIv,
	unsigned char *hdr_iv_len);

void RTMPSoftEncryptionAction(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char CipherAlg,
	IN unsigned char* pHdr,
	IN unsigned char* pSrcBufData,
	IN unsigned int SrcBufLen,
	IN unsigned char KeyIdx,
	IN PCIPHER_KEY pKey,
	unsigned char *ext_len);

void RTMPMakeRSNIE(
	IN PRTMP_ADAPTER pAd,
	IN unsigned int AuthMode,
	IN unsigned int WepStatus,
	IN unsigned char apidx);

void WPAInstallPairwiseKey(
	PRTMP_ADAPTER pAd,
	unsigned char BssIdx,
	PMAC_TABLE_ENTRY pEntry,
	unsigned char bAE);

void WPAInstallSharedKey(
	PRTMP_ADAPTER pAd,
	unsigned char GroupCipher,
	unsigned char BssIdx,
	unsigned char KeyIdx,
	unsigned char Wcid,
	unsigned char bAE,
	unsigned char* pGtk,
	unsigned char GtkLen);

void RTMPSetWcidSecurityInfo(
	PRTMP_ADAPTER pAd,
	unsigned char BssIdx,
	unsigned char KeyIdx,
	unsigned char CipherAlg,
	unsigned char Wcid,
	unsigned char KeyTabFlag);

void CalculateMIC(
	IN unsigned char KeyDescVer,
	IN unsigned char *PTK,
	PEAPOL_PACKET pMsg);

char* GetEapolMsgType(
	char msg);

#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */

/* 
 =====================================	
 	function prototype in cmm_wep.c
 =====================================	
*/
unsigned int RTMP_CALC_FCS32(
	IN unsigned int Fcs,
	IN unsigned char* Cp,
	IN int Len);

void RTMPConstructWEPIVHdr(
	IN unsigned char key_idx,
	IN unsigned char *pn,
	unsigned char *iv_hdr);

unsigned char RTMPSoftEncryptWEP(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pIvHdr,
	IN PCIPHER_KEY pKey,
	unsigned char* pData,
	IN unsigned long DataByteCnt);

unsigned char RTMPSoftDecryptWEP(
	IN PRTMP_ADAPTER pAd,
	IN PCIPHER_KEY pKey,
	unsigned char* pData,
	unsigned short *DataByteCnt);

/* 
 =====================================	
 	function prototype in cmm_tkip.c
 =====================================	
*/
unsigned char RTMPSoftDecryptTKIP(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pHdr,
	IN unsigned char UserPriority,
	IN PCIPHER_KEY pKey,
	unsigned char* pData,
	IN unsigned short *DataByteCnt);

void TKIP_GTK_KEY_WRAP(
	IN unsigned char *key,
	IN unsigned char *iv,
	IN unsigned char *input_text,
	IN unsigned int input_len,
	unsigned char *output_text);

void TKIP_GTK_KEY_UNWRAP(
	IN unsigned char *key,
	IN unsigned char *iv,
	IN unsigned char *input_text,
	IN unsigned int input_len,
	unsigned char *output_text);

/* 
 =====================================	
 	function prototype in cmm_aes.c
 =====================================	
*/
unsigned char RTMPSoftDecryptAES(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pData,
	IN unsigned long DataByteCnt,
	IN PCIPHER_KEY pWpaKey);

void RTMPConstructCCMPHdr(
	IN unsigned char key_idx,
	IN unsigned char *pn,
	unsigned char *ccmp_hdr);

unsigned char RTMPSoftEncryptCCMP(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pHdr,
	IN unsigned char* pIV,
	IN unsigned char* pKey,
	unsigned char* pData,
	IN unsigned int DataLen);

unsigned char RTMPSoftDecryptCCMP(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char* pHdr,
	IN PCIPHER_KEY pKey,
	unsigned char* pData,
	unsigned short *DataLen);

void CCMP_test_vector(
	IN PRTMP_ADAPTER pAd,
	IN int input);

#endif
