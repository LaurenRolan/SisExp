# Author: Lauren Sampaio
# File: Makefile
EXE = agent2 case_officer2

CC = gcc
SRC_DIR = src
OBJ_DIR = obj

OBJ = sem_stuff.o

CFLAGS=-W -Wall -Iinclude
LDFLAGS += -Llib -lrt
LDLIBS += 

.PHONY: all clean

all: $(EXE)

$(EXE): %: $(SRC_DIR)/%.c $(OBJ_DIR)/sem_stuff.o
	$(CC) $(CFLAGS) -o $@ $< $^ $(LDFLAGS)

$(OBJ_DIR)/sem_stuff.o: $(SRC_DIR)/sem_stuff.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXE)

