#include <stdio.h>

void print_bin(unsigned int integer, unsigned int bitcount) {
    while(bitcount--) {
        printf("%d", ((integer >> bitcount) & 1));
    }
}