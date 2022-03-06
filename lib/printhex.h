#include <stdio.h>

void printhex(unsigned char *msg, int msglen) {
    for(int i = 0; i < msglen; i++) 
        printf("0x%02X ", msg[i]);
    putchar('\n');
}