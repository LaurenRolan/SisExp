/* Author: Lauren Rolan
 * File: singleton.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>
#include "messages.h"

void display_coded_messages(boite_struct *boite, int num_messages);
void decode_messages(boite_struct *boite, int num_messages);

int main(int argc, char const *argv[])
{
	boite_struct boite;
	int fd;
	fd = shm_open("/oss0612",  O_RDWR, 0644);

	if(fd == -1) {
		fprintf(stderr, "Error while opening mem shared\n");
	}
	if(ftruncate(fd, sizeof(boite)) == -1) {
		fprintf(stderr, "Error while loading memory\n");
		exit(-1);
	}
	void *shared_memory = mmap(&boite,
	 sizeof(boite), 
	 PROT_READ | PROT_WRITE, 
	 MAP_SHARED,
	 fd, 
	 0);

	if (shared_memory == (void *) -1) {
		printf("Error allocating shared memory using mmap!\n");
		exit(1);
	}
	
	display_coded_messages(&boite, 3);
	decode_messages(&boite, 3);
	return 0;
}

void decode_messages(boite_struct *boite, int num_messages)
{
	int msg;
	for(msg = 0; msg < num_messages; msg++)
	{
		message_struct message = boite->messages[msg];
		int dec = 0;
		for(dec = 100; dec < 300; dec ++)
		{
			printf("Dec(%d)\t", dec);
			int index;
			printf("%s", message.message);
			for(index = 0; index < strlen(message.message); index++)
			{
				printf("%c ", message.message[index] + dec + 13);
			}
			printf("\n");
		}	
	}
}

void display_coded_messages(boite_struct *boite, int num_messages)
{
	fprintf(stderr, "%p\n", boite);
	int i;
	printf("IntA(%d)  IntB(%d)\n", boite->a, boite->b);
	for(i = 0; i < num_messages; i++)
	{
		message_struct msg = boite->messages[i];
		printf("Agent: %s  Message: %s\n", msg.agent, msg.message);
		for(int j = 0; j < strlen(msg.agent); j++)
			printf("%d ", msg.agent[j]);
	}	
}
