#include "file.h"

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
