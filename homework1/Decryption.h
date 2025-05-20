//
// Created by 임준식 on 25. 5. 6.
//

#ifndef INFORMATION_SECURITY_DECRYPTION_H
#define INFORMATION_SECURITY_DECRYPTION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * caesar_cipher_decryption(char *, int, int);
char * affine_cipher_decryption(char *, int, int, int);
char * vigenere_cipher_decryption(char *, int, const char *, int);
char * gronsfeld_cipher_decryption(char *, int, const char *, int);
char * rail_fence_cipher_decryption(char *, int, char *);
char * rail_fence_cipher_multi_rail_decryption(char *, int, char *, int);
#endif //INFORMATION_SECURITY_DECRYPTION_H
