/*
ncrypt is a simple symmetric key file encryption utility.

usage: 
    encrypt:    cat <infilename> | ./ncrypt -k <key> > <encryptedfilename>
    decrypt:    cat <encryptedfilename> | ./ncrypt -k <key> -d > <outfilename>

    UPDATE THIS 
*/
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h> // <-- had to add this one for some reason after vs code was updated.
                    //     worked before without it.

#define FC_ENCRYPT 1
#define FC_DECRYPT 0

#define RB_LEFT 1
#define RB_RIGHT 0

int rotatebits(const uint8_t inchar, const int offset, const int lorr) {
    int tmpchar;

    switch (lorr) {
        case RB_LEFT:  tmpchar = ((inchar << offset) | (inchar >> (CHAR_BIT - offset))); break;
        case RB_RIGHT: tmpchar = ((inchar >> offset) | (inchar << (CHAR_BIT - offset))); break;
        default:       tmpchar = inchar;
    }

    return tmpchar;
}

int flipcrypt(FILE *fpin, FILE *fpout, const char *key, const int eord) {

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

int openfile(const char *filename, FILE **fileptr, const char *mode) {
    int errcount = 0;
    
    if(filename != NULL) {
        *fileptr = fopen(filename, mode);
        if(*fileptr == NULL) {
            fprintf(stderr, "Error: could not open file %s\n", filename);
            errcount += 1;
        }
    }
    return errcount;
}

int main(int argc, char *argv[]) {

    int opt = -1; 
    int errcount = 0; //increment this counter each time there is an error
    int cryptmode = FC_ENCRYPT; //encryption will be the default behavior
                                //decryption will be set by cli arg if necessary

    char *key = NULL;

    FILE *infileptr = stdin;
    FILE *outfileptr = stdout;

    char *infilename = NULL;  //NULL value indicates stdin
    char *outfilename = NULL; //NULL value indicates stdout

    // see example below for guidance
    // https://www.gnu.org/software/libc/manual/html_node/Getopt.html
    while((opt = getopt(argc, argv, "dk:i:o:")) != -1) {
        switch(opt) {
            case 'd': cryptmode = FC_DECRYPT;
            case 'k': key = optarg; break;
            case 'i': infilename = optarg; break;
            case 'o': outfilename = optarg; break;
            default:
                fprintf(stderr, "Usage: %s [-d -k <key> -i <input file> -o <output file>]\n", argv[0]);
                return -1;
        }
    }

    if(key == NULL) {
        fprintf(stderr, "Key required.  Use -k <key> to indicate key value.\n");
        return -1;
    }


    // redirect input and/or output away from from std*** if filenames are provided
    errcount += openfile(infilename,  &infileptr,  "rb");
    errcount += openfile(outfilename, &outfileptr, "wb");

    // call appropriate function for encryption or decryption
    if(errcount == 0) { flipcrypt(infileptr, outfileptr, key, cryptmode); }
    
    //close files if you have a valid file pointer (do not close std***)
    if((infileptr  != stdin)  && (infileptr  != NULL)) { fclose(infileptr); }
    if((outfileptr != stdout) && (outfileptr != NULL)) { fclose(outfileptr); }

    return errcount;
}