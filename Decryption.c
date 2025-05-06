#include "Decryption.h"
#include "Calculate.h"

char * caesar_cipher_decryption(char * cipher_text, int cipher_text_size, int key)
{
    int i;

    for(i = 0; i < cipher_text_size; i++){

        if((cipher_text[i] >= 'A') && (cipher_text[i] <= 'Z'))
        {
            cipher_text[i] = (cipher_text[i] - 'A' - key + 26) % 26 + 'A';
        }
        else if((cipher_text[i] >= 'a') && (cipher_text[i] <= 'z'))
        {
            cipher_text[i] = (cipher_text[i] - 'a' - key + 26) % 26 + 'a';
        }
        else ;
    }
    return cipher_text;
}
char * affine_cipher_decryption(char * cipher_text, int cipher_text_size, int key1, int key2)
{
    int i;
    int key1_mod_inverse = mod_inverse(key1,26);
    if(key1_mod_inverse == -1){
        printf("key1과 26은 서로소여야 합니다.");
        return NULL;
    }
    for(i = 0; i < cipher_text_size; i++){
        if((cipher_text[i] >= 'A') && (cipher_text[i] <= 'Z'))
        {
            cipher_text[i] = ((cipher_text[i] - 'A' - key2 + 26) * key1_mod_inverse) % 26 + 'A';
        }
        else if((cipher_text[i] >= 'a') && (cipher_text[i] <= 'z'))
        {
            cipher_text[i] = ((cipher_text[i] - 'a' - key2 + 26) *  key1_mod_inverse) % 26 + 'a';
        }
    }
    return cipher_text;
}
char * vigenere_cipher_decryption(char * cipher_text, int cipher_text_size, const char * key, int key_size)
{
    int i = 0;
    int j = 0;
    int key_shift = 0;

    for(i = 0; i < cipher_text_size; i++){
        j = i % key_size;
        key_shift = (key[j] >= 'A' && key[j] <= 'Z') ? key[j] - 'A' : key[j] - 'a';

        if((cipher_text[i] >= 'a') && (cipher_text[i] <= 'z')) {
            cipher_text[i] = ((cipher_text[i] - 'a') - key_shift + 26) % 26 + 'a';
        }else if((cipher_text[i] >= 'A') && (cipher_text[i] <= 'Z')){
            cipher_text[i] = ((cipher_text[i] - 'A') - key_shift + 26) % 26 + 'A';
        }
    }
    return cipher_text;
}
char * gronsfeld_cipher_decryption(char * cipher_text, int cipher_text_size, const char * key, int key_size){
    int i = 0;
    int j = 0;
    int key_shift = 0;
    for(i = 0; i < cipher_text_size; i++){
        j = i % key_size;
        key_shift = (key[j] >= '0' && key[j] <= '9') ? key[j] - '0' : -1;
        if(key_shift == -1)
        {
            fprintf(stderr, "키값에 숫자가 아닌 문자가 포함되어 있습니다.\n");
            return NULL;
        }
        if((cipher_text[i] >= 'a') && (cipher_text[i] <= 'z')){
            cipher_text[i] = ((cipher_text[i] - 'a') - key_shift + 26) % 26 + 'a';
        }else if((cipher_text[i] >= 'A') && (cipher_text[i] <= 'Z')){
            cipher_text[i] = ((cipher_text[i] - 'A') - key_shift + 26) % 26 + 'A';
        }
    }
    return cipher_text;
}

char * rail_fence_cipher_decryption(char * cipher_text, int cipher_text_size, char * plaintext)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < cipher_text_size; i += 2){
        plaintext[i] = cipher_text[j++];
    }
    for(i = 1; i < cipher_text_size; i +=2) {
        plaintext[i] = cipher_text[j++];
    }
    plaintext[cipher_text_size] = '\0';

    return plaintext;
}

char * rail_fence_cipher_multi_rail_decryption(char * cipher_text, int cipher_text_size, char * plaintext, int rail_count)
{
    int i = 0;
    int j = 0;
    int row = 0;
    int dir = 1;
    int rail_index[rail_count];
    int rail_length[rail_count];
    char * rail[rail_count];

    for(i = 0; i < sizeof(rail_length)/sizeof(int); i++){
        rail_length[i] = 0;
    }

    for (i = 0; i < cipher_text_size; i++) {
        rail_length[row]++;
        if (row == 0) dir = 1;
        else if (row == rail_count - 1) dir = -1;
        row += dir;
    }

    int pos = 0;
    for (i = 0; i < rail_count; i++) {
        rail[i] = (char *)malloc((rail_length[i] + 1) * sizeof(char));
        strncpy(rail[i], cipher_text + pos, rail_length[i]);
        pos += rail_length[i];
        rail_index[i] = 0;
    }

    row = 0; dir = 1;
    for (i = 0; i < cipher_text_size; i++) {
        plaintext[i] = rail[row][rail_index[row]++];
        if (row == 0) dir = 1;
        else if (row == rail_count - 1) dir = -1;
        row += dir;
    }

    plaintext[cipher_text_size] = '\0';

    for(i = 0; i < rail_count; i++) free(rail[i]);

    return plaintext;
}