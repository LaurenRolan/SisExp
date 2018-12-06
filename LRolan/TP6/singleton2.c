/* Author: Lauren Rolan
 * File: singleton2.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>
#include <signal.h>
#include "messages.h"

int current = 0;
int dead_pid;
boite_struct boite;

char * cypher(char * message, int size);
void kill_agent(int dead_pid);
void pretend_to_be_him(boite_struct *boite, int size, int dead_pid);
void update(int sig);

int main(int argc, char const *argv[])
{
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

	dead_pid = boite.messages[0].agent;
	kill_agent(dead_pid);
	pretend_to_be_him(&boite, 3, dead_pid);

	return 0;
}


char * cypher(char * message, int size)
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

void kill_agent(int dead_pid)
{
	kill(dead_pid, 1);
}

void update(int sig)
{
	FILE * fp;	
	fp = popen("date", "r");

	char * date[50];
	fgets(date, sizeof(date)-1, fp);
	
	char * msg;
	sprintf(msg, "[%s] NUL/Je suis un intrus.", date);

	boite.messages[0].agent = dead_pid;
	char *cyphred = cypher(msg, strlen(msg));
	strcpy(boite.messages[0].message, cyphred);

	alarm(5);
}

void pretend_to_be_him()
{
	struct sigaction action;
	action.sa_handler = &update;
	sigaction(SIGALRM, &action, NULL);
	alarm(1);
}
