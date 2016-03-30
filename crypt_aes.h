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


#ifndef __CRYPT_AES_H__
#define __CRYPT_AES_H__

#include "rt_config.h"


/* AES definition & structure */
#define AES_STATE_ROWS 4     /* Block size: 4*4*8 = 128 bits */
#define AES_STATE_COLUMNS 4
#define AES_BLOCK_SIZES AES_STATE_ROWS*AES_STATE_COLUMNS
#define AES_KEY_ROWS 4
#define AES_KEY_COLUMNS 8    /*Key length: 4*{4,6,8}*8 = 128, 192, 256 bits */
#define AES_KEY128_LENGTH 16
#define AES_KEY192_LENGTH 24
#define AES_KEY256_LENGTH 32
#define AES_CBC_IV_LENGTH 16

typedef struct {
    unsigned char State[AES_STATE_ROWS][AES_STATE_COLUMNS];
    unsigned char KeyWordExpansion[AES_KEY_ROWS][AES_KEY_ROWS*((AES_KEY256_LENGTH >> 2) + 6 + 1)];
} AES_CTX_STRUC, *PAES_CTX_STRUC;


/* AES operations */
void RT_AES_KeyExpansion (
    IN unsigned char Key[],
    IN unsigned int KeyLength,
    IN AES_CTX_STRUC *paes_ctx);

void RT_AES_Encrypt (
    IN unsigned char PlainBlock[],
    IN unsigned int PlainBlockSize,
    IN unsigned char Key[],
    IN unsigned int KeyLength,
    unsigned char CipherBlock[],
    unsigned int *CipherBlockSize);

void RT_AES_Decrypt (
    IN unsigned char CipherBlock[],
    IN unsigned int CipherBlockSize,
    IN unsigned char Key[],
    IN unsigned int KeyLength,
    unsigned char PlainBlock[],
    unsigned int *PlainBlockSize);

/* AES Counter with CBC-MAC operations */
void AES_CCM_MAC (
    IN unsigned char Payload[],
    IN unsigned int  PayloadLength,
    IN unsigned char Key[],
    IN unsigned int  KeyLength,
    IN unsigned char Nonce[],
    IN unsigned int  NonceLength,
    IN unsigned char AAD[],
    IN unsigned int  AADLength,
    IN unsigned int  MACLength,
    unsigned char MACText[]);

int AES_CCM_Encrypt (
    IN unsigned char Plaintext[],
    IN unsigned int  PlaintextLength,
    IN unsigned char Key[],
    IN unsigned int  KeyLength,
    IN unsigned char Nonce[],
    IN unsigned int  NonceLength,
    IN unsigned char AAD[],
    IN unsigned int  AADLength,
    IN unsigned int  MACLength,
    unsigned char CipherText[],
    unsigned int *CipherTextLength);

int AES_CCM_Decrypt (
    IN unsigned char CipherText[],
    IN unsigned int  CipherTextLength,
    IN unsigned char Key[],
    IN unsigned int  KeyLength,
    IN unsigned char Nonce[],
    IN unsigned int  NonceLength,
    IN unsigned char AAD[],
    IN unsigned int  AADLength,
    IN unsigned int  MACLength,
    unsigned char Plaintext[],
    unsigned int *PlaintextLength);

/* AES-CMAC operations */
void AES_CMAC_GenerateSubKey (
    IN unsigned char Key[],
    IN unsigned int KeyLength,
    unsigned char SubKey1[],
    unsigned char SubKey2[]);

void AES_CMAC (
    IN unsigned char Plaintext[],
    IN unsigned int PlaintextLength,
    IN unsigned char Key[],
    IN unsigned int KeyLength,
    unsigned char MACText[],
    unsigned int *MACTextLength);



/* AES-CBC operations */
void AES_CBC_Encrypt (
    IN unsigned char Plaintext[],
    IN unsigned int PlaintextLength,
    IN unsigned char Key[],
    IN unsigned int KeyLength,
    IN unsigned char IV[],
    IN unsigned int IVLength,
    unsigned char CipherText[],
    unsigned int *CipherTextLength);

void AES_CBC_Decrypt (
    IN unsigned char CipherText[],
    IN unsigned int CipherTextLength,
    IN unsigned char Key[],
    IN unsigned int KeyLength,
    IN unsigned char IV[],
    IN unsigned int IVLength,
    unsigned char Plaintext[],
    unsigned int *PlaintextLength);

/* AES key wrap operations */
int AES_Key_Wrap (
    IN unsigned char Plaintext[],
    IN unsigned int  PlaintextLength,
    IN unsigned char Key[],
    IN unsigned int  KeyLength,
    unsigned char CipherText[],
    unsigned int *CipherTextLength);
        
int AES_Key_Unwrap (
    IN unsigned char CipherText[],
    IN unsigned int  CipherTextLength,
    IN unsigned char Key[],
    IN unsigned int  KeyLength,
    unsigned char Plaintext [],
    unsigned int *PlaintextLength);


#endif /* __CRYPT_AES_H__ */

