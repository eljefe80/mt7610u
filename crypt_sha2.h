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


#ifndef __CRYPT_SHA2_H__
#define __CRYPT_SHA2_H__


/* Algorithm options */
#define SHA1_SUPPORT
#define SHA256_SUPPORT

#ifdef SHA1_SUPPORT
#define SHA1_BLOCK_SIZE    64	/* 512 bits = 64 bytes */
#define SHA1_DIGEST_SIZE   20	/* 160 bits = 20 bytes */
typedef struct _SHA1_CTX_STRUC {
	unsigned int HashValue[5];	/* 5 = (SHA1_DIGEST_SIZE / 32) */
	unsigned long MessageLen;	/* total size */
	unsigned char Block[SHA1_BLOCK_SIZE];
	unsigned int BlockLen;
} SHA1_CTX_STRUC, *PSHA1_CTX_STRUC;

void RT_SHA1_Init(
	IN SHA1_CTX_STRUC * pSHA_CTX);
void RT_SHA1_Hash(
	IN SHA1_CTX_STRUC * pSHA_CTX);
void RT_SHA1_Append(
	IN SHA1_CTX_STRUC * pSHA_CTX,
	IN const unsigned char Message[],
	IN unsigned int MessageLen);
void RT_SHA1_End(
	IN SHA1_CTX_STRUC * pSHA_CTX,
	unsigned char DigestMessage[]);
void RT_SHA1(
	IN const unsigned char Message[],
	IN unsigned int MessageLen,
	unsigned char DigestMessage[]);
#endif /* SHA1_SUPPORT */

#ifdef SHA256_SUPPORT
#define SHA256_BLOCK_SIZE   64	/* 512 bits = 64 bytes */
#define SHA256_DIGEST_SIZE  32	/* 256 bits = 32 bytes */
typedef struct _SHA256_CTX_STRUC {
	unsigned int HashValue[8];	/* 8 = (SHA256_DIGEST_SIZE / 32) */
	unsigned long MessageLen;	/* total size */
	unsigned char Block[SHA256_BLOCK_SIZE];
	unsigned int BlockLen;
} SHA256_CTX_STRUC, *PSHA256_CTX_STRUC;

void RT_SHA256_Init(
	IN SHA256_CTX_STRUC * pSHA_CTX);
void RT_SHA256_Hash(
	IN SHA256_CTX_STRUC * pSHA_CTX);
void RT_SHA256_Append(
	IN SHA256_CTX_STRUC * pSHA_CTX,
	IN const unsigned char Message[],
	IN unsigned int MessageLen);
void RT_SHA256_End(
	IN SHA256_CTX_STRUC * pSHA_CTX,
	unsigned char DigestMessage[]);
void RT_SHA256(
	IN const unsigned char Message[],
	IN unsigned int MessageLen,
	unsigned char DigestMessage[]);
#endif /* SHA256_SUPPORT */


#endif /* __CRYPT_SHA2_H__ */
