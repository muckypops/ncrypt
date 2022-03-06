/*
ncrypt is a simple symmetric key file encryption utility.

usage: 
    encrypt:    cat infilename | ./ncrypt -k <key> > encryptedfilename
    decrypt:    cat encryptedfilename | ./ncrypt -k <key> -d outfilename
*/

#include "lib/encryption.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int opt = -1;

    char *key = NULL;

    int (*fn)(FILE*, FILE*, char*) = encrypt;

    while((opt = getopt(argc, argv, "dk:")) != -1) {
        switch(opt) {
            case 'd': fn = decrypt; break;
            case 'k': key = optarg; break;
            default:
                fprintf(stderr, "Usage: %s [-d -k <key>]\n", argv[0]);
                return -1;
        }
    }

    if(key == NULL) {
        fprintf(stderr, "Key required.  Use -k <key> to indicate key value.\n");
        return -1;
    }

    return fn(stdin, stdout, key);

}