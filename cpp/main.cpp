#include "main.h"

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

    // perform encryption or decryption
    if(errcount == 0) { flipcrypt(infileptr, outfileptr, key, cryptmode); }
    
    //close files if you have a valid file pointer (do not close std***)
    if((infileptr  != stdin)  && (infileptr  != NULL)) { fclose(infileptr); }
    if((outfileptr != stdout) && (outfileptr != NULL)) { fclose(outfileptr); }

    return errcount;
}