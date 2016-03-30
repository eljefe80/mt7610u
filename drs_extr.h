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


#ifndef __DRS_EXTR_H__
#define __DRS_EXTR_H__

struct _RTMP_ADAPTER;
struct _MAC_TABLE_ENTRY;


typedef struct _RTMP_TX_RATE {
	unsigned char mode;
	unsigned char bw;
	unsigned char mcs;
	unsigned char nss;
	unsigned char sgi;
	unsigned char stbc;
}RTMP_TX_RATE;


typedef struct _RTMP_RA_LEGACY_TB
{
	unsigned char   ItemNo;
#ifdef RT_BIG_ENDIAN
	unsigned char	Rsv2:1;
	unsigned char	Mode:3;
	unsigned char	BW:2;
	unsigned char	ShortGI:1;
	unsigned char	STBC:1;
#else
	unsigned char	STBC:1;
	unsigned char	ShortGI:1;
	unsigned char	BW:2;
	unsigned char	Mode:3;
	unsigned char	Rsv2:1;
#endif	
	unsigned char   CurrMCS;
	unsigned char   TrainUp;
	unsigned char   TrainDown;
} RTMP_RA_LEGACY_TB;

#define PTX_RA_LEGACY_ENTRY(pTable, idx)	((RTMP_RA_LEGACY_TB *)&(pTable[(idx+1)*5]))


#ifdef NEW_RATE_ADAPT_SUPPORT
typedef struct  _RTMP_RA_GRP_TB
{
	unsigned char   ItemNo;
#ifdef RT_BIG_ENDIAN
	unsigned char	Rsv2:1;
	unsigned char	Mode:3;	
	unsigned char	BW:2;
	unsigned char	ShortGI:1;
	unsigned char	STBC:1;
#else
	unsigned char	STBC:1;
	unsigned char	ShortGI:1;
	unsigned char	BW:2;
	unsigned char	Mode:3;
	unsigned char	Rsv2:1;
#endif	
	unsigned char   CurrMCS;
	unsigned char   TrainUp;
	unsigned char   TrainDown;
	unsigned char	downMcs;
	unsigned char	upMcs3;
	unsigned char	upMcs2;
	unsigned char	upMcs1;
	unsigned char	dataRate;
} RTMP_RA_GRP_TB;

#define PTX_RA_GRP_ENTRY(pTable, idx)	((RTMP_RA_GRP_TB *)&(pTable[(idx+1)*10]))
#endif /* NEW_RATE_ADAPT_SUPPORT */

#define RATE_TABLE_SIZE(pTable)			((pTable)[0])		/* Byte 0 is number of rate indices */
#define RATE_TABLE_INIT_INDEX(pTable)	((pTable)[1])		/* Byte 1 is initial rate index */

enum RATE_ADAPT_ALG{
	RATE_ALG_LEGACY = 1,
	RATE_ALG_GRP = 2,
	RATE_ALG_AGS = 3,
	RATE_ALG_MAX_NUM
};


typedef enum {
	RAL_OLD_DRS,
	RAL_NEW_DRS,
	RAL_QUICK_DRS
}RA_LOG_TYPE;


extern unsigned char RateSwitchTable11B[];
extern unsigned char RateSwitchTable11G[];
extern unsigned char RateSwitchTable11BG[];

#ifdef DOT11_N_SUPPORT
extern unsigned char RateSwitchTable11BGN1S[];
extern unsigned char RateSwitchTable11BGN2S[];
extern unsigned char RateSwitchTable11BGN2SForABand[];
extern unsigned char RateSwitchTable11N1S[];
extern unsigned char RateSwitchTable11N1SForABand[];
extern unsigned char RateSwitchTable11N2S[];
extern unsigned char RateSwitchTable11N2SForABand[];
extern unsigned char RateSwitchTable11BGN3S[];
extern unsigned char RateSwitchTable11BGN3SForABand[];

#ifdef NEW_RATE_ADAPT_SUPPORT
extern unsigned char RateSwitchTableAdapt11N1S[];
extern unsigned char RateSwitchTableAdapt11N2S[];
extern unsigned char RateSwitchTableAdapt11N3S[];

#define PER_THRD_ADJ			1

/* ADAPT_RATE_TABLE - true if pTable is one of the Adaptive Rate Switch tables */
#ifdef DOT11_VHT_AC
extern unsigned char RateTableVht1S[];
extern unsigned char RateTableVht1S_MCS7[];
extern unsigned char RateTableVht2S[];

#define ADAPT_RATE_TABLE(pTable)	((pTable)==RateSwitchTableAdapt11N1S ||\
									(pTable)==RateSwitchTableAdapt11N2S ||\
									(pTable)==RateSwitchTableAdapt11N3S ||\
									(pTable)==RateTableVht1S ||\
									(pTable)==RateTableVht1S_MCS7 ||\
									(pTable)==RateTableVht2S)
#else
#define ADAPT_RATE_TABLE(pTable)	((pTable)==RateSwitchTableAdapt11N1S || \
									(pTable)==RateSwitchTableAdapt11N2S || \
									(pTable)==RateSwitchTableAdapt11N3S)
#endif /* DOT11_VHT_AC */
#endif /* NEW_RATE_ADAPT_SUPPORT */
#endif /* DOT11_N_SUPPORT */


/* FUNCTION */
void MlmeGetSupportedMcs(
	IN struct _RTMP_ADAPTER *pAd,
	IN unsigned char *pTable,
	char mcs[]);

unsigned char MlmeSelectTxRate(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN char mcs[],
	IN char Rssi,
	IN char RssiOffset);

void MlmeClearTxQuality(struct _MAC_TABLE_ENTRY *pEntry);
void MlmeClearAllTxQuality(struct _MAC_TABLE_ENTRY *pEntry);
void MlmeDecTxQuality(struct _MAC_TABLE_ENTRY *pEntry, unsigned char rateIndex);
unsigned short MlmeGetTxQuality(struct _MAC_TABLE_ENTRY *pEntry, unsigned char rateIndex);
void MlmeSetTxQuality(
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN unsigned char rateIndex,
	IN unsigned short txQuality);



void MlmeOldRateAdapt(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN unsigned char			CurrRateIdx,
	IN unsigned char			UpRateIdx,
	IN unsigned char			DownRateIdx,
	IN unsigned long			TrainUp,
	IN unsigned long			TrainDown,
	IN unsigned long			TxErrorRatio);

void MlmeRestoreLastRate(
	IN struct _MAC_TABLE_ENTRY *pEntry);

void MlmeCheckRDG(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry);

void RTMPSetSupportMCS(
	IN struct _RTMP_ADAPTER *pAd,
	IN unsigned char OpMode,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN unsigned char SupRate[],
	IN unsigned char SupRateLen,
	IN unsigned char ExtRate[],
	IN unsigned char ExtRateLen,
#ifdef DOT11_VHT_AC
	IN unsigned char vht_cap_len,
	IN VHT_CAP_IE *vht_cap,
#endif /* DOT11_VHT_AC */
	IN HT_CAPABILITY_IE *pHtCapability,
	IN unsigned char HtCapabilityLen);

#ifdef NEW_RATE_ADAPT_SUPPORT
void MlmeSetMcsGroup(struct _RTMP_ADAPTER *pAd, struct _MAC_TABLE_ENTRY *pEnt);

unsigned char MlmeSelectUpRate(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN RTMP_RA_GRP_TB *pCurrTxRate);

unsigned char MlmeSelectDownRate(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN unsigned char			CurrRateIdx);

void MlmeGetSupportedMcsAdapt(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN unsigned char	mcs23GI,
	char 	mcs[]);

unsigned char MlmeSelectTxRateAdapt(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN char		mcs[],
	IN char		Rssi,
	IN char		RssiOffset);

unsigned char MlmeRAHybridRule(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN RTMP_RA_GRP_TB *pCurrTxRate,
	IN unsigned long			NewTxOkCount,
	IN unsigned long			TxErrorRatio);

void MlmeNewRateAdapt(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN unsigned char			UpRateIdx,
	IN unsigned char			DownRateIdx,
	IN unsigned long			TrainUp,
	IN unsigned long			TrainDown,
	IN unsigned long			TxErrorRatio);

INT	Set_PerThrdAdj_Proc(
	IN struct _RTMP_ADAPTER *pAd,
	IN PSTRING arg);

INT	Set_LowTrafficThrd_Proc(
	IN struct _RTMP_ADAPTER *pAd,
	IN PSTRING			arg);

INT	Set_TrainUpRule_Proc(
	IN struct _RTMP_ADAPTER *pAd,
	IN PSTRING			arg);

INT	Set_TrainUpRuleRSSI_Proc(
	IN struct _RTMP_ADAPTER *pAd,
	IN PSTRING			arg);

INT	Set_TrainUpLowThrd_Proc(
	IN struct _RTMP_ADAPTER *pAd,
	IN PSTRING			arg);

INT	Set_TrainUpHighThrd_Proc(
	IN struct _RTMP_ADAPTER *pAd,
	IN PSTRING			arg);

INT Set_RateTable_Proc(
	IN  struct _RTMP_ADAPTER *pAd,
	IN  PSTRING arg);


#ifdef CONFIG_STA_SUPPORT
void StaQuickResponeForRateUpExecAdapt(
	IN struct _RTMP_ADAPTER *pAd,
	IN unsigned long i,
	IN char Rssi);

void MlmeDynamicTxRateSwitchingAdapt(
	IN struct _RTMP_ADAPTER *pAd,
	IN unsigned long i,
	IN unsigned long TxSuccess,
	IN unsigned long TxRetransmit,
	IN unsigned long TxFailCount);
#endif /* CONFIG_STA_SUPPORT */
#endif /* NEW_RATE_ADAPT_SUPPORT */


#ifdef CONFIG_STA_SUPPORT
void MlmeDynamicTxRateSwitching(
	IN struct _RTMP_ADAPTER *pAd);

void StaQuickResponeForRateUpExec(
	IN void * SystemSpecific1, 
	IN void * FunctionContext, 
	IN void * SystemSpecific2, 
	IN void * SystemSpecific3);

void MlmeSetTxRate(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN RTMP_RA_LEGACY_TB *pTxRate);
#endif /* CONFIG_STA_SUPPORT */

void MlmeRAInit(struct _RTMP_ADAPTER *pAd, struct _MAC_TABLE_ENTRY *pEntry);
void MlmeNewTxRate(struct _RTMP_ADAPTER *pAd, struct _MAC_TABLE_ENTRY *pEntry);

void MlmeRALog(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN RA_LOG_TYPE raLogType,
	IN unsigned long TxErrorRatio,
	IN unsigned long TxTotalCnt);

void MlmeSelectTxRateTable(
	IN struct _RTMP_ADAPTER *pAd,
	IN struct _MAC_TABLE_ENTRY *pEntry,
	IN unsigned char **ppTable,
	IN unsigned char *pTableSize,
	IN unsigned char *pInitTxRateIdx);

/* normal rate switch */
#define RTMP_DRS_ALG_INIT(__pAd, __Alg)										\
	(__pAd)->rateAlg = __Alg;

#endif /* __DRS_EXTR_H__ */

/* End of drs_extr.h */
