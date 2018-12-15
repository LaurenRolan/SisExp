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
#include <semaphore.h>
#include "messages.h"

#define SEM_COURRIEL "tp7"
typedef sem_t semaphore_t;

boite_struct * boite;
semaphore_t * sem_courriel;

void handle_fatal_error(char message[]);
semaphore_t *create_and_open_semaphore(char *name);
semaphore_t *open_semaphore(char *name);
void destroy_semaphore(semaphore_t *sem, char *name);
void P(semaphore_t *sem);
void V(semaphore_t *sem);
void read_messages();

int main()
{
	int fd;
	sem_courriel = create_and_open_semaphore(SEM_COURRIEL);

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
	
	while(1){
		read_messages();
		sleep(1);
	}

	munmap(boite, sizeof(boite));
	return 0;
}

void read_messages()
{
	int courriel=0;
	int i;
	sem_getvalue(sem_courriel, &courriel);
	if(courriel < 5)
	{
		for(i = MAX_LETTRES - 1; i >= courriel; i--)
		{
			V(sem_courriel);
			message_struct msg = boite->messages[i];
			if(strstr(msg.message, "OSS") != NULL)
			{
				fprintf(stderr, "x");
			} else {
				fprintf(stderr, ".");
			}
		}
	}
}

void handle_fatal_error(char message[]) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}


semaphore_t *create_and_open_semaphore(char *name) {
	semaphore_t *sem = NULL;

	sem = sem_open(name, O_CREAT, 0644, 1);
	sem_init(sem, 0, MAX_LETTRES);
	if (sem == SEM_FAILED) {
		handle_fatal_error("Error trying to create semaphore\n");
	}
	return sem;
}

void destroy_semaphore(semaphore_t *sem, char *name) {
	int r = 0;

	r = sem_close(sem);
	if (r < 0) {
		handle_fatal_error("Error trying to destroy semaphore\n");
	}
	r = sem_unlink(name);
	if (r < 0) {
		perror("Error trying to unlink semaphore\n");
	}
}

void P(semaphore_t *sem) {
	int r = 0;

	r = sem_wait(sem);
	if (r < 0) {
		handle_fatal_error("Error with P() operation\n");
	}
}

void V(semaphore_t *sem) {
	int r = 0;

	sem_post(sem);
	if (r < 0) {
		handle_fatal_error("Error with V() operation\n");
	}
}