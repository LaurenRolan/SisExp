/* Author: Lauren Sampaio
 * File: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "fsieve.h"


void primes( int pipe[], int n )
{
		
}

int main( int argc, char *argv[] )
{
	if(argc < 2){
		printf(stderr, "Invalid nulber of arguments.\n");
		exit(1);
	}

	int n = strtol(argv[1], NULL, 10);

	int anonymous_pipe[n];

	if( pipe(anonymous_pipe) == 1 ){
		handle_fatal_error("Error creating pipe.\n");
		exit(1);
	}

	pid1 = fork( );

	
	if(pid1 < 0 ) {
		printf("Erreur: échec du fork()\n");
		exit(EXIT_FAILURE);
	} else if( pid1 == 0 ) {
		primes(anonymous_pipe, n);
		for(;;);
	} else {
		father(anonymous_pipe);
		for(int i = 0; i < n; i++)
			anonymous_pipe
	}
	return 0;
}
