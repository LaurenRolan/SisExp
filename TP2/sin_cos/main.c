/* Author: Lauren Sampaio
 * File: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "sin_cos.h"

double angle; /* Nombre d'interval */
int pid1; /* PID du processus fils 1 */
int pid2; /* PID du processus fils 2 */

void update( int sig )
{
	sinus(pid1, angle);
	cosinus(pid2, angle);
	angle += 10;
	if(angle > 360)
		exit(0);
	else
		alarm(1);
}

int main( ) 
{
	struct sigaction action;
	angle = 0.0;

	action.sa_handler = &update;
	sigaction(SIGALRM, &action, NULL);

	pid1 = fork( );

	
	if(pid1 < 0 ) {
		printf("Erreur: échec du fork()\n");
		exit(EXIT_FAILURE);
	} else if( pid1 == 0 ) {
		pid1 = getpid();
		printf("Fils 1: %d\n", pid1);
		for(;;);
	} else {
		pid2 = fork( );
		if (pid2 < 0) {	
			printf("Erreur: échec du fork()\n");
			exit(EXIT_FAILURE);
		} else if( pid2 == 0 ) {
			pid2 = getpid();
			printf("Fils 2: %d\n", pid2);
			for(;;);
		} else {
			printf("Pere: %d\n", getpid());
			alarm(1);
			for(;;);
		}
	}

	return 0;
}
