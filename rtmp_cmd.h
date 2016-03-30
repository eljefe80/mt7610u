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


#ifndef __RTMP_CMD_H__
#define __RTMP_CMD_H__


typedef struct _CmdQElmt {
	unsigned int command;
	void*buffer;
	unsigned long bufferlength;
	unsigned char CmdFromNdis;
	unsigned char SetOperation;
	struct _CmdQElmt *next;
} CmdQElmt, *PCmdQElmt;

typedef struct _CmdQ {
	unsigned int size;
	CmdQElmt *head;
	CmdQElmt *tail;
	unsigned int CmdQState;
} CmdQ, *PCmdQ;

#define EnqueueCmd(cmdq, cmdqelmt)		\
{										\
	if (cmdq->size == 0)				\
		cmdq->head = cmdqelmt;			\
	else								\
		cmdq->tail->next = cmdqelmt;	\
	cmdq->tail = cmdqelmt;				\
	cmdqelmt->next = NULL;				\
	cmdq->size++;						\
}

#define NDIS_OID	unsigned int

/* OS_RTCMDUp is only used in UTIL/NETIF module */
#define OS_RTCMDUp						RtmpOsCmdUp



/* RALINK command status code */
#define RTMP_IO_EINVAL							30000
#define RTMP_IO_EOPNOTSUPP						30001
#define RTMP_IO_EFAULT							30002
#define RTMP_IO_ENETDOWN						30003
#define RTMP_IO_E2BIG							30004
#define RTMP_IO_ENOMEM							30005
#define RTMP_IO_EAGAIN							30006
#define RTMP_IO_ENOTCONN						30007

enum {
	SHOW_CONN_STATUS = 4,
	SHOW_DRVIER_VERION = 5,
	SHOW_BA_INFO = 6,
	SHOW_DESC_INFO = 7,
#ifdef RTMP_MAC_USB
	SHOW_RXBULK_INFO = 8,
	SHOW_TXBULK_INFO = 9,
#endif /* RTMP_MAC_USB */
	RAIO_OFF = 10,
	RAIO_ON = 11,
#ifdef QOS_DLS_SUPPORT
	SHOW_DLS_ENTRY_INFO = 20,
#endif /* QOS_DLS_SUPPORT */
	SHOW_CFG_VALUE = 21,
	SHOW_ADHOC_ENTRY_INFO = 22,
	SHOW_DEV_INFO = 26,
	SHOW_STA_INFO = 27,
};

#ifdef CONFIG_STA_SUPPORT

#ifdef WPA_SUPPLICANT_SUPPORT
#ifndef NATIVE_WPA_SUPPLICANT_SUPPORT
#define	RT_ASSOC_EVENT_FLAG                         0x0101
#define	RT_DISASSOC_EVENT_FLAG                      0x0102
#define	RT_REQIE_EVENT_FLAG                         0x0103
#define	RT_RESPIE_EVENT_FLAG                        0x0104
#define	RT_ASSOCINFO_EVENT_FLAG                     0x0105
#define RT_PMKIDCAND_FLAG                           0x0106
#define RT_intERFACE_DOWN                           0x0107
#define RT_intERFACE_UP                             0x0108
#endif /* NATIVE_WPA_SUPPLICANT_SUPPORT */
#endif /* WPA_SUPPLICANT_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

/* RALINK command handle ID */
/* ap commands */
typedef enum _CMD_RTPRIV_IOCTL_AP {

	/* general */
	CMD_RTPRIV_IOCTL_SET_WSCOOB = 0x0001,
	CMD_RTPRIV_IOCTL_GET_MAC_TABLE,
	CMD_RTPRIV_IOCTL_GSITESURVEY,
	CMD_RTPRIV_IOCTL_STATISTICS,
	CMD_RTPRIV_IOCTL_QUERY_BATABLE,
	CMD_RTPRIV_IOCTL_E2P,
	CMD_RTPRIV_IOCTL_BBP,
	CMD_RTPRIV_IOCTL_MAC,
	CMD_RTPRIV_IOCTL_RF,
	CMD_RT_PRIV_IOCTL,
	CMD_RTPRIV_IOCTL_SET,
	CMD_RTPRIV_IOCTL_SHOW,
	CMD_RTPRIV_IOCTL_GET_AR9_SHOW,
	CMD_RTPRIV_IOCTL_ATE,
	CMD_RTPRIV_IOCTL_CHID_2_FREQ,
	CMD_RTPRIV_IOCTL_FREQ_2_CHID,
	CMD_RTPRIV_IOCTL_GET_MAC_TABLE_STRUCT,

	/* mbss */
	CMD_RTPRIV_IOCTL_MBSS_BEACON_UPDATE,
	CMD_RTPRIV_IOCTL_MBSS_OPEN,
	CMD_RTPRIV_IOCTL_MBSS_CLOSE,
	CMD_RTPRIV_IOCTL_MBSS_INIT,
	CMD_RTPRIV_IOCTL_MBSS_REMOVE,

	/* wsc */
	CMD_RTPRIV_IOCTL_WSC_PROFILE,
	CMD_RTPRIV_IOCTL_WSC_INIT,

	/* apc */
	CMD_RTPRIV_IOCTL_APC_UP,
	CMD_RTPRIV_IOCTL_APC_DISCONNECT,
	CMD_RTPRIV_IOCTL_APC_INIT,
	CMD_RTPRIV_IOCTL_APC_OPEN,
	CMD_RTPRIV_IOCTL_APC_CLOSE,
	CMD_RTPRIV_IOCTL_APC_REMOVE,

	/* interface */
	CMD_RTPRIV_IOCTL_MAIN_OPEN,

	/* ioctl */
	CMD_RTPRIV_IOCTL_PREPARE,
	CMD_RTPRIV_IOCTL_AP_SIOCGIWAP,
	CMD_RTPRIV_IOCTL_AP_SIOCGIFHWADDR,
	CMD_RTPRIV_IOCTL_AP_SIOCGIWESSID,
	CMD_RTPRIV_IOCTL_AP_SIOCGIWRATEQ,
	CMD_RTPRIV_IOCTL_AP_SIOCSIWGENIE,

	/* can not exceed 0x5000 */
} CMD_RTPRIV_IOCTL_AP;

/* common commands */
typedef enum _CMD_RTPRIV_IOCTL_COMMON {

	/* general */
	CMD_RTPRIV_IOCTL_NETDEV_GET = 0x5000,
	CMD_RTPRIV_IOCTL_NETDEV_SET,
	CMD_RTPRIV_IOCTL_OPMODE_GET,
	CMD_RTPRIV_IOCTL_TASK_LIST_GET,
	CMD_RTPRIV_IOCTL_IRQ_INIT,
	CMD_RTPRIV_IOCTL_IRQ_RELEASE,
	CMD_RTPRIV_IOCTL_MSI_ENABLE,
	CMD_RTPRIV_IOCTL_NIC_NOT_EXIST,
	CMD_RTPRIV_IOCTL_MCU_SLEEP_CLEAR,
#ifdef CONFIG_APSTA_MIXED_SUPPORT
	CMD_RTPRIV_IOCTL_MAX_IN_BIT,
#endif /* CONFIG_APSTA_MIXED_SUPPORT */
//#ifdef CONFIG_STA_SUPPORT
//#ifdef CONFIG_PM
//#ifdef USB_SUPPORT_SELECTIVE_SUSPEND
	CMD_RTPRIV_IOCTL_USB_DEV_GET,
	CMD_RTPRIV_IOCTL_USB_intF_GET,
	CMD_RTPRIV_IOCTL_ADAPTER_SUSPEND_SET,
	CMD_RTPRIV_IOCTL_ADAPTER_SUSPEND_CLEAR,
	CMD_RTPRIV_IOCTL_ADAPTER_SEND_DISSASSOCIATE,
	CMD_RTPRIV_IOCTL_ADAPTER_SUSPEND_TEST,
	CMD_RTPRIV_IOCTL_ADAPTER_IDLE_RADIO_OFF_TEST,
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_USB_ASICRADIO_OFF,
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_USB_ASICRADIO_ON,
#ifdef WOW_SUPPORT
#ifdef RTMP_MAC_USB
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_USB_WOW_STATUS,
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_USB_WOW_ENABLE,
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_USB_WOW_DISABLE,
#endif /* RTMP_MAC_USB */
#endif /* WOW_SUPPORT */
//#endif /* USB_SUPPORT_SELECTIVE_SUSPEND */
//#endif /* CONFIG_PM */
	CMD_RTPRIV_IOCTL_AP_BSSID_GET,
//#endif /* CONFIG_STA_SUPPORT */
	CMD_RTPRIV_IOCTL_SANITY_CHECK,
	CMD_RTPRIV_IOCTL_SANITY_CHECK_ON_SET_CMD,	
#ifdef EXT_BUILD_CHANNEL_LIST
	CMD_RTPRIV_SET_PRECONFIG_VALUE,
#endif /* EXT_BUILD_CHANNEL_LIST */


	/* mesh */
	CMD_RTPRIV_IOCTL_MESH_INIT,
	CMD_RTPRIV_IOCTL_MESH_REMOVE,
	CMD_RTPRIV_IOCTL_MESH_OPEN_PRE,
	CMD_RTPRIV_IOCTL_MESH_OPEN_POST,
	CMD_RTPRIV_IOCTL_MESH_IS_VALID,
	CMD_RTPRIV_IOCTL_MESH_CLOSE,

	/* p2p */
	CMD_RTPRIV_IOCTL_P2P_INIT,
	CMD_RTPRIV_IOCTL_P2P_REMOVE,
	CMD_RTPRIV_IOCTL_P2P_OPEN_PRE,
	CMD_RTPRIV_IOCTL_P2P_OPEN_POST,
	CMD_RTPRIV_IOCTL_P2P_IS_VALID,
	CMD_RTPRIV_IOCTL_P2P_CLOSE,

	/* usb */
	CMD_RTPRIV_IOCTL_USB_MORE_FLAG_SET,
	CMD_RTPRIV_IOCTL_USB_CONFIG_INIT,
	CMD_RTPRIV_IOCTL_USB_SUSPEND,
	CMD_RTPRIV_IOCTL_USB_RESUME,

	/* pci */
	CMD_RTPRIV_IOCTL_PCI_SUSPEND,
	CMD_RTPRIV_IOCTL_PCI_RESUME,
	CMD_RTPRIV_IOCTL_PCI_CSR_SET,
	CMD_RTPRIV_IOCTL_PCIE_INIT,

	/* cfg80211 */
	CMD_RTPRIV_IOCTL_CFG80211_CFG_START,

	/* inf ppa */
	CMD_RTPRIV_IOCTL_INF_PPA_INIT,
	CMD_RTPRIV_IOCTL_INF_PPA_EXIT,

	/* wireless */
	CMD_RTPRIV_IOCTL_BEACON_UPDATE,
	CMD_RTPRIV_IOCTL_RXPATH_GET,
	CMD_RTPRIV_IOCTL_CHAN_LIST_NUM_GET,
	CMD_RTPRIV_IOCTL_CHAN_LIST_GET,
	CMD_RTPRIV_IOCTL_FREQ_LIST_GET,

	/* interface */
	CMD_RTPRIV_IOCTL_VIRTUAL_INF_UP,
	CMD_RTPRIV_IOCTL_VIRTUAL_INF_DOWN,
	CMD_RTPRIV_IOCTL_VIRTUAL_INF_GET,
	CMD_RTPRIV_IOCTL_INF_TYPE_GET,
	CMD_RTPRIV_IOCTL_INF_STATS_GET,
	CMD_RTPRIV_IOCTL_INF_IW_STATUS_GET,
	CMD_RTPRIV_IOCTL_INF_MAIN_CREATE,
	CMD_RTPRIV_IOCTL_INF_MAIN_ID_GET,
	CMD_RTPRIV_IOCTL_INF_MAIN_CHECK,
	CMD_RTPRIV_IOCTL_INF_P2P_CHECK,

	/* ioctl */
	CMD_RTPRIV_IOCTL_SIOCGIWFREQ,
	CMD_RTPRIV_IOCTL_SIOCGIWNAME,

	/* wds */
	CMD_RTPRIV_IOCTL_WDS_INIT,
	CMD_RTPRIV_IOCTL_WDS_REMOVE,
	CMD_RTPRIV_IOCTL_WDS_STATS_GET,

	CMD_RTPRIV_IOCTL_MAC_ADDR_GET,

#ifdef RT_CFG80211_SUPPORT
	/* cfg802.11 */
	/* Note: All cfg commands must be continue. */
	CMD_RTPRIV_IOCTL_80211_START,
	CMD_RTPRIV_IOCTL_80211_CB_GET,
	CMD_RTPRIV_IOCTL_80211_CB_SET,
	CMD_RTPRIV_IOCTL_80211_CHAN_SET,
	CMD_RTPRIV_IOCTL_80211_VIF_CHG,
	CMD_RTPRIV_IOCTL_80211_SCAN,
	CMD_RTPRIV_IOCTL_80211_IBSS_JOIN,
	CMD_RTPRIV_IOCTL_80211_STA_LEAVE,
	CMD_RTPRIV_IOCTL_80211_STA_GET,
	CMD_RTPRIV_IOCTL_80211_KEY_ADD,
	CMD_RTPRIV_IOCTL_80211_KEY_DEFAULT_SET,
	CMD_RTPRIV_IOCTL_80211_CONNECT_TO,
	CMD_RTPRIV_IOCTL_80211_RFKILL,
	CMD_RTPRIV_IOCTL_80211_REG_NOTIFY_TO,
	CMD_RTPRIV_IOCTL_80211_UNREGISTER,
	CMD_RTPRIV_IOCTL_80211_BANDINFO_GET,
	CMD_RTPRIV_IOCTL_80211_SURVEY_GET,
	CMD_RTPRIV_IOCTL_80211_EXTRA_IES_SET,
	CMD_RTPRIV_IOCTL_80211_REMAIN_ON_CHAN_SET,
	CMD_RTPRIV_IOCTL_80211_MGMT_FRAME_REG,
	CMD_RTPRIV_IOCTL_80211_CHANNEL_LOCK,
	CMD_RTPRIV_IOCTL_80211_MGMT_FRAME_SEND,
	CMD_RTPRIV_IOCTL_80211_REMAIN_ON_CHAN_DUR_TIMER_INIT,
	CMD_RTPRIV_IOCTL_80211_CHANNEL_LIST_SET,
	CMD_RTPRIV_IOCTL_80211_ACTION_FRAME_REG,
	CMD_RTPRIV_IOCTL_80211_BEACON_ADD,
	CMD_RTPRIV_IOCTL_80211_BEACON_SET,
	CMD_RTPRIV_IOCTL_80211_BEACON_DEL,
	CMD_RTPRIV_IOCTL_80211_AP_KEY_ADD,
	CMD_RTPRIV_IOCTL_80211_CHANGE_BSS_PARM,
	CMD_RTPRIV_IOCTL_80211_AP_KEY_DEL,
	CMD_RTPRIV_IOCTL_80211_AP_PROBE_RSP,
	CMD_RTPRIV_IOCTL_80211_PORT_SECURED,
	CMD_RTPRIV_IOCTL_80211_AP_STA_DEL,
	CMD_RTPRIV_IOCTL_80211_CANCEL_REMAIN_ON_CHAN_SET,
	CMD_RTPRIV_IOCTL_80211_BITRATE_SET,
#ifdef RT_P2P_SPECIFIC_WIRELESS_EVENT
	CMD_RTPRIV_IOCTL_80211_SEND_WIRELESS_EVENT,
#endif /* RT_P2P_SPECIFIC_WIRELESS_EVENT */
	CMD_RTPRIV_IOCTL_80211_END,
#endif /* RT_CFG80211_SUPPORT */

	CMD_RTPRIV_IOCTL_ADAPTER_CSO_SUPPORT_TEST,
	CMD_RTPRIV_IOCTL_ADAPTER_TSO_SUPPORT_TEST,

	/* can not exceed 0xa000 */
	CMD_RTPRIV_IOCTL_80211_COM_LATEST_ONE,
} CMD_RTPRIV_IOCTL_COMMON;

#ifdef RT_CFG80211_SUPPORT
typedef struct __CMD_RTPRIV_IOCTL_80211_VIF_SET {
	int  vifType;
	char vifName[IFNAMSIZ];
	int  vifNameLen;
} CMD_RTPRIV_IOCTL_80211_VIF_SET;

typedef struct __CMD_RTPRIV_IOCTL_80211_BSS_PARM {
	int   use_cts_prot;
	int   use_short_preamble;
	int   use_short_slot_time;
	unsigned char *basic_rates;
	unsigned char basic_rates_len;
	int   ap_isolate;
	int   ht_opmode;	

} CMD_RTPRIV_IOCTL_80211_BSS_PARM;

typedef struct __CMD_RTPRIV_IOCTL_80211_BEACON {
        int interval;
        int dtim_period;
        unsigned char *beacon_head;
		unsigned char *beacon_tail;
        unsigned int beacon_head_len; /* Before TIM IE */
		unsigned int beacon_tail_len; /* After TIM IE */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
	unsigned char *beacon_ies;
	unsigned int beacon_ies_len;
	unsigned char *proberesp_ies;
	unsigned int proberesp_ies_len;
	unsigned char *assocresp_ies;
	unsigned int assocresp_ies_len;
	unsigned char *probe_resp;
	unsigned int probe_resp_len;
	unsigned long ssid_len;
	unsigned char hidden_ssid;
	struct cfg80211_crypto_settings crypto;
	unsigned char privacy;
	unsigned char auth_type;
	int inactivity_timeout;
#endif
} CMD_RTPRIV_IOCTL_80211_BEACON;

typedef struct __CMD_RTPRIV_IOCTL_80211_CHAN {

	unsigned char ChanId;

#define RT_CMD_80211_IFTYPE_STATION		0x00
#define RT_CMD_80211_IFTYPE_ADHOC		0x01
#define RT_CMD_80211_IFTYPE_MONITOR		0x02
	unsigned char IfType;

#define RT_CMD_80211_CHANTYPE_NOHT		0x00
#define RT_CMD_80211_CHANTYPE_HT20		0x01
#define RT_CMD_80211_CHANTYPE_HT40MINUS	0X02
#define RT_CMD_80211_CHANTYPE_HT40PLUS	0X03
	unsigned char ChanType;

	unsigned int MonFilterFlag;

//#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0))	
//	PWIRELESS_DEV pWdev;	
//#endif /* LINUX_VERSION_CODE: 3.6.0 */
} CMD_RTPRIV_IOCTL_80211_CHAN;

#define RT_CMD_80211_FILTER_FCSFAIL		0x01
#define RT_CMD_80211_FILTER_PLCPFAIL	0x02
#define RT_CMD_80211_FILTER_CONTROL		0x04
#define RT_CMD_80211_FILTER_OTHER_BSS	0x08

typedef struct __CMD_RTPRIV_IOCTL_80211_IBSS {

	unsigned int Beaconinterval;
	unsigned char *pSsid;
} CMD_RTPRIV_IOCTL_80211_IBSS;

typedef struct __CMD_RTPRIV_IOCTL_80211_STA {

	unsigned char MAC[6];
	unsigned long DataRate;

#define RT_CMD_80211_TXRATE_LEGACY		0x01
#define RT_CMD_80211_TXRATE_BW_40		0x02
#define RT_CMD_80211_TXRATE_SHORT_GI	0x04
	unsigned int TxRateFlags;
	
	unsigned int TxRateMCS;
	int Signal;
	unsigned int TxPacketCnt;
	unsigned int InactiveTime;
} CMD_RTPRIV_IOCTL_80211_STA;

/*typedef struct __CMD_RTPRIV_IOCTL_80211_KEY {

#define RT_CMD_80211_KEY_WEP			0x00
#define RT_CMD_80211_KEY_WPA			0x01
	unsigned char KeyType;
	unsigned char KeyBuf[50];
	unsigned char KeyId;
} CMD_RTPRIV_IOCTL_80211_KEY;*/

#define RT_CMD_80211_KEY_WEP40			0x00
#define RT_CMD_80211_KEY_WEP104			0x01
#define RT_CMD_80211_KEY_WPA			0x02
#ifdef DOT11W_PMF_SUPPORT
#define RT_CMD_80211_KEY_AES_CMAC	0x03
#endif /* DOT11W_PMF_SUPPORT */

typedef struct __CMD_RTPRIV_IOCTL_80211_KEY {
	unsigned char KeyType;
	unsigned char KeyBuf[50];
	unsigned char KeyId;
	unsigned char bPairwise;
	unsigned char KeyLen;
	unsigned int cipher;
	unsigned char MAC[ETH_LENGTH_OF_ADDRESS];
} CMD_RTPRIV_IOCTL_80211_KEY;


#define RT_CMD_80211_CONN_ENCRYPT_NONE	0x01
#define RT_CMD_80211_CONN_ENCRYPT_WEP	0x02
#define RT_CMD_80211_CONN_ENCRYPT_TKIP	0x04
#define RT_CMD_80211_CONN_ENCRYPT_CCMP	0x08

typedef struct __CMD_RTPRIV_IOCTL_80211_CONNECT {

	unsigned char WpaVer;
	unsigned char FlgIs8021x;
	unsigned char AuthType;
	//unsigned char FlgIsAuthOpen;

	unsigned char PairwiseEncrypType;
	unsigned char GroupwiseEncrypType;

	unsigned char *pKey;
	unsigned int KeyLen;
	unsigned char KeyIdx;

	unsigned char *pSsid;
	unsigned int SsidLen;




	unsigned char *pBssid;  
	
	unsigned char bWpsConnection;
#ifdef DOT11W_PMF_SUPPORT
	unsigned char mfp;
#endif /* DOT11W_PMF_SUPPORT */

} CMD_RTPRIV_IOCTL_80211_CONNECT;

typedef struct __CMD_RTPRIV_IOCTL_80211_REG_NOTIFY {

	unsigned char Alpha2[2];
	void*pWiphy;
} CMD_RTPRIV_IOCTL_80211_REG_NOTIFY;

typedef struct __CMD_RTPRIV_IOCTL_80211_SURVEY {

	void*pCfg80211;
/*	unsigned int64 ChannelTime; */ /* idle + busy, not support */
	unsigned int64 ChannelTimeBusy;
	unsigned int64 ChannelTimeExtBusy;
} CMD_RTPRIV_IOCTL_80211_SURVEY;

#endif /* RT_CFG80211_SUPPORT */

/* station commands */
#ifdef CONFIG_STA_SUPPORT
typedef enum _CMD_RTPRIV_IOCTL_STATION {

	/* general */
	CMD_RTPRIV_IOCTL_PARAM_SET = 0xa000,
	CMD_RTPRIV_IOCTL_SITESURVEY_GET,
	CMD_RTPRIV_IOCTL_SITESURVEY,
	CMD_RTPRIV_IOCTL_ORI_DEV_TYPE_SET,
	CMD_RTPRIV_IOCTL_STA_SCAN_SANITY_CHECK,
	CMD_RTPRIV_IOCTL_STA_SCAN_END,

	/* wireless */
	CMD_RTPRIV_IOCTL_BSS_LIST_GET,

	/* standard ioctl */
	CMD_RTPRIV_IOCTL_STA_SIOCSIWFREQ,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWFREQ,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWMODE,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWMODE,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWAP,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWAP,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWSCAN,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWSCAN,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWESSID,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWESSID,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWNICKN,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWNICKN,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWRTS,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWRTS,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWFRAG,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWFRAG,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWENCODE,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWENCODE,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWMLME,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWAUTH,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWAUTH,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWENCODEEXT,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWENCODEEXT,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWGENIE,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWGENIE,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWPMKSA,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWRATE,
	CMD_RTPRIV_IOCTL_STA_SIOCGIWRATE,
	CMD_RTPRIV_IOCTL_STA_SIOCGIFHWADDR,
	CMD_RTPRIV_IOCTL_STA_SIOCSIWPRIVRSSI,

	CMD_RTPRIV_IOCTL_STA_IW_SET_WSC_U32_ITEM,
	CMD_RTPRIV_IOCTL_STA_IW_SET_WSC_STR_ITEM,
	CMD_RTPRIV_IOCTL_STA_IW_GET_STATISTICS,
} CMD_RTPRIV_IOCTL_STATION;

#define RT_CMD_MODE_ADHOC								0x01
#define RT_CMD_MODE_INFRA								0x02
#define RT_CMD_MODE_MONITOR								0x03
#endif /* CONFIG_STA_SUPPORT */

/* when adding any new type, please also add codes in LINUX_WEVENT_TRANSLATE */
#define RT_WLAN_EVENT_CUSTOM							0x01
#define RT_WLAN_EVENT_CGIWAP							0x02
#define RT_WLAN_EVENT_ASSOC_REQ_IE						0x03
#define RT_WLAN_EVENT_SCAN								0x04
#define RT_WLAN_EVENT_EXPIRED							0x05
#define RT_WLAN_EVENT_SHOWPIN							0x06
#define RT_WLAN_EVENT_PIN							0x07

typedef struct __RT_CMD_RATE_SET {
unsigned intRate;
unsigned intFixed;
} RT_CMD_RATE_SET;

typedef struct __RT_CMD_PARAM_SET {
char*  pThischar;
char*  pValue;
} RT_CMD_PARAM_SET;

typedef struct __RT_CMD_SHARED_KEY_ADD {
unsigned char KeyIdx;
unsigned char FlgHaveGTK;
} RT_CMD_SHARED_KEY_ADD;

typedef struct __RT_CMD_MBSS_KICK{
int BssId;
unsigned short Reason;
} RT_CMD_MBSS_KICKOUT;

typedef struct __RT_CMD_USB_MORE_FLAG_CONFIG {
unsigned intVendorID;
unsigned intProductID;
} RT_CMD_USB_MORE_FLAG_CONFIG;

typedef struct __RT_CMD_USB_DEV_CONFIG {
unsigned int NumberOfPipes;
unsigned char BulkInEpAddr[2];
unsigned short BulkInMaxPacketSize;
unsigned char BulkOutEpAddr[6];
unsigned short BulkOutMaxPacketSize;
void*pConfig;
} RT_CMD_USB_DEV_CONFIG;

typedef struct __RT_CMD_CFG80211_CONFIG {
void*pCfgDev;
void(
	*CFG80211_Register) (
void* pAd,
void* pDev,
void* pNetDev);
} RT_CMD_CFG80211_CONFIG;

typedef struct __RT_CMD_WAIT_QUEUE_LIST {
	RTMP_OS_TASK *pMlmeTask;
	RTMP_OS_TASK *pTimerTask;
	RTMP_OS_TASK *pCmdQTask;
	RTMP_OS_TASK *pWscTask;
} RT_CMD_WAIT_QUEUE_LIST;

typedef struct __RT_CMD_INF_UP_DOWN {

int (*rt28xx_open)(void*net_dev);
int (*rt28xx_close)(void*net_dev);
} RT_CMD_INF_UP_DOWN;

typedef struct __RT_CMD_STATS {
void*pNetDev;
	void*pStats;	/* point to pAd->stats */

	unsigned long rx_packets;	/* total packets received       */
	unsigned long tx_packets;	/* total packets transmitted */
	unsigned long rx_bytes;	/* total bytes received         */
	unsigned long tx_bytes;	/* total bytes transmitted      */
	unsigned long rx_errors;	/* bad packets received         */
	unsigned long tx_errors;	/* packet transmit problems     */
	unsigned long multicast;	/* multicast packets received */
	unsigned long collisions;

	unsigned long rx_over_errors;	/* receiver ring buff overflow  */
	unsigned long rx_crc_errors;	/* recved pkt with crc error    */
	unsigned long rx_frame_errors;	/* recv'd frame alignment error */
	unsigned long rx_fifo_errors;	/* recv'r fifo overrun                  */
} RT_CMD_STATS;

typedef struct __RT_CMD_IW_STATS {

	unsigned long priv_flags;
	unsigned char *dev_addr;

	void*pStats;		/* point to pAd->iw_stats */

	unsigned char qual;
	unsigned char level;
	unsigned char noise;
	unsigned char updated;
} RT_CMD_IW_STATS;

typedef struct __RT_CMD_PCIE_INIT {

void*pPciDev;
unsigned intConfigDeviceID;
unsigned intConfigSubsystemVendorID;
unsigned intConfigSubsystemID;
} RT_CMD_PCIE_INIT;

typedef struct __RT_CMD_AP_IOCTL_CONFIG {
void*net_dev;
unsigned long priv_flags;
char *pCmdData;
int CmdId_RTPRIV_IOCTL_SET;
char *name;
int apidx;

	int Status;
} RT_CMD_AP_IOCTL_CONFIG;

typedef struct __RT_CMD_AP_IOCTL_SSID {
unsigned long priv_flags;
int apidx;

	char *pSsidStr;
	int length;
} RT_CMD_AP_IOCTL_SSID;

typedef struct __RT_CMD_IOCTL_RATE {
unsigned long priv_flags;
	unsigned int BitRate;
} RT_CMD_IOCTL_RATE;

#define RTMP_CMD_STA_MODE_AUTO			0x00
#define RTMP_CMD_STA_MODE_ADHOC			0x01
#define RTMP_CMD_STA_MODE_INFRA			0x02
#define RTMP_CMD_STA_MODE_MONITOR		0x03

typedef struct __RT_CMD_STA_IOCTL_FREQ {
int m;		/* Mantissa */
short e;		/* Exponent */
} RT_CMD_STA_IOCTL_FREQ;

typedef struct __RT_CMD_STA_IOCTL_BSS {
	unsigned char Bssid[6];
	unsigned char ChannelQuality;
	char Rssi;
	char Noise;
} RT_CMD_STA_IOCTL_BSS;

typedef struct __RT_CMD_STA_IOCTL_BSS_LIST {
unsigned intMaxNum;
	unsigned int BssNum;
	RT_CMD_STA_IOCTL_BSS *pList;
} RT_CMD_STA_IOCTL_BSS_LIST;

typedef struct __RT_CMD_STA_IOCTL_SCAN {
unsigned char FlgScanThisSsid;
unsigned intSsidLen;
char *pSsid;
	int Status;
} RT_CMD_STA_IOCTL_SCAN;

typedef struct __RT_CMD_STA_IOCTL_BSS_TABLE {
	unsigned char Bssid[6];
	unsigned char Channel;
	unsigned char BssType;
	unsigned char HtCapabilityLen;

	unsigned char SupRate[12];
	unsigned char SupRateLen;
	unsigned char ExtRate[12];
	unsigned char ExtRateLen;

	unsigned char SsidLen;
	char Ssid[32];

	unsigned short CapabilityInfo;
	unsigned char ChannelWidth, ShortGIfor40, ShortGIfor20, MCSSet;

	unsigned short WpaIeLen;
	unsigned char *pWpaIe;

	unsigned short RsnIeLen;
	unsigned char *pRsnIe;

	unsigned short WpsIeLen;
	unsigned char *pWpsIe;

	unsigned char FlgIsPrivacyOn;

	RT_CMD_STA_IOCTL_BSS Signal;
} RT_CMD_STA_IOCTL_BSS_TABLE;

typedef struct __RT_CMD_STA_IOCTL_SCAN_TABLE {
unsigned long priv_flags;
	unsigned int BssNr;
	RT_CMD_STA_IOCTL_BSS_TABLE *pBssTable;	/* must be freed by caller */
	unsigned char MainSharedKey[4][16];
} RT_CMD_STA_IOCTL_SCAN_TABLE;

typedef struct __RT_CMD_STA_IOCTL_SSID {
unsigned char FlgAnySsid;
	unsigned int SsidLen;
	char *pSsid;
	int Status;
} RT_CMD_STA_IOCTL_SSID;

typedef struct __RT_CMD_STA_IOCTL_NICK_NAME {
	unsigned int NameLen;
	char *pName;
} RT_CMD_STA_IOCTL_NICK_NAME;

typedef struct __RT_CMD_STA_IOCTL_SECURITY {
	char *pData;
	unsigned short length;
int KeyIdx;
int MaxKeyLen;

#define RT_CMD_STA_IOCTL_SECURITY_ALG_NONE		0x01
#define RT_CMD_STA_IOCTL_SECURITY_ALG_WEP		0x02
#define RT_CMD_STA_IOCTL_SECURITY_ALG_TKIP		0x03
#define RT_CMD_STA_IOCTL_SECURITY_ALG_CCMP		0x04
unsigned intAlg;

#define RT_CMD_STA_IOCTL_SECURTIY_EXT_SET_TX_KEY	0x01
#define RT_CMD_STA_IOCTL_SECURTIY_EXT_GROUP_KEY		0x02
unsigned short ext_flags;

#define RT_CMD_STA_IOCTL_SECURITY_DISABLED		0x01
#define RT_CMD_STA_IOCTL_SECURITY_ENABLED		0x02
#define RT_CMD_STA_IOCTL_SECURITY_RESTRICTED	0x04
#define RT_CMD_STA_IOCTL_SECURITY_OPEN			0x08
#define RT_CMD_STA_IOCTL_SECURITY_NOKEY			0x10
#define RT_CMD_STA_IOCTL_SECURITY_MODE			0x20
	unsigned short flags;

	int Status;
} RT_CMD_STA_IOCTL_SECURITY;

typedef struct __RT_CMD_STA_IOCTL_WSC_U32_ITEM {
unsigned int*pUWrq;
	int Status;
} RT_CMD_STA_IOCTL_WSC_U32_ITEM;

typedef struct __RT_CMD_STA_IOCTL_WSC_STR_ITEM {
unsigned intSubcmd;
char *pData;
unsigned intlength;

	int Status;
} RT_CMD_STA_IOCTL_WSC_STR_ITEM;

typedef struct __RT_CMD_STA_IOCTL_SHOW {
char *pData;
unsigned intMaxSize;
unsigned intInfType;
} RT_CMD_STA_IOCTL_SHOW;

#define RT_CMD_STA_IOCTL_IW_MLME_DEAUTH		0x01
#define RT_CMD_STA_IOCTL_IW_MLME_DISASSOC	0x02

typedef struct __RT_CMD_STA_IOCTL_SECURITY_ADV {

#define RT_CMD_STA_IOCTL_WPA_VERSION					0x10
#define RT_CMD_STA_IOCTL_WPA_VERSION1				0x11
#define RT_CMD_STA_IOCTL_WPA_VERSION2				0x12

#define RT_CMD_STA_IOCTL_WPA_PAIRWISE					0x20
#define RT_CMD_STA_IOCTL_WPA_PAIRWISE_NONE			0x21
#define RT_CMD_STA_IOCTL_WPA_PAIRWISE_WEP40			0x22
#define RT_CMD_STA_IOCTL_WPA_PAIRWISE_WEP104		0x23
#define RT_CMD_STA_IOCTL_WPA_PAIRWISE_TKIP			0x24
#define RT_CMD_STA_IOCTL_WPA_PAIRWISE_CCMP			0x25

#define RT_CMD_STA_IOCTL_WPA_GROUP						0x30
#define RT_CMD_STA_IOCTL_WPA_GROUP_NONE				0x31
#define RT_CMD_STA_IOCTL_WPA_GROUP_WEP40			0x32
#define RT_CMD_STA_IOCTL_WPA_GROUP_WEP104			0x33
#define RT_CMD_STA_IOCTL_WPA_GROUP_TKIP				0x34
#define RT_CMD_STA_IOCTL_WPA_GROUP_CCMP				0x35

#define RT_CMD_STA_IOCTL_WPA_KEY_MGMT					0x40
#define RT_CMD_STA_IOCTL_WPA_KEY_MGMT_1X			0x41
#define RT_CMD_STA_IOCTL_WPA_KEY_MGMT_WPS			0x42

#define RT_CMD_STA_IOCTL_WPA_AUTH_RX_UNENCRYPTED_EAPOL	0x50
#define RT_CMD_STA_IOCTL_WPA_AUTH_PRIVACY_INVOKED		0x60
#define RT_CMD_STA_IOCTL_WPA_AUTH_DROP_UNENCRYPTED		0x70

#define RT_CMD_STA_IOCTL_WPA_AUTH_80211_AUTH_ALG		0x80
#define RT_CMD_STA_IOCTL_WPA_AUTH_80211_AUTH_ALG_SHARED		0x81
#define RT_CMD_STA_IOCTL_WPA_AUTH_80211_AUTH_ALG_OPEN		0x82
#define RT_CMD_STA_IOCTL_WPA_AUTH_80211_AUTH_ALG_LEAP		0x83

#define RT_CMD_STA_IOCTL_WPA_AUTH_WPA_ENABLED			0x90
unsigned intflags;
unsigned intvalue;
} RT_CMD_STA_IOCTL_SECURITY_ADV;

typedef struct __RT_CMD_STA_IOCTL_RSN_IE {
	unsigned int length;
	unsigned char *pRsnIe;
} RT_CMD_STA_IOCTL_RSN_IE;

typedef struct __RT_CMD_STA_IOCTL_PMA_SA {
#define RT_CMD_STA_IOCTL_PMA_SA_FLUSH					0x01
#define RT_CMD_STA_IOCTL_PMA_SA_REMOVE					0x02
#define RT_CMD_STA_IOCTL_PMA_SA_ADD						0x03
unsigned intCmd;
unsigned char *pBssid;
unsigned char *pPmkid;
} RT_CMD_STA_IOCTL_PMA_SA;

#endif /* __RTMP_CMD_H__ */
