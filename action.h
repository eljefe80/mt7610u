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


#ifndef	__ACTION_H__
#define	__ACTION_H__

typedef struct __attribute__ ((packed)) __HT_INFO_OCTET {
#ifdef RT_BIG_ENDIAN
	unsigned char Reserved:5;
	unsigned char STA_Channel_Width:1;
	unsigned char Forty_MHz_Intolerant:1;
	unsigned char Request:1;
#else
	unsigned char Request:1;
	unsigned char Forty_MHz_Intolerant:1;
	unsigned char STA_Channel_Width:1;
	unsigned char Reserved:5;
#endif
} HT_INFORMATION_OCTET;

typedef struct __attribute__ ((packed)) __FRAME_HT_INFO {
	HEADER_802_11 Hdr;
	unsigned char Category;
	unsigned char Action;
	HT_INFORMATION_OCTET HT_Info;
} FRAME_HT_INFO, *PFRAME_HT_INFO;

#endif /* __ACTION_H__ */
