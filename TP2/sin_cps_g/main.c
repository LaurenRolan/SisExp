/* Author: Lauren Sampaio
 * File: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sin_cos_g.h"

int main( ) 
{
	double angle = 0.0; /* Nombre d'interval */
	int pid1; /* PID du processus fils 1 */
	int pid2; /* PID du processus fils 2 */

	FILE * cos = fopen("cosinus.txt", "w");
	FILE * sin = fopen("sinus.txt", "w");
	if(!cos || !sin)
		exit(EXIT_FAILURE);
	fclose(cos);
	fclose(sin);
	
	pid2 = fork( );
	pid1 = fork( );

	do {
		if(pid1 < 0 || pid2 < 0) {
			printf("Erreur: échec du fork()\n");
			exit(EXIT_FAILURE);
		} else if( pid1 == 0 && pid2 != 0 ) {
			sinus(angle);
			sleep(1);
		} else if( pid1 != 0 && pid2 == 0 ) {
			cossinus(angle);
			sleep(1);
		} else { wait(0); }
		
		angle += 10.0;	
	}while(angle <= 360);
	
	return 0;
}
