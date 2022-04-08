/*
ncrypt is a simple symmetric key file encryption utility.

usage: 
    encrypt:    cat <infilename> | ./ncrypt -k <key> > <encryptedfilename>
    decrypt:    cat <encryptedfilename> | ./ncrypt -k <key> -d > <outfilename>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <getopt.h> // <-- had to add this one for some reason after vs code was updated.
                    //     worked before without it.

#define FC_ENCRYPT 1
#define FC_DECRYPT 0

#define RB_LEFT 1
#define RB_RIGHT 0

int rotatebits(int inchar, int offset, int lorr) {
    int tmpchar;

    switch (lorr) {
        case RB_LEFT:  tmpchar = ((inchar << offset) | (inchar >> (CHAR_BIT - offset))); break;
        case RB_RIGHT: tmpchar = ((inchar >> offset) | (inchar << (CHAR_BIT - offset))); break;
        default:       tmpchar = inchar;
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

int encrypt(FILE *fpin, FILE *fpout, char *key) { return flipcrypt(fpin, fpout, key, FC_ENCRYPT); }

int decrypt(FILE *fpin, FILE *fpout, char *key) { return flipcrypt(fpin, fpout, key, FC_DECRYPT); }

int main(int argc, char *argv[]) {

    int opt = -1;
    int abortflag = 0;

    char *key = NULL;

    FILE *infile = stdin;
    FILE *outfile = stdout;

    char *infilename = NULL;  //NULL value indicates stdin
    char *outfilename = NULL; //NULL value indicates stdout

    int (*fn)(FILE*, FILE*, char*) = encrypt; //encryption will be the default behavior
                                              //decryption will be set by cli arg if necessary

    // doing this WRONG, see example below for guidance
    // https://www.gnu.org/software/libc/manual/html_node/Getopt.html
    // for more info on how to properly handle these cli args
    // example uses abort().  don't use this use exit() instead if you have to use anything of that nature.
    while((opt = getopt(argc, argv, "dk:i:o:")) != -1) {
        switch(opt) {
            case 'd': fn = decrypt; break;
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

    // duplicate code alert!!
    // make the next 2 sequences into a function call for each.  

    // get a filepointer for input file name if provided
    if(infilename != NULL) {
        infile = fopen(infilename, "r"); //read access
        if(infile == NULL) {
            fprintf(stderr, "Error: could not open input file %s\n", infilename);
            abortflag = 1;
        }
    }

    // get a filepointer for output file name if provided
    if(outfilename != NULL) {
        outfile = fopen(outfilename, "w"); // write access
        if(outfile == NULL) {
            fprintf(stderr, "Error: could not open output file %s\n", outfilename);
            abortflag = 1;
        }
    }

    if(abortflag == 0) { fn(infile, outfile, key); }
    
    //close files if you have a valid file pointer (do not close std***)
    if((infile  != stdin)  && (infile  != NULL)) { fclose(infile); }
    if((outfile != stdout) && (outfile != NULL)) { fclose(outfile); }

    return abortflag;
}