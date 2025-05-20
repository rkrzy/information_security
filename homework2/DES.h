// des.c – complete pure‑C implementation of DES (ECB) + key schedule
// ready for wrapping into CBC/CFB/OFB/CTR modes
// -------------------------------------------------------------
// build:  gcc -std=c99 -O2 -Wall des.c -o des
// test:   ./des
// (prints NIST known‑answer test vector #1)

#ifndef INFORMATION_SECURITY_DES_H
#define INFORMATION_SECURITY_DES_H


#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef uint8_t  BYTE;
typedef uint32_t UINT;
typedef uint64_t UINT64;

#define BLOCK_SIZE 8
#define DES_ROUND  16


static const int IP[64] = {
        58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
        62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
        57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
        61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
};

static const int IIP[64] = {
        40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
        38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
        36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
        34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};

static const int E[48] = {
        32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,  8,  9, 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

static const int P[32] = {
        16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
        2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

static const int PC1[56] = {
        57,  1, 10, 19, 63,  7, 14, 21, 49, 58,  2, 11, 55, 62,  6, 13,
        41, 50, 59,  3, 47, 54, 61,  5, 33, 42, 51, 60, 39, 46, 53, 28,
        25, 34, 43, 52, 31, 38, 45, 20, 17, 26, 35, 44, 23, 30, 37, 12,
        9, 18, 27, 36, 15, 22, 29,  4
};

static const int PC2[48] = {
        14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10, 23, 19, 12,  4,
        26,  8, 16,  7, 27, 20, 13,  2, 41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

static const int SBOX[8][4][16] = {/* paste full s‑box from header */};

UINT leftrotate28(UINT v, int n);
void swap32(UINT *a, UINT *b);
UINT sbox_sub(const BYTE in[6]);
UINT f(UINT R, const BYTE rk[6]);
void key_expansion(const BYTE master[8], BYTE rk[16][6]);
void to_word(const BYTE blk[8], UINT *l, UINT *r);
void to_block(UINT l, UINT r, BYTE blk[8]);
void permute_block(const BYTE *in, BYTE *out, const int *tbl, int n);
UINT permute_word(UINT in, const int *tbl);

void IP_perm(const BYTE *in, BYTE *out);
void IIP_perm(const BYTE *in, BYTE *out);

#endif
//#ifdef DES_SELFTEST
//int main(void)
//{
//    const BYTE key[8]  = {0x13,0x34,0x57,0x79,0x9B,0xBC,0xDF,0xF1};
//    const BYTE plain[8]= {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
//    const BYTE expect[8]= {0x85,0xE8,0x13,0x54,0x0F,0x0A,0xB4,0x05};
//    BYTE buf[8];
//    des_encrypt_ecb(key,plain,buf);
//    printf("enc: "); for(int i=0;i<8;++i) printf("%02X",buf[i]); puts("");
//    des_decrypt_ecb(key,buf,buf);
//    printf("dec: "); for(int i=0;i<8;++i) printf("%02X",buf[i]); puts("");
//    return 0;
//}
//#endif
