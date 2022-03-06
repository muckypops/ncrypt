#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define FC_ENCRYPT 1
#define FC_DECRYPT 0

#define RB_LEFT 1
#define RB_RIGHT 0

unsigned char rotatebits(unsigned char inchar, int offset, int lorr) {
    unsigned char tmpchar;

    switch (lorr) {
        case RB_LEFT:
            tmpchar = ((inchar << offset) | (inchar >> (CHAR_BIT - offset)));
            break;
        case RB_RIGHT:
            tmpchar = ((inchar >> offset) | (inchar << (CHAR_BIT - offset)));
            break;
        default:
            tmpchar = inchar;
    }

    return tmpchar;
}

int flipcrypt(char *instr, int instrlen, char *outstr, char *key, int keylen, int eord) {

    unsigned char tmpchar;

    int i, ik, broffset;

    i = 0;
    ik = 0;

    while (i < instrlen) {
        
        // broffset determines bit rotation offset based on key value
        broffset = (key[ik] % CHAR_BIT);
        
        tmpchar = instr[i];

        if(eord == FC_ENCRYPT) tmpchar = rotatebits(tmpchar, broffset, RB_RIGHT);

        outstr[i] = (tmpchar ^ key[ik]);

        tmpchar = outstr[i];

        if(eord == FC_DECRYPT) outstr[i] = rotatebits(tmpchar, broffset, RB_LEFT);

        i++;
        ik++;
        if(ik == (keylen -1)) ik = 0;
    }

    return 0;
}

int encrypt(char *instr, int instrlen, char *outstr, char *key, int keylen) {
    flipcrypt(instr, instrlen, outstr, key, keylen, FC_ENCRYPT);
    return 0;
}

int decrypt(char *instr, int instrlen, char *outstr, char *key, int keylen) {
    flipcrypt(instr, instrlen, outstr, key, keylen, FC_DECRYPT);
    return 0;
}