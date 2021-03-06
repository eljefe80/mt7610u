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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                       *
 *************************************************************************/


#ifndef __MT65XX_H__
#define __MT65XX_H__

struct _RTMP_ADAPTER;

#define MAX_CHECK_COUNT 200

#define ENABLE_WLAN_FUN(__WlanFunCtrl)\
{\
	__WlanFunCtrl.field.WLAN_CLK_EN = 1;\
	__WlanFunCtrl.field.WLAN_EN = 1;\
}

#define DISABLE_WLAN_FUN(__WlanFunCtrl)\
{\
	__WlanFunCtrl.field.PCIE_APP0_CLK_REQ = 0;\
	__WlanFunCtrl.field.WLAN_EN = 0;\
	__WlanFunCtrl.field.WLAN_CLK_EN = 0;\
}

#define COEXCFG0			0x40
#define COEXCFG3 			0x4C

#ifdef RT_BIG_ENDIAN
typedef union _COEXCFG0_STRUC{
	struct{
		unsigned int       	COEX_CFG1:8;
		unsigned int       	COEX_CFG0:8;		
		unsigned int       	FIX_WL_RF_LNA:2;
		unsigned int		FIX_BT_H_PA:3;
		unsigned int		FIX_BT_L_PA:3;
		unsigned int		FIX_WL_TX_PWR:2;
		unsigned int		Rsv:3;
		unsigned int		FIX_WL_ANT_EN:1;
		unsigned int		FIX_WL_DI_ANT:1;
		unsigned int		COEX_ENT:1;
	}field;
	unsigned int word;
}COEXCFG0_STRUC, *PCOEXCFG0_STRUC;
#else
typedef union _COEXCFG0_STRUC{
	struct{
		unsigned int		COEX_ENT:1;
		unsigned int		FIX_WL_DI_ANT:1;
		unsigned int		FIX_WL_ANT_EN:1;
		unsigned int		Rsv:3;
		unsigned int		FIX_WL_TX_PWR:2;
		unsigned int		FIX_BT_L_PA:3;
		unsigned int		FIX_BT_H_PA:3;
		unsigned int       	FIX_WL_RF_LNA:2;

		unsigned int       	COEX_CFG0:8;
		unsigned int       	COEX_CFG1:8;
	}field;
	unsigned int word;
}COEXCFG0_STRUC, *PCOEXCFG0_STRUC;
#endif

#ifdef RTMP_USB_SUPPORT
void RT65xxUsbAsicRadioOn(struct _RTMP_ADAPTER *pAd, unsigned char Stage);
void RT65xxUsbAsicRadioOff(struct _RTMP_ADAPTER *pAd, unsigned char Stage);
#endif

/*
	EEPROM format
*/

#ifdef RT_BIG_ENDIAN
typedef union _EEPROM_NIC_CINFIG0_STRUC {
	struct {
		unsigned short Rsv:6;
		unsigned short PAType:2;			/* 00: 2.4G+5G external PA, 01: 5G external PA, 10: 2.4G external PA, 11: Internal PA */
		unsigned short TxPath:4;			/* 1: 1T, 2: 2T, 3: 3T */
		unsigned short RxPath:4;			/* 1: 1R, 2: 2R, 3: 3R */
	} field;
	unsigned short word;
} EEPROM_NIC_CONFIG0_STRUC, *PEEPROM_NIC_CONFIG0_STRUC;
#else
typedef union _EEPROM_NIC_CINFIG0_STRUC {
	struct {
		unsigned short RxPath:4;			/* 1: 1R, 2: 2R, 3: 3R */
		unsigned short TxPath:4;			/* 1: 1T, 2: 2T, 3: 3T */
		unsigned short PAType:2;			/* 00: 2.4G+5G external PA, 01: 5G external PA, 10: 2.4G external PA, 11: Internal PA */
		unsigned short Rsv:6;
	} field;
	unsigned short word;
} EEPROM_NIC_CONFIG0_STRUC, *PEEPROM_NIC_CONFIG0_STRUC;
#endif

void RT65xxDisableTxRx(struct _RTMP_ADAPTER *pAd, unsigned char Level);
void RT65xx_WLAN_ChipOnOff(struct _RTMP_ADAPTER *pAd, char bOn,
							char bResetWLAN);

void dump_bw_info(struct _RTMP_ADAPTER *pAd);
#endif
