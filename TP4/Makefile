# Author: Lauren Sampaio
# File: Makefile

CC=gcc
CFLAGS=-W -Wall -I. 
LDFLAGS=-lm -lpthread

matrix: matrix.o main.o
	$(CC) -o matrix matrix.o main.o $(LDFLAGS) 

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -o matrix.o -c matrix.c

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o matrix