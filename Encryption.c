#include "Encryption.h"

char * caesar_cipher_encryption(char * plaintext, int plaintext_size, int key)
{
    int i;

    for(i = 0; i < plaintext_size; i++){
        if((plaintext[i] >= 'A') && (plaintext[i] <= 'Z'))
        {
            plaintext[i] = (plaintext[i] - 'A' + key + 26) % 26 + 'A';
        }
        else if((plaintext[i] >= 'a') && (plaintext[i] <= 'z'))
        {
            plaintext[i] = (plaintext[i] -'a' + key + 26) % 26 + 'a';
        }
        else ;
    }
    return plaintext;
}
char * affine_cipher_encryption(char * plaintext, int plaintext_size, int key1, int key2)
{
    int i;
    for(i = 0; i < plaintext_size; i++){
        if((plaintext[i] >= 'A') && (plaintext[i] <= 'Z'))
        {
            plaintext[i] = ((plaintext[i] - 'A') * key1 + key2 + 26) % 26 + 'A';
        }
        else if((plaintext[i] >= 'a') && (plaintext[i] <= 'z'))
        {
            plaintext[i] = ((plaintext[i] - 'a') * key1 + key2 + 26) % 26 + 'a';
        }
    }
    return plaintext;
}
char * vigenere_cipher_encryption(char * plaintext, int plaintext_size, const char * key, int key_size)
{
    int i = 0;
    int j = 0;
    int key_shift;
    for(i = 0; i < plaintext_size; i++){
        j = i % key_size;
        key_shift = (key[j] >= 'A' && key[j] <= 'Z') ? key[j] - 'A' : key[j] - 'a';
            if((plaintext[i] >= 'a') && (plaintext[i] <= 'z')) {
                plaintext[i] = ((plaintext[i] - 'a') + key_shift + 26) % 26 + 'a';
            }
            else if((plaintext[i] >= 'A') && (plaintext[i] <= 'Z')) {
                plaintext[i] = ((plaintext[i] - 'A') + key_shift + 26) % 26 + 'A';
            }

    }
    return plaintext;
}
char * gronsfeld_cipher_encryption(char * plaintext, int plaintext_size, const char * key, int key_size)
{
    int i = 0;
    int j = 0;
    int key_shift = 0;
    for(i = 0; i < plaintext_size; i++){
        j = i % key_size;
        key_shift = (key[j] >= '0' && key[j] <= '9') ? key[j] - '0' : -1;
        if(key_shift == -1)
        {
            fprintf(stderr, "키값에 숫자가 아닌 문자가 포함되어 있습니다.\n");
            return NULL;
        }
        if((plaintext[i] >= 'a') && (plaintext[i] <= 'z')){
            plaintext[i] = ((plaintext[i] - 'a') + key_shift + 26) % 26 + 'a';
        }else if((plaintext[i] >= 'A') && (plaintext[i] <= 'Z')){
            plaintext[i] = ((plaintext[i] - 'A') + key_shift + 26) % 26 + 'A';
        }
    }
    return plaintext;
}

char * rail_fence_cipher_encryption(char * plaintext, int plaintext_size, char * cipher_text)
{
    char rail1[50];
    char rail2[50];
    char * rail[2] = {rail1, rail2};
    int i = 0;
    int val = 0;
    for(i = 0; i < plaintext_size; i++){
        if(((plaintext[i] >= 'a') && (plaintext[i] <= 'z')) ||
        ((plaintext[i] >= 'A') && (plaintext[i] <= 'Z')))
        {
            val = i%2;
            rail[val][i/2] = plaintext[i];
        }
    }
    if(plaintext_size%2 == 0){
        for(i = 0; i < (plaintext_size/2); i++)
        {
            cipher_text[i] = rail[0][i];
            cipher_text[i + (plaintext_size/2)] = rail[1][i];
        }
    }
    else{
        for(i = 0; i < (plaintext_size/2); i++)
        {
            cipher_text[i] = rail[0][i];
            cipher_text[i + (plaintext_size/2) + 1] = rail[1][i];
        }
        cipher_text[plaintext_size/2] = rail[0][i];
    }
    return cipher_text;
}
char * rail_fence_cipher_multi_rail_encryption(char * plaintext, int plaintext_size, char * cipher_text, int rail_count)
{
    int i = 0;
    int j = 0;
    int dir = 1;
    int index = 0;
    int row = 0;
    int rail_index[rail_count];
    char * rail[rail_count];
    for(i = 0; i < rail_count; i++){
        rail[i] = (char *)malloc((plaintext_size + 1) * sizeof(char));
        rail_index[i] = 0;
    }
    for(i = 0; i < plaintext_size; i++){
        if(((plaintext[i] >= 'a') && (plaintext[i] <= 'z')) ||
           ((plaintext[i] >= 'A') && (plaintext[i] <= 'Z')))
        {
            rail[row][rail_index[row]++] = plaintext[i];

            if(row == 0){
                dir = 1;
            }else if(row == rail_count - 1) dir = -1;

            row += dir;
        }
    }
    for(i = 0; i < rail_count; i++){
        for(j = 0; j < rail_index[i]; j++){
            cipher_text[index++] = rail[i][j];
        }
        free(rail[i]);
    }
    cipher_text[index] = '\0';

    return cipher_text;
}