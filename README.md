# ncrypt
a simple symmetric key encryption utility

Usage: ./ncrypt [-d -k \<key\> -i \<input file\> -o \<output file\>]

to compile: gcc ncrypt.c -o ncrypt

if no intput or output filename ncrypt will stdin and stdout respectively and can be used as follows:
  
to encrypt: cat \<infilename\> | ./ncrypt -k \<key\> \> \<encryptedfilename\>\
        or: ./ncrypt -k \<key\> -i \<input file\> \> \<encryptedfilename\>
  
same for decryption but with -d option
