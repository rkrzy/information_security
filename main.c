#include <stdio.h>
#include "Encryption.h"
#include "Decryption.h"
#include "Calculate.h"

int main(void) {
    int i = 0;
    int key = 0;
    int key2 =0;
    int str_size = 0;
    int key_size = 0;

    char key_str[50] = {0,};
    char str[50] = {0,};
    char cipher_text[50] = {0,};


    /* caesar cipher encryption decryption 출력
    printf("평문 또는 암호문을 입력하시오:");
    fgets(str, sizeof(str), stdin);

    printf("키 값을 입력하시오:");
    scanf("%d", &key);

    str_size = strlen(str);
    caesar_cipher_encryption(str, str_size, key);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf(str);
    caesar_cipher_decryption(str, str_size, key);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf(str);
    */


    /* affine cryption, decryption 출력
    printf("평문 또는 암호문을 입력하시오:");
    fgets(str, sizeof(str), stdin);

    printf("첫번째 키 값을 입력하시오:");
    scanf("%d", &key);
    printf("두번째 키 값을 입력하시오:");
    scanf("%d", & key2);

    str_size = strlen(str);
    affine_cipher_encryption(str, str_size, key, key2);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf(str);
    affine_cipher_decryption(str, str_size, key, key2);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf(str);
*/
    /* Gronsfeld cipher encryption decryption
    printf("평문 또는 암호문을 입력하시오:");
    fgets(str, sizeof(str), stdin);
    remove_newline(str);

    printf("키 값을 입력하시오:");
    fgets(key_str, sizeof(key_str), stdin);
    remove_newline(key_str);

    str_size = my_strlen(str);
    key_size = my_strlen(key_str);
    gronsfeld_cipher_encryption(str, str_size, key_str, key_size);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf("%s",str);
    gronsfeld_cipher_decryption(str, str_size, key_str, key_size);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf("%s",str);
     */
    /* vigenere cipher encryption decryption
    printf("평문 또는 암호문을 입력하시오:");
    fgets(str, sizeof(str), stdin);
    remove_newline(str);

    printf("키 값을 입력하시오:");
    fgets(key_str, sizeof(key_str), stdin);
    remove_newline(key_str);

    str_size = my_strlen(str);
    key_size = my_strlen(key_str);
    vigenere_cipher_encryption(str, str_size, key_str, key_size);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf("%s",str);
    vigenere_cipher_decryption(str, str_size, key_str, key_size);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf("%s",str);
    */

    /* rail fence cipher Encryption decryption
    printf("평문 또는 암호문을 입력하시오:");
    fgets(str, sizeof(str), stdin);
    remove_newline(str);

    str_size = my_strlen(str);
    rail_fence_cipher_encryption(str, str_size,cipher_text);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf("%s",cipher_text);
    rail_fence_cipher_decryption(cipher_text, str_size,str);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf("%s",str);
    */

    /* rail fence cipher multi Encryption decryption
    printf("평문 또는 암호문을 입력하시오:");
    fgets(str, sizeof(str), stdin);
    remove_newline(str);

    str_size = my_strlen(str);
    rail_fence_cipher_multi_rail_encryption(str, str_size,cipher_text, 5);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf("%s",cipher_text);
    rail_fence_cipher_multi_rail_decryption(cipher_text, str_size, str, 5);
    printf("\n암호화 또는 복호화된 결과 출력:");
    printf("%s",str);
     */
    return 0;
}

