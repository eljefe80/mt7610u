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


#ifndef	__RTMP_CHIP_H__
#define	__RTMP_CHIP_H__


struct _RTMP_ADAPTER;
struct _RSSI_SAMPLE;

#include "pbf.h"

#include "eeprom.h"


#ifdef RTMP_MAC_USB
#include "rtmp_mac.h"
#include "mac_usb.h"
#endif /* RTMP_MAC_USB */

typedef struct _RTMP_REG_PAIR {
        unsigned int Register;
        unsigned int Value;
} RTMP_REG_PAIR, *PRTMP_REG_PAIR;

typedef struct _REG_PAIR_CHANNEL {
        unsigned char Register;
        unsigned char FirstChannel;
        unsigned char LastChannel;
        unsigned char Value;
} REG_PAIR_CHANNEL, *PREG_PAIR_CHANNEL;

typedef struct _REG_PAIR_BW {
        unsigned char Register;
        unsigned char BW;
        unsigned char Value;
} REG_PAIR_BW, *PREG_PAIR_BW;


typedef struct _REG_PAIR_PHY{
        unsigned char reg;
        unsigned char s_ch;
        unsigned char e_ch;
        unsigned char phy;      /* RF_MODE_XXX */
        unsigned char bw;       /* RF_BW_XX */
        unsigned char val;
}REG_PAIR_PHY;


/* Register set pair for initialzation register set definition */
typedef struct _RTMP_RF_REGS {
        unsigned char Channel;
        unsigned int R1;
        unsigned int R2;
        unsigned int R3;
        unsigned int R4;
} RTMP_RF_REGS, *PRTMP_RF_REGS;

typedef struct _FREQUENCY_ITEM {
        unsigned char Channel;
        unsigned char N;
        unsigned char R;
        unsigned char K;
} FREQUENCY_ITEM, *PFREQUENCY_ITEM;

#define STATUS_SUCCESS                  0x00
#define STATUS_UNSUCCESSFUL             0x01

typedef struct _QUEUE_ENTRY {
        struct _QUEUE_ENTRY *Next;
} QUEUE_ENTRY, *PQUEUE_ENTRY;

/* Queue structure */
/*typedef struct _QUEUE_HEADER {
        PQUEUE_ENTRY Head;
        PQUEUE_ENTRY Tail;
        unsigned long Number;
} QUEUE_HEADER, *PQUEUE_HEADER;
*/
typedef struct _BANK_RF_REG_PAIR {
        unsigned char Bank;
        unsigned char Register;
        unsigned char Value;
} BANK_RF_REG_PAIR, *PBANK_RF_REG_PAIR;

typedef struct _R_M_W_REG{
        unsigned int Register;
        unsigned int ClearBitMask;
        unsigned int Value;
} R_M_W_REG, *PR_M_W_REG;

typedef struct _RF_R_M_W_REG{
        unsigned char Bank;
        unsigned char Register;
        unsigned char ClearBitMask;
        unsigned char Value;
} RF_R_M_W_REG, *PRF_R_M_W_REG;









#ifdef RT3290
#include "chip/rt3290.h"
#endif /* RT3290 */

#ifdef RT65xx
#include "rt65xx.h"
#endif

#ifdef MT76x0
#include "mt76x0.h"
#endif



#include "mcu_and.h"

#define IS_RT3090A(_pAd)    ((((_pAd)->MACVersion & 0xffff0000) == 0x30900000))

/* We will have a cost down version which mac version is 0x3090xxxx */
#define IS_RT3090(_pAd)     ((((_pAd)->MACVersion & 0xffff0000) == 0x30710000) || (IS_RT3090A(_pAd)))

#define IS_RT3070(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x30700000)
#define IS_RT3071(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x30710000)
#define IS_RT2070(_pAd)		(((_pAd)->RfIcType == RFIC_2020) || ((_pAd)->EFuseTag == 0x27))

#define IS_RT2860(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x28600000)
#define IS_RT2872(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x28720000)
#define IS_RT2880(_pAd)		(IS_RT2860(_pAd) && IS_RBUS_INF(_pAd))

#define IS_RT30xx(_pAd)		(((_pAd)->MACVersion & 0xfff00000) == 0x30700000||IS_RT3090A(_pAd)||IS_RT3390(_pAd))

#define IS_RT3052B(_pAd)	(((_pAd)->CommonCfg.CID == 0x102) && (((_pAd)->CommonCfg.CN >> 16) == 0x3033)) 
#define IS_RT3052(_pAd)		(((_pAd)->MACVersion == 0x28720200) && (_pAd->Antenna.field.TxPath == 2))
#define IS_RT3050(_pAd)		(((_pAd)->MACVersion == 0x28720200) && ((_pAd)->RfIcType == RFIC_3020))
#define IS_RT3350(_pAd)		(((_pAd)->MACVersion == 0x28720200) && ((_pAd)->RfIcType == RFIC_3320))
#define IS_RT3352(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x33520000)
#define IS_RT5350(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x53500000)
#define IS_RT305x(_pAd)		(IS_RT3050(_pAd) || IS_RT3052(_pAd) || IS_RT3350(_pAd) || IS_RT3352(_pAd) || IS_RT5350(_pAd))
#define IS_RT3050_3052_3350(_pAd) (\
	((_pAd)->MACVersion == 0x28720200) && \
	((((_pAd)->CommonCfg.CN >> 16) == 0x3333) || (((_pAd)->CommonCfg.CN >> 16) == 0x3033)) \
)


/* RT3572, 3592, 3562, 3062 share the same MAC version */
#define IS_RT3572(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x35720000)

/* Check if it is RT3xxx, or Specified ID in registry for debug */
#define IS_DEV_RT3xxx(_pAd)( \
	(_pAd->DeviceID == NIC3090_PCIe_DEVICE_ID) || \
	(_pAd->DeviceID == NIC3091_PCIe_DEVICE_ID) || \
	(_pAd->DeviceID == NIC3092_PCIe_DEVICE_ID) || \
	(_pAd->DeviceID == NIC3592_PCIe_DEVICE_ID) || \
	((_pAd->DeviceID == NIC3593_PCI_OR_PCIe_DEVICE_ID) && (RT3593OverPCIe(_pAd))) \
)

#define RT3593_DEVICE_ID_CHECK(__DevId)			\
	(0)

#define RT3592_DEVICE_ID_CHECK(__DevId)			\
	(__DevId == NIC3592_PCIe_DEVICE_ID)

#define IS_RT2883(_pAd)		(0)

#define IS_RT3883(_pAd)		(0)

#define IS_VERSION_BEFORE_F(_pAd)			(((_pAd)->MACVersion&0xffff) <= 0x0211)
/* F version is 0x0212, E version is 0x0211. 309x can save more power after F version. */
#define IS_VERSION_AFTER_F(_pAd)			((((_pAd)->MACVersion&0xffff) >= 0x0212) || (((_pAd)->b3090ESpecialChip == TRUE)))

#define IS_RT3290(_pAd)	(((_pAd)->MACVersion & 0xffff0000) == 0x32900000)
#define IS_RT3290LE(_pAd)   ((((_pAd)->MACVersion & 0xffffffff) >= 0x32900011))

/* 3593 */
#define IS_RT3593(_pAd) (((_pAd)->MACVersion & 0xFFFF0000) == 0x35930000)

/* RT5392 */
#define IS_RT5392(_pAd)   ((_pAd->MACVersion & 0xFFFF0000) == 0x53920000) /* Include RT5392, RT5372 and RT5362 */

/* RT5390 */
#define IS_RT5390(_pAd)   ((((_pAd)->MACVersion & 0xFFFF0000) == 0x53900000) || IS_RT5390H(_pAd)) /* Include RT5390, RT5370 and RT5360 */

/* RT5390F */
#define IS_RT5390F(_pAd)	((IS_RT5390(_pAd)) && (((_pAd)->MACVersion & 0x0000FFFF) >= 0x0502))

/* RT5370G */
#define IS_RT5370G(_pAd)	((IS_RT5390(_pAd)) && (((_pAd)->MACVersion & 0x0000FFFF) >= 0x0503)) /* support HW PPAD ( the hardware rx antenna diversity ) */

/* RT5390R */
#define IS_RT5390R(_pAd)   ((IS_RT5390(_pAd)) && (((_pAd)->MACVersion & 0x0000FFFF) == 0x1502)) /* support HW PPAD ( the hardware rx antenna diversity ) */

/* PCIe interface NIC */
#define IS_MINI_CARD(_pAd) ((_pAd)->Antenna.field.BoardType == BOARD_TYPE_MINI_CARD)

/* 5390U (5370 using PCIe interface) */
#define IS_RT5390U(_pAd)   (IS_MINI_CARD(_pAd) && ((_pAd)->MACVersion & 0xFFFF0000) == 0x53900000)

/* RT5390H */
#define IS_RT5390H(_pAd)   (((_pAd->MACVersion & 0xFFFF0000) == 0x53910000) && (((_pAd)->MACVersion & 0x0000FFFF) >= 0x1500))

/* RT5390BC8 (WiFi + BT) */


/* RT5390D */
#define IS_RT5390D(_pAd)	((IS_RT5390(_pAd)) && (((_pAd)->MACVersion & 0x0000FFFF) >= 0x0502))

/* RT5392C */
#define IS_RT5392C(_pAd)	((IS_RT5392(_pAd)) && (((_pAd)->MACVersion & 0x0000FFFF) >= 0x0222)) /* Include RT5392, RT5372 and RT5362 */

#define IS_RT5592(_pAd)		(((_pAd)->MACVersion & 0xFFFF0000) == 0x55920000)
#define REV_RT5592C			0x0221

#define IS_RT65XX(_pAd)		((((_pAd)->MACVersion & 0xFFFF0000) == 0x65900000) ||\
							 (((_pAd)->MACVersion & 0xfffff000) == 0x85592000) ||\
							 (((_pAd)->MACVersion & 0xffff0000) == 0x76500000) ||\
							 (((_pAd)->MACVersion & 0xffff0000) == 0x76620000))

#define IS_MT76x0(_pAd)		((((_pAd)->MACVersion & 0xffff0000) == 0x65900000) ||\
							 (((_pAd)->MACVersion & 0xffff0000) == 0x76500000))
#define IS_MT7650(_pAd)		(((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76500000)
#define IS_MT7650E(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76500000) && (IS_PCIE_INF(_pAd)))
#define IS_MT7650U(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76500000) && (IS_USB_INF(_pAd)))
#define IS_MT7630(_pAd)		(((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76300000)
#define IS_MT7630E(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76300000) && (IS_PCIE_INF(_pAd)))
#define IS_MT7630U(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76300000) && (IS_USB_INF(_pAd)))
#define IS_MT7610(_pAd)		(((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76100000)
#define IS_MT7610E(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76100000) && (IS_PCIE_INF(_pAd)))
#define IS_MT7610U(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76100000) && (IS_USB_INF(_pAd)))
#define IS_MT76x2(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x76620000)
#define IS_MT7662(_pAd)		(((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76620000)
#define IS_MT7662E(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76620000) && (IS_PCIE_INF(_pAd)))
#define IS_MT7662U(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76620000) && (IS_USB_INF(_pAd)))
#define IS_MT7632(_pAd)		(((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76320000)
#define IS_MT7632E(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76320000) && (IS_PCIE_INF(_pAd)))
#define IS_MT7632U(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76320000) && (IS_USB_INF(_pAd)))
#define IS_MT7612(_pAd)		(((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76120000)
#define IS_MT7612E(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76120000) && (IS_PCIE_INF(_pAd)))
#define IS_MT7612U(_pAd)	((((_pAd)->chipCap.ChipID & 0xffff0000) == 0x76120000) && (IS_USB_INF(_pAd)))
#define IS_MT76x0E(_pAd)	(IS_MT7650E(_pAd) || IS_MT7630E(_pAd) || IS_MT7610E(_pAd))
#define IS_MT76x0U(_pAd)	(IS_MT7650U(_pAd) || IS_MT7630U(_pAd) || IS_MT7610U(_pAd))
#define IS_MT76xx(_pAd)		(IS_MT76x0(_pAd) || IS_MT76x2(_pAd))
#define IS_RT8592(_pAd)		(((_pAd)->MACVersion & 0xffff0000) == 0x85590000)


/* RT3592BC8 (WiFi + BT) */

#define IS_USB_INF(_pAd)		((_pAd)->infType == RTMP_DEV_INF_USB)
#define IS_PCIE_INF(_pAd)		((_pAd)->infType == RTMP_DEV_INF_PCIE)
#define IS_PCI_INF(_pAd)		(((_pAd)->infType == RTMP_DEV_INF_PCI) || IS_PCIE_INF(_pAd))
#define IS_PCI_ONLY_INF(_pAd)	((_pAd)->infType == RTMP_DEV_INF_PCI)
#define IS_RBUS_INF(_pAd) ((_pAd)->infType == RTMP_DEV_INF_RBUS)

#define RT_REV_LT(_pAd, _chip, _rev)\
	IS_##_chip(_pAd) && (((_pAd)->MACVersion & 0x0000FFFF) < (_rev))

#define RT_REV_GTE(_pAd, _chip, _rev)\
	IS_##_chip(_pAd) && (((_pAd)->MACVersion & 0x0000FFFF) >= (_rev))

/* Dual-band NIC (RF/BBP/MAC are in the same chip.) */

#define IS_RT_NEW_DUAL_BAND_NIC(_pAd) ((FALSE))


/* Is the NIC dual-band NIC? */

#define IS_DUAL_BAND_NIC(_pAd) (((_pAd->RfIcType == RFIC_2850) || (_pAd->RfIcType == RFIC_2750) || (_pAd->RfIcType == RFIC_3052)		\
								|| (_pAd->RfIcType == RFIC_3053) || (_pAd->RfIcType == RFIC_2853) || (_pAd->RfIcType == RFIC_3853) 	\
								|| IS_RT_NEW_DUAL_BAND_NIC(_pAd)) && !IS_RT5390(_pAd))


/* RT3593 over PCIe bus */
#define RT3593OverPCIe(_pAd) (IS_RT3593(_pAd) && (_pAd->CommonCfg.bPCIeBus == TRUE))

/* RT3593 over PCI bus */
#define RT3593OverPCI(_pAd) (IS_RT3593(_pAd) && (_pAd->CommonCfg.bPCIeBus == FALSE))

/*RT3390,RT3370 */
#define IS_RT3390(_pAd)				(((_pAd)->MACVersion & 0xFFFF0000) == 0x33900000)

#define CCA_AVG_MAX_COUNT	5

/* ------------------------------------------------------ */
/* PCI registers - base address 0x0000 */
/* ------------------------------------------------------ */
#define CHIP_PCI_CFG		0x0000
#define CHIP_PCI_EECTRL		0x0004
#define CHIP_PCI_MCUCTRL	0x0008

#define OPT_14			0x114

#define RETRY_LIMIT		10

/* ------------------------------------------------------ */
/* BBP & RF	definition */
/* ------------------------------------------------------ */
#define	BUSY		                1
#define	IDLE		                0

/*------------------------------------------------------------------------- */
/* EEPROM definition */
/*------------------------------------------------------------------------- */
#define EEDO                        0x08
#define EEDI                        0x04
#define EECS                        0x02
#define EESK                        0x01
#define EERL                        0x80

#define EEPROM_WRITE_OPCODE         0x05
#define EEPROM_READ_OPCODE          0x06
#define EEPROM_EWDS_OPCODE          0x10
#define EEPROM_EWEN_OPCODE          0x13

#define NUM_EEPROM_BBP_PARMS		19	/* Include NIC Config 0, 1, CR, TX ALC step, BBPs */
#define NUM_EEPROM_TX_G_PARMS		7

#define VALID_EEPROM_VERSION        1
#define EEPROM_VERSION_OFFSET       0x02
#define EEPROM_NIC1_OFFSET          0x34	/* The address is from NIC config 0, not BBP register ID */
#define EEPROM_NIC2_OFFSET          0x36	/* The address is from NIC config 1, not BBP register ID */


#define EEPROM_COUNTRY_REGION			0x38

#define EEPROM_DEFINE_MAX_TXPWR			0x4e

#define EEPROM_FREQ_OFFSET			0x3a
#define EEPROM_LEDAG_CONF_OFFSET	0x3c
#define EEPROM_LEDACT_CONF_OFFSET	0x3e
#define EEPROM_LED_POLARITY_OFFSET	0x40
#if defined(BT_COEXISTENCE_SUPPORT) || defined(RT3290) || defined(RT8592)
#define	EEPROM_NIC3_OFFSET			0x42
#endif /* defined(BT_COEXISTENCE_SUPPORT) || defined(RT3290) || defined(RT8592) */

#define EEPROM_LNA_OFFSET			0x44

#define EEPROM_RSSI_BG_OFFSET			0x46
#define EEPROM_RSSI_A_OFFSET			0x4a
#define EEPROM_TXMIXER_GAIN_2_4G		0x48
#define EEPROM_TXMIXER_GAIN_5G			0x4c

#define EEPROM_TXPOWER_DELTA			0x50	/* 20MHZ AND 40 MHZ use different power. This is delta in 40MHZ. */

#define EEPROM_G_TX_PWR_OFFSET			0x52
#define EEPROM_G_TX2_PWR_OFFSET			0x60

#define EEPROM_G_TSSI_BOUND1			0x6e
#define EEPROM_G_TSSI_BOUND2			0x70
#define EEPROM_G_TSSI_BOUND3			0x72
#define EEPROM_G_TSSI_BOUND4			0x74
#define EEPROM_G_TSSI_BOUND5			0x76

#define EEPROM_A_TX_PWR_OFFSET      		0x78
#define EEPROM_A_TX2_PWR_OFFSET			0xa6

#define MBSSID_MODE0 0
#define MBSSID_MODE1 1
#ifdef ENHANCE_NEW_MBSSID_MODE
#define MBSSID_MODE2	2	/* Enhance NEW MBSSID MODE mapping to mode 1 */
#define MBSSID_MODE3	3	/* Enhance NEW MBSSID MODE mapping to mode 2 */
#define MBSSID_MODE4	4	/* Enhance NEW MBSSID MODE mapping to mode 3 */
#define MBSSID_MODE5	5	/* Enhance NEW MBSSID MODE mapping to mode 4 */
#define MBSSID_MODE6	6	/* Enhance NEW MBSSID MODE mapping to mode 5 */
#endif /* ENHANCE_NEW_MBSSID_MODE */

enum FREQ_CAL_INIT_MODE {
	FREQ_CAL_INIT_MODE0,
	FREQ_CAL_INIT_MODE1,
	FREQ_CAL_INIT_MODE2,
	FREQ_CAL_INIT_UNKNOW,
};

enum FREQ_CAL_MODE {
	FREQ_CAL_MODE0,
	FREQ_CAL_MODE1,
	FREQ_CAL_MODE2,
};

enum RXWI_FRQ_OFFSET_FIELD {
	RXWI_FRQ_OFFSET_FIELD0, /* SNR1 */
	RXWI_FRQ_OFFSET_FIELD1, /* Frequency Offset */
};


#ifdef MT76x0
#define EEPROM_MT76x0_TEMPERATURE_OFFSET	0xd1 /* signed value */
#define EEPROM_MT76x0_A_BAND_MB				0xdc
#define EEPROM_MT76x0_A_BAND_HB				0xdd

#define EEPROM_MT76x0_2G_TARGET_POWER		0xd0
#define EEPROM_MT76x0_5G_TARGET_POWER		0xd2
#define EEPROM_MT76x0_2G_SLOPE_OFFSET		0x6E
#define EEPROM_MT76x0_5G_SLOPE_OFFSET		0xf0
#define EEPROM_MT76x0_5G_CHANNEL_BOUNDARY 	0xd4
#endif /* MT76x0 */

#define EEPROM_A_TSSI_BOUND1		0xd4
#define EEPROM_A_TSSI_BOUND2		0xd6
#define EEPROM_A_TSSI_BOUND3		0xd8
#define EEPROM_A_TSSI_BOUND4		0xda
#define EEPROM_A_TSSI_BOUND5		0xdc

/* ITxBF calibration values EEPROM locations 0x1a0 to 0x1ab */
#define EEPROM_ITXBF_CAL				0x1a0

#else
#define EEPROM_TXPOWER_BYRATE 			0xde	/* 20MHZ power. */
#define EEPROM_TXPOWER_BYRATE_20MHZ_2_4G	0xde	/* 20MHZ 2.4G tx power. */
#define EEPROM_TXPOWER_BYRATE_40MHZ_2_4G	0xee	/* 40MHZ 2.4G tx power. */
#define EEPROM_TXPOWER_BYRATE_20MHZ_5G		0xfa	/* 20MHZ 5G tx power. */
#define EEPROM_TXPOWER_BYRATE_40MHZ_5G		0x10a	/* 40MHZ 5G tx power. */

#define EEPROM_BBP_BASE_OFFSET			0xf0	/* The address is from NIC config 0, not BBP register ID */

/* */
/* Bit mask for the Tx ALC and the Tx fine power control */
/* */
#define GET_TX_ALC_BIT_MASK					0x1F	/* Valid: 0~31, and in 0.5dB step */
#define GET_TX_FINE_POWER_CTRL_BIT_MASK	0xE0	/* Valid: 0~4, and in 0.1dB step */
#define NUMBER_OF_BITS_FOR_TX_ALC			5	/* The length, in bit, of the Tx ALC field */


/* TSSI gain and TSSI attenuation */

#define EEPROM_TSSI_GAIN_AND_ATTENUATION	0x76

/*#define EEPROM_Japan_TX_PWR_OFFSET      0x90 // 802.11j */
/*#define EEPROM_Japan_TX2_PWR_OFFSET      0xbe */
/*#define EEPROM_TSSI_REF_OFFSET	0x54 */
/*#define EEPROM_TSSI_DELTA_OFFSET	0x24 */
/*#define EEPROM_CCK_TX_PWR_OFFSET  0x62 */
/*#define EEPROM_CALIBRATE_OFFSET	0x7c */

#define EEPROM_NIC_CFG1_OFFSET		0
#define EEPROM_NIC_CFG2_OFFSET		1
#define EEPROM_NIC_CFG3_OFFSET		2
#define EEPROM_COUNTRY_REG_OFFSET	3
#define EEPROM_BBP_ARRAY_OFFSET		4

#if defined(RTMP_intERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 
/* */
/* The TSSI over OFDM 54Mbps */
/* */
#define EEPROM_TSSI_OVER_OFDM_54		0x6E

/* */
/* The TSSI value/step (0.5 dB/unit) */
/* */
#define EEPROM_TSSI_STEP_OVER_2DOT4G	0x77
#define EEPROM_TSSI_STEP_OVER_5DOT5G	0xDD
#define TSSI_READ_SAMPLE_NUM			3

/* */
/* Per-channel Tx power offset (for the extended TSSI mode) */
/* */
#define EEPROM_TX_POWER_OFFSET_OVER_CH_1	0x6F
#define EEPROM_TX_POWER_OFFSET_OVER_CH_3	0x70
#define EEPROM_TX_POWER_OFFSET_OVER_CH_5	0x71
#define EEPROM_TX_POWER_OFFSET_OVER_CH_7	0x72
#define EEPROM_TX_POWER_OFFSET_OVER_CH_9	0x73
#define EEPROM_TX_POWER_OFFSET_OVER_CH_11	0x74
#define EEPROM_TX_POWER_OFFSET_OVER_CH_13	0x75

/* */
/* Tx power configuration (bit3:0 for Tx0 power setting and bit7:4 for Tx1 power setting) */
/* */
#define EEPROM_CCK_MCS0_MCS1				0xDE
#define EEPROM_CCK_MCS2_MCS3				0xDF
#define EEPROM_OFDM_MCS0_MCS1			0xE0
#define EEPROM_OFDM_MCS2_MCS3			0xE1
#define EEPROM_OFDM_MCS4_MCS5			0xE2
#define EEPROM_OFDM_MCS6_MCS7			0xE3
#define EEPROM_HT_MCS0_MCS1				0xE4
#define EEPROM_HT_MCS2_MCS3				0xE5
#define EEPROM_HT_MCS4_MCS5				0xE6
#define EEPROM_HT_MCS6_MCS7				0xE7
#define EEPROM_HT_MCS8_MCS9                     	0xE8
#define EEPROM_HT_MCS10_MCS11                   	0xE9
#define EEPROM_HT_MCS12_MCS13                   	0xEA
#define EEPROM_HT_MCS14_MCS15                   	0xEB
#define EEPROM_HT_USING_STBC_MCS0_MCS1	0xEC
#define EEPROM_HT_USING_STBC_MCS2_MCS3	0xED
#define EEPROM_HT_USING_STBC_MCS4_MCS5	0xEE
#define EEPROM_HT_USING_STBC_MCS6_MCS7	0xEF

/* */
/* Bit mask for the Tx ALC and the Tx fine power control */
/* */

#define DEFAULT_BBP_TX_FINE_POWER_CTRL 	0

#endif /* RTMP_intERNAL_TX_ALC || RTMP_TEMPERATURE_COMPENSATION */


#ifdef RT_BIG_ENDIAN
typedef union _EEPROM_ANTENNA_STRUC {
	struct {
		unsigned short RssiIndicationMode:1; 	/* RSSI indication mode */
		unsigned short Rsv:1;
		unsigned short BoardType:2; 		/* 0: mini card; 1: USB pen */
		unsigned short RfIcType:4;			/* see E2PROM document */
		unsigned short TxPath:4;			/* 1: 1T, 2: 2T, 3: 3T */
		unsigned short RxPath:4;			/* 1: 1R, 2: 2R, 3: 3R */
	} field;
	unsigned short word;
} EEPROM_ANTENNA_STRUC, *PEEPROM_ANTENNA_STRUC;
#else
typedef union _EEPROM_ANTENNA_STRUC {
	struct {
		unsigned short RxPath:4;			/* 1: 1R, 2: 2R, 3: 3R */
		unsigned short TxPath:4;			/* 1: 1T, 2: 2T, 3: 3T */
		unsigned short RfIcType:4;			/* see E2PROM document */
		unsigned short BoardType:2; 		/* 0: mini card; 1: USB pen */
		unsigned short Rsv:1;
		unsigned short RssiIndicationMode:1; 	/* RSSI indication mode */	
	} field;
	unsigned short word;
} EEPROM_ANTENNA_STRUC, *PEEPROM_ANTENNA_STRUC;
#endif


/*
  *   EEPROM operation related marcos
  */
#define RT28xx_EEPROM_READ16(_pAd, _offset, _value)			\
	(_pAd)->chipOps.eeread((RTMP_ADAPTER *)(_pAd), (unsigned short)(_offset), (Punsigned short)&(_value))

#define RT28xx_EEPROM_WRITE16(_pAd, _offset, _value)		\
	(_pAd)->chipOps.eewrite((RTMP_ADAPTER *)(_pAd), (unsigned short)(_offset), (unsigned short)(_value))


#if defined(RTMP_intERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 
/* The Tx power tuning entry */
typedef struct _TX_POWER_TUNING_ENTRY_STRUCT {
	char	RF_TX_ALC; 		/* 3390: RF R12[4:0]: Tx0 ALC, 5390: RF R49[5:0]: Tx0 ALC */
	char 	MAC_PowerDelta;	/* Tx power control over MAC 0x1314~0x1324 */
} TX_POWER_TUNING_ENTRY_STRUCT, *PTX_POWER_TUNING_ENTRY_STRUCT;
#endif /* defined(RTMP_intERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) */

struct RF_BANK_OFFSET {
	unsigned char RFBankIndex;
	unsigned short RFStart;
	unsigned short RFEnd;
};

/*
	2860: 28xx
	2870: 28xx

	30xx:
		3090
		3070
		2070 3070

	33xx:	30xx
		3390 3090
		3370 3070

	35xx:	30xx
		3572, 2870, 28xx
		3062, 2860, 28xx
		3562, 2860, 28xx

	3593, 28xx, 30xx, 35xx

	< Note: 3050, 3052, 3350 can not be compiled simultaneously. >
	305x:
		3052
		3050
		3350, 3050

	3352: 305x

	2880: 28xx
	2883:
	3883:
*/

struct _RTMP_CHIP_CAP_ {
	unsigned int ChipID;
	/* register */
	RTMP_REG_PAIR *pRFRegTable;
	RTMP_REG_PAIR *pBBPRegTable;
	unsigned char bbpRegTbSize;

	unsigned int MaxNumOfRfId;
	unsigned int MaxNumOfBbpId;

#define RF_REG_WT_METHOD_NONE			0
#define RF_REG_WT_METHOD_STEP_ON		1
	unsigned char RfReg17WtMethod;

	/* beacon */
	unsigned char FlgIsSupSpecBcnBuf;	/* SPECIFIC_BCN_BUF_SUPPORT */
	unsigned char BcnMaxNum;	/* software use */
	unsigned char BcnMaxHwNum;	/* hardware limitation */
	unsigned char WcidHwRsvNum;	/* hardware available WCID number */
	unsigned short BcnMaxHwSize;	/* hardware maximum beacon size */
	unsigned short BcnBase[HW_BEACON_MAX_NUM];	/* hardware beacon base address */
	
	/* function */
	/* use unsigned char, not bit-or to speed up driver */
	unsigned char FlgIsHwWapiSup;

	/* VCO calibration mode */
	unsigned char	VcoPeriod; /* default 10s */
#define VCO_CAL_DISABLE		0	/* not support */
#define VCO_CAL_MODE_1		1	/* toggle RF7[0] */
#define VCO_CAL_MODE_2		2	/* toggle RF3[7] */
#define VCO_CAL_MODE_3		3	/* toggle RF4[7] */	
	unsigned char	FlgIsVcoReCalMode;

	unsigned char FlgIsHwAntennaDiversitySup;
#ifdef STREAM_MODE_SUPPORT
	unsigned char FlgHwStreamMode;
#endif /* STREAM_MODE_SUPPORT */
#ifdef TXBF_SUPPORT
	unsigned char FlgHwTxBfCap;
#endif /* TXBF_SUPPORT */
#ifdef FIFO_EXT_SUPPORT
	unsigned char FlgHwFifoExtCap;
#endif /* FIFO_EXT_SUPPORT */


	enum ASIC_CAP asic_caps;
	enum PHY_CAP phy_caps;
	
#ifdef TXRX_SW_ANTDIV_SUPPORT
	unsigned char bTxRxSwAntDiv;
#endif /* TXRX_SW_ANTDIV_SUPPORT */

	/* ---------------------------- signal ---------------------------------- */
#define SNR_FORMULA1		0	/* ((0xeb     - pAd->StaCfg.LastSNR0) * 3) / 16; */
#define SNR_FORMULA2		1	/* (pAd->StaCfg.LastSNR0 * 3 + 8) >> 4; */
#define SNR_FORMULA3		2	/* (pAd->StaCfg.LastSNR0) * 3) / 16; */
	unsigned char SnrFormula;

	unsigned char MaxNss;			/* maximum Nss, 3 for 3883 or 3593 */

	unsigned char bTempCompTxALC;
	unsigned char rx_temp_comp;

	unsigned char bLimitPowerRange; /* TSSI compensation range limit */

#if defined(RTMP_intERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION)
	unsigned char TxAlcTxPowerUpperBound_2G;
	const TX_POWER_TUNING_ENTRY_STRUCT *TxPowerTuningTable_2G;
#ifdef A_BAND_SUPPORT
	unsigned char TxAlcTxPowerUpperBound_5G;
	const TX_POWER_TUNING_ENTRY_STRUCT *TxPowerTuningTable_5G;
#endif /* A_BAND_SUPPORT */
#endif /* defined(RTMP_intERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) */

#ifdef SINGLE_SKU_V2
	int16	PAModeCCK[4];
	int16	PAModeOFDM[8];
	int16	PAModeHT[16];
#ifdef DOT11_VHT_AC
	int16	PAModeVHT[10];
#endif /* DOT11_VHT_AC */
#endif /* SINGLE_SKU_V2 */

	/* ---------------------------- packet ---------------------------------- */
	unsigned char TXWISize;
	unsigned char RXWISize;

	/* ---------------------------- others ---------------------------------- */
#ifdef RTMP_EFUSE_SUPPORT
	unsigned short EFUSE_USAGE_MAP_START;
	unsigned short EFUSE_USAGE_MAP_END;
	unsigned char EFUSE_USAGE_MAP_SIZE;
#endif /* RTMP_EFUSE_SUPPORT */

#ifdef RTMP_FLASH_SUPPORT
	unsigned char *eebuf;
#endif /* RTMP_FLASH_SUPPORT */
#ifdef CARRIER_DETECTION_SUPPORT
	unsigned char carrier_func;
#endif /* CARRIER_DETECTION_SUPPORT */
#ifdef DFS_SUPPORT
	unsigned char DfsEngineNum;
#endif /* DFS_SUPPORT */

	/*
		Define the burst size of WPDMA of PCI
		0 : 4 DWORD (16bytes)
		1 : 8 DWORD (32 bytes)
		2 : 16 DWORD (64 bytes)
		3 : 32 DWORD (128 bytes)
	*/
	unsigned char WPDMABurstSIZE;

	/* 
 	 * 0: MBSSID_MODE0 
 	 * (The multiple MAC_ADDR/BSSID are distinguished by [bit2:bit0] of byte5) 
 	 * 1: MBSSID_MODE1
 	 * (The multiple MAC_ADDR/BSSID are distinguished by [bit4:bit2] of byte0) 
 	 */
	unsigned char MBSSIDMode;

	/* 2nd CCA Detection ++ */
	unsigned char b2ndCCACheck;
	unsigned char CCARatioA;
	unsigned char CCARatioB;
	unsigned char CCACheckPeriod; /* unit: second */
	char RssiThreshold;
	char RssiAvg;
	unsigned int CCAThresholdA;
	unsigned int CCAThresholdB;
	unsigned long CCARecordCnt; /* unit: second */
	unsigned long CCAAvg[CCA_AVG_MAX_COUNT];
	unsigned char CCAAvgIdx;
	void*pWeakestEntry;
	/* 2nd CCA Detection -- */


#ifdef CONFIG_STA_SUPPORT
	unsigned char init_vga_gain_5G;
	unsigned char init_vga_gain_2G;
#endif /* CONFIG_STA_SUPPORT */

#ifdef RT5592EP_SUPPORT
	unsigned int Priv; /* Flag for RT5592 EP */
#endif /* RT5592EP_SUPPORT */

#ifdef RT65xx
	unsigned char PAType; /* b'00: 2.4G+5G external PA, b'01: 5G external PA, b'10: 2.4G external PA, b'11: internal PA */
#endif /* RT65xx */

#ifdef CONFIG_ANDES_SUPPORT
	unsigned int WlanMemmapOffset;
	unsigned int InbandPacketMaxLen; /* must be 48 multible */
	unsigned char CmdRspRxRing;
	unsigned char IsComboChip;
	u8 load_iv;
	u32 ilm_offset;
	u32 dlm_offset;
#endif

	unsigned char cmd_header_len;
	unsigned char cmd_padding_len;

#ifdef RTMP_USB_SUPPORT
	unsigned char DataBulkInAddr;
	unsigned char CommandRspBulkInAddr;
	unsigned char WMM0ACBulkOutAddr[4];
	unsigned char WMM1ACBulkOutAddr;
	unsigned char CommandBulkOutAddr;
#endif
	
	enum MCU_TYPE MCUType;
	unsigned char *FWImageName;
	unsigned char *MACRegisterVer;
	unsigned char *BBPRegisterVer;
	unsigned char *RFRegisterVer;

#ifdef MT76x0
	unsigned char bDoTemperatureSensor;
	short TemperatureOffset;
	short LastTemperatureforVCO;
	short LastTemperatureforCal;
	short NowTemperature;
	unsigned char a_band_mid_ch;
	unsigned char a_band_high_ch;
	unsigned char ext_pa_current_setting;
	MT76x0_RATE_PWR_Table rate_pwr_table;
	unsigned char delta_tw_pwr_bw40_5G;
	unsigned char delta_tw_pwr_bw40_2G;
	unsigned char delta_tw_pwr_bw80;
#ifdef MT76x0_TSSI_CAL_COMPENSATION
	unsigned char binternalTxALC; /* internal Tx ALC */
	unsigned char tssi_info_1;
	unsigned char tssi_info_2;
	unsigned char tssi_info_3;
	unsigned char tssi_2G_target_power;
	unsigned char tssi_5G_target_power;
	unsigned char efuse_2G_54M_tx_power;
	unsigned char efuse_5G_54M_tx_power;
	MT76x0_TSSI_Table tssi_table;
	char tssi_slope_2G;
	char tssi_offset_2G;
	unsigned char tssi_slope_5G[8];
	char tssi_offset_5G[8];
	unsigned char tssi_5G_channel_boundary[7];
	char tssi_current_DC;
	int tssi_pre_delta_pwr;
#endif /* MT76x0_TSSI_CAL_COMPENSATION */
#endif /* MT76x0 */

#ifdef CONFIG_WIFI_TEST
	unsigned int MemMapStart;
	unsigned int MemMapEnd;
	unsigned int BBPMemMapOffset;
	unsigned short BBPStart;
	unsigned short BBPEnd;
	unsigned short RFStart;
	unsigned short RFEnd;
	unsigned char RFBankNum;
	struct RF_BANK_OFFSET *RFBankOffset;
	unsigned int MacMemMapOffset;
	unsigned int MacStart;
	unsigned int MacEnd;
	unsigned short E2PStart;
	unsigned short E2PEnd;
#endif
};

typedef void(*CHIP_SPEC_FUNC)(void *pAd, void *pData, unsigned long Data);

/* The chip specific function ID */
typedef enum _CHIP_SPEC_ID
{
	CHIP_SPEC_RESV_FUNC
} CHIP_SPEC_ID;

#define CHIP_SPEC_ID_NUM 	CHIP_SPEC_RESV_FUNC


struct _RTMP_CHIP_OP_ {
	/*  Calibration access related callback functions */
	int (*eeinit)(struct _RTMP_ADAPTER *pAd);
	int (*eeread)(struct _RTMP_ADAPTER *pAd, unsigned short offset, unsigned short* pValue);
	int (*eewrite)(struct _RTMP_ADAPTER *pAd, unsigned short offset, unsigned short value);

	/* MCU related callback functions */
	int (*loadFirmware)(struct _RTMP_ADAPTER *pAd);
	int (*eraseFirmware)(struct _RTMP_ADAPTER *pAd);
	int (*sendCommandToMcu)(struct _RTMP_ADAPTER *pAd, unsigned char cmd, unsigned char token, unsigned char arg0, unsigned char arg1, unsigned char FlgIsNeedLocked);	/* int (*sendCommandToMcu)(RTMP_ADAPTER *pAd, unsigned char cmd, unsigned char token, unsigned char arg0, unsigned char arg1); */
#ifdef CONFIG_ANDES_SUPPORT
	int (*sendCommandToAndesMcu)(struct _RTMP_ADAPTER *pAd, unsigned char QueIdx, unsigned char cmd, unsigned char *pData, unsigned short DataLen, unsigned char FlgIsNeedLocked);
#endif

	void (*AsicRfInit)(struct _RTMP_ADAPTER *pAd);
	void (*AsicBbpInit)(struct _RTMP_ADAPTER *pAd);
	void (*AsicMacInit)(struct _RTMP_ADAPTER *pAd);

	void (*AsicRfTurnOn)(struct _RTMP_ADAPTER *pAd);
	void (*AsicRfTurnOff)(struct _RTMP_ADAPTER *pAd);
	void (*AsicReverseRfFromSleepMode)(struct _RTMP_ADAPTER *pAd, unsigned char FlgIsInitState);
	void (*AsicHaltAction)(struct _RTMP_ADAPTER *pAd);

	/* Power save */
	void(*EnableAPMIMOPS)(struct _RTMP_ADAPTER *pAd, unsigned char ReduceCorePower);
	void(*DisableAPMIMOPS)(struct _RTMP_ADAPTER *pAd);
	int (*PwrSavingOP)(struct _RTMP_ADAPTER *pAd, unsigned int PwrOP, unsigned int PwrLevel, 
							unsigned int Listeninterval, unsigned int PreTBTTLeadTime,
							unsigned char TIMByteOffset, unsigned char TIMBytePattern);

	/* Chip tuning */
	void(*RxSensitivityTuning)(struct _RTMP_ADAPTER *pAd);

	/* MAC */
	void(*BeaconUpdate)(struct _RTMP_ADAPTER *pAd, unsigned short Offset, unsigned int Value, unsigned char Unit);

	/* BBP adjust */
	void(*ChipBBPAdjust)(struct _RTMP_ADAPTER *pAd);

	/* AGC */
	void(*ChipAGCInit)(struct _RTMP_ADAPTER *pAd, unsigned char bw);
	unsigned char (*ChipAGCAdjust)(struct _RTMP_ADAPTER *pAd, char Rssi, unsigned char OrigR66Value);
	
	/* Channel */
	void(*ChipSwitchChannel)(struct _RTMP_ADAPTER *pAd, unsigned char ch, enum SWITCH_CHANNEL_STAGE Stage);

	/* IQ Calibration */
	void(*ChipIQCalibration)(struct _RTMP_ADAPTER *pAd, unsigned char Channel);

	/* TX ALC */
	unsigned int (*TSSIRatio)(int delta_power);
	void(*InitDesiredTSSITable)(struct _RTMP_ADAPTER *pAd);
	int (*ATETssiCalibration)(struct _RTMP_ADAPTER *pAd, char * arg);
	int (*ATETssiCalibrationExtend)(struct _RTMP_ADAPTER *pAd, char * arg);
	int (*ATEReadExternalTSSI)(struct _RTMP_ADAPTER *pAd, char * arg);

	void(*AsicTxAlcGetAutoAgcOffset)(
				struct _RTMP_ADAPTER	*pAd,
				char *				pDeltaPwr,
				char *				pTotalDeltaPwr,
				char *				pAgcCompensate,
				char * 				pDeltaPowerByBbpR1);


	
	void(*AsicGetTxPowerOffset)(struct _RTMP_ADAPTER *pAd, unsigned long *TxPwr);
	void(*AsicExtraPowerOverMAC)(struct _RTMP_ADAPTER *pAd);
	
	/* Antenna */
	void(*AsicAntennaDefaultReset)(struct _RTMP_ADAPTER *pAd, union _EEPROM_ANTENNA_STRUC *pAntenna);
	void(*SetRxAnt)(struct _RTMP_ADAPTER *pAd, unsigned char Ant);

	/* EEPROM */
	void(*NICInitAsicFromEEPROM)(struct _RTMP_ADAPTER *pAd);

	/* high power tuning */
	void(*HighPowerTuning)(struct _RTMP_ADAPTER *pAd, struct _RSSI_SAMPLE *pRssi);
	
	/* Others */
	void(*NetDevNickNameInit)(struct _RTMP_ADAPTER *pAd);

	/* The chip specific function list */
	CHIP_SPEC_FUNC ChipSpecFunc[CHIP_SPEC_ID_NUM];
	
	void(*AsicResetBbpAgent)(struct _RTMP_ADAPTER *pAd);

#ifdef CARRIER_DETECTION_SUPPORT
	void(*ToneRadarProgram)(struct _RTMP_ADAPTER *pAd, unsigned long  threshold);
#endif /* CARRIER_DETECTION_SUPPORT */
	void(*CckMrcStatusCtrl)(struct _RTMP_ADAPTER *pAd);
	void(*RadarGLRTCompensate)(struct _RTMP_ADAPTER *pAd);
	
	void(*Calibration)(struct _RTMP_ADAPTER *pAd, unsigned int CalibrationID, unsigned int Parameter);
	void(*SecondCCADetection)(struct _RTMP_ADAPTER *pAd);

	int (*BurstWrite)(struct _RTMP_ADAPTER *ad, unsigned int Offset, unsigned int *Data, unsigned int Cnt);

	int (*BurstRead)(struct _RTMP_ADAPTER *ad, unsigned int Offset, unsigned int Cnt, unsigned int *Data);

	int (*RandomRead)(struct _RTMP_ADAPTER *ad, RTMP_REG_PAIR *RegPair, unsigned int Num);

	int (*RFRandomRead)(struct _RTMP_ADAPTER *ad, BANK_RF_REG_PAIR *RegPair, unsigned int Num);

	int (*ReadModifyWrite)(struct _RTMP_ADAPTER *ad, R_M_W_REG *RegPair, unsigned int Num);

	int (*RFReadModifyWrite)(struct _RTMP_ADAPTER *ad, RF_R_M_W_REG *RegPair, unsigned int Num);

	int (*RandomWrite)(struct _RTMP_ADAPTER *ad, RTMP_REG_PAIR *RegPair, unsigned int Num);

	int (*RFRandomWrite)(struct _RTMP_ADAPTER *ad, BANK_RF_REG_PAIR *RegPair, unsigned int Num);

	void (*DisableTxRx)(struct _RTMP_ADAPTER *ad, unsigned char Level);

	void (*AsicRadioOn)(struct _RTMP_ADAPTER *ad, unsigned char Stage);

	void (*AsicRadioOff)(struct _RTMP_ADAPTER *ad, u8 Stage);

	void (*MCUCtrlInit)(struct _RTMP_ADAPTER *ad);
	
	void (*MCUCtrlExit)(struct _RTMP_ADAPTER *ad);

	void (*usb_cfg_read)(struct _RTMP_ADAPTER *ad, u32 *value);

	void (*usb_cfg_write)(struct _RTMP_ADAPTER *ad, u32 value);
};

#define RTMP_CHIP_ENABLE_AP_MIMOPS(__pAd, __ReduceCorePower)	\
do {	\
		if (__pAd->chipOps.EnableAPMIMOPS != NULL)	\
			__pAd->chipOps.EnableAPMIMOPS(__pAd, __ReduceCorePower);	\
} while (0)

#define RTMP_CHIP_DISABLE_AP_MIMOPS(__pAd)	\
do {	\
		if (__pAd->chipOps.DisableAPMIMOPS != NULL)	\
			__pAd->chipOps.DisableAPMIMOPS(__pAd);	\
} while (0)
	
#define PWR_SAVING_OP(__pAd, __PwrOP, __PwrLevel, __Listeninterval, \
						__PreTBTTLeadTime, __TIMByteOffset, __TIMBytePattern)	\
do {	\
		if (__pAd->chipOps.PwrSavingOP != NULL)	\
			__pAd->chipOps.PwrSavingOP(__pAd, __PwrOP, __PwrLevel,	\
										__Listeninterval,__PreTBTTLeadTime, \
										__TIMByteOffset, __TIMBytePattern);	\
} while (0)

#define RTMP_CHIP_RX_SENSITIVITY_TUNING(__pAd)	\
do {	\
		if (__pAd->chipOps.RxSensitivityTuning != NULL)	\
			__pAd->chipOps.RxSensitivityTuning(__pAd);	\
} while (0)

#define RTMP_CHIP_ASIC_AGC_ADJUST(__pAd, __Rssi, __R66)	\
do {	\
		if (__pAd->chipOps.ChipAGCAdjust != NULL)	\
			__R66 = __pAd->chipOps.ChipAGCAdjust(__pAd, __Rssi, __R66);	\
} while (0)

#define RTMP_CHIP_ASIC_TSSI_TABLE_INIT(__pAd)	\
do {	\
		if (__pAd->chipOps.InitDesiredTSSITable != NULL)	\
			__pAd->chipOps.InitDesiredTSSITable(__pAd);	\
} while (0)

#define RTMP_CHIP_ATE_TSSI_CALIBRATION(__pAd, __pData)	\
do {	\
		if (__pAd->chipOps.ATETssiCalibration != NULL)	\
			__pAd->chipOps.ATETssiCalibration(__pAd, __pData);	\
} while (0)

#define RTMP_CHIP_ATE_TSSI_CALIBRATION_EXTEND(__pAd, __pData)	\
do {	\
		if (__pAd->chipOps.ATETssiCalibrationExtend != NULL)	\
			__pAd->chipOps.ATETssiCalibrationExtend(__pAd, __pData);	\
} while (0)	

#define RTMP_CHIP_ATE_READ_EXTERNAL_TSSI(__pAd, __pData)	\
do {	\
		if (__pAd->chipOps.ATEReadExternalTSSI != NULL)	\
			__pAd->chipOps.ATEReadExternalTSSI(__pAd, __pData);	\
} while (0)

#define RTMP_CHIP_ASIC_TX_POWER_OFFSET_GET(__pAd, __pCfgOfTxPwrCtrlOverMAC)	\
do {	\
		if (__pAd->chipOps.AsicGetTxPowerOffset != NULL)	\
			__pAd->chipOps.AsicGetTxPowerOffset(__pAd, __pCfgOfTxPwrCtrlOverMAC);	\
} while (0)
		
#define RTMP_CHIP_ASIC_AUTO_AGC_OFFSET_GET(	\
		__pAd, __pDeltaPwr, __pTotalDeltaPwr, __pAgcCompensate, __pDeltaPowerByBbpR1)	\
do {	\
		if (__pAd->chipOps.AsicTxAlcGetAutoAgcOffset != NULL)	\
			__pAd->chipOps.AsicTxAlcGetAutoAgcOffset(	\
		__pAd, __pDeltaPwr, __pTotalDeltaPwr, __pAgcCompensate, __pDeltaPowerByBbpR1);	\
} while (0)

#define RTMP_CHIP_ASIC_EXTRA_POWER_OVER_MAC(__pAd)	\
do {	\
		if (__pAd->chipOps.AsicExtraPowerOverMAC != NULL)	\
			__pAd->chipOps.AsicExtraPowerOverMAC(__pAd);	\
} while (0)

#define RTMP_CHIP_ASIC_GET_TSSI_RATIO(__pAd, __DeltaPwr)	\
do {	\
		if (__pAd->chipOps.AsicFreqCalStop != NULL)	\
			__pAd->chipOps.TSSIRatio(__DeltaPwr);	\
} while (0)

#define RTMP_CHIP_ASIC_FREQ_CAL_STOP(__pAd)	\
do {	\
		if (__pAd->chipOps.AsicFreqCalStop != NULL)	\
			__pAd->chipOps.AsicFreqCalStop(__pAd);	\
} while (0)

#define RTMP_CHIP_IQ_CAL(__pAd, __pChannel)	\
do {	\
		if (__pAd->chipOps.ChipIQCalibration != NULL)	\
			 __pAd->chipOps.ChipIQCalibration(__pAd, __pChannel);	\
} while (0)

#define RTMP_CHIP_HIGH_POWER_TUNING(__pAd, __pRssi)	\
do {	\
		if (__pAd->chipOps.HighPowerTuning != NULL)	\
			__pAd->chipOps.HighPowerTuning(__pAd, __pRssi);	\
} while (0)

#define RTMP_CHIP_ANTENNA_INFO_DEFAULT_RESET(__pAd, __pAntenna)	\
do {	\
		if (__pAd->chipOps.AsicAntennaDefaultReset != NULL)	\
			__pAd->chipOps.AsicAntennaDefaultReset(__pAd, __pAntenna);	\
} while (0)

#define RTMP_NET_DEV_NICKNAME_INIT(__pAd)	\
do {	\
		if (__pAd->chipOps.NetDevNickNameInit != NULL)	\
			__pAd->chipOps.NetDevNickNameInit(__pAd);	\
} while (0)

#define RTMP_EEPROM_ASIC_INIT(__pAd)	\
do {	\
		if (__pAd->chipOps.NICInitAsicFromEEPROM != NULL)	\
			__pAd->chipOps.NICInitAsicFromEEPROM(__pAd);	\
} while (0)

#define RTMP_CHIP_SPECIFIC(__pAd, __FuncId, __pData, __Data)	\
do {	\
		if ((__FuncId >= 0) && (__FuncId < CHIP_SPEC_RESV_FUNC))	\
		{	\
			if (__pAd->chipOps.ChipSpecFunc[__FuncId] != NULL)	\
				__pAd->chipOps.ChipSpecFunc[__FuncId](__pAd, __pData, __Data);	\
		}	\
} while (0)

#define RTMP_CHIP_ASIC_RESET_BBP_AGENT(__pAd)	\
do {	\
		if (__pAd->chipOps.AsicResetBbpAgent != NULL)	\
			__pAd->chipOps.AsicResetBbpAgent(__pAd);	\
		else	\
		{	\
			BBP_CSR_CFG_STRUC	BbpCsr;	\
			DBGPRint(RT_DEBUG_INFO, ("Reset BBP Agent busy bit.!! \n"));	\
			RTMP_IO_READ32(__pAd, H2M_BBP_AGENT, &BbpCsr.word);	\
			BbpCsr.field.Busy = 0;	\
			RTMP_IO_WRITE32(__pAd, H2M_BBP_AGENT, BbpCsr.word);	\
		}	\
} while (0)

#define RTMP_CHIP_UPDATE_BEACON(__pAd, Offset, Value, Unit)	\
do {	\
		if (__pAd->chipOps.BeaconUpdate != NULL)	\
			__pAd->chipOps.BeaconUpdate(__pAd, Offset, Value, Unit);	\
} while (0)

#ifdef CARRIER_DETECTION_SUPPORT
#define	RTMP_CHIP_CARRIER_PROGRAM(__pAd, threshold)	\
do {	\
		if(__pAd->chipOps.ToneRadarProgram != NULL)	\
			__pAd->chipOps.ToneRadarProgram(__pAd, threshold);	\
} while (0)
#endif /* CARRIER_DETECTION_SUPPORT */

#define RTMP_CHIP_CCK_MRC_STATUS_CTRL(__pAd)	\
do {	\
		if(__pAd->chipOps.CckMrcStatusCtrl != NULL)	\
			__pAd->chipOps.CckMrcStatusCtrl(__pAd);	\
} while (0)

#define RTMP_CHIP_RADAR_GLRT_COMPENSATE(__pAd) \
do {	\
		if(__pAd->chipOps.RadarGLRTCompensate != NULL)	\
			__pAd->chipOps.RadarGLRTCompensate(__pAd);	\
} while (0)


#define CHIP_CALIBRATION(__pAd, __CalibrationID, __parameter) \
do {	\
	if(__pAd->chipOps.Calibration != NULL) \
		__pAd->chipOps.Calibration(__pAd, __CalibrationID, __parameter); \
} while (0)

#define RTMP_CHIP_CALIBRATION(__pAd, __CalibrationID, __parameter) \
do {	\
	if(__pAd->chipOps.Calibration != NULL) \
		__pAd->chipOps.Calibration(__pAd, __CalibrationID, __parameter); \
} while (0)

#define BURST_WRITE(_pAd, _Offset, _pData, _Cnt)	\
do {												\
		if (_pAd->chipOps.BurstWrite != NULL)		\
			_pAd->chipOps.BurstWrite(_pAd, _Offset, _pData, _Cnt);\
} while (0)

#define BURST_READ(_pAd, _Offset, _Cnt, _pData)	\
do {											\
		if (_pAd->chipOps.BurstRead != NULL)	\
			_pAd->chipOps.BurstRead(_pAd, _Offset, _Cnt, _pData);	\
} while (0)

#define RANDOM_READ(_pAd, _RegPair, _Num)	\
do {										\
		if (_pAd->chipOps.RandomRead != NULL)	\
			_pAd->chipOps.RandomRead(_pAd, _RegPair, _Num);	\
} while (0)

#define RF_RANDOM_READ(_pAd, _RegPair, _Num)	\
do {											\
		if (_pAd->chipOps.RFRandomRead != NULL)	\
			_pAd->chipOps.RFRandomRead(_pAd, _RegPair, _Num); \
} while (0)

#define READ_MODIFY_WRITE(_pAd, _RegPair, _Num)	\
do {	\
		if (_pAd->chipOps.ReadModifyWrite != NULL)	\
			_pAd->chipOps.ReadModifyWrite(_pAd, _RegPair, _Num);	\
} while (0)

#define RF_READ_MODIFY_WRITE(_pAd, _RegPair, _Num)	\
do {	\
		if (_pAd->chipOps.RFReadModifyWrite != NULL)	\
			_pAd->chipOps.RFReadModifyWrite(_pAd, _RegPair, _Num);	\
} while (0)

#define RANDOM_WRITE(_pAd, _RegPair, _Num)	\
do {	\
		if (_pAd->chipOps.RandomWrite != NULL)	\
			_pAd->chipOps.RandomWrite(_pAd, _RegPair, _Num);	\
} while (0)

#define RF_RANDOM_WRITE(_pAd, _RegPair, _Num)	\
do {	\
		if (_pAd->chipOps.RFRandomWrite != NULL)	\
			_pAd->chipOps.RFRandomWrite(_pAd, _RegPair, _Num);	\
} while (0)

#define RTMP_SECOND_CCA_DETECTION(__pAd)	\
do {	\
	if (__pAd->chipOps.SecondCCADetection != NULL)	\
	{	\
		__pAd->chipOps.SecondCCADetection(__pAd);	\
	}	\
} while (0)

#define DISABLE_TX_RX(_pAd, _Level)	\
do {	\
	if (_pAd->chipOps.DisableTxRx != NULL)	\
		_pAd->chipOps.DisableTxRx(_pAd, _Level);	\
} while (0)

#define ASIC_RADIO_ON(_pAd, _Stage)	\
do {	\
	if (_pAd->chipOps.AsicRadioOn != NULL)	\
		_pAd->chipOps.AsicRadioOn(_pAd, _Stage);	\
} while (0)

#define ASIC_RADIO_OFF(_pAd, _Stage)	\
do {	\
	if (_pAd->chipOps.AsicRadioOff != NULL)	\
		_pAd->chipOps.AsicRadioOff(_pAd, _Stage);	\
} while (0)

#define MCU_CTRL_INIT(_pAd)	\
do {	\
	if (_pAd->chipOps.MCUCtrlInit != NULL)	\
		_pAd->chipOps.MCUCtrlInit(_pAd);	\
} while (0)

#define MCU_CTRL_EXIT(_pAd)	\
do {	\
	if (_pAd->chipOps.MCUCtrlExit != NULL)	\
		_pAd->chipOps.MCUCtrlExit(_pAd);	\
} while (0)

#define USB_CFG_READ(_ad, _pvalue)	\
do {	\
	if (_ad->chipOps.usb_cfg_read != NULL)	\
		_ad->chipOps.usb_cfg_read(_ad, _pvalue);	\
} while (0)

#define USB_CFG_WRITE(_ad, _value)	\
do {	\
	if (_ad->chipOps.usb_cfg_write != NULL)	\
		_ad->chipOps.usb_cfg_write(_ad, _value);	\
} while (0)
		
int RtmpChipOpsHook(void*pCB);
void RtmpChipBcnInit(struct _RTMP_ADAPTER *pAd);
void RtmpChipBcnSpecInit(struct _RTMP_ADAPTER *pAd);
#ifdef RLT_MAC
void Rlt_bcn_buf_init(struct _RTMP_ADAPTER *pAd);
#endif /* RLT_MAC */

void RtmpChipWriteHighMemory(
struct _RTMP_ADAPTER *pAd,
unsigned short			Offset,
unsigned int		Value,
unsigned char			Unit);

void RtmpChipWriteMemory(
struct _RTMP_ADAPTER *pAd,
unsigned short			Offset,
unsigned int		Value,
unsigned char			Unit);

void RTMPReadChannelPwr(struct _RTMP_ADAPTER *pAd);
void RTMPReadTxPwrPerRate(struct _RTMP_ADAPTER *pAd);


void NetDevNickNameInit(struct _RTMP_ADAPTER *pAd);





/* global variable */
extern FREQUENCY_ITEM RtmpFreqItems3020[];
extern FREQUENCY_ITEM FreqItems3020_Xtal20M[];
extern unsigned char NUM_OF_3020_CHNL;
extern FREQUENCY_ITEM *FreqItems3020;
extern RTMP_RF_REGS RF2850RegTable[];
extern unsigned char NUM_OF_2850_CHNL;

unsigned char AsicWaitPDMAIdle(struct _RTMP_ADAPTER *pAd, int round, int wait_us);
int AsicSetPreTbttint(struct _RTMP_ADAPTER *pAd, unsigned char enable);
int AsicReadAggCnt(struct _RTMP_ADAPTER *pAd, unsigned long *aggCnt, int cnt_len);

void StopDmaTx(struct _RTMP_ADAPTER *pAd, unsigned char Level);
void StopDmaRx(struct _RTMP_ADAPTER *pAd, unsigned char Level);

#endif /* __RTMP_CHIP_H__ */
