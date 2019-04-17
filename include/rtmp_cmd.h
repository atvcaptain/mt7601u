#ifndef __RTMP_CMD_H__
#define __RTMP_CMD_H__

#include "rtmp_type.h"

typedef struct _CmdQElmt {
	UINT command;
	PVOID buffer;
	ULONG bufferlength;
	BOOLEAN CmdFromNdis;
	BOOLEAN SetOperation;
	struct _CmdQElmt *next;
} CmdQElmt, *PCmdQElmt;

typedef struct _CmdQ {
	UINT size;
	CmdQElmt *head;
	CmdQElmt *tail;
	UINT32 CmdQState;
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

#define NDIS_OID	UINT

/* OS_RTCMDUp is only used in UTIL/NETIF module */
#define OS_RTCMDUp						RtmpOsCmdUp

#if 0 /* os abl move */
#ifdef KTHREAD_SUPPORT
#define OS_RTCMDUp(_cmdQTask) \
	do{	\
		OS_TASK	*_pTask = RTMP_OS_TASK_GET((_cmdQTask));	\
		{ \
			_pTask->kthread_running = TRUE; \
	        wake_up(&_pTask->kthread_q); \
		} \
	}while(0)
#else
#define OS_RTCMDUp(_cmdQTask)	                \
	do{									    \
		OS_TASK	*_pTask = RTMP_OS_TASK_GET((_cmdQTask));	\
		CHECK_PID_LEGALITY(_pTask->taskPID)	    \
		{\
			RTMP_SEM_EVENT_UP(&(_pTask->taskSema)); \
		}\
	}while(0)
#endif
#endif

#if defined(RTMP_MAC_PCI) || defined(RTMP_RBUS_SUPPORT)
#define CMDTHREAD_CHAN_RESCAN					0x0D730101
#define CMDTHREAD_REG_HINT						0x0D730102
#define CMDTHREAD_REG_HINT_11D					0x0D730103
#define CMDTHREAD_SCAN_END						0x0D730104
#define CMDTHREAD_CONNECT_RESULT_INFORM			0x0D730105
#define CMDTHREAD_PS_CLEAR         				0x0D730106
#define CMDTHREAD_PS_RETRIEVE_START       0x0D730107
#define CMDTHREAD_APCLI_PBC_TIMEOUT       0x0D730108
#define HWCMD_ID_BMC_CNT_UPDATE                     0x0D73012C
#define CMDTHREAD_PERODIC_CR_ACCESS_ASIC_UPDATE_PROTECT			0x0D73012D
#define CMDTHREAD_PERODIC_CR_ACCESS_MLME_DYNAMIC_TX_RATE_SWITCHING	0x0D73012E
#define CMDTHREAD_PERODIC_CR_ACCESS_NIC_UPDATE_RAW_COUNTERS	0x0D73012F
#define CMDTHREAD_PERODIC_CR_ACCESS_WTBL_RATE_TABLE_UPDATE		0x0D730130
#define CMDTHREAD_FORCE_WAKE_UP									0x0D730131
#define CMDTHREAD_FORCE_SLEEP_AUTO_WAKEUP						0x0D730132
#define CMDTHREAD_MLME_PERIOIDC_EXEC							0x0D730133

#endif /* RTMP_MAC_PCI || RTMP_RBUS_SUPPORT */

#define CMDTHREAD_RESPONSE_EVENT_CALLBACK		0x0D730123

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
#ifdef MAT_SUPPORT
	SHOW_IPV4_MAT_INFO = 1,
	SHOW_IPV6_MAT_INFO = 2,
	SHOW_ETH_CLONE_MAC = 3,
#endif /* MAT_SUPPORT */
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
#ifdef MESH_SUPPORT
	SHOW_MESH_INFO = 12,
	SHOW_NEIGHINFO_INFO = 13,
	SHOW_MESH_ROUTE_INFO = 14,
	SHOW_MESH_ENTRY_INFO = 15,
	SHOW_MULPATH_INFO = 16,
	SHOW_MCAST_AGEOUT_INFO = 17,
	SHOW_MESH_PKTSIG_INFO = 18,
	SHOW_MESH_PROXY_INFO = 19,
#endif /* MESH_SUPPORT */
#ifdef QOS_DLS_SUPPORT
	SHOW_DLS_ENTRY_INFO = 20,
#endif /* QOS_DLS_SUPPORT */
	SHOW_CFG_VALUE = 21,
	SHOW_ADHOC_ENTRY_INFO = 22,
#ifdef WMM_ACM_SUPPORT
	SHOW_ACM_BADNWIDTH = 23,
	SHOW_ACM_STREAM = 24,
#endif /* WMM_ACM_SUPPORT */
#if defined(DOT11Z_TDLS_SUPPORT) || defined(CFG_TDLS_SUPPORT)
	SHOW_TDLS_ENTRY_INFO = 25,
#endif /* DOT11Z_TDLS_SUPPORT */
	SHOW_DEV_INFO = 26,
	SHOW_STA_INFO = 27,
	SHOW_TR_INFO = 28,
	SHOW_SYS_INFO = 29,
	SHOW_PWR_INFO = 30,
	SHOW_DIAGNOSE_INFO = 31,
	SHOW_WTBL_INFO = 32,
	SHOW_MIB_INFO = 33,
	SHOW_PS_INFO = 34,
	SHOW_TEMP_INFO = 35,
	
};

#ifdef CONFIG_STA_SUPPORT
#ifdef WSC_STA_SUPPORT
enum {
	WSC_CREDENTIAL_COUNT = 1,
	WSC_CREDENTIAL_SSID = 2,
	WSC_CREDENTIAL_AUTH_MODE = 3,
	WSC_CREDENTIAL_ENCR_TYPE = 4,
	WSC_CREDENTIAL_KEY_INDEX = 5,
	WSC_CREDENTIAL_KEY = 6,
	WSC_CREDENTIAL_MAC = 7,
	WSC_SET_DRIVER_CONNECT_BY_CREDENTIAL_IDX = 8,
	WSC_SET_DRIVER_AUTO_CONNECT = 9,
	WSC_SET_CONF_MODE = 10,	/* Enrollee or Registrar */
	WSC_SET_MODE = 11,	/* PIN or PBC */
	WSC_SET_PIN = 12,
	WSC_SET_SSID = 13,
	WSC_START = 14,
	WSC_STOP = 15,
	WSC_GEN_PIN_CODE = 16,
	WSC_AP_BAND = 17,
	WSC_SET_BSSID = 18,
};
#endif /* WSC_STA_SUPPORT */

#ifdef WPA_SUPPLICANT_SUPPORT
#ifndef NATIVE_WPA_SUPPLICANT_SUPPORT
#define	RT_ASSOC_EVENT_FLAG                         0x0101
#define	RT_DISASSOC_EVENT_FLAG                      0x0102
#define	RT_REQIE_EVENT_FLAG                         0x0103
#define	RT_RESPIE_EVENT_FLAG                        0x0104
#define	RT_ASSOCINFO_EVENT_FLAG                     0x0105
#define RT_PMKIDCAND_FLAG                           0x0106
#define RT_INTERFACE_DOWN                           0x0107
#define RT_INTERFACE_UP                             0x0108
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
#ifdef MT_MAC
    CMD_RTPRIV_IOCTL_MBSS_CR_ENABLE,
    CMD_RTPRIV_IOCTL_MBSS_CR_DISABLE,
#endif

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
#ifdef CONFIG_STA_SUPPORT
	CMD_RTPRIV_IOCTL_USB_DEV_GET,
	CMD_RTPRIV_IOCTL_USB_INTF_GET,
	CMD_RTPRIV_IOCTL_ADAPTER_SUSPEND_SET,
	CMD_RTPRIV_IOCTL_ADAPTER_SUSPEND_CLEAR,
	CMD_RTPRIV_IOCTL_ADAPTER_SEND_DISSASSOCIATE,
	CMD_RTPRIV_IOCTL_ADAPTER_SUSPEND_TEST,
	CMD_RTPRIV_IOCTL_ADAPTER_IDLE_RADIO_OFF_TEST,
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_USB_ASICRADIO_OFF,
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_USB_ASICRADIO_ON,

#if (defined(WOW_SUPPORT) && defined(RTMP_MAC_USB)) || defined(MT_WOW_SUPPORT)
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_WOW_STATUS,
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_WOW_ENABLE,
	CMD_RTPRIV_IOCTL_ADAPTER_RT28XX_WOW_DISABLE,
#endif /* (defined(WOW_SUPPORT) && defined(RTMP_MAC_USB)) || defined(MT_WOW_SUPPORT) */

	CMD_RTPRIV_IOCTL_AP_BSSID_GET,
#endif /* CONFIG_STA_SUPPORT */
	CMD_RTPRIV_IOCTL_SANITY_CHECK,
	CMD_RTPRIV_IOCTL_SANITY_CHECK_ON_SET_CMD,	
#ifdef EXT_BUILD_CHANNEL_LIST
	CMD_RTPRIV_SET_PRECONFIG_VALUE,
#endif /* EXT_BUILD_CHANNEL_LIST */

	/* sniffer */
	CMD_RTPRIV_IOCTL_SNIFF_UP,
	CMD_RTPRIV_IOCTL_SNIFF_DISCONNECT,
	CMD_RTPRIV_IOCTL_SNIFF_INIT,
	CMD_RTPRIV_IOCTL_SNIFF_OPEN,
	CMD_RTPRIV_IOCTL_SNIFF_CLOSE,
	CMD_RTPRIV_IOCTL_SNIFF_REMOVE,


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
	CMD_RTPRIV_IOCTL_USB_INIT,

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
	/* CFG_TODO Sort by function */
	CMD_RTPRIV_IOCTL_80211_START,
	CMD_RTPRIV_IOCTL_80211_CB_GET,
	CMD_RTPRIV_IOCTL_80211_CB_SET,
	CMD_RTPRIV_IOCTL_80211_CHAN_SET,
	CMD_RTPRIV_IOCTL_80211_VIF_CHG,
	CMD_RTPRIV_IOCTL_80211_SCAN,
	CMD_RTPRIV_IOCTL_80211_IBSS_JOIN,
	CMD_RTPRIV_IOCTL_80211_STA_LEAVE,
	CMD_RTPRIV_IOCTL_80211_STA_GET,
	CMD_RTPRIV_IOCTL_80211_STA_KEY_ADD,
	CMD_RTPRIV_IOCTL_80211_STA_KEY_DEFAULT_SET,
#ifdef DOT11W_PMF_SUPPORT
	CMD_RTPRIV_IOCTL_80211_STA_MGMT_KEY_DEFAULT_SET,
#endif /* DOT11W_PMF_SUPPORT */	
	CMD_RTPRIV_IOCTL_80211_POWER_MGMT_SET,
	CMD_RTPRIV_IOCTL_80211_AP_KEY_DEFAULT_SET,
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
	CMD_RTPRIV_IOCTL_80211_TX_NETDEV_SET,
	CMD_RTPRIV_IOCTL_80211_MGMT_FRAME_SEND,
	CMD_RTPRIV_IOCTL_80211_CHANNEL_LIST_SET,
	CMD_RTPRIV_IOCTL_80211_ACTION_FRAME_REG,
	CMD_RTPRIV_IOCTL_80211_BEACON_ADD,
	CMD_RTPRIV_IOCTL_80211_BEACON_SET,
	CMD_RTPRIV_IOCTL_80211_BEACON_DEL,
	CMD_RTPRIV_IOCTL_80211_AP_KEY_ADD,
	CMD_RTPRIV_IOCTL_80211_RTS_THRESHOLD_ADD,
	CMD_RTPRIV_IOCTL_80211_FRAG_THRESHOLD_ADD,
	CMD_RTPRIV_IOCTL_80211_CHANGE_BSS_PARM,
	CMD_RTPRIV_IOCTL_80211_AP_KEY_DEL,
	CMD_RTPRIV_IOCTL_80211_AP_PROBE_RSP_EXTRA_IE,
	CMD_RTPRIV_IOCTL_80211_AP_ASSOC_RSP_EXTRA_IE,
	CMD_RTPRIV_IOCTL_80211_PORT_SECURED,
	CMD_RTPRIV_IOCTL_80211_AP_STA_DEL,
	CMD_RTPRIV_IOCTL_80211_CANCEL_REMAIN_ON_CHAN_SET,
	CMD_RTPRIV_IOCTL_80211_BITRATE_SET,
	CMD_RTPRIV_IOCTL_80211_VIF_ADD,
	CMD_RTPRIV_IOCTL_80211_VIF_DEL,
	CMD_RTPRIV_IOCTL_80211_RESET,
	CMD_RTPRIV_IOCTL_80211_P2PCLI_ASSSOC_IE_SET,
	CMD_RTPRIV_IOCTL_80211_P2P_CLIENT_KEY_ADD,
	CMD_RTPRIV_IOCTL_80211_CHANNEL_RESTORE,
	CMD_RTPRIV_IOCTL_80211_SCAN_STATUS_LOCK_INIT,
	CMD_RTPRIV_IOCTL_80211_NETDEV_EVENT,
#ifdef RT_CFG80211_ANDROID_PRIV_LIB_SUPPORT
	CMD_RTPRIV_IOCTL_80211_ANDROID_PRIV_CMD,
#endif /* RT_CFG80211_ANDROID_PRIV_LIB_SUPPORT */
#ifdef RT_P2P_SPECIFIC_WIRELESS_EVENT
	CMD_RTPRIV_IOCTL_80211_SEND_WIRELESS_EVENT,
#endif /* RT_P2P_SPECIFIC_WIRELESS_EVENT */
#ifdef CFG_TDLS_SUPPORT
	CMD_RTPRIV_IOCTL_80211_STA_TDLS_INSERT_PENTRY,
#endif
	CMD_RTPRIV_IOCTL_80211_END,
#endif /* RT_CFG80211_SUPPORT */

	CMD_RTPRIV_IOCTL_ADAPTER_CSO_SUPPORT_TEST,
	CMD_RTPRIV_IOCTL_ADAPTER_TSO_SUPPORT_TEST,
#ifdef CONFIG_HAS_EARLYSUSPEND
	CMD_RTPRIV_IOCTL_LOAD_FIRMWARE_CHECK,
	CMD_RTPRIV_IOCTL_REGISTER_EARLYSUSPEND,
	CMD_RTPRIV_IOCTL_UNREGISTER_EARLYSUSPEND,
	CMD_RTPRIV_IOCTL_CHECK_EARLYSUSPEND,
	CMD_RTPRIV_IOCTL_OS_COOKIE_GET,
	CMD_RTPRIV_IOCTL_SET_SUSPEND_FLAG,
#endif
	CMD_RTPRIV_IOCTL_SDIO_INIT,
	/* can not exceed 0xa000 */
	CMD_RTPRIV_IOCTL_80211_COM_LATEST_ONE,
} CMD_RTPRIV_IOCTL_COMMON;

#ifdef RT_CFG80211_SUPPORT
typedef struct __CMD_RTPRIV_IOCTL_80211_VIF_SET {
	INT  vifType;
	char vifName[IFNAMSIZ];
	INT  vifNameLen;
} CMD_RTPRIV_IOCTL_80211_VIF_SET;

typedef struct __CMD_RTPRIV_IOCTL_80211_BSS_PARM {
	INT   use_cts_prot;
	INT   use_short_preamble;
	INT   use_short_slot_time;
	UINT8 *basic_rates;
	UINT8 basic_rates_len;
	INT   ap_isolate;
	INT   ht_opmode;	

} CMD_RTPRIV_IOCTL_80211_BSS_PARM;

typedef struct __CMD_RTPRIV_IOCTL_80211_BEACON {
        INT32 interval;
        INT32 dtim_period;
        UCHAR *beacon_head;
		UCHAR *beacon_tail;
        UINT32 beacon_head_len; /* Before TIM IE */
		UINT32 beacon_tail_len; /* After TIM IE */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
	UCHAR *beacon_ies;
	UINT32 beacon_ies_len;
	UCHAR *proberesp_ies;
	UINT32 proberesp_ies_len;
	UCHAR *assocresp_ies;
	UINT32 assocresp_ies_len;
	UCHAR *probe_resp;
	UINT32 probe_resp_len;
	ULONG ssid_len;
	CHAR ssid[32];
	UCHAR hidden_ssid;
	struct cfg80211_crypto_settings crypto;
	BOOLEAN privacy;
	UCHAR auth_type;
	INT32 inactivity_timeout;
#endif /* LINUX_VERSION_CODE: 3.4.0 */
} CMD_RTPRIV_IOCTL_80211_BEACON;

#define RT_CMD_80211_IFTYPE_UNSPECIFIED         0x00
#define RT_CMD_80211_IFTYPE_ADHOC				0x01
#define RT_CMD_80211_IFTYPE_STATION				0x02
#define RT_CMD_80211_IFTYPE_AP                  0x03
#define RT_CMD_80211_IFTYPE_AP_VLAN             0x04
#define RT_CMD_80211_IFTYPE_WDS                 0x05
#define RT_CMD_80211_IFTYPE_MONITOR             0x06
#define RT_CMD_80211_IFTYPE_P2P_CLIENT          0x08
#define RT_CMD_80211_IFTYPE_P2P_GO              0x09
#define RT_CMD_80211_IFTYPE_P2P_DEVICE          0x10

/* Must sync with nl80211_channel_type@nl80211.h */
#define RT_CMD_80211_CHANTYPE_NOHT		0x00
#define RT_CMD_80211_CHANTYPE_HT20		0x01
#define RT_CMD_80211_CHANTYPE_HT40MINUS	0X02
#define RT_CMD_80211_CHANTYPE_HT40PLUS	0X03

typedef struct __CMD_RTPRIV_IOCTL_80211_CHAN {
	UINT8 ChanId;
	UINT8 IfType;
	UINT8 ChanType;

	UINT32 MonFilterFlag;
	
	UINT64 cookie;
	PVOID chan;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0))	
	PWIRELESS_DEV pWdev;	
#endif /* LINUX_VERSION_CODE: 3.6.0 */
} CMD_RTPRIV_IOCTL_80211_CHAN;

#define RT_CMD_80211_FILTER_FCSFAIL		0x01
#define RT_CMD_80211_FILTER_PLCPFAIL	0x02
#define RT_CMD_80211_FILTER_CONTROL		0x04
#define RT_CMD_80211_FILTER_OTHER_BSS	0x08

typedef struct __CMD_RTPRIV_IOCTL_80211_VIF_PARM {
	PNET_DEV net_dev;
	UINT8 newIfType;
	UINT8 oldIfType;

	UINT32 MonFilterFlag;
	
} CMD_RTPRIV_IOCTL_80211_VIF_PARM;

typedef struct __CMD_RTPRIV_IOCTL_80211_IBSS {

	UINT  BeaconInterval;
	UCHAR Ssid[33];
	UINT  privacy;
	PUCHAR BeaconExtraIe;
	UINT  BeaconExtraIeLen;
} CMD_RTPRIV_IOCTL_80211_IBSS;

#define RT_CMD_80211_TXRATE_LEGACY		0x01
#define RT_CMD_80211_TXRATE_BW_40		0x02
#define RT_CMD_80211_TXRATE_SHORT_GI	0x04

typedef struct __CMD_RTPRIV_IOCTL_80211_STA {
	UINT8 MAC[MAC_ADDR_LEN];
	ULONG DataRate;

	UINT32 TxRateFlags;
	
	UINT32 TxRateMCS;
	INT32 Signal;
	UINT32 TxPacketCnt;
	UINT32 InactiveTime;
	
	UINT32 rx_packets;
	UINT32 tx_packets;
	UINT32 tx_retries;
	UINT32 tx_failed;	
} CMD_RTPRIV_IOCTL_80211_STA;

#define RT_CMD_80211_KEY_WEP40			0x00
#define RT_CMD_80211_KEY_WEP104			0x01
#define RT_CMD_80211_KEY_WPA			0x02
#ifdef DOT11W_PMF_SUPPORT
#define RT_CMD_80211_KEY_AES_CMAC	0x03
#endif /* DOT11W_PMF_SUPPORT */

typedef struct __CMD_RTPRIV_IOCTL_80211_KEY {
	UINT8 KeyType;
	UINT8 KeyBuf[50];
	UINT8 KeyId;
	BOOLEAN bPairwise;
	UINT8 KeyLen;
	UINT32 cipher;
	UINT8 MAC[MAC_ADDR_LEN];
	PNET_DEV pNetDev;
} CMD_RTPRIV_IOCTL_80211_KEY;

#define RT_CMD_80211_CONN_ENCRYPT_NONE	0x01
#define RT_CMD_80211_CONN_ENCRYPT_WEP	0x02
#define RT_CMD_80211_CONN_ENCRYPT_TKIP	0x04
#define RT_CMD_80211_CONN_ENCRYPT_CCMP	0x08

typedef struct __CMD_RTPRIV_IOCTL_80211_CONNECT {
	UINT8 WpaVer;
	BOOLEAN FlgIs8021x;
	UINT8 AuthType;

	UINT8 PairwiseEncrypType;
	UINT8 GroupwiseEncrypType;

	UINT8 *pKey;
	UINT32 KeyLen;
	UINT8 KeyIdx;

	const UINT8 *pSsid;
	UINT32 SsidLen;
	
	const UINT8 *pBssid;

	BOOLEAN bWpsConnection;
	PNET_DEV pNetDev;
#ifdef DOT11W_PMF_SUPPORT
	BOOLEAN mfp;
#endif /* DOT11W_PMF_SUPPORT */	
} CMD_RTPRIV_IOCTL_80211_CONNECT;

typedef struct __CMD_RTPRIV_IOCTL_80211_ASSOC_IE {
	PNET_DEV pNetDev;
	const UINT8 *ie;
	UINT32 ie_len;
} CMD_RTPRIV_IOCTL_80211_ASSOC_IE;

typedef struct __CMD_RTPRIV_IOCTL_80211_REG_NOTIFY {

	UCHAR Alpha2[2];
	VOID *pWiphy;
} CMD_RTPRIV_IOCTL_80211_REG_NOTIFY;

typedef struct __CMD_RTPRIV_IOCTL_80211_SURVEY {

	VOID *pCfg80211;
/*	UINT64 ChannelTime; */ /* idle + busy, not support */
	UINT64 ChannelTimeBusy;
	UINT64 ChannelTimeExtBusy;
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
#if 0
	CMD_RTPRIV_IOCTL_STA_INF_TYPE_SET,
#endif	
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

#if 0
	CMD_RTPRIV_IOCTL_STA_IW_SET_PARAM_PRE,
#endif
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
	IN UINT32 Rate;
	IN UINT32 Fixed;
} RT_CMD_RATE_SET;

typedef struct __RT_CMD_PARAM_SET {
	IN RTMP_STRING *pThisChar;
	IN RTMP_STRING *pValue;
} RT_CMD_PARAM_SET;

typedef struct __RT_CMD_SHARED_KEY_ADD {
	IN UCHAR KeyIdx;
	IN BOOLEAN FlgHaveGTK;
} RT_CMD_SHARED_KEY_ADD;

typedef struct __RT_CMD_MBSS_KICKOUT {
	INT BssId;
	USHORT Reason;
} RT_CMD_MBSS_KICKOUT;

typedef struct __RT_CMD_USB_MORE_FLAG_CONFIG {
	UINT32 VendorID;
	UINT32 ProductID;
} RT_CMD_USB_MORE_FLAG_CONFIG;

typedef struct __RT_CMD_USB_DEV_CONFIG {
	UINT NumberOfPipes;
	UINT8 BulkInEpAddr[2];
	USHORT BulkInMaxPacketSize;
	UINT8 BulkOutEpAddr[6];
	USHORT BulkOutMaxPacketSize;
	VOID *pConfig;
} RT_CMD_USB_DEV_CONFIG;

typedef struct __RT_CMD_WAIT_QUEUE_LIST {
	RTMP_OS_TASK *pMlmeTask;
	RTMP_OS_TASK *pTimerTask;
	RTMP_OS_TASK *pCmdQTask;
	RTMP_OS_TASK *pWscTask;
} RT_CMD_WAIT_QUEUE_LIST;

typedef struct __RT_CMD_INF_UP_DOWN {

	IN	int (*rt28xx_open)(VOID *net_dev);
	IN	int (*rt28xx_close)(VOID *net_dev);
} RT_CMD_INF_UP_DOWN;

typedef struct __RT_CMD_STATS {
	IN VOID *pNetDev;
	OUT VOID *pStats;	/* point to pAd->stats */

	OUT unsigned long rx_packets;	/* total packets received       */
	OUT unsigned long tx_packets;	/* total packets transmitted */
	OUT unsigned long rx_bytes;	/* total bytes received         */
	OUT unsigned long tx_bytes;	/* total bytes transmitted      */
	OUT unsigned long rx_errors;	/* bad packets received         */
	OUT unsigned long tx_errors;	/* packet transmit problems     */
	OUT unsigned long multicast;	/* multicast packets received */
	OUT unsigned long collisions;

	OUT unsigned long rx_over_errors;	/* receiver ring buff overflow  */
	OUT unsigned long rx_crc_errors;	/* recved pkt with crc error    */
	OUT unsigned long rx_frame_errors;	/* recv'd frame alignment error */
	OUT unsigned long rx_fifo_errors;	/* recv'r fifo overrun                  */
} RT_CMD_STATS;

typedef struct __RT_CMD_IW_STATS {

	ULONG priv_flags;
	UCHAR *dev_addr;

	VOID *pStats;		/* point to pAd->iw_stats */

	UINT8 qual;
	UINT8 level;
	UINT8 noise;
	UINT8 updated;
} RT_CMD_IW_STATS;


typedef struct __RT_CMD_PCIE_INIT {
	VOID *pPciDev;
	UINT32 ConfigDeviceID;
	UINT32 ConfigSubsystemVendorID;
	UINT32 ConfigSubsystemID;
} RT_CMD_PCIE_INIT;

typedef struct __RT_CMD_AP_IOCTL_CONFIG {
	VOID *net_dev;
	VOID *wdev;
	ULONG priv_flags;
	char *pCmdData;
	INT32 CmdId_RTPRIV_IOCTL_SET;
	char *name;
	INT apidx;

	INT32 Status;
} RT_CMD_AP_IOCTL_CONFIG;

typedef struct __RT_CMD_AP_IOCTL_SSID {
	ULONG priv_flags;
	INT apidx;

	char *pSsidStr;
	INT32 length;
} RT_CMD_AP_IOCTL_SSID;

typedef struct __RT_CMD_IOCTL_RATE {
	IN ULONG priv_flags;
	OUT UINT32 BitRate;
} RT_CMD_IOCTL_RATE;

#define RTMP_CMD_STA_MODE_AUTO			0x00
#define RTMP_CMD_STA_MODE_ADHOC			0x01
#define RTMP_CMD_STA_MODE_INFRA			0x02
#define RTMP_CMD_STA_MODE_MONITOR		0x03

typedef struct __RT_CMD_STA_IOCTL_FREQ {
	IN INT32 m;		/* Mantissa */
	IN INT16 e;		/* Exponent */
} RT_CMD_STA_IOCTL_FREQ;

typedef struct __RT_CMD_STA_IOCTL_BSS {
	OUT UCHAR Bssid[6];
	OUT UCHAR ChannelQuality;
	OUT CHAR Rssi;
	OUT CHAR Noise;
} RT_CMD_STA_IOCTL_BSS;

typedef struct __RT_CMD_STA_IOCTL_BSS_LIST {
	IN UINT32 MaxNum;
	OUT UINT32 BssNum;
	OUT RT_CMD_STA_IOCTL_BSS *pList;
} RT_CMD_STA_IOCTL_BSS_LIST;

typedef struct __RT_CMD_STA_IOCTL_SCAN {
	IN UCHAR FlgScanThisSsid;
	IN UINT32 SsidLen;
	IN CHAR *pSsid;
	IN UINT ScanType;
	OUT INT32 Status;
} RT_CMD_STA_IOCTL_SCAN;

typedef struct __RT_CMD_STA_IOCTL_BSS_TABLE {
	UCHAR Bssid[6];
	UCHAR Channel;
	UCHAR BssType;
	UCHAR HtCapabilityLen;

	UCHAR SupRate[12];
	UCHAR SupRateLen;
	UCHAR ExtRate[12];
	UCHAR ExtRateLen;

	UCHAR SsidLen;
	CHAR Ssid[32];

	USHORT CapabilityInfo;
	UCHAR ChannelWidth, ShortGIfor40, ShortGIfor20, MCSSet;

	USHORT WpaIeLen;
	UCHAR *pWpaIe;

	USHORT RsnIeLen;
	UCHAR *pRsnIe;

	USHORT WpsIeLen;
	UCHAR *pWpsIe;

	UCHAR FlgIsPrivacyOn;

	RT_CMD_STA_IOCTL_BSS Signal;
} RT_CMD_STA_IOCTL_BSS_TABLE;

typedef struct __RT_CMD_STA_IOCTL_SCAN_TABLE {
	ULONG priv_flags;
	UINT32 BssNr;
	RT_CMD_STA_IOCTL_BSS_TABLE *pBssTable;	/* must be freed by caller */
	UCHAR MainSharedKey[4][16];
} RT_CMD_STA_IOCTL_SCAN_TABLE;

typedef struct __RT_CMD_STA_IOCTL_SSID {
	UCHAR FlgAnySsid;
	UINT32 SsidLen;
	CHAR *pSsid;
	INT32 Status;
} RT_CMD_STA_IOCTL_SSID;

typedef struct __RT_CMD_STA_IOCTL_NICK_NAME {
	UINT NameLen;
	CHAR *pName;
} RT_CMD_STA_IOCTL_NICK_NAME;

typedef struct __RT_CMD_STA_IOCTL_SECURITY {
	CHAR *pData;
	UINT16 length;
	INT32 KeyIdx;
	INT32 MaxKeyLen;

#define RT_CMD_STA_IOCTL_SECURITY_ALG_NONE		0x01
#define RT_CMD_STA_IOCTL_SECURITY_ALG_WEP		0x02
#define RT_CMD_STA_IOCTL_SECURITY_ALG_TKIP		0x03
#define RT_CMD_STA_IOCTL_SECURITY_ALG_CCMP		0x04
	UINT32 Alg;

#define RT_CMD_STA_IOCTL_SECURTIY_EXT_SET_TX_KEY	0x01
#define RT_CMD_STA_IOCTL_SECURTIY_EXT_GROUP_KEY		0x02
	UINT16 ext_flags;

#define RT_CMD_STA_IOCTL_SECURITY_DISABLED		0x01
#define RT_CMD_STA_IOCTL_SECURITY_ENABLED		0x02
#define RT_CMD_STA_IOCTL_SECURITY_RESTRICTED	0x04
#define RT_CMD_STA_IOCTL_SECURITY_OPEN			0x08
#define RT_CMD_STA_IOCTL_SECURITY_NOKEY			0x10
#define RT_CMD_STA_IOCTL_SECURITY_MODE			0x20
	UINT16 flags;

	INT32 Status;
} RT_CMD_STA_IOCTL_SECURITY;

typedef struct __RT_CMD_STA_IOCTL_WSC_U32_ITEM {
	IN UINT32 *pUWrq;
	OUT INT32 Status;
} RT_CMD_STA_IOCTL_WSC_U32_ITEM;

typedef struct __RT_CMD_STA_IOCTL_WSC_STR_ITEM {
	IN UINT32 Subcmd;
	IN CHAR *pData;
	IN UINT32 length;

	OUT INT32 Status;
} RT_CMD_STA_IOCTL_WSC_STR_ITEM;

typedef struct __RT_CMD_STA_IOCTL_SHOW {
	IN CHAR *pData;
	IN UINT32 MaxSize;
	IN UINT32 InfType;
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

#define RT_CMD_STA_IOCTL_WPA_AUTH_COUNTERMEASURES			0xA0

	UINT32 flags;
	UINT32 value;
} RT_CMD_STA_IOCTL_SECURITY_ADV;

typedef struct __RT_CMD_STA_IOCTL_RSN_IE {
	UINT32 length;
	UCHAR *pRsnIe;
} RT_CMD_STA_IOCTL_RSN_IE;

typedef struct __RT_CMD_STA_IOCTL_PMA_SA {
#define RT_CMD_STA_IOCTL_PMA_SA_FLUSH					0x01
#define RT_CMD_STA_IOCTL_PMA_SA_REMOVE					0x02
#define RT_CMD_STA_IOCTL_PMA_SA_ADD						0x03
	UINT32 Cmd;
	UCHAR *pBssid;
	const UCHAR *pPmkid;
} RT_CMD_STA_IOCTL_PMA_SA;

typedef struct __RT_CMD_USB_INIT {
	VOID *pUsbDev;
	UINT32 driver_info;
} RT_CMD_USB_INIT;

#endif /* __RTMP_CMD_H__ */
