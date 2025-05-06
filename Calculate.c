#include "Calculate.h"

int mod_inverse(int x, int y){
    for (int i = 1; i < y; i++) {
        if ((x * i) % y == 1) return i;
    }
    return -1;
}

void remove_newline(char *str) {
    size_t len = my_strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
int my_strlen(char * str){
    int len = 0;
    while(str[len] != '\0'){
        len++;
    }
    return len;
}
