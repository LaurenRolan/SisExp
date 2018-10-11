/* Author: Lauren Sampaio
 * File: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "iplot.h"

int main( ) 
{
	int borne; /* Nombre d'interval */
	int pid; /* PID du processus fils */
	
	do
	{
		printf("Type the number of the interval: [0, ");
		scanf("%d", &borne);
		writeCommand(borne);

		pid = fork( );

		if(pid < 0) {
			printf("Erreur: échec du fork()\n");
			exit(EXIT_FAILURE);
		} else if( pid == 0 ) {
			printf("Processus fils : pid = %d\n", getpid());
			sleep(1);
			execlp("gnuplot", "gnuplot","-persist", "commandes.gp", 0);
			exit(EXIT_SUCCESS);
		} else {
			printf("Ici le père: le fils a un pid=%d\n", pid );
			wait(0); 
			printf("Fin du père.\n");	
		}
	}while(1);
	return 0;
}
