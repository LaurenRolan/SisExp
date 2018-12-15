/* Author: Lauren Rolan
 * File: case_officer2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <semaphore.h>
#include <unistd.h>
#include "messages.h"
#include "sem.h"
#include "shm.h"

boite_struct * boite;
semaphore_t * sem_courriel;

void read_messages();

int main()
{
	
	sem_courriel = create_and_open_semaphore(SEM_COURRIEL);
	
	boite = create_shm();
	
	while(1){
		read_messages();
		sleep(1);
	}

	close_shm(boite);
	return 0;
}

void read_messages()
{
	int courriel = get_semaphore_value(sem_courriel);
	int i;
	
	if(courriel < 5)
	{
		for(i = MAX_LETTRES - 1; i >= courriel; i--)
		{
			V(sem_courriel);
			message_struct msg = boite->messages[i];
			char decoded[256];
			strcpy(decoded, msg.message);
			decode_message(decoded);
			if(is_important(decoded))
			{
				fprintf(stderr, "x");
			} else {
				fprintf(stderr, ".");
			}
		}
	}
}