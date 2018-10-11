# Author: Lauren Sampaio
# File: Makefile

CC=gcc
CFLAGS=-W -Wall -I.
LDFLAGS=

iplot: iplot.o main.o
	$(CC) -o iplot iplot.o main.o $(LDFLAGS) 

iplot.o: iplot.c iplot.h
	$(CC) $(CFLAGS) -o iplot.o -c iplot.c

main.o: main.c iplot.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o iplot