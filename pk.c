#include <stdio.h>
#include "lib/encryption.h"

void printhex(unsigned char *msg, int msglen) {
    for(int i = 0; i < msglen; i++) 
        printf("0x%02X ", msg[i]);
    putchar('\n');
}

int main() {

    char msg[] = "Hola!  Mi nombre es Miguel DeCastro.  I am an international playboy and a bit of a pimp.  I have written several books on the subject.  You should check them out at your local library!";
    int msglen = sizeof msg;

    char key[] = "(fuck you)";
    int keylen = sizeof key;
    
    char crypt[msglen];
    char msg2[msglen];

    char newkey[keylen];
    // char newkey[] = "some key value";
    // strcpy(newkey, key);
    memcpy(newkey, key, keylen);
    int newkeylen = sizeof newkey;


    printf("Welcome to pk passkeeper.\n");

    encrypt(msg, msglen, crypt, key, keylen);

    printf("    msg: %s\n", msg);
    printhex(msg, msglen);

    printf("    key: %s\n", key);
    printhex(key, keylen);
    
    printf("  crypt: %s\n", crypt);
    printhex(crypt, msglen);

    decrypt(crypt, msglen, msg2, newkey, newkeylen);

    // printf("CHAR_BIT=%d\n", CHAR_BIT);

    printf("decrypt: %s\n", msg2);
    printhex(msg2, msglen);



    return 0;

}