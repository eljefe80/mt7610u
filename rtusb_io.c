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


#ifdef RTMP_MAC_USB


#include	"rt_config.h"

#define MAX_VENDOR_REQ_RETRY_COUNT  10

/*
	========================================================================

	Routine Description: NIC initialization complete

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/

void usb_cfg_read_v1(PRTMP_ADAPTER ad, u32 *value)
{
	RTUSBReadMACRegister(ad, USB_DMA_CFG, value);
}

void usb_cfg_write_v1(PRTMP_ADAPTER ad, u32 value)
{
	RTUSBWriteMACRegister(ad, USB_DMA_CFG, value, FALSE);
}

void usb_cfg_read_v2(PRTMP_ADAPTER ad, u32 *value)
{
	int ret;
	u32 io_value;

	ret = RTUSB_VendorRequest(ad,
							  (USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
							  DEVICE_VENDOR_REQUEST_IN,
							  0x47,
							  0,
							  U3DMA_WLCFG,
							  &io_value,
							  4);

	*value = le2cpu32(io_value);

	if (ret)
		*value = 0xffffffff;
}

void usb_cfg_write_v2(PRTMP_ADAPTER ad, u32 value)
{
	int ret;
	u32 io_value;


	io_value = cpu2le32(value);

	ret = RTUSB_VendorRequest(ad,
							  USBD_TRANSFER_DIRECTION_OUT,
							  DEVICE_VENDOR_REQUEST_OUT,
							  0x46,
							  0,
							  U3DMA_WLCFG,
							  &io_value,
							  4);


	if (ret) {
		DBGPRINT(RT_DEBUG_ERROR, ("usb cfg write fail\n"));
		return;
	}
}

static int	RTUSBFirmwareRun(
	IN	PRTMP_ADAPTER	pAd)
{
	int	Status;

	Status = RTUSB_VendorRequest(
		pAd,
		USBD_TRANSFER_DIRECTION_OUT,
		DEVICE_VENDOR_REQUEST_OUT,
		0x01,
		0x8,
		0,
		NULL,
		0);

	return Status;
}



/*
	========================================================================

	Routine Description: Get current firmware operation mode (Return Value)

	Arguments:

	Return Value:
		0 or 1 = Downloaded by host driver
		others = Driver doesn't download firmware

	IRQL =

	Note:

	========================================================================
*/
int	RTUSBFirmwareOpmode(
	IN	PRTMP_ADAPTER	pAd,
	OUT	unsigned long*			pValue)
{
	int	Status;

	Status = RTUSB_VendorRequest(
		pAd,
		(USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
		DEVICE_VENDOR_REQUEST_IN,
		0x1,
		0x11,
		0,
		pValue,
		4);
	return Status;
}


/*
	========================================================================

	Routine Description: Write Firmware to NIC.

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int RTUSBFirmwareWrite(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char*		pFwImage,
	IN unsigned long		FwLen)
{
	unsigned int		MacReg;
	int 	Status;
/*	unsigned long 		i;*/
	unsigned short		writeLen;
	/*unsigned long		FMode = 0;*/


	Status = RTUSBReadMACRegister(pAd, MAC_CSR0, &MacReg);


	/* write firmware */
	writeLen = FwLen;
#ifdef USB_FIRMWARE_MULTIBYTE_WRITE
	DBGPRINT(RT_DEBUG_TRACE, ("USB_FIRMWARE_MULTIBYTE_WRITE defined! Write_Bytes = %d\n", MULTIWRITE_BYTES));
	RTUSBMultiWrite_nBytes(pAd, FIRMWARE_IMAGE_BASE, pFwImage, writeLen, MULTIWRITE_BYTES);
#else
	DBGPRINT(RT_DEBUG_TRACE, ("USB_FIRMWARE_MULTIBYTE_WRITE not defined!\n"));
	RTUSBMultiWrite(pAd, FIRMWARE_IMAGE_BASE, pFwImage, writeLen, FALSE);
#endif
	Status = RTUSBWriteMACRegister(pAd, 0x7014, 0xffffffff, FALSE);
	Status = RTUSBWriteMACRegister(pAd, 0x701c, 0xffffffff, FALSE);

	/* change 8051 from ROM to RAM */
	Status = RTUSBFirmwareRun(pAd);


	return Status;
}


int	RTUSBVenderReset(
	IN	PRTMP_ADAPTER	pAd)
{
	int	Status;
	DBGPRINT_RAW(RT_DEBUG_ERROR, ("-->RTUSBVenderReset\n"));
	Status = RTUSB_VendorRequest(
		pAd,
		USBD_TRANSFER_DIRECTION_OUT,
		DEVICE_VENDOR_REQUEST_OUT,
		0x01,
		0x1,
		0,
		NULL,
		0);

	DBGPRINT_RAW(RT_DEBUG_ERROR, ("<--RTUSBVenderReset\n"));
	return Status;
}
/*
	========================================================================

	Routine Description: Read various length data from RT2573

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int	RTUSBMultiRead(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned short			Offset,
	OUT	unsigned char*			pData,
	IN	unsigned short			length)
{
	int	Status;

	Status = RTUSB_VendorRequest(
		pAd,
		(USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
		DEVICE_VENDOR_REQUEST_IN,
		0x7,
		0,
		Offset,
		pData,
		length);

	return Status;
}


/*
	========================================================================

	Routine Description: Write various length data to RT USB Wifi device, the maxima length should not large than 65535 bytes.

	Arguments:

	Return Value:

	IRQL =

	Note:
		Use this funciton carefully cause it may not stable in some special USB host controllers.

	========================================================================
*/
int RTUSBMultiWrite_nBytes(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned short			Offset,
	IN	unsigned char*			pData,
	IN	unsigned short			length,
	IN	unsigned short			batchLen)
{
	int Status = STATUS_SUCCESS;
	unsigned short index = Offset, actLen = batchLen, leftLen = length;
	unsigned char* pSrc = pData;


	do
	{
		actLen = (actLen > batchLen ? batchLen : actLen);
		Status = RTUSB_VendorRequest(
			pAd,
			USBD_TRANSFER_DIRECTION_OUT,
			DEVICE_VENDOR_REQUEST_OUT,
			0x6,
			0,
			index,
			pSrc,
			actLen);

		if (Status != STATUS_SUCCESS)
		{
			DBGPRINT(RT_DEBUG_ERROR, ("VendrCmdMultiWrite_nBytes failed!\n"));
			break;
		}

		index += actLen;
		leftLen -= actLen;
		pSrc = pSrc + actLen;
	}while(leftLen > 0);

	return Status;
}


/*
	========================================================================

	Routine Description: Write various length data to RT2573

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int	RTUSBMultiWrite_OneByte(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned short			Offset,
	IN	unsigned char*			pData)
{
	int	Status;

	/* TODO: In 2870, use this funciton carefully cause it's not stable.*/
	Status = RTUSB_VendorRequest(
		pAd,
		USBD_TRANSFER_DIRECTION_OUT,
		DEVICE_VENDOR_REQUEST_OUT,
		0x6,
		0,
		Offset,
		pData,
		1);

	return Status;
}

int	RTUSBMultiWrite(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned short			Offset,
	IN	unsigned char*			pData,
	IN	unsigned short			length,
	IN	unsigned char			bWriteHigh)
{
	int	Status;


	unsigned short          index = 0,Value;
	unsigned char*          pSrc = pData;
	unsigned short          resude = 0;

	resude = length % 2;
	length  += resude;
	do
	{
			Value =(unsigned short)( *pSrc  | (*(pSrc + 1) << 8));
		Status = RTUSBSingleWrite(pAd,Offset + index, Value, bWriteHigh);
            index +=2;
            length -= 2;
            pSrc = pSrc + 2;
        }while(length > 0);

	return Status;
}


int RTUSBSingleWrite(
	IN 	RTMP_ADAPTER 	*pAd,
	IN	unsigned short			Offset,
	IN	unsigned short			Value,
	IN	unsigned char			WriteHigh)
{
	int	Status;

	Status = RTUSB_VendorRequest(
		pAd,
		USBD_TRANSFER_DIRECTION_OUT,
		DEVICE_VENDOR_REQUEST_OUT,
		(WriteHigh == TRUE) ? 0x10 : 0x2,
		Value,
		Offset,
		NULL,
		0);

	return Status;

}


/*
	========================================================================

	Routine Description: Read 32-bit MAC register

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int	RTUSBReadMACRegister(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned short			Offset,
	OUT	unsigned int*			pValue)
{
	int	Status = 0;
	unsigned int		localVal;

	Status = RTUSB_VendorRequest(
		pAd,
		(USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
		DEVICE_VENDOR_REQUEST_IN,
		0x7,
		0,
		Offset,
		&localVal,
		4);

	*pValue = le2cpu32(localVal);


	if (Status != 0)
		*pValue = 0xffffffff;

	return Status;
}


/*
	========================================================================

	Routine Description: Write 32-bit MAC register

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int RTUSBWriteMACRegister(
	IN RTMP_ADAPTER *pAd,
	IN unsigned short Offset,
	IN unsigned int Value,
	IN unsigned char bWriteHigh)
{
	int Status;
	unsigned int localVal;

	localVal = Value;

	/* MT76xx HW has 4 byte alignment constrained */    
	if (IS_MT76xx(pAd)) {   
		Status = RTUSBMultiWrite_nBytes(
		pAd,
		Offset,
		&Value,
		4,
		4);
	} else {
		Status = RTUSBSingleWrite(pAd, Offset, (unsigned short)(localVal & 0xffff), bWriteHigh);
		Status = RTUSBSingleWrite(pAd, Offset + 2, (unsigned short)((localVal & 0xffff0000) >> 16), bWriteHigh);
	}

	return Status;
}

int write_reg(
	RTMP_ADAPTER *ad,
	u32 base,
	u16 offset,
	u32 value)
{
	int ret;
	u8 req;
	u32 io_value;

	if (base == 0x40)
		req = 0x46;

	io_value = cpu2le32(value);

	ret = RTUSB_VendorRequest(ad,
							  USBD_TRANSFER_DIRECTION_OUT,
							  DEVICE_VENDOR_REQUEST_OUT,
							  req,
							  0,
							  offset,
							  &io_value,
							  4);


	if (ret) {
		DBGPRINT(RT_DEBUG_ERROR, ("write reg fail\n"));
		return;
	}
}

int read_reg(
	RTMP_ADAPTER *ad,
	u32 base,
	u16 offset,
	u32 *value)
{
	int ret;
	u8 req;
	u32 io_value;
	
	if (base == 0x40)
		req = 0x47;
	else if (base == 0x41)
		req = 0x7;

	ret = RTUSB_VendorRequest(ad,
							  (USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
							  DEVICE_VENDOR_REQUEST_IN,
							  req,
							  0,
							  offset,
							  &io_value,
							  4);

	*value = le2cpu32(io_value);

	if (ret)
		*value = 0xffffffff;
}

/*
	========================================================================

	Routine Description: Read 8-bit BBP register via firmware

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int	RTUSBReadBBPRegister(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned char			Id,
	IN	unsigned char*			pValue)
{
	BBP_CSR_CFG_STRUC	BbpCsr;
	int i, k, ret;


	RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, ret);
	if (ret != 0)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
		return STATUS_UNSUCCESSFUL;
	}

	for (i=0; i<MAX_BUSY_COUNT; i++)
	{
		RTUSBReadMACRegister(pAd, H2M_BBP_AGENT, &BbpCsr.word);
		if (BbpCsr.field.Busy == BUSY)
			continue;

		BbpCsr.word = 0;
		BbpCsr.field.fRead = 1;
		BbpCsr.field.BBP_RW_MODE = 1;
		BbpCsr.field.Busy = 1;
		BbpCsr.field.RegNum = Id;
		RTUSBWriteMACRegister(pAd, H2M_BBP_AGENT, BbpCsr.word, FALSE);
		AsicSendCommandToMcu(pAd, 0x80, 0xff, 0x0, 0x0, TRUE);
		for (k=0; k<MAX_BUSY_COUNT; k++)
		{
			RTUSBReadMACRegister(pAd, H2M_BBP_AGENT, &BbpCsr.word);
			if (BbpCsr.field.Busy == IDLE)
				break;
		}
		if ((BbpCsr.field.Busy == IDLE) &&
			(BbpCsr.field.RegNum == Id))
		{
			*pValue = (unsigned char)BbpCsr.field.Value;
			break;
		}
	}

	RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
	
	if (BbpCsr.field.Busy == BUSY)
	{
		DBGPRINT_ERR(("BBP read R%d=0x%x fail\n", Id, BbpCsr.word));
		*pValue = pAd->BbpWriteLatch[Id];
		return STATUS_UNSUCCESSFUL;
	}
	return STATUS_SUCCESS;
}


/*
	========================================================================

	Routine Description: Write 8-bit BBP register via firmware

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int RTUSBWriteBBPRegister(
	IN PRTMP_ADAPTER pAd,
	IN unsigned char Id,
	IN unsigned char Value)
{
	BBP_CSR_CFG_STRUC BbpCsr;
	int BusyCnt;
	int ret;

	RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, ret);
	if (ret != 0)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
		return STATUS_UNSUCCESSFUL;
	}

	for (BusyCnt=0; BusyCnt<MAX_BUSY_COUNT; BusyCnt++)
	{
		RTMP_IO_READ32(pAd, H2M_BBP_AGENT, &BbpCsr.word);
		if (BbpCsr.field.Busy == BUSY)
			continue;
		BbpCsr.word = 0;
		BbpCsr.field.fRead = 0;
		BbpCsr.field.BBP_RW_MODE = 1;
		BbpCsr.field.Busy = 1;
		BbpCsr.field.Value = Value;
		BbpCsr.field.RegNum = Id;
		RTMP_IO_WRITE32(pAd, H2M_BBP_AGENT, BbpCsr.word);
		AsicSendCommandToMcu(pAd, 0x80, 0xff, 0x0, 0x0, TRUE);
		pAd->BbpWriteLatch[Id] = Value;
		break;
	}

	RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
	
	if (BusyCnt == MAX_BUSY_COUNT)
	{
		DBGPRINT_ERR(("BBP write R%d=0x%x fail\n", Id, BbpCsr.word));
		return STATUS_UNSUCCESSFUL;
	}
	return STATUS_SUCCESS;
}


/*
	========================================================================

	Routine Description: Write RF register through MAC

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int	RTUSBWriteRFRegister(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned int			Value)
{
	RF_CSR_CFG0_STRUC PhyCsr4;
	unsigned int			i = 0;
	int		status;

	NdisZeroMemory(&PhyCsr4, sizeof(RF_CSR_CFG0_STRUC));

	RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, status);
	if (status != 0) {
		DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", status));
		return STATUS_UNSUCCESSFUL;
	}

	status = STATUS_UNSUCCESSFUL;
	do
	{
		status = RTUSBReadMACRegister(pAd, RF_CSR_CFG0, &PhyCsr4.word);
		if (status >= 0)
		{
		if (!(PhyCsr4.field.Busy))
			break;
		}
		DBGPRINT(RT_DEBUG_TRACE, ("RTUSBWriteRFRegister(RF_CSR_CFG0):retry count=%d!\n", i));
		i++;
	}
	while ((i < RETRY_LIMIT) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)));

	if ((i == RETRY_LIMIT) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
	{
		DBGPRINT_RAW(RT_DEBUG_ERROR, ("Retry count exhausted or device removed!!!\n"));
		goto done;
	}

	RTUSBWriteMACRegister(pAd, RF_CSR_CFG0, Value, FALSE);
	status = STATUS_SUCCESS;

done:
	RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
	
	return status;
}


/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int RTUSBReadEEPROM(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned short			Offset,
	OUT	unsigned char*			pData,
	IN	unsigned short			length)
{
	int	Status = STATUS_SUCCESS;

		Status = RTUSB_VendorRequest(
			pAd,
			(USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
			DEVICE_VENDOR_REQUEST_IN,
			0x9,
			0,
			Offset,
			pData,
			length);

	return Status;
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int RTUSBWriteEEPROM(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned short			Offset,
	IN	unsigned char*			pData,
	IN	unsigned short			length)
{
	int Status = STATUS_SUCCESS;
	unsigned short Value;

	Status = RTUSB_VendorRequest(
				pAd,
				USBD_TRANSFER_DIRECTION_OUT,
				DEVICE_VENDOR_REQUEST_OUT,
				0x8,
				0,
				Offset,
				pData,
				length);

	return Status;
}


int RTUSBReadEEPROM16(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned short			offset,
	OUT	unsigned short*			pData)
{
	int status;
	unsigned short  localData;

	status = RTUSBReadEEPROM(pAd, offset, (unsigned char*)(&localData), 2);
	if (status == STATUS_SUCCESS)
		*pData = le2cpu16(localData);

	return status;

}

int RTUSBWriteEEPROM16(
	IN RTMP_ADAPTER *pAd,
	IN unsigned short offset,
	IN unsigned short value)
{
	unsigned short tmpVal;

	tmpVal = cpu2le16(value);
	return RTUSBWriteEEPROM(pAd, offset, (unsigned char*)&(tmpVal), 2);
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
void RTUSBPutToSleep(
	IN	PRTMP_ADAPTER	pAd)
{
	unsigned int		value;

	/* Timeout 0x40 x 50us*/
	value = (SLEEPCID<<16)+(OWNERMCU<<24)+ (0x40<<8)+1;
	RTUSBWriteMACRegister(pAd, 0x7010, value, FALSE);
	RTUSBWriteMACRegister(pAd, 0x404, 0x30, FALSE);
	/*RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS);			*/
	DBGPRINT_RAW(RT_DEBUG_ERROR, ("Sleep Mailbox testvalue %x\n", value));

}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int RTUSBWakeUp(
	IN	PRTMP_ADAPTER	pAd)
{
	int	Status;

	Status = RTUSB_VendorRequest(
		pAd,
		USBD_TRANSFER_DIRECTION_OUT,
		DEVICE_VENDOR_REQUEST_OUT,
		0x01,
		0x09,
		0,
		NULL,
		0);

	return Status;
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NDIS_STATUS	RTUSBEnqueueCmdFromNdis(
	IN	PRTMP_ADAPTER	pAd,
	IN	NDIS_OID		Oid,
	IN	unsigned char			SetInformation,
	IN	void*			pInformationBuffer,
	IN	unsigned int			InformationBufferLength)
{
	NDIS_STATUS	status;
	PCmdQElmt	cmdqelmt = NULL;
	RTMP_OS_TASK	*pTask = &pAd->cmdQTask;


	RTMP_OS_TASK_LEGALITY(pTask)
		;
	else
		return (NDIS_STATUS_RESOURCES);

	status = os_alloc_mem(pAd, (unsigned char* *)(&cmdqelmt), sizeof(CmdQElmt));
	if ((status != NDIS_STATUS_SUCCESS) || (cmdqelmt == NULL))
		return (NDIS_STATUS_RESOURCES);

		cmdqelmt->buffer = NULL;
		if (pInformationBuffer != NULL)
		{
			status = os_alloc_mem(pAd, (unsigned char* *)&cmdqelmt->buffer, InformationBufferLength);
			if ((status != NDIS_STATUS_SUCCESS) || (cmdqelmt->buffer == NULL))
			{
/*				kfree(cmdqelmt);*/
				os_free_mem(NULL, cmdqelmt);
				return (NDIS_STATUS_RESOURCES);
			}
			else
			{
				NdisMoveMemory(cmdqelmt->buffer, pInformationBuffer, InformationBufferLength);
				cmdqelmt->bufferlength = InformationBufferLength;
			}
		}
		else
			cmdqelmt->bufferlength = 0;

	cmdqelmt->command = Oid;
	cmdqelmt->CmdFromNdis = TRUE;
	if (SetInformation == TRUE)
		cmdqelmt->SetOperation = TRUE;
	else
		cmdqelmt->SetOperation = FALSE;

	NdisAcquireSpinLock(&pAd->CmdQLock);
	if (pAd->CmdQ.CmdQState & RTMP_TASK_CAN_DO_INSERT)
	{
		EnqueueCmd((&pAd->CmdQ), cmdqelmt);
		status = NDIS_STATUS_SUCCESS;
	}
	else
	{
		status = NDIS_STATUS_FAILURE;
	}
	NdisReleaseSpinLock(&pAd->CmdQLock);

	if (status == NDIS_STATUS_FAILURE)
	{
		if (cmdqelmt->buffer)
			os_free_mem(pAd, cmdqelmt->buffer);
		os_free_mem(pAd, cmdqelmt);
	}
	else
	RTCMDUp(&pAd->cmdQTask);


    return(NDIS_STATUS_SUCCESS);
}


/*
    ========================================================================
 	Routine Description:
		RTUSB_VendorRequest - Builds a ralink specific request, sends it off to USB endpoint zero and waits for completion

	Arguments:
		@pAd:
	  	@TransferFlags:
	  	@RequestType: USB message request type value
	  	@Request: USB message request value
	  	@Value: USB message value
	  	@Index: USB message index value
	  	@TransferBuffer: USB data to be sent
	  	@TransferBufferLength: Lengths in bytes of the data to be sent

	Context: ! in atomic context

	Return Value:
		NDIS_STATUS_SUCCESS
		NDIS_STATUS_FAILURE

	Note:
		This function sends a simple control message to endpoint zero
		and waits for the message to complete, or CONTROL_TIMEOUT_JIFFIES timeout.
		Because it is synchronous transfer, so don't use this function within an atomic context,
		otherwise system will hang, do be careful.

		TransferBuffer may located in stack region which may not in DMA'able region in some embedded platforms,
		so need to copy TransferBuffer to UsbVendorReqBuf allocated by kmalloc to do DMA transfer.
		Use UsbVendorReq_semaphore to protect this region which may be accessed by multi task.
		Normally, coherent issue is resloved by low-level HC driver, so do not flush this zone by RTUSB_VendorRequest.

	========================================================================
*/
int    RTUSB_VendorRequest(
	IN	PRTMP_ADAPTER	pAd,
	IN	unsigned int			TransferFlags,
	IN	unsigned char			RequestType,
	IN	unsigned char			Request,
	IN	unsigned short			Value,
	IN	unsigned short			Index,
	IN	void*			TransferBuffer,
	IN	unsigned int			TransferBufferLength)
{
	int				RET = 0;
	POS_COOKIE		pObj = (POS_COOKIE) pAd->OS_Cookie;

	if(in_interrupt())
	{
		DBGPRINT(RT_DEBUG_ERROR, ("BUG: RTUSB_VendorRequest is called from invalid context\n"));
		return NDIS_STATUS_FAILURE;
	}

	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)) 
	{
		DBGPRINT(RT_DEBUG_ERROR, ("WIFI device has been disconnected\n"));
		return NDIS_STATUS_FAILURE;
	} 
	else if (RTMP_TEST_PSFLAG(pAd, fRTMP_PS_MCU_SLEEP))
	{
		DBGPRINT(RT_DEBUG_ERROR, ("MCU has entered sleep mode\n"));
		return NDIS_STATUS_FAILURE;
	}
	else
	{

		int RetryCount = 0; /* RTUSB_CONTROL_MSG retry counts*/
		ASSERT(TransferBufferLength <MAX_PARAM_BUFFER_SIZE);

		RTMP_SEM_EVENT_WAIT(&(pAd->UsbVendorReq_semaphore), RET);
		if (RET != 0)
		{
			DBGPRINT(RT_DEBUG_ERROR, ("UsbVendorReq_semaphore get failed\n"));
			return NDIS_STATUS_FAILURE;
		}

		if ((TransferBufferLength > 0) && (RequestType == DEVICE_VENDOR_REQUEST_OUT))
			NdisMoveMemory(pAd->UsbVendorReqBuf, TransferBuffer, TransferBufferLength);

		do {
				RTUSB_CONTROL_MSG(pObj->pUsb_Dev, 0, Request, RequestType, Value, Index, pAd->UsbVendorReqBuf, TransferBufferLength, CONTROL_TIMEOUT_JIFFIES, RET);
				
			if (RET < 0 ) {
				DBGPRINT(RT_DEBUG_OFF, ("#\n"));
				if (RET == RTMP_USB_CONTROL_MSG_ENODEV)
				{
					RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
					break;
				}
				RetryCount++;
				RTMPusecDelay(5000); /* wait for 5ms*/
			}
		} while((RET < 0 ) && (RetryCount < MAX_VENDOR_REQ_RETRY_COUNT));

	  	if ( (!(RET < 0)) && (TransferBufferLength > 0) && (RequestType == DEVICE_VENDOR_REQUEST_IN))
			NdisMoveMemory(TransferBuffer, pAd->UsbVendorReqBuf, TransferBufferLength);

	  	RTMP_SEM_EVENT_UP(&(pAd->UsbVendorReq_semaphore));

        	if (RET < 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("RTUSB_VendorRequest failed(%d),TxFlags=0x%x, ReqType=%s, Req=0x%x, Idx=0x%x,pAd->Flags=0x%lx\n",
						RET, TransferFlags, (RequestType == DEVICE_VENDOR_REQUEST_OUT? "OUT" : "IN"), Request, Index, pAd->Flags));
			if (Request == 0x2)
				DBGPRINT(RT_DEBUG_ERROR, ("\tRequest Value=0x%04x!\n", Value));

			if ((!TransferBuffer) && (TransferBufferLength > 0))
				hex_dump("Failed TransferBuffer value", TransferBuffer, TransferBufferLength);

			if (RET == RTMP_USB_CONTROL_MSG_ENODEV)
					RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);

		}

	}

	if (RET < 0)
		return NDIS_STATUS_FAILURE;
	else
		return NDIS_STATUS_SUCCESS;

}


/*
	========================================================================

	Routine Description:
	  Creates an IRP to submite an IOCTL_INTERNAL_USB_RESET_PORT
	  synchronously. Callers of this function must be running at
	  PASSIVE LEVEL.

	Arguments:

	Return Value:

	Note:

	========================================================================
*/
int RTUSB_ResetDevice(
	IN	PRTMP_ADAPTER	pAd)
{
	int		Status = TRUE;

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("--->USB_ResetDevice\n"));
	/*RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS);*/
	return Status;
}


int CheckGPIOHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{

#ifdef RALINK_ATE
		if (ATE_ON(pAd))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("The driver is in ATE mode now\n"));
			return NDIS_STATUS_SUCCESS;
		}
#endif /* RALINK_ATE */

#ifdef CONFIG_STA_SUPPORT

		IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		{
			unsigned int data;
			/* Read GPIO pin2 as Hardware controlled radio state*/

			RTUSBReadMACRegister( pAd, GPIO_CTRL_CFG, &data);

			if (data & 0x04)
			{
				pAd->StaCfg.bHwRadio = TRUE;
			}
			else
			{
				pAd->StaCfg.bHwRadio = FALSE;
			}

			if (pAd->StaCfg.bRadio != (pAd->StaCfg.bHwRadio && pAd->StaCfg.bSwRadio))
			{
				pAd->StaCfg.bRadio = (pAd->StaCfg.bHwRadio && pAd->StaCfg.bSwRadio);
				if (pAd->StaCfg.bRadio == TRUE)
				{
					DBGPRINT_RAW(RT_DEBUG_ERROR, ("!!! Radio On !!!\n"));

					MlmeRadioOn(pAd);
					/* Update extra information                                                                                                             */
					pAd->ExtraInfo = EXTRA_INFO_CLEAR;
				}
				else
				{
					DBGPRINT_RAW(RT_DEBUG_ERROR, ("!!! Radio Off !!!\n"));

					MlmeRadioOff(pAd);
					/* Update extra information                                                                                                             */
					pAd->ExtraInfo = HW_RADIO_OFF;
				}
			}
		} /* end IF_DEV_CONFIG_OPMODE_ON_STA*/

#endif /* CONFIG_STA_SUPPORT */

	return NDIS_STATUS_SUCCESS;
}


static int ResetBulkOutHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{

	int MACValue = 0;
	unsigned char Index = 0;
	int ret=0;
	PHT_TX_CONTEXT	pHTTXContext;
/*	RTMP_TX_RING *pTxRing;*/
	unsigned long IrqFlags;

	DBGPRINT(RT_DEBUG_TRACE, ("CMDTHREAD_RESET_BULK_OUT(ResetPipeid=0x%0x)===>\n", pAd->bulkResetPipeid));

	/* All transfers must be aborted or cancelled before attempting to reset the pipe.						*/
	/*RTUSBCancelPendingBulkOutIRP(pAd);*/
	/* Wait 10ms to let previous packet that are already in HW FIFO to clear. by MAXLEE 12-25-2007*/
	do
	{
		if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			break;

		RTUSBReadMACRegister(pAd, TXRXQ_PCNT, &MACValue);
		if ((MACValue & 0xf00000/*0x800000*/) == 0)
			break;

		Index++;
		RTMPusecDelay(10000);
	}while(Index < 100);

	RTUSBReadMACRegister(pAd, USB_DMA_CFG, &MACValue);

	/* 2nd, to prevent Read Register error, we check the validity.*/
	if ((MACValue & 0xc00000) == 0)
		RTUSBReadMACRegister(pAd, USB_DMA_CFG, &MACValue);

	/* 3rd, to prevent Read Register error, we check the validity.*/
	if ((MACValue & 0xc00000) == 0)
		RTUSBReadMACRegister(pAd, USB_DMA_CFG, &MACValue);

	MACValue |= 0x80000;
	RTUSBWriteMACRegister(pAd, USB_DMA_CFG, MACValue, FALSE);

	/* Wait 1ms to prevent next URB to bulkout before HW reset. by MAXLEE 12-25-2007*/
	RTMPusecDelay(1000);

	MACValue &= (~0x80000);
	RTUSBWriteMACRegister(pAd, USB_DMA_CFG, MACValue, FALSE);
	DBGPRINT(RT_DEBUG_TRACE, ("\tSet 0x2a0 bit19. Clear USB DMA TX path\n"));

	/* Wait 5ms to prevent next URB to bulkout before HW reset. by MAXLEE 12-25-2007*/
	/*RTMPusecDelay(5000);*/

	if ((pAd->bulkResetPipeid & BULKOUT_MGMT_RESET_FLAG) == BULKOUT_MGMT_RESET_FLAG)
	{
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

		if (pAd->MgmtRing.TxSwFreeIdx < MGMT_RING_SIZE /* pMLMEContext->bWaitingBulkOut == TRUE */)
			RTUSB_SET_BULK_FLAG(pAd, fRTUSB_BULK_OUT_MLME);

		RTUSBKickBulkOut(pAd);
		DBGPRINT(RT_DEBUG_TRACE, ("\tTX MGMT RECOVER Done!\n"));
	}
	else
	{
		pHTTXContext = &(pAd->TxContext[pAd->bulkResetPipeid]);

		/*NdisAcquireSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]);*/
		RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);
		if ( pAd->BulkOutPending[pAd->bulkResetPipeid] == FALSE)
		{
			pAd->BulkOutPending[pAd->bulkResetPipeid] = TRUE;
			pHTTXContext->IRPPending = TRUE;
			pAd->watchDogTxPendingCnt[pAd->bulkResetPipeid] = 1;

			/* no matter what, clean the flag*/
			RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

			/*NdisReleaseSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]);*/
			RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

#ifdef RALINK_ATE
			if (ATE_ON(pAd))
				ret = ATEResetBulkOut(pAd);
			else
#endif /* RALINK_ATE */
			{
				RTUSBInitHTTxDesc(pAd, pHTTXContext, pAd->bulkResetPipeid,
													pHTTXContext->BulkOutSize,
													RtmpUsbBulkOutDataPacketComplete);

				if ((ret = RTUSB_SUBMIT_URB(pHTTXContext->pUrb))!=0)
				{
						RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);
						pAd->BulkOutPending[pAd->bulkResetPipeid] = FALSE;
						pHTTXContext->IRPPending = FALSE;
						pAd->watchDogTxPendingCnt[pAd->bulkResetPipeid] = 0;
						RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

						DBGPRINT(RT_DEBUG_ERROR, ("CMDTHREAD_RESET_BULK_OUT:Submit Tx URB failed %d\n", ret));
				}
				else
				{
						RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

						DBGPRINT(RT_DEBUG_TRACE,("\tCMDTHREAD_RESET_BULK_OUT: TxContext[%d]:CWPos=%ld, NBPos=%ld, ENBPos=%ld, bCopy=%d, pending=%d!\n",
											pAd->bulkResetPipeid, pHTTXContext->CurWritePosition, pHTTXContext->NextBulkOutPosition,
											pHTTXContext->ENextBulkOutPosition, pHTTXContext->bCopySavePad,
											pAd->BulkOutPending[pAd->bulkResetPipeid]));
						DBGPRINT(RT_DEBUG_TRACE,("\t\tBulkOut Req=0x%lx, Complete=0x%lx, Other=0x%lx\n",
											pAd->BulkOutReq, pAd->BulkOutComplete, pAd->BulkOutCompleteOther));

						RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

						DBGPRINT(RT_DEBUG_TRACE, ("\tCMDTHREAD_RESET_BULK_OUT: Submit Tx DATA URB for failed BulkReq(0x%lx) Done, status=%d!\n",
											pAd->bulkResetReq[pAd->bulkResetPipeid],
											RTMP_USB_URB_STATUS_GET(pHTTXContext->pUrb)));
				}
			}
		}
		else
		{
			/*NdisReleaseSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]);*/
			/*RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);*/

			DBGPRINT(RT_DEBUG_ERROR, ("CmdThread : TX DATA RECOVER FAIL for BulkReq(0x%lx) because BulkOutPending[%d] is TRUE!\n",
								pAd->bulkResetReq[pAd->bulkResetPipeid], pAd->bulkResetPipeid));

			if (pAd->bulkResetPipeid == 0)
			{
				unsigned char	pendingContext = 0;
				PHT_TX_CONTEXT pHTTXContext = (PHT_TX_CONTEXT)(&pAd->TxContext[pAd->bulkResetPipeid ]);
				PTX_CONTEXT pMLMEContext = (PTX_CONTEXT)(pAd->MgmtRing.Cell[pAd->MgmtRing.TxDmaIdx].AllocVa);
				PTX_CONTEXT pNULLContext = (PTX_CONTEXT)(&pAd->PsPollContext);
				PTX_CONTEXT pPsPollContext = (PTX_CONTEXT)(&pAd->NullContext);

				if (pHTTXContext->IRPPending)
					pendingContext |= 1;
				else if (pMLMEContext->IRPPending)
					pendingContext |= 2;
				else if (pNULLContext->IRPPending)
					pendingContext |= 4;
				else if (pPsPollContext->IRPPending)
					pendingContext |= 8;
				else
					pendingContext = 0;

				DBGPRINT(RT_DEBUG_ERROR, ("\tTX Occupied by %d!\n", pendingContext));
			}

			/* no matter what, clean the flag*/
			RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

			RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

			RTUSB_SET_BULK_FLAG(pAd, (fRTUSB_BULK_OUT_DATA_NORMAL << pAd->bulkResetPipeid));
		}

		RTMPDeQueuePacket(pAd, FALSE, NUM_OF_TX_RING, MAX_TX_PROCESS);
		/*RTUSBKickBulkOut(pAd);*/
	}

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_OUT<===\n"));
	return NDIS_STATUS_SUCCESS;


}


/* All transfers must be aborted or cancelled before attempting to reset the pipe.*/
static int ResetBulkInHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	unsigned int MACValue;
	int ntStatus;

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_IN === >\n"));

#ifdef CONFIG_STA_SUPPORT
	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
	{
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKIN_RESET);
		return NDIS_STATUS_SUCCESS;
	}
#endif /* CONFIG_STA_SUPPORT */

#ifdef RALINK_ATE
	if (ATE_ON(pAd))
		ATEResetBulkIn(pAd);
	else
#endif /* RALINK_ATE */
	{
		/*while ((atomic_read(&pAd->PendingRx) > 0) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) */
		if((pAd->PendingRx > 0) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
		{
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("BulkIn IRP Pending!!!\n"));
			RTUSBCancelPendingBulkInIRP(pAd);
			RTMPusecDelay(100000);
			pAd->PendingRx = 0;
		}
	}

	/* Wait 10ms before reading register.*/
	RTMPusecDelay(10000);
	ntStatus = RTUSBReadMACRegister(pAd, MAC_CSR0, &MACValue);

	/* It must be removed. Or ATE will have no RX success. */ 
	if ((NT_SUCCESS(ntStatus) == TRUE) &&
				(!(RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_RADIO_OFF |
												fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST)))))
	{
		unsigned char	i;

		if (RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_RADIO_OFF |
									fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST)))
			return NDIS_STATUS_SUCCESS;

		pAd->NextRxBulkInPosition = pAd->RxContext[pAd->NextRxBulkInIndex].BulkInOffset;

		DBGPRINT(RT_DEBUG_TRACE, ("BULK_IN_RESET: NBIIdx=0x%x,NBIRIdx=0x%x, BIRPos=0x%lx. BIReq=x%lx, BIComplete=0x%lx, BICFail0x%lx\n",
					pAd->NextRxBulkInIndex,  pAd->NextRxBulkInReadIndex, pAd->NextRxBulkInPosition, pAd->BulkInReq, pAd->BulkInComplete, pAd->BulkInCompleteFail));

		for (i = 0; i < RX_RING_SIZE; i++)
		{
 			DBGPRINT(RT_DEBUG_TRACE, ("\tRxContext[%d]: IRPPending=%d, InUse=%d, Readable=%d!\n"
							, i, pAd->RxContext[i].IRPPending, pAd->RxContext[i].InUse, pAd->RxContext[i].Readable));
		}

		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKIN_RESET);

		for (i = 0; i < pAd->CommonCfg.NumOfBulkInIRP; i++)
		{
			/*RTUSBBulkReceive(pAd);*/
			PRX_CONTEXT		pRxContext;
			PURB			pUrb;
			int				ret = 0;
			unsigned long	IrqFlags;

			RTMP_IRQ_LOCK(&pAd->BulkInLock, IrqFlags);
			pRxContext = &(pAd->RxContext[pAd->NextRxBulkInIndex]);

			if ((pAd->PendingRx > 0) || (pRxContext->Readable == TRUE) || (pRxContext->InUse == TRUE))
			{
				RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);
				return NDIS_STATUS_SUCCESS;
			}

			pRxContext->InUse = TRUE;
			pRxContext->IRPPending = TRUE;
			pAd->PendingRx++;
			pAd->BulkInReq++;
			RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);

			/* Init Rx context descriptor*/
			RTUSBInitRxDesc(pAd, pRxContext);
			pUrb = pRxContext->pUrb;
			if ((ret = RTUSB_SUBMIT_URB(pUrb))!=0)
			{	/* fail*/
				RTMP_IRQ_LOCK(&pAd->BulkInLock, IrqFlags);
				pRxContext->InUse = FALSE;
				pRxContext->IRPPending = FALSE;
				pAd->PendingRx--;
				pAd->BulkInReq--;
				RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);
				DBGPRINT(RT_DEBUG_ERROR, ("CMDTHREAD_RESET_BULK_IN: Submit Rx URB failed(%d), status=%d\n", ret, RTMP_USB_URB_STATUS_GET(pUrb)));
			}
			else
			{	/* success*/
				/*DBGPRINT(RT_DEBUG_TRACE, ("BIDone, Pend=%d,BIIdx=%d,BIRIdx=%d!\n", */
				/*							pAd->PendingRx, pAd->NextRxBulkInIndex, pAd->NextRxBulkInReadIndex));*/
				DBGPRINT_RAW(RT_DEBUG_TRACE, ("CMDTHREAD_RESET_BULK_IN: Submit Rx URB Done, status=%d!\n", RTMP_USB_URB_STATUS_GET(pUrb)));
				ASSERT((pRxContext->InUse == pRxContext->IRPPending));
			}
		}

	}
	else
	{
		/* Card must be removed*/
		if (NT_SUCCESS(ntStatus) != TRUE)
		{
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("CMDTHREAD_RESET_BULK_IN: Read Register Failed!Card must be removed!!\n\n"));
		}
		else
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("CMDTHREAD_RESET_BULK_IN: Cannot do bulk in because flags(0x%lx) on !\n", pAd->Flags));
	}

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_IN <===\n"));
	return NDIS_STATUS_SUCCESS;
}


static int SetAsicWcidHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RT_SET_ASIC_WCID	SetAsicWcid;
	unsigned short		offset;
	unsigned int		MACValue, MACRValue = 0;
	SetAsicWcid = *((PRT_SET_ASIC_WCID)(CMDQelmt->buffer));

	if (SetAsicWcid.WCID >= MAX_LEN_OF_MAC_TABLE)
		return NDIS_STATUS_FAILURE;

	offset = MAC_WCID_BASE + ((unsigned char)SetAsicWcid.WCID)*HW_WCID_ENTRY_SIZE;

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_SET_ASIC_WCID : WCID = %ld, SetTid  = %lx, DeleteTid = %lx.\n",
						SetAsicWcid.WCID, SetAsicWcid.SetTid, SetAsicWcid.DeleteTid));

	MACValue = (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[3]<<24)+(pAd->MacTab.Content[SetAsicWcid.WCID].Addr[2]<<16)+(pAd->MacTab.Content[SetAsicWcid.WCID].Addr[1]<<8)+(pAd->MacTab.Content[SetAsicWcid.WCID].Addr[0]);

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("1-MACValue= %x,\n", MACValue));
	RTUSBWriteMACRegister(pAd, offset, MACValue, FALSE);
	/* Read bitmask*/
	RTUSBReadMACRegister(pAd, offset+4, &MACRValue);
	if ( SetAsicWcid.DeleteTid != 0xffffffff)
		MACRValue &= (~SetAsicWcid.DeleteTid);
	if (SetAsicWcid.SetTid != 0xffffffff)
		MACRValue |= (SetAsicWcid.SetTid);

	MACRValue &= 0xffff0000;
	MACValue = (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[5]<<8)+pAd->MacTab.Content[SetAsicWcid.WCID].Addr[4];
	MACValue |= MACRValue;
	RTUSBWriteMACRegister(pAd, offset+4, MACValue, FALSE);

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("2-MACValue= %x,\n", MACValue));

	return NDIS_STATUS_SUCCESS;
}

static int DelAsicWcidHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RT_SET_ASIC_WCID SetAsicWcid;
	SetAsicWcid = *((PRT_SET_ASIC_WCID)(CMDQelmt->buffer));
        
	if (SetAsicWcid.WCID >= MAX_LEN_OF_MAC_TABLE)
		return NDIS_STATUS_FAILURE;
        
        AsicDelWcidTab(pAd, (unsigned char)SetAsicWcid.WCID);

        return NDIS_STATUS_SUCCESS;
}

static int SetWcidSecInfoHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_SEC_INFO pInfo;

	pInfo = (PRT_ASIC_WCID_SEC_INFO)CMDQelmt->buffer;
	RTMPSetWcidSecurityInfo(pAd,
							 pInfo->BssIdx,
							 pInfo->KeyIdx,
							 pInfo->CipherAlg,
							 pInfo->Wcid,
							 pInfo->KeyTabFlag);

	return NDIS_STATUS_SUCCESS;
}


static int SetAsicWcidIVEIVHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_IVEIV_ENTRY pInfo;

	pInfo = (PRT_ASIC_WCID_IVEIV_ENTRY)CMDQelmt->buffer;
	AsicUpdateWCIDIVEIV(pAd,
						  pInfo->Wcid,
						  pInfo->Iv,
						  pInfo->Eiv);

	return NDIS_STATUS_SUCCESS;
}


static int SetAsicWcidAttrHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_ATTR_ENTRY pInfo;

	pInfo = (PRT_ASIC_WCID_ATTR_ENTRY)CMDQelmt->buffer;
	AsicUpdateWcidAttributeEntry(pAd,
								  pInfo->BssIdx,
								  pInfo->KeyIdx,
								  pInfo->CipherAlg,
								  pInfo->Wcid,
								  pInfo->KeyTabFlag);

	return NDIS_STATUS_SUCCESS;
}

static int SETAsicSharedKeyHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_SHARED_KEY pInfo;

	pInfo = (PRT_ASIC_SHARED_KEY)CMDQelmt->buffer;
	AsicAddSharedKeyEntry(pAd,
						       pInfo->BssIndex,
							pInfo->KeyIdx,
							&pInfo->CipherKey);

	return NDIS_STATUS_SUCCESS;
}

static int SetAsicPairwiseKeyHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_PAIRWISE_KEY pInfo;

	pInfo = (PRT_ASIC_PAIRWISE_KEY)CMDQelmt->buffer;
	AsicAddPairwiseKeyEntry(pAd,
							 pInfo->WCID,
							 &pInfo->CipherKey);

	return NDIS_STATUS_SUCCESS;
}

#ifdef CONFIG_STA_SUPPORT
static int SetPortSecuredHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	STA_PORT_SECURED(pAd);
	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_STA_SUPPORT */


static int RemovePairwiseKeyHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	unsigned char Wcid = *((unsigned char*)(CMDQelmt->buffer));

	AsicRemovePairwiseKeyEntry(pAd, Wcid);
	return NDIS_STATUS_SUCCESS;
}


static int SetClientMACEntryHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_SET_ASIC_WCID pInfo;

	pInfo = (PRT_SET_ASIC_WCID)CMDQelmt->buffer;
	AsicUpdateRxWCIDTable(pAd, pInfo->WCID, pInfo->Addr);
	return NDIS_STATUS_SUCCESS;
}


static int UpdateProtectHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_PROTECT_INFO pAsicProtectInfo;

	pAsicProtectInfo = (PRT_ASIC_PROTECT_INFO)CMDQelmt->buffer;
	AsicUpdateProtect(pAd, pAsicProtectInfo->OperationMode, pAsicProtectInfo->SetMask,
							pAsicProtectInfo->bDisableBGProtect, pAsicProtectInfo->bNonGFExist);
	
	return NDIS_STATUS_SUCCESS;
}






#ifdef CONFIG_STA_SUPPORT
static int SetPSMBitHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		unsigned short *pPsm = (unsigned short *)CMDQelmt->buffer;
		MlmeSetPsmBit(pAd, *pPsm);
	}

	return NDIS_STATUS_SUCCESS;
}


static int ForceWakeUpHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		AsicForceWakeup(pAd, TRUE);

	return NDIS_STATUS_SUCCESS;
}


static int ForceSleepAutoWakeupHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	unsigned short  TbttNumToNextWakeUp;
	unsigned short  NextDtim = pAd->StaCfg.DtimPeriod;
	unsigned long   Now;

	NdisGetSystemUpTime(&Now);
	NextDtim -= (unsigned short)(Now - pAd->StaCfg.LastBeaconRxTime)/pAd->CommonCfg.BeaconPeriod;

	TbttNumToNextWakeUp = pAd->StaCfg.DefaultListenCount;
	if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM) && (TbttNumToNextWakeUp > NextDtim))
		TbttNumToNextWakeUp = NextDtim;

	RTMP_SET_PSM_BIT(pAd, PWR_SAVE);

	/* if WMM-APSD is failed, try to disable following line*/
	AsicSleepThenAutoWakeup(pAd, TbttNumToNextWakeUp);

	return NDIS_STATUS_SUCCESS;
}


int QkeriodicExecutHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	StaQuickResponeForRateUpExec(NULL, pAd, NULL, NULL);
	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_STA_SUPPORT*/




#ifdef LED_CONTROL_SUPPORT
static int SetLEDStatusHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	unsigned char LEDStatus = *((unsigned char*)(CMDQelmt->buffer));

	RTMPSetLEDStatus(pAd, LEDStatus);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: CMDTHREAD_SET_LED_STATUS (LEDStatus = %d)\n",
								__FUNCTION__, LEDStatus));

	return NDIS_STATUS_SUCCESS;
}
#endif /* LED_CONTROL_SUPPORT */





#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
static int RegHintHdlr (IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_CRDA_REG_HINT(pAd, CMDQelmt->buffer, CMDQelmt->bufferlength);
	return NDIS_STATUS_SUCCESS;
}

static int RegHint11DHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_CRDA_REG_HINT11D(pAd, CMDQelmt->buffer, CMDQelmt->bufferlength);
	return NDIS_STATUS_SUCCESS;
}

static int RT_Mac80211_ScanEnd(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_SCAN_END(pAd, FALSE);
	return NDIS_STATUS_SUCCESS;
}

static int RT_Mac80211_ConnResultInfom(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_CONN_RESULT_INFORM(pAd,
								pAd->MlmeAux.Bssid,
								CMDQelmt->buffer, CMDQelmt->bufferlength,
								CMDQelmt->buffer, CMDQelmt->bufferlength,
								1);
	return NDIS_STATUS_SUCCESS;
}
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */



#ifdef STREAM_MODE_SUPPORT
static int UpdateTXChainAddress(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	AsicUpdateTxChainAddress(pAd, CMDQelmt->buffer);
	return NDIS_STATUS_SUCCESS;
}
#endif /* STREAM_MODE_SUPPORT */

extern MSG_EVENT_HANDLER msg_event_handler_tb[];

static int CmdRspEventCallback(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RXFCE_INFO_CMD *pFceInfo = CMDQelmt->buffer;

	(*msg_event_handler_tb[pFceInfo->evt_type])(pAd, CMDQelmt->buffer, 
												CMDQelmt->bufferlength);
	
	return NDIS_STATUS_SUCCESS;
}


typedef int (*CMDHdlr)(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt);

static CMDHdlr CMDHdlrTable[] = {
	ResetBulkOutHdlr,				/* CMDTHREAD_RESET_BULK_OUT*/
	ResetBulkInHdlr,					/* CMDTHREAD_RESET_BULK_IN*/
	CheckGPIOHdlr,					/* CMDTHREAD_CHECK_GPIO	*/
	SetAsicWcidHdlr,					/* CMDTHREAD_SET_ASIC_WCID*/
	DelAsicWcidHdlr,					/* CMDTHREAD_DEL_ASIC_WCID*/
	SetClientMACEntryHdlr,			/* CMDTHREAD_SET_CLIENT_MAC_ENTRY*/

#ifdef CONFIG_STA_SUPPORT
	SetPSMBitHdlr,					/* CMDTHREAD_SET_PSM_BIT*/
	ForceWakeUpHdlr,				/* CMDTHREAD_FORCE_WAKE_UP*/
	ForceSleepAutoWakeupHdlr,		/* CMDTHREAD_FORCE_SLEEP_AUTO_WAKEUP*/
	QkeriodicExecutHdlr,				/* CMDTHREAD_QKERIODIC_EXECUT*/
#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* CONFIG_STA_SUPPORT */

	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,

#ifdef LED_CONTROL_SUPPORT
	SetLEDStatusHdlr,			/* CMDTHREAD_SET_LED_STATUS*/
#else
    NULL,
#endif /* LED_CONTROL_SUPPORT */

	NULL,

	/* Security related */
	SetWcidSecInfoHdlr,				/* CMDTHREAD_SET_WCID_SEC_INFO*/
	SetAsicWcidIVEIVHdlr,			/* CMDTHREAD_SET_ASIC_WCID_IVEIV*/
	SetAsicWcidAttrHdlr,				/* CMDTHREAD_SET_ASIC_WCID_ATTR*/
	SETAsicSharedKeyHdlr,			/* CMDTHREAD_SET_ASIC_SHARED_KEY*/
	SetAsicPairwiseKeyHdlr,			/* CMDTHREAD_SET_ASIC_PAIRWISE_KEY*/
	RemovePairwiseKeyHdlr,			/* CMDTHREAD_REMOVE_PAIRWISE_KEY*/

#ifdef CONFIG_STA_SUPPORT
	SetPortSecuredHdlr,				/* CMDTHREAD_SET_PORT_SECURED*/
#else
	NULL,
#endif /* CONFIG_STA_SUPPORT */

	NULL,

	UpdateProtectHdlr,				/* CMDTHREAD_UPDATE_PROTECT*/


#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
	RegHintHdlr,
	RegHint11DHdlr,
	RT_Mac80211_ScanEnd,
	RT_Mac80211_ConnResultInfom,
#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* RT_CFG80211_SUPPORT */

#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* LINUX */

	NULL,

	NULL,

#ifdef STREAM_MODE_SUPPORT
	UpdateTXChainAddress, /* CMDTHREAD_UPDATE_TX_CHAIN_ADDRESS */
#else
	NULL,
#endif
	CmdRspEventCallback, /* CMDTHREAD_RESPONSE_EVENT_CALLBACK */
};


static inline unsigned char ValidCMD(IN PCmdQElmt CMDQelmt)
{
	short CMDIndex = CMDQelmt->command - CMDTHREAD_FIRST_CMD_ID;
	unsigned short CMDHdlrTableLength= sizeof(CMDHdlrTable) / sizeof(CMDHdlr);

	if ( (CMDIndex >= 0) && (CMDIndex < CMDHdlrTableLength))
	{
		if (CMDHdlrTable[CMDIndex] > 0)
			return TRUE;
		else
		{
			DBGPRINT(RT_DEBUG_ERROR, ("No corresponding CMDHdlr for this CMD(%x)\n",  CMDQelmt->command));
			return FALSE;
		}
	}
	else
	{
		DBGPRINT(RT_DEBUG_ERROR, ("CMD(%x) is out of boundary\n", CMDQelmt->command));
		return FALSE;
	}
}


void CMDHandler(
    IN PRTMP_ADAPTER pAd)
{
	PCmdQElmt		cmdqelmt;
	NDIS_STATUS		NdisStatus = NDIS_STATUS_SUCCESS;
	int		ntStatus;
/*	unsigned long	IrqFlags;*/

	while (pAd && pAd->CmdQ.size > 0)
	{
		NdisStatus = NDIS_STATUS_SUCCESS;

		NdisAcquireSpinLock(&pAd->CmdQLock);
		RTThreadDequeueCmd(&pAd->CmdQ, &cmdqelmt);
		NdisReleaseSpinLock(&pAd->CmdQLock);

		if (cmdqelmt == NULL)
			break;


		if(!(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST) || RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS)))
		{
			if(ValidCMD(cmdqelmt))
				ntStatus = (*CMDHdlrTable[cmdqelmt->command - CMDTHREAD_FIRST_CMD_ID])(pAd, cmdqelmt);
		}

		if (cmdqelmt->CmdFromNdis == TRUE)
		{
			if (cmdqelmt->buffer != NULL)
				os_free_mem(pAd, cmdqelmt->buffer);
			os_free_mem(pAd, cmdqelmt);
		}
		else
		{
			if ((cmdqelmt->buffer != NULL) && (cmdqelmt->bufferlength != 0))
				os_free_mem(pAd, cmdqelmt->buffer);
			os_free_mem(pAd, cmdqelmt);
		}
	}	/* end of while */
}


void RTUSBWatchDog(IN RTMP_ADAPTER *pAd)
{
	PHT_TX_CONTEXT		pHTTXContext;
	int 					idx;
	unsigned long				irqFlags;
	PURB		   		pUrb;
	unsigned char				needDumpSeq = FALSE;
	unsigned int          	MACValue;

	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
		return;

#ifdef CONFIG_STA_SUPPORT
	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
		return;
#endif /* CONFIG_STA_SUPPORT */

	idx = 0;
	RTMP_IO_READ32(pAd, TXRXQ_PCNT, &MACValue);
	if ((MACValue & 0xff) !=0 )
	{
		DBGPRINT(RT_DEBUG_TRACE, ("TX QUEUE 0 Not EMPTY(Value=0x%0x). !!!!!!!!!!!!!!!\n", MACValue));
		RTMP_IO_WRITE32(pAd, PBF_CFG, 0xf40012);
		while((MACValue &0xff) != 0 && (idx++ < 10))
		{
		        RTMP_IO_READ32(pAd, TXRXQ_PCNT, &MACValue);
		        RTMPusecDelay(1);
		}
		RTMP_IO_WRITE32(pAd, PBF_CFG, 0xf40006);
	}

	idx = 0;
	if ((MACValue & 0xff00) !=0 )
	{
		DBGPRINT(RT_DEBUG_TRACE, ("TX QUEUE 1 Not EMPTY(Value=0x%0x). !!!!!!!!!!!!!!!\n", MACValue));
		RTMP_IO_WRITE32(pAd, PBF_CFG, 0xf4000a);
		while((MACValue &0xff00) != 0 && (idx++ < 10))
		{
			RTMP_IO_READ32(pAd, TXRXQ_PCNT, &MACValue);
			RTMPusecDelay(1);
		}
		RTMP_IO_WRITE32(pAd, PBF_CFG, 0xf40006);
	}


	if (pAd->watchDogRxOverFlowCnt >= 2)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("Maybe the Rx Bulk-In hanged! Cancel the pending Rx bulks request!\n"));
		if ((!RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS |
									fRTMP_ADAPTER_BULKIN_RESET |
									fRTMP_ADAPTER_HALT_IN_PROGRESS |
									fRTMP_ADAPTER_NIC_NOT_EXIST))))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("Call CMDTHREAD_RESET_BULK_IN to cancel the pending Rx Bulk!\n"));
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_BULKIN_RESET);
			RTEnqueueInternalCmd(pAd, CMDTHREAD_RESET_BULK_IN, NULL, 0);
			needDumpSeq = TRUE;
		}
		pAd->watchDogRxOverFlowCnt = 0;
	}


	for (idx = 0; idx < NUM_OF_TX_RING; idx++)
	{
		pUrb = NULL;

		RTMP_IRQ_LOCK(&pAd->BulkOutLock[idx], irqFlags);
/*		if ((pAd->BulkOutPending[idx] == TRUE) && pAd->watchDogTxPendingCnt)*/
		if (pAd->BulkOutPending[idx] == TRUE)
		{
			pAd->watchDogTxPendingCnt[idx]++;

			if ((pAd->watchDogTxPendingCnt[idx] > 2) &&
				 (!RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST | fRTMP_ADAPTER_BULKOUT_RESET)))
				)
			{
				/* FIXME: Following code just support single bulk out. If you wanna support multiple bulk out. Modify it!*/
				pHTTXContext = (PHT_TX_CONTEXT)(&pAd->TxContext[idx]);
				if (pHTTXContext->IRPPending)
				{	/* Check TxContext.*/
					pUrb = pHTTXContext->pUrb;
				}
				else if (idx == MGMTPIPEIDX)
				{
					PTX_CONTEXT pMLMEContext, pNULLContext, pPsPollContext;

					/*Check MgmtContext.*/
					pMLMEContext = (PTX_CONTEXT)(pAd->MgmtRing.Cell[pAd->MgmtRing.TxDmaIdx].AllocVa);
					pPsPollContext = (PTX_CONTEXT)(&pAd->PsPollContext);
					pNULLContext = (PTX_CONTEXT)(&pAd->NullContext);

					if (pMLMEContext->IRPPending)
					{
						ASSERT(pMLMEContext->IRPPending);
						pUrb = pMLMEContext->pUrb;
					}
					else if (pNULLContext->IRPPending)
					{
						ASSERT(pNULLContext->IRPPending);
						pUrb = pNULLContext->pUrb;
					}
					else if (pPsPollContext->IRPPending)
					{
						ASSERT(pPsPollContext->IRPPending);
						pUrb = pPsPollContext->pUrb;
					}
				}

				RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[idx], irqFlags);

				DBGPRINT(RT_DEBUG_TRACE, ("Maybe the Tx Bulk-Out hanged! Cancel the pending Tx bulks request of idx(%d)!\n", idx));
				if (pUrb)
				{
					DBGPRINT(RT_DEBUG_TRACE, ("Unlink the pending URB!\n"));
					/* unlink it now*/
					RTUSB_UNLINK_URB(pUrb);
					/* Sleep 200 microseconds to give cancellation time to work*/
					RTMPusecDelay(200);
					needDumpSeq = TRUE;
				}
				else
				{
					DBGPRINT(RT_DEBUG_ERROR, ("Unkonw bulkOut URB maybe hanged!!!!!!!!!!!!\n"));
				}
			}
			else
			{
				RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[idx], irqFlags);
			}
		}
		else
		{
			RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[idx], irqFlags);
		}
	}

#ifdef DOT11_N_SUPPORT
	/* For Sigma debug, dump the ba_reordering sequence.*/
	if((needDumpSeq == TRUE) && (pAd->CommonCfg.bDisableReordering == 0))
	{
		unsigned short				Idx;
		PBA_REC_ENTRY		pBAEntry = NULL;
		unsigned char				count = 0;
		struct reordering_mpdu *mpdu_blk;

		Idx = pAd->MacTab.Content[BSSID_WCID].BARecWcidArray[0];

		pBAEntry = &pAd->BATable.BARecEntry[Idx];
		if((pBAEntry->list.qlen > 0) && (pBAEntry->list.next != NULL))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("NICUpdateRawCounters():The Queueing pkt in reordering buffer:\n"));
			NdisAcquireSpinLock(&pBAEntry->RxReRingLock);
			mpdu_blk = pBAEntry->list.next;
			while (mpdu_blk)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("\t%d:Seq-%d, bAMSDU-%d!\n", count, mpdu_blk->Sequence, mpdu_blk->bAMSDU));
				mpdu_blk = mpdu_blk->next;
				count++;
			}

			DBGPRINT(RT_DEBUG_TRACE, ("\npBAEntry->LastIndSeq=%d!\n", pBAEntry->LastIndSeq));
			NdisReleaseSpinLock(&pBAEntry->RxReRingLock);
		}
	}
#endif /* DOT11_N_SUPPORT */
}

#endif /* RTMP_MAC_USB */
