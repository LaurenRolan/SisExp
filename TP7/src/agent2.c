/* Author: Lauren Rolan
 * File: agent2.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "messages.h"
#include "sem.h"
#include "shm.h"

boite_struct * boite;
semaphore_t * sem_courriel;

void insert_message(char * msg, int courriel);
void send_stuff(int sig);


int main()
{
	struct sigaction action;
	action.sa_handler = &send_stuff;
	sigaction(SIGUSR2, &action, NULL);
	
	sem_courriel = open_semaphore(SEM_COURRIEL);

	boite = open_shm();
	
	raise(SIGUSR2);
	fprintf(stderr, "OI");
	while(1);
	
	close_shm(boite);

	return 0;
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
	int courriel;
	
	get_importance(importance);
	
	if (strcmp(importance, "OSS")==0)
		fprintf(stderr, "x");
	else
		fprintf(stderr, ".");
	create_message(message, importance);
	
	P(sem_courriel);
	courriel = get_semaphore_value(sem_courriel);

	code_message(message);
	insert_message(message, courriel);

	sleep(rand() % 10);
	raise(SIGUSR2);
}
