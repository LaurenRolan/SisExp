# Author: Lauren Sampaio
# File: Makefile

CC=gcc
CFLAGS=-W -Wall -I. 
LDFLAGS=-lm -lpthread

plotter: plotter.o
	$(CC) -o plotter plotter.o $(LDFLAGS) 

plotter.o: plotter.c
	$(CC) $(CFLAGS) -o plotter.o -c plotter.c

clean:
	rm -rf *.o plotter