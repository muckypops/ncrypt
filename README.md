# ncrypt
a simple symmetric key encryption utility

Usage: ./ncrypt [-d -k \<key\> -i \<infilename\> -o \<outfilename\>]

to compile: gcc ncrypt.c -o ncrypt

if no input or output filename is provided ncrypt will use stdin and stdout respectively and can be used as follows:
  
to encrypt: cat \<infilename\> | ./ncrypt -k \<key\> \> \<outfilename\>\
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; or: ./ncrypt -k \<key\> -i \<input file\> \> \<outfilename\>\
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; or: cat \<infilename\> | ./ncrypt -k \<key\> -o \<outfilename\>
  
same for decryption but with -d option
