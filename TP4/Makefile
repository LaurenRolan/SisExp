# Author: Lauren Sampaio
# File: Makefile

CC=gcc
CFLAGS=-W -Wall -I. 
LDFLAGS=-lm -lpthread

matrix: matrix.o main.o
	$(CC) -o matrix matrix.o main.o $(LDFLAGS) 

matrix.o: matrix_product.c matrix_product.h
	$(CC) $(CFLAGS) -o matrix.o -c matrix_product.c

main.o: main.c matrix_product.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o matrix