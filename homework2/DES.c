
#include "DES.h"

// 28비트 값을 n비트 순환시킨다.
 UINT leftrotate28(UINT v, int n)
{
    return ((v << n) | (v >> (28 - n))) & 0x0FFFFFFF;
}

// 32비트 두값을 간단히 교환한다. Feistel 루프 끝에서 L, R 뒤집을 때 용도다
 void swap32(UINT *a, UINT *b)
{
    UINT t = *a; *a = *b; *b = t;
}

//48비트 입력을 8개의 S-box에 넣어 32비트로 축소한다.
 UINT sbox_sub(const BYTE in[6])
{
    UINT out = 0;
    for (int i = 0; i < 8; ++i) {
        int row = ((in[i>>0] >> (7 - (i*6)%8)) & 0x20)>>4 | ((in[i>>0] >> (7 - ((i*6+5)%8))) & 1);
        int col = 0;
        for (int b=1;b<=4;++b)
            col = (col<<1) | ((in[(i*6+b)>>3] >> (7 - ((i*6+b)%8))) & 1);
        out |= SBOX[i][row][col] << (28 - 4*i);
    }
    return out;
}
/*DES 라운드 함수 다
1. R을 E로확장 -> 48비트
2. 라운드 키 XOR
3. S-box 축소
4. p 퍼뮤테이션으로 32비트 출력 만든다.
 */
 UINT f(UINT R, const BYTE rk[6])
{
    BYTE exp[6] = {0};
    BYTE rblk[4];
    rblk[0]=R>>24; rblk[1]=R>>16; rblk[2]=R>>8; rblk[3]=R;
    permute_block(rblk, exp, E, 48);
    for (int i=0;i<6;++i) exp[i]^=rk[i];
    UINT s_out = sbox_sub(exp);
    return permute_word(s_out, P);
}

/*
 * 64비트 마스터키 -> 16개의 48비트 라운드 키 생성
 * PC-1로 56비트 추출 -> C, D 분할
 * 라운드마다 1.2비트 회전
 * PC-2로 48비트 뽑아 rk[round]에 저장한다.
 */
 void key_expansion(const BYTE master[8], BYTE rk[16][6])
{
    BYTE pc1[7] = {0};
    permute_block(master, pc1, PC1, 56);

    UINT C = (pc1[0]<<20)|(pc1[1]<<12)|(pc1[2]<<4)|((pc1[3]>>4)&0xF);
    UINT D = ((UINT)(pc1[3]&0x0F)<<24)|(pc1[4]<<16)|(pc1[5]<<8)|pc1[6];

     const int shifts[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    for (int round = 0; round < 16; ++round) {
        C = leftrotate28(C, shifts[round]);
        D = leftrotate28(D, shifts[round]);
        BYTE cd[7] = {0};
        for (int i=0;i<28;++i) if (C & (1u<<(27-i))) cd[i>>3]|=1u<<(7-(i&7));
        for (int i=0;i<28;++i) if (D & (1u<<(27-i))) cd[(i+28)>>3]|=1u<<(7-((i+28)&7));
        permute_block(cd, rk[round], PC2, 48);
    }
}

/*
 * 8비트 블록을 상위 32비트 L 하위 32비트 R로 분리한다.
 */

 void to_word(const BYTE blk[8], UINT *l, UINT *r)
{
    *l =  (UINT)blk[0]<<24 | (UINT)blk[1]<<16 | (UINT)blk[2]<<8 | blk[3];
    *r =  (UINT)blk[4]<<24 | (UINT)blk[5]<<16 | (UINT)blk[6]<<8 | blk[7];
}

/*
 * 위의 역-방향 L, R 두 워드를 8바이트 블록으로 합친다.
 */
 void to_block(UINT l, UINT r, BYTE blk[8])
{
    blk[0]=l>>24; blk[1]=l>>16; blk[2]=l>>8; blk[3]=l;
    blk[4]=r>>24; blk[5]=r>>16; blk[6]=r>>8; blk[7]=r;
}

/*
 * 주어진 비트 테이블대로 최대 64비트를 재배치한다.
 */
 void permute_block(const BYTE *in, BYTE *out, const int *tbl, int n)
{
    memset(out, 0, (n + 7) / 8);
    for (int i = 0; i < n; ++i) {
        int bit = (in[(tbl[i] - 1) >> 3] >> (7 - ((tbl[i] - 1) & 7))) & 1;
        out[i >> 3] |= bit << (7 - (i & 7));
    }
}

/*
 * 32비트 입력을 P 테이블처럼 워드 단위로 재배치한다.
 */
 UINT permute_word(UINT in, const int *tbl)
{
    UINT out = 0;
    for (int i = 0; i < 32; ++i) {
        if (in & (1u << (32 - tbl[i]))) out |= 1u << (31 - i);
    }
    return out;
}

/*
 * 초기 퍼뮤테이션 래퍼, 8바이트 평문 -> 재배치
 */
 void IP_perm(const BYTE *in, BYTE *out)
{
    permute_block(in,out,IP,64);
}

/*
 * 역-초기 퍼뮤테이션래퍼. 마지막에 8바이트 암호문을 원래 순서로 돌려놓는다.
 */

 void IIP_perm(const BYTE *in, BYTE *out)
{
    permute_block(in,out,IIP,64);
}
