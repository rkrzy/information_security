#include "des_encryption.h"

void des_encrypt_ecb(const BYTE key[8], const BYTE in[8], BYTE out[8])
{
    BYTE data[8];
    BYTE rk[16][6];
    UINT L,R;
    key_expansion(key,rk); //키 확장을 수행한다.
    IP_perm(in,data); //8바이트 평문을 재패치한다.
    to_word(data,&L,&R); //8바이트 블록을 상위 32비트 L, 하위 32비트 R로 분리한다.
    for(int i=0;i<DES_ROUND;++i){
        UINT tmp=L^f(R,rk[i]); //오른쪽 32비트에 대해서 F연산 수행 후 왼쪽 32비트와 XOR연산
        //위치 변경
        L=R;
        R=tmp;
    }
    swap32(&L,&R); //DES마지막 라운드 후 Swap 규칙 수행
    to_block(L,R,data); // L, R을 다시 8바이트로 묶는다.
    IIP_perm(data,out); // 역 초기 퍼뮤테이션을 적용해서 최종 암호문 블록을 만든다.
}

void des_encrypt_cbc(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE * in, BYTE *out)
{
    BYTE prev[8];
    memcpy(prev, IV, 8);

    BYTE xor_block[8];

    for (int i = 0; i < msg_len; i += 8) {

        for (int j = 0; j < 8; ++j){
            xor_block[j] = in[i + j] ^ prev[j];
        }

        des_encrypt_ecb(key, xor_block, out + i);

        memcpy(prev, out + i, 8);
    }
}
void des_encrypt_cfb(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE * in, BYTE * out){

    BYTE prev[8];
    memcpy(prev, IV, 8);
    BYTE key_stream[8];
    for(int i = 0; i < msg_len; i+=8){
        des_encrypt_ecb(key, prev, key_stream); //IV를 먼저 암호화 수행한다.
        for (int j = 0; j < 8; ++j){
            out[i + j] = in[i + j] ^ key_stream[j];
        }
        memcpy(prev, out + i, 8);
    }
}


void des_encrypt_ofb(const BYTE key[8], const BYTE IV[8], int msg_len,const BYTE in[8], BYTE out[8])
{
    BYTE prev[8];
    BYTE key_stream[8];
    memcpy(prev, IV, 8);

    for(int i = 0; i < msg_len; i+=8){
        des_encrypt_ecb(key, prev, key_stream); //IV를 먼저 암호화 수행한다.
        for(int j = 0; j < 8; j++){
            out[i + j] = in[i + j] ^ key_stream[j];
        }
        memcpy(prev, key_stream, 8);
    }
}
void des_encrypt_ctr(const BYTE key[8], const BYTE ctr[8], int msg_len,const BYTE in[8], BYTE out[8])
{
    BYTE counter[8];
    BYTE key_stream[8];
    memcpy(counter, &ctr, 8);

    for(int i = 0; i < msg_len; i+=8){
        des_encrypt_ecb(key, counter, key_stream);
        for (int j = 0; j < 8; ++j){
            out[i + j] = in[i + j] ^ key_stream[j];
        }
        for (int k = 7; k >= 0; --k) {
            if (++counter[k] != 0) break;
        }
    }
}