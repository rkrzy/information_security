//
// Created by 임준식 on 25. 5. 6.
//

#ifndef INFORMATION_SECURITY_ENCRYPTION_H
#define INFORMATION_SECURITY_ENCRYPTION_H
#include <stdio.h>
#include <stdlib.h>
#include "Calculate.h"
char * caesar_cipher_encryption(char *, int, int);
char * affine_cipher_encryption(char *, int, int, int);
char * vigenere_cipher_encryption(char *, int, const char *, int);
char * gronsfeld_cipher_encryption(char *, int, const char *, int);
char * rail_fence_cipher_encryption(char *, int, char *);
char * rail_fence_cipher_multi_rail_encryption(char *, int, char *, int);


#endif //INFORMATION_SECURITY_ENCRYPTION_H

