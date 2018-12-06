# Author: Lauren Sampaio
# File: Makefile
EXE = singleton singleton2

CC = gcc
SRC_DIR = src
OBJ_DIR = obj

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS=-W -Wall -Iinclude
LDFLAGS += -Llib -lrt
LDLIBS += 

.PHONY: all clean

all: $(EXE)

$(EXE): %: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
clean:
	$(RM) $(OBJ) $(EXE)

