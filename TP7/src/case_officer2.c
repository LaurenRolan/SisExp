/* Author: Lauren Rolan
 * File: case_officer2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>
#include <signal.h>
#include "messages.h"
#include "sem_stuff.h"

boite_struct * boite;

void read_messages(int sig);

int main()
{
	int fd;
	semaphore_t * sem_courriel;
	sem_courriel = create_and_open_semaphore(SEM_COURRIEL);

	struct sigaction action;
	action.sa_handler = &read_messages;
	sigaction(SIGALRM, &action, NULL);

	fd = shm_open("/oss0612",  O_RDWR | O_CREAT, 0644);
	if(fd == -1) {
		fprintf(stderr, "Error while opening mem shared\n");
	}
	if(ftruncate(fd, sizeof(boite)) == -1) {
		fprintf(stderr, "Error while loading memory\n");
		exit(-1);
	}
	boite = (boite_struct *) mmap(&boite,
	 sizeof(boite), 
	 PROT_READ | PROT_WRITE, 
	 MAP_SHARED,
	 fd, 
	 0);

	if (boite == (void *) -1) {
		printf("Error allocating shared memory using mmap!\n");
		exit(1);
	}
	while(1) {
		alarm(5);
	}

	munmap(boite, sizeof(boite));
	return 0;
}

void read_messages()
{
	for(int i = 0; i < MAX_LETTRES; i++)
	{
		message_struct msg = boite->messages[i];
		printf("Agent: %s  Message: %s\n", msg.agent, msg.message);
	}
}