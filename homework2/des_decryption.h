//
// Created by 임준식 on 25. 5. 18.
//

#ifndef INFORMATION_SECURITY_DES_DECRYPTION_H
#define INFORMATION_SECURITY_DES_DECRYPTION_H
#include "DES.h"

void des_decrypt_ecb(const BYTE key[8], const BYTE in[8], BYTE out[8]);
void des_decrypt_cbc(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE in[8], BYTE out[8]);
void des_decrypt_cfb(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE in[8], BYTE out[8]);
void des_decrypt_ofb(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE in[8], BYTE out[8]);
void des_decrypt_ctr(const BYTE key[8], const BYTE ctr[8], int msg_len,const BYTE in[8], BYTE out[8]);
#endif //INFORMATION_SECURITY_DES_DECRYPTION_H
