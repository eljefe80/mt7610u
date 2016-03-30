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


#ifndef __CHLIST_H__
#define __CHLIST_H__

#include "rtmp_def.h"


typedef struct _CH_DESC {
	unsigned char FirstChannel;
	unsigned char NumOfCh;
	unsigned char ChannelProp;
}CH_DESC, *PCH_DESC;

typedef struct _COUNTRY_REGION_CH_DESC {
	unsigned char RegionIndex;
	PCH_DESC pChDesc;
}COUNTRY_REGION_CH_DESC, *PCOUNTRY_REGION_CH_DESC;

#ifdef EXT_BUILD_CHANNEL_LIST
#define ODOR			0
#define IDOR			1
#define BOTH			2

typedef struct _CH_DESP {
	unsigned char FirstChannel;
	unsigned char NumOfCh;
	CHAR MaxTxPwr;			/* dBm */
	unsigned char Geography;			/* 0:out door, 1:in door, 2:both */
	unsigned char DfsReq;			/* Dfs require, 0: No, 1: yes. */
} CH_DESP, *PCH_DESP;

typedef struct _CH_REGION {
	unsigned char CountReg[3];
	unsigned char DfsType;			/* 0: CE, 1: FCC, 2: JAP, 3:JAP_W53, JAP_W56 */
	CH_DESP *pChDesp;
} CH_REGION, *PCH_REGION;

extern CH_REGION ChRegion[];
#endif /* EXT_BUILD_CHANNEL_LIST */

#ifdef SINGLE_SKU_V2
#define SINGLE_SKU_TABLE_LENGTH			(SINGLE_SKU_TABLE_CCK_LENGTH+SINGLE_SKU_TABLE_OFDM_LENGTH+(SINGLE_SKU_TABLE_HT_LENGTH*2)+SINGLE_SKU_TABLE_VHT_LENGTH)

#define SINGLE_SKU_TABLE_CCK_LENGTH		4
#define SINGLE_SKU_TABLE_OFDM_LENGTH		8
#define SINGLE_SKU_TABLE_HT_LENGTH		16
#define SINGLE_SKU_TABLE_VHT_LENGTH		10 /* VHT MCS 0 ~ 9 */

typedef struct _CH_POWER_{
	DL_LIST		List;
	unsigned char		channel;
	unsigned char		num;
	unsigned char		PwrCCK[SINGLE_SKU_TABLE_CCK_LENGTH];
	unsigned char		PwrOFDM[SINGLE_SKU_TABLE_OFDM_LENGTH];
	unsigned char		PwrHT20[SINGLE_SKU_TABLE_HT_LENGTH];
	unsigned char		PwrHT40[SINGLE_SKU_TABLE_HT_LENGTH];
	unsigned char		PwrVHT80[SINGLE_SKU_TABLE_VHT_LENGTH];
}CH_POWER;
#endif /* SINGLE_SKU_V2 */

typedef struct _CH_FREQ_MAP_{
	unsigned short		channel;
	unsigned short		freqKHz;
}CH_FREQ_MAP;

extern CH_FREQ_MAP CH_HZ_ID_MAP[];
extern int CH_HZ_ID_MAP_NUM;


#define     MAP_CHANNEL_ID_TO_KHZ(_ch, _khz)                 \
			RTMP_MapChannelID2KHZ(_ch, (unsigned int *)&(_khz))
#define     MAP_KHZ_TO_CHANNEL_ID(_khz, _ch)                 \
			RTMP_MapKHZ2ChannelID(_khz, (int *)&(_ch))

/* Check if it is Japan W53(ch52,56,60,64) channel. */
#define JapanChannelCheck(_ch)  ((_ch == 52) || (_ch == 56) || (_ch == 60) || (_ch == 64))


#ifdef EXT_BUILD_CHANNEL_LIST
void BuildChannelListEx(
	IN PRTMP_ADAPTER pAd);

void BuildBeaconChList(
	IN PRTMP_ADAPTER pAd,
	Punsigned char pBuf,
	OUT	unsigned long* pBufLen);
#endif /* EXT_BUILD_CHANNEL_LIST */

#ifdef DOT11_N_SUPPORT
void N_ChannelCheck(RTMP_ADAPTER *pAd);
unsigned char N_SetCenCh(RTMP_ADAPTER *pAd, unsigned char channel);
unsigned char N_ChannelGroupCheck(RTMP_ADAPTER *pAd, unsigned char channel);

#endif /* DOT11_N_SUPPORT */

unsigned char GetCuntryMaxTxPwr(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char channel);

void RTMP_MapChannelID2KHZ(
	IN unsigned char Ch,
	unsigned int *pFreq);

void RTMP_MapKHZ2ChannelID(
	IN unsigned long Freq,
	int *pCh);

unsigned char GetChannel_5GHZ(
	IN PCH_DESC pChDesc, 
	IN unsigned char index);

unsigned char GetChannel_2GHZ(
	IN PCH_DESC pChDesc, 
	IN unsigned char index);

unsigned char GetChannelFlag(
	IN PCH_DESC pChDesc, 
	IN unsigned char index);

unsigned short TotalChNum(
	IN PCH_DESC pChDesc);
	
#endif /* __CHLIST_H__ */

