/* Author: Lauren Sampaio
 * File: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "sin_cos_g.h"

double angle = 0.0; /* Nombre d'interval */

void update( int sig )
{
	printf("Update\n");
	sinus(angle);
	cosinus(angle);
	angle += 10;
	if(angle > 360)
    {
        execlp("gnuplot", "gnuplot","-persist", "commandes.gp", 0);
        exit(2);
    }
		
	else
    {
        alarm(1);
    }
		
}

int main( ) 
{
    int status;
	int pid1; /* PID du processus fils 1 */
	int pid2; /* PID du processus fils 2 */
	struct sigaction action;

	action.sa_handler = &update;
	sigaction(SIGALRM, &action, NULL);

	FILE * commande = fopen("commandes.gp", "w");

	if(!commande)	/* Si ce n'est pas possible d'ouvrir le fichier */
		exit(EXIT_FAILURE);
	
	/* Récrire le fichier <<commande.gp>> */
	fprintf(commande, "plot \"sinus.txt\" using 1:2 smooth cspline\n");
	fprintf(commande, "plot \"cosinus.txt\" using 1:2 smooth cspline\n"); 
	fclose(commande);


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
			wait(&status);
		}
	}
	
	return 0;
}
