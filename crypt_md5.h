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


#ifndef __CRYPT_MD5_H__
#define __CRYPT_MD5_H__


/* Algorithm options */
#define MD5_SUPPORT

#ifdef MD5_SUPPORT
#define MD5_BLOCK_SIZE    64	/* 512 bits = 64 bytes */
#define MD5_DIGEST_SIZE   16	/* 128 bits = 16 bytes */
typedef struct {
	unsigned int HashValue[4];
	unsigned long MessageLen;
	unsigned char Block[MD5_BLOCK_SIZE];
	unsigned int BlockLen;
} MD5_CTX_STRUC, *PMD5_CTX_STRUC;

void RT_MD5_Init(
	MD5_CTX_STRUC * pMD5_CTX);
void RT_MD5_Hash(
	MD5_CTX_STRUC * pMD5_CTX);
void RT_MD5_Append(
	MD5_CTX_STRUC * pMD5_CTX,
	const unsigned char Message[],
	unsigned int MessageLen);
void RT_MD5_End(
	MD5_CTX_STRUC * pMD5_CTX,
	unsigned char DigestMessage[]);
void RT_MD5(
	const unsigned char Message[],
	unsigned int MessageLen,
	unsigned char DigestMessage[]);
#endif /* MD5_SUPPORT */


#endif /* __CRYPT_MD5_H__ */
