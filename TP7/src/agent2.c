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
#include "messages.h"
#include "sem_stuff.h"

boite_struct * boite;

void create_message(char * msg) ;
void insert_message(char * msg);
void send_stuff(int sig);

int main()
{
	struct sigaction action;
	action.sa_handler = &send_stuff;
	sigaction(SIGALRM, &action, NULL);

	int fd;

	semaphore_t * sem_courriel;
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

	while(1) {
		alarm(2); //Sleep aleatoire
	}
	

	munmap(boite, sizeof(boite));	

	return 0;
}

void create_message(char * msg) {
	FILE * fp;	
	fp = popen("date", "r");
	char date[100];
	fgets(date, sizeof(date), fp);

	size_t ln = strlen(date)-1;
	if (date[ln] == '\n')
    	date[ln] = '\0';
	
	sprintf(msg, "[%s] NUL/Je suis un intrus.", date);
	printf("%s\n", msg);

}

void insert_message(char * msg) {
	strcpy(boite->messages[0].message, msg);
}

void send_stuff(int sig) {
	char message[256];
	create_message(message);
	insert_message(message);
}