#include "des_decryption.h"
#include "des_encryption.h"
void des_decrypt_ecb(const BYTE key[8], const BYTE in[8], BYTE out[8])
{
    BYTE data[8];
    BYTE rk[16][6];
    UINT L,R;
    key_expansion(key,rk);
    IP_perm(in,data);
    to_word(data,&L,&R);
    for(int i=15;i>=0;--i){ UINT tmp=L^f(R,rk[i]); L=R; R=tmp; }
    swap32(&L,&R);
    to_block(L,R,data);
    IIP_perm(data,out);
}

void des_decrypt_cbc(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE in[8], BYTE out[8])
{
    if (msg_len % 8 != 0) return;

    BYTE prev[8];
    BYTE tmp[8];
    memcpy(prev, IV, 8);

    for (int i = 0; i < msg_len; i += 8) {

        des_decrypt_ecb(key, in + i, tmp);

        for (int j = 0; j < 8; ++j)
            out[i + j] = tmp[j] ^ prev[j];

        memcpy(prev, in + i, 8);
    }
}

void des_decrypt_cfb(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE in[8], BYTE out[8])
{
    if (msg_len % 8 != 0) return;

    BYTE feedback[8];
    BYTE key_stream[8];
    memcpy(feedback, IV, 8);

    for (int i = 0; i < msg_len; i += 8) {

        des_encrypt_ecb(key, feedback, key_stream);

        for (int j = 0; j < 8; ++j)
            out[i + j] = in[i + j] ^ key_stream[j];

        memcpy(feedback, in + i, 8);
    }
}

void des_decrypt_ofb(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE in[8], BYTE out[8])
{
    if (msg_len % 8 != 0) return;

    BYTE feedback[8];
    BYTE key_stream[8];
    memcpy(feedback, IV, 8);

    for (int i = 0; i < msg_len; i += 8) {

        des_encrypt_ecb(key, feedback, key_stream);

        for (int j = 0; j < 8; ++j)
            out[i + j] = in[i + j] ^ key_stream[j];

        memcpy(feedback, key_stream, 8);
    }
}

void des_decrypt_ctr(const BYTE key[8], const BYTE ctr[8], int msg_len,const BYTE in[8], BYTE out[8])
{
    if (msg_len % 8 != 0) return;

    BYTE counter[8];
    BYTE key_stream[8];
    memcpy(counter, &ctr, 8);

    for (int i = 0; i < msg_len; i += 8) {

        des_encrypt_ecb(key, counter, key_stream);

        for (int j = 0; j < 8; ++j)
            out[i + j] = in[i + j] ^ key_stream[j];

        for (int k = 7; k >= 0; --k) {
            if (++counter[k] != 0) break;
        }
    }
}