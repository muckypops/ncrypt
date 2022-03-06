#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#define FC_ENCRYPT 1
#define FC_DECRYPT 0

#define RB_LEFT 1
#define RB_RIGHT 0

int rotatebits(int inchar, int offset, int lorr) {
    int tmpchar;

    switch (lorr) {
        case RB_LEFT: tmpchar = ((inchar << offset) | (inchar >> (CHAR_BIT - offset))); break;
        case RB_RIGHT: tmpchar = ((inchar >> offset) | (inchar << (CHAR_BIT - offset))); break;
        default: tmpchar = inchar;
    }

    return tmpchar;
}

int flipcrypt(FILE *fpin, FILE *fpout, char *key, int eord) {

    int tmpchar;
    int keylen = strlen(key);
    int ik, broffset;

    ik = 0;

    tmpchar = fgetc(fpin);
    while (tmpchar != EOF) {
        
        // broffset determines bit rotation offset based on key value
        broffset = (key[ik] % CHAR_BIT);

        if(eord == FC_ENCRYPT) tmpchar = rotatebits(tmpchar, broffset, RB_RIGHT);

        tmpchar = (tmpchar ^ key[ik]);

        if(eord == FC_DECRYPT) tmpchar = rotatebits(tmpchar, broffset, RB_LEFT);

        ik++;
        if(ik == (keylen)) ik = 0;
        fputc(tmpchar, fpout);
        tmpchar = fgetc(fpin);
    }

    return 0;
}

int encrypt(FILE *fpin, FILE *fpout, char *key) {
    return flipcrypt(fpin, fpout, key, FC_ENCRYPT);
}

int decrypt(FILE *fpin, FILE *fpout, char *key) {
    return flipcrypt(fpin, fpout, key, FC_DECRYPT);
}