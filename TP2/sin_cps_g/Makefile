# Author: Lauren Sampaio
# File: Makefile

CC=gcc
CFLAGS=-W -Wall -I.
LDFLAGS=-lm

sin_cos_g: sin_cos_g.o main.o
	$(CC) -o sin_cos_g sin_cos_g.o main.o $(LDFLAGS) 

sin_cos.o: sin_cos_g.c sin_cos_g.h
	$(CC) $(CFLAGS) -o sin_cos_g.o -c sin_cos_g.c

main.o: main.c sin_cos_g.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o sin_cos_g