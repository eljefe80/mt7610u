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


#ifndef __CRYPT_HMAC_H__
#define __CRYPT_HMAC_H__

#include "rt_config.h"


#ifdef SHA1_SUPPORT
#define HMAC_SHA1_SUPPORT
void RT_HMAC_SHA1(
	IN const unsigned char Key[],
	IN unsigned int KeyLen,
	IN const unsigned char Message[],
	IN unsigned int MessageLen,
	unsigned char MAC[],
	IN unsigned int MACLen);
#endif /* SHA1_SUPPORT */

#ifdef SHA256_SUPPORT
#define HMAC_SHA256_SUPPORT
void RT_HMAC_SHA256(
	IN const unsigned char Key[],
	IN unsigned int KeyLen,
	IN const unsigned char Message[],
	IN unsigned int MessageLen,
	unsigned char MAC[],
	IN unsigned int MACLen);
#endif /* SHA256_SUPPORT */

#ifdef MD5_SUPPORT
#define HMAC_MD5_SUPPORT
void RT_HMAC_MD5(
	IN const unsigned char Key[],
	IN unsigned int KeyLen,
	IN const unsigned char Message[],
	IN unsigned int MessageLen,
	unsigned char MAC[],
	IN unsigned int MACLen);
#endif /* MD5_SUPPORT */


#endif /* __CRYPT_HMAC_H__ */
