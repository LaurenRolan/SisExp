# Author: Lauren Sampaio
# File: Makefile

CC=gcc
CFLAGS=-W -Wall -I.
LDFLAGS=-lm -lpthread -lrt

single: single.o 
	$(CC) -o single single.o $(LDFLAGS) 

single.o: singleton.c messages.h
	$(CC) $(CFLAGS) -o single.o -c singleton.c

clean:
	rm -rf *.o single
