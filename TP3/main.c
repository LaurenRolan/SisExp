/* Author: Lauren Sampaio
 * File: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fsieve.h"

#define PREP 0

int main( int argc, char *argv[] )
{
	int n = strtol(argv[1], NULL, 10);
	int anonymous_pipe[2];
	pid_t pid1;
	FILE *primes;

	/* Clear prime_numbers.txt */
	primes = fopen("prime_numbers.txt", "w");
	fclose(primes);

	if(argc < 2){
		fprintf(stderr, "Invalid nulber of arguments.\n");
		exit(1);
	}

	if( pipe(anonymous_pipe) == -1 ){
		fprintf(stderr, "Error creating pipe.\n");
		exit(1);
	}

	pid1 = fork( );

	
	if(pid1 < 0 ) {
		fprintf(stderr, "Erreur: échec du fork()\n");
		exit(EXIT_FAILURE);
	} else if( pid1 == 0 ) {
		if(PREP){
			prep_fils(anonymous_pipe);
		} else {
			prime_fils(anonymous_pipe, n);
		}

	} else {
		if(PREP)
		{
			prep_pere(anonymous_pipe, n);
		} else {
			prime_pere(anonymous_pipe, n);
		}
	}
	return 0;
}
