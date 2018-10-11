# Author: Lauren Sampaio
# File: Makefile

CC=gcc
CFLAGS=-W -Wall -I.
LDFLAGS=-lm

sin_cos: sin_cos.o main.o
	$(CC) -o sin_cos sin_cos.o main.o $(LDFLAGS) 

sin_cos.o: sin_cos.c sin_cos.h
	$(CC) $(CFLAGS) -o sin_cos.o -c sin_cos.c

main.o: main.c sin_cos.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o sin_cos