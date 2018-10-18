# Author: Lauren Sampaio
# File: Makefile

CC=gcc
CFLAGS=-W -Wall -I.
LDFLAGS=-lm

fsieve: fsieve.o main.o
	$(CC) -o fsieve fsieve.o main.o $(LDFLAGS) 

fsieve.o: fsieve.c fsieve.h
	$(CC) $(CFLAGS) -o fsieve.o -c fsieve.c

main.o: main.c fsieve.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o fsieve