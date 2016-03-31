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


#ifndef __RT_OS_UTIL_H__
#define __RT_OS_UTIL_H__
#include "link_list.h"
/* ============================ rt_linux.c ================================== */
/* General */
void RtmpUtilInit(void);

/* OS Time */
void RTMPusecDelay(
unsigned long					usec);

void RtmpOsUsDelay(unsigned long value);

void RtmpOsMsDelay(
unsigned long					msec);

void RTMP_GetCurrentSystemTime(
unsigned long long			*time);

unsigned long RTMPMsecsToJiffies(unsigned int msec);

void RTMP_GetCurrentSystemTick(
unsigned long					*pNow);

void RtmpOsWait(
unsigned int				Time);

unsigned intRtmpOsTimerAfter(
unsigned long					a,
unsigned long					b);

unsigned intRtmpOsTimerBefore(
unsigned long					a,
unsigned long					b);

void RtmpOsGetSystemUpTime(
unsigned long					*pTime);

unsigned intRtmpOsTickUnitGet(void);

/* OS Memory */
int os_alloc_mem(
void				*pReserved,
		unsigned char					**mem,
unsigned long					size);

int os_alloc_mem_suspend(
void				*pReserved,
		unsigned char					**mem,
unsigned long					size);

int os_free_mem(
void				*pReserved,
void*				mem);

int AdapterBlockAllocateMemory(
void*				handle,
		void*				*ppAd,
unsigned int				SizeOfpAd);

void* RtmpOsVmalloc(
unsigned long					Size);

void RtmpOsVfree(
void				*pMem);

unsigned long RtmpOsCopyFromUser(
		void				*to,
const void				*from,
unsigned long					n);

unsigned long RtmpOsCopyToUser(
	 void				*to,
const void				*from,
unsigned long					n);

unsigned char RtmpOsStatsAlloc(
void				**ppStats,
void				**ppIwStats);

/* OS Packet */
PNDIS_PACKET RtmpOSNetPktAlloc(
void				*pReserved,
int						size);

PNDIS_PACKET RTMP_AllocateFragPacketBuffer(
void				*pReserved,
unsigned long					Length);

int RTMPAllocateNdisPacket(
void				*pReserved,
	 PNDIS_PACKET			*ppPacket,
unsigned char *					pHeader,
unsigned int					HeaderLen,
unsigned char *					pData,
unsigned int					DataLen);

void RTMPFreeNdisPacket(
void				*pReserved,
PNDIS_PACKET			pPacket);

int Sniff2BytesFromNdisBuffer(
 PNDIS_BUFFER			pFirstBuffer,
 unsigned char           		DesiredOffset,
	 unsigned char *          		pByte0,
	 unsigned char *          		pByte1);

void RTMP_QueryPacketInfo(
 PNDIS_PACKET			pPacket,
	 PACKET_INFO  			*pPacketInfo,
	 unsigned char *		 			*pSrcBufVA,
		unsigned int		 			*pSrcBufLen);

PNDIS_PACKET DuplicatePacket(
struct net_device *				pNetDev,
PNDIS_PACKET			pPacket,
unsigned char					FromWhichBSSID);

PNDIS_PACKET duplicate_pkt(
struct net_device *				pNetDev,
unsigned char *					pHeader802_3,
    IN  unsigned int            		HdrLen,
unsigned char *					pData,
unsigned long					DataSize,
unsigned char					FromWhichBSSID);

PNDIS_PACKET duplicate_pkt_with_TKIP_MIC(
void				*pReserved,
PNDIS_PACKET			pOldPkt);

PNDIS_PACKET duplicate_pkt_with_VLAN(
struct net_device *				pNetDev,
unsigned short					VLAN_VID,
unsigned short					VLAN_Priority,
unsigned char *					pHeader802_3,
    IN  unsigned int            		HdrLen,
unsigned char *					pData,
unsigned long					DataSize,
unsigned char					FromWhichBSSID,
unsigned char					*TPID);

typedef void (*RTMP_CB_8023_PACKET_ANNOUNCE)(
			IN	void		*pCtrlBkPtr, 
			IN	PNDIS_PACKET	pPacket,
			IN	unsigned char			OpMode);

unsigned char RTMPL2FrameTxAction(
 void				*pCtrlBkPtr,
struct net_device *				pNetDev,
RTMP_CB_8023_PACKET_ANNOUNCE _announce_802_3_packet,
unsigned char					apidx,
unsigned char *					pData,
unsigned int				data_len,
unsigned char			OpMode);

PNDIS_PACKET ExpandPacket(
void				*pReserved,
PNDIS_PACKET			pPacket,
unsigned int				ext_head_len,
unsigned int				ext_tail_len);

PNDIS_PACKET ClonePacket(
void				*pReserved,
PNDIS_PACKET			pPacket,
unsigned char *					pData,
unsigned long					DataSize);

void wlan_802_11_to_802_3_packet(
struct net_device *				pNetDev,
unsigned char					OpMode,
unsigned short					VLAN_VID,
unsigned short					VLAN_Priority,
PNDIS_PACKET			pRxPacket,
unsigned char					*pData,
unsigned long					DataSize,
unsigned char *					pHeader802_3,
 unsigned char					FromWhichBSSID,
unsigned char					*TPID);

void send_monitor_packets(
struct net_device *				pNetDev,
PNDIS_PACKET			pRxPacket,
PHEADER_802_11			pHeader,
unsigned char					*pData,
unsigned short					DataSize,
unsigned char					L2PAD,
unsigned char					PHYMODE,
unsigned char					BW,
unsigned char					ShortGI,
unsigned char					MCS,
unsigned char					AMPDU,
unsigned char					STBC,
unsigned char					RSSI1,
unsigned char					BssMonitorFlag11n,
unsigned char					*pDevName,
unsigned char					Channel,
unsigned char					CentralChannel,
unsigned int				MaxRssi);

unsigned char VLAN_8023_Header_Copy(
unsigned short					VLAN_VID,
unsigned short					VLAN_Priority,
unsigned char *					pHeader802_3,
unsigned int            		HdrLen,
	 unsigned char *					pData,
unsigned char					FromWhichBSSID,
unsigned char					*TPID);

void RtmpOsPktBodyCopy(
struct net_device *				pNetDev,
PNDIS_PACKET			pNetPkt,
unsigned long					ThisFrameLen,
unsigned char *					pData);

int RtmpOsIsPktCloned(
PNDIS_PACKET			pNetPkt);

PNDIS_PACKET RtmpOsPktCopy(
PNDIS_PACKET			pNetPkt);

PNDIS_PACKET RtmpOsPktClone(
PNDIS_PACKET			pNetPkt);

void RtmpOsPktDataPtrAssign(
PNDIS_PACKET			pNetPkt,
unsigned char					*pData);

void RtmpOsPktLenAssign(
PNDIS_PACKET			pNetPkt,
long					Len);

void RtmpOsPktTailAdjust(
PNDIS_PACKET			pNetPkt,
unsigned int					removedTagLen);

unsigned char * RtmpOsPktTailBufExtend(
PNDIS_PACKET			pNetPkt,
unsigned int					Len);

unsigned char * RtmpOsPktHeadBufExtend(
PNDIS_PACKET			pNetPkt,
unsigned int					Len);

void RtmpOsPktReserve(
PNDIS_PACKET			pNetPkt,
unsigned int					Len);

void RtmpOsPktProtocolAssign(
PNDIS_PACKET			pNetPkt);

void RtmpOsPktInfPpaSend(
PNDIS_PACKET			pNetPkt);

void RtmpOsPktRcvHandle(
PNDIS_PACKET			pNetPkt);

void RtmpOsPktNatMagicTag(
PNDIS_PACKET			pNetPkt);

void RtmpOsPktNatNone(
PNDIS_PACKET			pNetPkt);

void RtmpOsPktInit(
PNDIS_PACKET			pNetPkt,
struct net_device *				pNetDev,
unsigned char					*pData,
unsigned short					DataSize);

PNDIS_PACKET RtmpOsPktIappMakeUp(
struct net_device *				pNetDev,
unsigned char					*pMac);

unsigned char RtmpOsPktOffsetInit(void);

/*
========================================================================
Routine Description:
	Initialize the OS atomic_t.
*/

unsigned short RtmpOsNtohs(
unsigned short					Value);

unsigned short RtmpOsHtons(
unsigned short					Value);

unsigned intRtmpOsNtohl(
unsigned int				Value);

unsigned intRtmpOsHtonl(
unsigned int				Value);

/* OS File */
RTMP_OS_FD RtmpOSFileOpen(char *pPath,  int flag, int mode);
int RtmpOSFileClose(RTMP_OS_FD osfd);
void RtmpOSFileSeek(RTMP_OS_FD osfd, int offset);
int RtmpOSFileRead(RTMP_OS_FD osfd, char *pDataPtr, int readLen);
int RtmpOSFileWrite(RTMP_OS_FD osfd, char *pDataPtr, int writeLen);

int RtmpOsFileIsErr(
void				*pFile);

void RtmpOSFSInfoChange(
RTMP_OS_FS_INFO			*pOSFSInfoOrg,
unsigned char					bSet);

/* OS Network interface */
int RtmpOSNetDevAddrSet(
unsigned char					OpMode,
struct net_device * 				pNetDev,
unsigned char *					pMacAddr,
unsigned char *					dev_name);

void RtmpOSNetDevClose(
struct net_device *					pNetDev);

void RtmpOSNetDevFree(
struct net_device *				pNetDev);

int RtmpOSNetDevAlloc(
struct net_device *				*new_dev_p,
unsigned int				privDataSize);

int RtmpOSNetDevOpsAlloc(
void*				*pNetDevOps);


struct net_device * RtmpOSNetDevGetByName(
struct net_device *				pNetDev,
char*					pDevName);

void RtmpOSNetDeviceRefPut(
struct net_device *				pNetDev);

int RtmpOSNetDevDestory(
void				*pReserved,
struct net_device *				pNetDev);

void RtmpOSNetDevDetach(
struct net_device *				pNetDev);

int RtmpOSNetDevAttach(
unsigned char					OpMode,
struct net_device *				pNetDev, 
RTMP_OS_NETDEV_OP_HOOK	*pDevOpHook);

void RtmpOSNetDevProtect(
unsigned char lock_it);

struct net_device * RtmpOSNetDevCreate(
int					MC_RowID,
unsigned int				*pIoctlIF,
int 					devType,
int						devNum,
int						privMemSize,
char*					pNamePrefix);

unsigned char RtmpOSNetDevIsUp(
void				*pDev);

unsigned char *RtmpOsNetDevGetPhyAddr(
void				*pDev);

void RtmpOsNetQueueStart(
struct net_device *				pDev);

void RtmpOsNetQueueStop(
struct net_device *				pDev);

void RtmpOsNetQueueWake(
struct net_device *				pDev);

void RtmpOsSetPktNetDev(
void				*pPkt,
void				*pDev);

struct net_device * RtmpOsPktNetDevGet(
void				*pPkt);

char *RtmpOsGetNetDevName(
void				*pDev);

void RtmpOsSetNetDevPriv(
void				*pDev,
void				*pPriv);

void*RtmpOsGetNetDevPriv(
void				*pDev);

unsigned short RtmpDevPrivFlagsGet(
void				*pDev);

void RtmpDevPrivFlagsSet(
void				*pDev,
unsigned short					PrivFlags);

void RtmpOsSetNetDevType(void *pDev, unsigned short Type);

void RtmpOsSetNetDevTypeMonitor(void *pDev);


/* OS Semaphore */
void RtmpOsCmdUp(RTMP_OS_TASK *pCmdQTask);
unsigned char RtmpOsSemaInitLocked(RTMP_OS_SEM *pSemOrg, LIST_HEADER *pSemList);
unsigned char RtmpOsSemaInit(RTMP_OS_SEM *pSemOrg, LIST_HEADER *pSemList);
unsigned char RtmpOsSemaDestroy(RTMP_OS_SEM *pSemOrg);
int RtmpOsSemaWaitinterruptible(RTMP_OS_SEM *pSemOrg);
void RtmpOsSemaWakeUp(RTMP_OS_SEM *pSemOrg);
void RtmpOsMlmeUp(RTMP_OS_TASK *pMlmeQTask);

void RtmpOsInitCompletion(RTMP_OS_COMPLETION *pCompletion);
void RtmpOsExitCompletion(RTMP_OS_COMPLETION *pCompletion);
void RtmpOsComplete(RTMP_OS_COMPLETION *pCompletion);
unsigned long RtmpOsWaitForCompletionTimeout(RTMP_OS_COMPLETION *pCompletion, unsigned long Timeout); 

/* OS Task */
unsigned char RtmpOsTaskletSche(RTMP_NET_TASK_STRUCT *pTasklet);

unsigned char RtmpOsTaskletInit(
	RTMP_NET_TASK_STRUCT *pTasklet,
	void(*pFunc)(unsigned long data),
	unsigned long Data,
	struct list_head *pTaskletList);

unsigned char RtmpOsTaskletKill(RTMP_NET_TASK_STRUCT *pTasklet);

void RtmpOsTaskletDataAssign(
	RTMP_NET_TASK_STRUCT *pTasklet,
	unsigned long Data);

void RtmpOsTaskWakeUp(RTMP_OS_TASK *pTaskOrg);

int RtmpOsTaskIsKilled(RTMP_OS_TASK *pTaskOrg);

unsigned char RtmpOsCheckTaskLegality(RTMP_OS_TASK *pTaskOrg);

unsigned char RtmpOSTaskAlloc(
RTMP_OS_TASK			*pTask,
struct list_head				*pTaskList);

void RtmpOSTaskFree(
RTMP_OS_TASK			*pTask);

int RtmpOSTaskKill(
RTMP_OS_TASK			*pTaskOrg);

int RtmpOSTaskNotifyToExit(
RTMP_OS_TASK			*pTaskOrg);

void RtmpOSTaskCustomize(
RTMP_OS_TASK			*pTaskOrg);

int RtmpOSTaskAttach(
RTMP_OS_TASK			*pTaskOrg,
RTMP_OS_TASK_CALLBACK	fn,
unsigned long					arg);

int RtmpOSTaskInit(
RTMP_OS_TASK			*pTaskOrg,
char*					pTaskName,
void				*pPriv,
LIST_HEADER				*pTaskList,
LIST_HEADER				*pSemList);

unsigned char RtmpOSTaskWait(
void				*pReserved,
RTMP_OS_TASK			*pTaskOrg,
int					*pStatus);

void*RtmpOsTaskDataGet(RTMP_OS_TASK *pTaskOrg);

int RtmpThreadPidKill(RTMP_OS_PID	 PID);

/* OS Cache */
void RtmpOsDCacheFlush(unsigned long AddrStart, unsigned long Size);

/* OS Timer */
void RTMP_SetPeriodicTimer(
NDIS_MINIPORT_TIMER *pTimerOrg, 
unsigned long timeout);

void RTMP_OS_Init_Timer(
void					*pReserved,
NDIS_MINIPORT_TIMER		*pTimerOrg, 
TIMER_FUNCTION			function,
void*				data,
LIST_HEADER				*pTimerList);

void RTMP_OS_Add_Timer(
NDIS_MINIPORT_TIMER *pTimerOrg,
unsigned long timeout);

void RTMP_OS_Mod_Timer(
NDIS_MINIPORT_TIMER *pTimerOrg,
unsigned long timeout);

void RTMP_OS_Del_Timer(
NDIS_MINIPORT_TIMER		*pTimerOrg,
		unsigned char					*pCancelled);

void RTMP_OS_Release_Timer(
NDIS_MINIPORT_TIMER		*pTimerOrg);

unsigned char RTMP_OS_Alloc_Rsc(
struct list_head				*pRscList,
void					*pRsc,
unsigned int				RscLen);

void RTMP_OS_Free_Rscs(
struct list_head				*pRscList);

/* OS Lock */
unsigned char RtmpOsAllocateLock(
NDIS_SPIN_LOCK			*pLock,
struct list_head				*pLockList);

void RtmpOsFreeSpinLock(
NDIS_SPIN_LOCK			*pLockOrg);

void RtmpOsSpinLockBh(
NDIS_SPIN_LOCK			*pLockOrg);

void RtmpOsSpinUnLockBh(NDIS_SPIN_LOCK *pLockOrg);
void RtmpOsintLock(NDIS_SPIN_LOCK *pLockOrg, unsigned long *pIrqFlags);
void RtmpOsintUnLock(NDIS_SPIN_LOCK *pLockOrg, unsigned long IrqFlags);

/* OS PID */
void RtmpOsGetPid(unsigned long *pDst, unsigned long PID);
void RtmpOsTaskPidInit(RTMP_OS_PID *pPid);

/* OS I/O */
void RTMP_PCI_Writel(unsigned long Value, void *pAddr);
void RTMP_PCI_Writew(unsigned long Value, void *pAddr);
void RTMP_PCI_Writeb(unsigned long Value, void *pAddr);
unsigned long RTMP_PCI_Readl(void*pAddr);
unsigned long RTMP_PCI_Readw(void*pAddr);
unsigned long RTMP_PCI_Readb(void*pAddr);

int RtmpOsPciConfigReadWord(
void				*pDev,
unsigned int				Offset,
	 unsigned short					*pValue);

int RtmpOsPciConfigWriteWord(
void				*pDev,
unsigned int				Offset,
unsigned short					Value);

int RtmpOsPciConfigReadDWord(
void				*pDev,
unsigned int				Offset,
	 unsigned int 				*pValue);

int RtmpOsPciConfigWriteDWord(
void				*pDev,
unsigned int				Offset,
unsigned int				Value);

int RtmpOsPciFindCapability(
void				*pDev,
int						Cap);

void*RTMPFindHostPCIDev(void *pPciDevSrc);

int RtmpOsPciMsiEnable(void*pDev);
void RtmpOsPciMsiDisable(void *pDev);

/* OS Wireless */
unsigned long RtmpOsMaxScanDataGet(void);

/* OS interrutp */
int RtmpOsIsIninterrupt(void);

/* OS USB */
void*RtmpOsUsbUrbDataGet(void *pUrb);
int RtmpOsUsbUrbStatusGet(void*pUrb);
unsigned long RtmpOsUsbUrbLenGet(void*pUrb);

/* OS Atomic */
unsigned char RtmpOsAtomicInit(RTMP_OS_ATOMIC *pAtomic, struct list_head *pAtomicList);
void RtmpOsAtomicDestroy(RTMP_OS_ATOMIC *pAtomic);
long RtmpOsAtomicRead(RTMP_OS_ATOMIC *pAtomic);
void RtmpOsAtomicDec(RTMP_OS_ATOMIC *pAtomic);
void RtmpOsAtomicinterlockedExchange(RTMP_OS_ATOMIC *pAtomicSrc, long Value);

/* OS Utility */
void hex_dump(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen);

typedef void(*RTMP_OS_SEND_WLAN_EVENT)(
void				*pAdSrc,
unsigned short					Event_flag,
unsigned char * 					pAddr,
 unsigned char					BssIdx,
char					Rssi);

void RtmpOsSendWirelessEvent(
void		*pAd,
unsigned short			Event_flag,
unsigned char * 			pAddr,
unsigned char			BssIdx,
char			Rssi,
RTMP_OS_SEND_WLAN_EVENT pFunc);


int RtmpOSWrielessEventSend(
struct net_device *				pNetDev,
unsigned int				eventType,
int						flags,
unsigned char *					pSrcMac,
unsigned char *					pData,
unsigned int				dataLen);

int RtmpOSWrielessEventSendExt(
struct net_device *				pNetDev,
unsigned int				eventType,
int						flags,
unsigned char *					pSrcMac,
unsigned char *					pData,
unsigned int				dataLen,
unsigned int				family);

unsigned int RtmpOsWirelessExtVerGet(void);

void RtmpDrvAllMacPrint(
void					*pReserved,
unsigned int				*pBufMac,
unsigned int				AddrStart,
unsigned int				AddrEnd,
unsigned int				AddrStep);

void RtmpDrvAllE2PPrint(
void				*pReserved,
unsigned short					*pMacContent,
unsigned int				AddrEnd,
unsigned int				AddrStep);

void RtmpDrvAllRFPrint(
void*pReserved,
unsigned int*pBuf,
unsigned intBufLen);

int RtmpOSIRQRelease(
struct net_device *				pNetDev,
unsigned int				infType,
PPCI_DEV				pci_dev,
unsigned char					*pHaveMsi);

void RtmpOsWlanEventSet(
void				*pReserved,
unsigned char					*pCfgWEnt,
unsigned char					FlgIsWEntSup);

unsigned short RtmpOsGetUnaligned(unsigned short *pWord);

unsigned intRtmpOsGetUnaligned32(unsigned int *pWord);

unsigned long RtmpOsGetUnalignedlong(unsigned long *pWord);

long RtmpOsSimpleStrtol(
const char				*cp,
char 					**endp,
unsigned int			base);

void RtmpOsOpsInit(RTMP_OS_ABL_OPS *pOps);

/* ============================ rt_os_util.c ================================ */
void RtmpDrvMaxRateGet(
void*pReserved,
unsigned char MODE,
unsigned char ShortGI,
unsigned char BW,
unsigned char MCS,
	 unsigned int *pRate);

char * rtstrchr(const char * s, int c);

char*   WscGetAuthTypeStr(unsigned short authFlag);

char*   WscGetEncryTypeStr(unsigned short encryFlag);

unsigned short WscGetAuthTypeFromStr(char* arg);

unsigned short WscGetEncrypTypeFromStr(char* arg);

void RtmpMeshDown(
void*pDrvCtrlBK,
unsigned char WaitFlag,
unsigned char (*RtmpMeshLinkCheck)(IN void*pAd));

unsigned short RtmpOsNetPrivGet(struct net_device * pDev);

unsigned char RtmpOsCmdDisplayLenCheck(
unsigned int				LenSrc,
unsigned int				Offset);

void   WpaSendMicFailureToWpaSupplicant(
struct net_device *				pNetDev,
    IN  unsigned char					bUnicast);

int wext_notify_event_assoc(
struct net_device *				pNetDev,
unsigned char					*ReqVarIEs,
unsigned int				ReqVarIELen);

void   SendAssocIEsToWpaSupplicant( 
struct net_device *				pNetDev,
unsigned char					*ReqVarIEs,
unsigned int				ReqVarIELen);

/* ============================ rt_rbus_pci_util.c ========================== */
void RtmpAllocDescBuf(
PPCI_DEV pPciDev,
unsigned int Index,
unsigned long Length,
unsigned char Cached,
	 void**VirtualAddress,
	 PNDIS_PHYSICAL_ADDRESS	PhysicalAddress);

void RtmpFreeDescBuf(
PPCI_DEV pPciDev,
unsigned long Length,
void*VirtualAddress,
NDIS_PHYSICAL_ADDRESS	PhysicalAddress);

void RTMP_AllocateFirstTxBuffer(
PPCI_DEV pPciDev,
unsigned int Index,
unsigned long Length,
unsigned char Cached,
	 void**VirtualAddress,
	 PNDIS_PHYSICAL_ADDRESS	PhysicalAddress);

void RTMP_FreeFirstTxBuffer(
PPCI_DEV				pPciDev,
unsigned long					Length,
unsigned char					Cached,
void*				VirtualAddress,
NDIS_PHYSICAL_ADDRESS	PhysicalAddress);

PNDIS_PACKET RTMP_AllocateRxPacketBuffer(
void				*pReserved,
void				*pPciDev,
unsigned long					Length,
unsigned char					Cached,
		void*				*VirtualAddress,
		PNDIS_PHYSICAL_ADDRESS	PhysicalAddress);

#ifdef CONFIG_STA_SUPPORT
#ifdef CONFIG_PM
#ifdef USB_SUPPORT_SELECTIVE_SUSPEND

int RTMP_Usb_AutoPM_Put_interface(
void		*pUsb_Dev,
void		*intf);

int  RTMP_Usb_AutoPM_Get_interface(
void		*pUsb_Dev,
void		*intf);

#endif /* USB_SUPPORT_SELECTIVE_SUSPEND */
#endif /* CONFIG_PM */
#endif /* CONFIG_STA_SUPPORT */



ra_dma_addr_t linux_pci_map_single(void *pPciDev, void *ptr, size_t size, int sd_idx, int direction);

void linux_pci_unmap_single(void *pPciDev, ra_dma_addr_t dma_addr, size_t size, int direction);

/* ============================ rt_usb_util.c =============================== */
#ifdef RTMP_MAC_USB
typedef void(*USB_COMPLETE_HANDLER)(void *);

void dump_urb(void*purb);

int rausb_register(void* new_driver);

void rausb_deregister(void* driver);

/*struct urb *rausb_alloc_urb(int iso_packets); */

void rausb_free_urb(void*urb);

void rausb_put_dev(void*dev);

struct usb_device *rausb_get_dev(void*dev);

int rausb_submit_urb(void*urb);

void *rausb_buffer_alloc(void*dev,
							size_t size,
							ra_dma_addr_t *dma);

void rausb_buffer_free(void*dev,
							size_t size,
							void *addr,
							ra_dma_addr_t dma);

int rausb_control_msg(void*dev,
						unsigned int pipe,
						__u8 request,
						__u8 requesttype,
						__u16 value,
						__u16 index,
						void *data,
						__u16 size,
						int timeout);

void rausb_fill_bulk_urb(void *urb,
						 void *dev,
						 unsigned int pipe,
						 void *transfer_buffer,
						 int buffer_length,
						 USB_COMPLETE_HANDLER complete_fn,
						 void *context);

unsigned int rausb_sndctrlpipe(void*dev, unsigned long address);

unsigned int rausb_rcvctrlpipe(void*dev, unsigned long address);


unsigned int rausb_sndbulkpipe(void *dev, unsigned long address);
unsigned int rausb_rcvbulkpipe(void *dev, unsigned long address);

void rausb_kill_urb(void*urb);

void RtmpOsUsbEmptyUrbCheck(
void			**ppWait,
NDIS_SPIN_LOCK		*pBulkInLock,
unsigned char				*pPendingRx);


void RtmpOsUsbInitHTTxDesc(
void		*pUrbSrc,
void		*pUsb_Dev,
unsigned int			BulkOutEpAddr,
unsigned char *			pSrc,
unsigned long			BulkOutSize,
USB_COMPLETE_HANDLER	Func,
void		*pTxContext,
ra_dma_addr_t		TransferDma);

void RtmpOsUsbInitRxDesc(
void		*pUrbSrc,
void		*pUsb_Dev,
unsigned int			BulkInEpAddr,
unsigned char			*pTransferBuffer,
unsigned int		BufSize,
USB_COMPLETE_HANDLER	Func,
void		*pRxContext,
ra_dma_addr_t		TransferDma);

void*RtmpOsUsbContextGet(
void		*pUrb);

int RtmpOsUsbStatusGet(
void		*pUrb);

void RtmpOsUsbDmaMapping(
void		*pUrb);
#endif /* RTMP_MAC_USB */

#if defined(RTMP_RBUS_SUPPORT) || defined(RTMP_FLASH_SUPPORT)
void RtmpFlashRead(
	unsigned char * p,
	unsigned long a,
	unsigned long b);

void RtmpFlashWrite(
	unsigned char * p,
	unsigned long a,
	unsigned long b);
#endif /* defined(RTMP_RBUS_SUPPORT) || defined(RTMP_FLASH_SUPPORT) */

unsigned intRtmpOsGetUsbDevVendorID(
void*pUsbDev);

unsigned intRtmpOsGetUsbDevProductID(
void*pUsbDev);

/* CFG80211 */
#ifdef RT_CFG80211_SUPPORT
typedef struct __CFG80211_BAND {

	unsigned char RFICType;
	unsigned char MpduDensity;
	unsigned char TxStream;
	unsigned char RxStream;
	unsigned int MaxTxPwr;
	unsigned int MaxBssTable;

	unsigned short RtsThreshold;
	unsigned short FragmentThreshold;
	unsigned int RetryMaxCnt; /* bit0~7: short; bit8 ~ 15: long */
	unsigned char FlgIsBMode;
} CFG80211_BAND;

voidCFG80211OS_UnRegister(
void					*pCB,
void					*pNetDev);

unsigned char CFG80211_SupBandInit(
void					*pCB,
CFG80211_BAND 			*pBandInfo,
void					*pWiphyOrg,
void					*pChannelsOrg,
void					*pRatesOrg);

unsigned char CFG80211OS_SupBandReInit(
void					*pCB,
CFG80211_BAND 			*pBandInfo);

voidCFG80211OS_RegHint(
void					*pCB,
unsigned char					*pCountryIe,
unsigned long					CountryIeLen);

voidCFG80211OS_RegHint11D(
void					*pCB,
unsigned char					*pCountryIe,
unsigned long					CountryIeLen);

unsigned char CFG80211OS_BandInfoGet(
void					*pCB,
void					*pWiphyOrg,
	 void				**ppBand24,
	 void				**ppBand5);

unsigned intCFG80211OS_ChanNumGet(
void					*pCB,
void					*pWiphyOrg,
unsigned int				IdBand);

unsigned char CFG80211OS_ChanInfoGet(
void					*pCB,
void					*pWiphyOrg,
unsigned int				IdBand,
unsigned int				IdChan,
	 unsigned int 				*pChanId,
	 unsigned int 				*pPower,
	 unsigned char					*pFlgIsRadar);

unsigned char CFG80211OS_ChanInfoInit(
void					*pCB,
unsigned int				InfoIndex,
unsigned char					ChanId,
unsigned char					MaxTxPwr,
unsigned char					FlgIsNMode,
unsigned char					FlgIsBW20M);

voidCFG80211OS_Scaning(
void					*pCB,
unsigned int				ChanId,
unsigned char					*pFrame,
unsigned int				FrameLen,
int					RSSI,
unsigned char					FlgIsNMode,
unsigned char					BW);

voidCFG80211OS_ScanEnd(
void					*pCB,
unsigned char					FlgIsAborted);

void CFG80211OS_ConnectResultInform(
void					*pCB,
unsigned char					*pBSSID,
unsigned char					*pReqIe,
unsigned int				ReqIeLen,
unsigned char					*pRspIe,
unsigned int				RspIeLen,
unsigned char					FlgIsSuccess);
#endif /* RT_CFG80211_SUPPORT */




/* ================================ MACRO =================================== */
#define RTMP_UTIL_DCACHE_FLUSH(__AddrStart, __Size)

/* ================================ EXTERN ================================== */
extern unsigned char SNAP_802_1H[6];
extern unsigned char SNAP_BRIDGE_TUNNEL[6];
extern unsigned char EAPOL[2];
extern unsigned char TPID[];
extern unsigned char IPX[2];
extern unsigned char APPLE_TALK[2];
extern unsigned char NUM_BIT8[8];
extern unsigned long RTPktOffsetData, RTPktOffsetLen, RTPktOffsetCB;

extern unsigned long OS_NumOfMemAlloc, OS_NumOfMemFree;

extern int ralinkrate[];
extern unsigned int RT_RateSize;

#ifdef PLATFORM_UBM_IPX8
#include "vrut_ubm.h"
#endif /* PLATFORM_UBM_IPX8 */

int  RtPrivIoctlSetVal(void);

void OS_SPIN_LOCK_IRQSAVE(NDIS_SPIN_LOCK *lock, unsigned long *flags);
void OS_SPIN_UNLOCK_IRQRESTORE(NDIS_SPIN_LOCK *lock, unsigned long *flags);
void OS_SPIN_LOCK_IRQ(NDIS_SPIN_LOCK *lock);
void OS_SPIN_UNLOCK_IRQ(NDIS_SPIN_LOCK *lock);
void RtmpOsSpinLockIrqSave(NDIS_SPIN_LOCK *lock, unsigned long *flags);
void RtmpOsSpinUnlockIrqRestore(NDIS_SPIN_LOCK *lock, unsigned long *flags);
void RtmpOsSpinLockIrq(NDIS_SPIN_LOCK *lock);
void RtmpOsSpinUnlockIrq(NDIS_SPIN_LOCK *lock);
int OS_TEST_BIT(int bit, unsigned long *flags);
void OS_SET_BIT(int bit, unsigned long *flags);
void OS_CLEAR_BIT(int bit, unsigned long *flags);

#endif /* __RT_OS_UTIL_H__ */
