//
// Created by 임준식 on 25. 5. 18.
//

#ifndef INFORMATION_SECURITY_DES_ENCRYPTION_H
#define INFORMATION_SECURITY_DES_ENCRYPTION_H
#include "DES.h"

void des_encrypt_ecb(const BYTE key[8], const BYTE in[8], BYTE out[8]);
void des_encrypt_cbc(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE * in, BYTE *out);
void des_encrypt_cfb(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE * in, BYTE * out);
void des_encrypt_ofb(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE in[8], BYTE out[8]);
void des_encrypt_ctr(const BYTE key[8], const BYTE ctr[8], int msg_len,const BYTE in[8], BYTE out[8]);
#endif //INFORMATION_SECURITY_DES_ENCRYPTION_H
