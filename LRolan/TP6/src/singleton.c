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
char * decypher(char * message, int size);
int is_important(char *message);

int main()
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
	boite = *((boite_struct *)shared_memory);


	display_coded_messages(&boite, 3);
	decode_messages(&boite, 3);

	return 0;
}


char * decypher(char * message, int size)
{
	int i;
	char *answer;
	answer = (char*) malloc(sizeof(char)*size);
	strcpy(answer, message);
	for(i = 0; i < size; i++)
	{
		if( message[i] >= 'A' && message[i] <= 'Z' )
		{
	 		if(message[i] <= 'M')
			{
				answer[i] = message[i] + 13;
			}
			else {
				answer[i] = message[i] - 13;
			}
		}
		else if(message[i] >= 'a' && message[i] <= 'z')
		{
			if(message[i] <= 'm')
			{
				answer[i] = message[i] + 13;
			}
			else {
				answer[i] = message[i] - 13;
			}
		}
		else {
			answer[i] = message[i];
		}
	}
	return answer;
}

void decode_messages(boite_struct *boite, int num_messages)
{
	int msg;
	char * msg_dec;
	FILE *fd;
	char path[100];

	snprintf(path, sizeof(path), "messages-%d.txt", getpid());

	fd = fopen(path, "a+");
	if(fd < 0) {
		fprintf(stderr, "Error while opening file.\n");
		exit(-1);
	}
	for(msg = 0; msg < num_messages; msg++)
	{
		message_struct message = boite->messages[msg];
		msg_dec = decypher(message.message, strlen(message.message));
		if(is_important(msg_dec)) {
			fprintf(fd, "%s", msg_dec);
			fprintf(fd, "\n");
		}
		else {	
			printf("%s\n", msg_dec);
		}	
	}
}

int is_important(char *message)
{
	if(strstr(message, "OSS") != NULL) {
		return 1;
	}
	return 0;
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
	}	
}
