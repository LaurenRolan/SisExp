# Author: Lauren Sampaio
# File: Makefile
EXE = agent2 case_officer2

CC = gcc
SRC_DIR = src
OBJ_DIR = obj

CFLAGS=-W -Wall -Iinclude -pthread
LDFLAGS += -Llib -lrt
LDLIBS += 

.PHONY: all clean

all: $(EXE)

$(EXE): %: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	$(RM) $(OBJ) $(EXE)

