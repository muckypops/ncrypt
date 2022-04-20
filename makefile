all: ncrypt.o
	gcc -o ncrypt ncrypt.o
ncrypt.o: ncrypt.c
	gcc -c ncrypt.c
clean:
	rm *.o ncrypt