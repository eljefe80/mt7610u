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


#ifndef __PBF_H__
#define __PBF_H__


#ifdef RLT_MAC
#include "ral_nmac_pbf.h"
#endif /* RLT_MAC */

#ifdef RTMP_MAC
#include "mac_ral/omac/ral_omac_pbf.h"
#endif /* RTMP_MAC */


/* ================================================================================= */
/* Register format  for PBF                                                                                                                                                     */
/* ================================================================================= */


#define WPDMA_GLO_CFG 	0x208
#ifdef RT_BIG_ENDIAN
typedef	union _WPDMA_GLO_CFG_STRUC	{
	struct	{
		unsigned int rx_2b_offset:1;
		unsigned int clk_gate_dis:1;
		unsigned int rsv:14;
		unsigned int HDR_SEG_LEN:8;
		unsigned int BigEndian:1;
		unsigned int EnTXWriteBackDDONE:1;
		unsigned int WPDMABurstSIZE:2;
		unsigned int RxDMABusy:1;
		unsigned int EnableRxDMA:1;
		unsigned int TxDMABusy:1;
		unsigned int EnableTxDMA:1;
	}	field;
	unsigned int word;
}WPDMA_GLO_CFG_STRUC, *PWPDMA_GLO_CFG_STRUC;
#else
typedef	union _WPDMA_GLO_CFG_STRUC	{
	struct {
		unsigned int EnableTxDMA:1;
		unsigned int TxDMABusy:1;
		unsigned int EnableRxDMA:1;
		unsigned int RxDMABusy:1;
		unsigned int WPDMABurstSIZE:2;
		unsigned int EnTXWriteBackDDONE:1;
		unsigned int BigEndian:1;
		unsigned int HDR_SEG_LEN:8;
		unsigned int rsv:14;
		unsigned int clk_gate_dis:1;
		unsigned int rx_2b_offset:1;
	} field;
	unsigned int word;
} WPDMA_GLO_CFG_STRUC, *PWPDMA_GLO_CFG_STRUC;
#endif


#define PBF_CTRL			0x0410
#define MCU_INT_STA		0x0414
#define MCU_INT_ENA	0x0418
#define TXRXQ_PCNT		0x0438
#define PBF_DBG			0x043c


#endif /* __PBF_H__ */

