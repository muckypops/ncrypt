# ncrypt
a simple symmetric key encryption utility

to encrypt: cat <infilename> | ./ncrypt -k<key> > outfilename
  
to decrypt: cat <outfilename> | ./ncrypt -k<key> > <infilename>
