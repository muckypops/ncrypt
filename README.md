# ncrypt
a simple symmetric key encryption utility

to encrypt: cat infilename | ./ncrypt -k key > encryptedfilename
  
to decrypt: cat encryptedfilename | ./ncrypt -d -k key > outfilename

to compile: gcc ncrypt.c -o ncrypt
