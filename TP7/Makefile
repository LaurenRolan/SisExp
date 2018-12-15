# Author: Lauren Sampaio
# File: Makefile
EXE = agent2 case_officer2

CC = gcc
SRC_DIR = src
OBJ_DIR = obj

OBJ = $(OBJ_DIR)/messages.o $(OBJ_DIR)/sem.o $(OBJ_DIR)/shm.o

CFLAGS=-W -Wall -Iinclude -pthread
LDFLAGS += -Llib -lrt
LDLIBS += 

.PHONY: all clean

all: $(EXE)

$(EXE): %: $(SRC_DIR)/%.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	$(RM) $(OBJ) $(EXE)

