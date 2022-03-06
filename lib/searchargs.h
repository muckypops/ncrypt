#include <stdio.h>
#include <string.h>

int searchargs(const char *searchstr, int argc, char *argv[]) {
    int rtnval = -1;

    for (int i = 1; i < argc; i++) {
        if(strcmp(searchstr, argv[i]) == 0) {
            rtnval = i + 1;
        }
    }

    return rtnval;
}