/* Author: Lauren Rolan
 * File: agent2.c
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
#include <time.h>
#include <semaphore.h>
#include "messages.h"

#define SEM_COURRIEL "tp7"
typedef sem_t semaphore_t;

boite_struct * boite;
semaphore_t * sem_courriel;

void create_message(char * msg, char * imp) ;
void insert_message(char * msg, int courriel);
void send_stuff(int sig);
void isImportant(char * imp);

void handle_fatal_error(char message[]);
semaphore_t *create_and_open_semaphore(char *name);
semaphore_t *open_semaphore(char *name);
void destroy_semaphore(semaphore_t *sem, char *name);
void P(semaphore_t *sem);
void V(semaphore_t *sem);

int main()
{
	struct sigaction action;
	action.sa_handler = &send_stuff;
	sigaction(SIGALRM, &action, NULL);

	int fd;

	sem_courriel = open_semaphore(SEM_COURRIEL);


	fd = shm_open("/oss0612",  O_RDWR, 0644);

	if(fd == -1) {
		fprintf(stderr, "Error while opening mem shared\n");
	}
	 boite = (boite_struct*) mmap(&boite,
	 sizeof(boite), 
	 PROT_READ | PROT_WRITE, 
	 MAP_SHARED,
	 fd, 
	 0);

	if (boite == (void *) -1) {
		printf("Error allocating shared memory using mmap!\n");
		exit(1);
	}
	
	alarm(1);
	
	while(1);
	
	munmap(boite, sizeof(boite));

	return 0;
}

void create_message(char * msg, char * imp) {
	FILE * fp;
	fp = popen("date", "r");
	char date[100];
	fgets(date, sizeof(date), fp);

	size_t ln = strlen(date)-1;
	if (date[ln] == '\n')
    	date[ln] = '\0';
		
	if (strcmp(imp, "OSS")==0)
		sprintf(msg, "[%s] %s/He is going to be there at 4 o'clock.", date, imp);
	else
		sprintf(msg, "[%s] %s/Not an important message.", date, imp);
	
	printf("%s\n", msg);

}

void insert_message(char * msg, int courriel) {
	char agent[20];
	strcpy(boite->messages[courriel].message, msg);
	sprintf(agent, "%d", getpid());
	strcpy(boite->messages[courriel].agent, agent);
}

void send_stuff(int sig) {
	char message[256];
	char importance[4];
	int courriel = 0;
	
	isImportant(importance);
	
	if (strcmp(importance, "OSS")==0)
		fprintf(stderr, "x");
	else
		fprintf(stderr, ".");
	create_message(message, importance);
	
	P(sem_courriel);
	sem_getvalue(sem_courriel, &courriel);
	insert_message(message, courriel);
	alarm(0);
	alarm(rand() % 10);
}

void isImportant(char * imp)
{
	if(rand() % 100 > 85) {
		strcpy(imp, "OSS");
	} else {
		strcpy(imp, "NUL");
	}
}

void handle_fatal_error(char message[]) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

semaphore_t *open_semaphore(char *name) {
	semaphore_t *sem = NULL;

	sem = sem_open(name, O_RDWR);
	if (sem == NULL) {
		sem_unlink(name);
		handle_fatal_error("Error trying to open semaphore\n");
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