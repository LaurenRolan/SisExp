/* Author: Lauren Sampaio
 * File: fsieve.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include "fsieve.h"

void write_on_file(int number)
{
	FILE *primes;
	primes = fopen("prime_numbers.txt", "a+");
	if(!primes) {
		fprintf(stderr, "Error opening text file.\n");
		exit(1);
	}
	printf("%d\n", number);
	fprintf(primes, "%d\n", number);
	fflush(primes);
	fclose(primes);
}

void prime_fils( int pipe_pere[], int n)
{
	printf("Child process (PID %d)\n", getpid());
	close(pipe_pere[INPUT]);

	int pipe_fils[2];
	int prime;
	read(pipe_pere[OUTPUT], &prime, sizeof(int));

	if(prime == -1){
		exit(EXIT_SUCCESS);
	}

	write_on_file(prime);

	if( pipe(pipe_fils) == -1 ){
		fprintf(stderr, "Error creating pipe.\n");
		exit(1);
	}

	pid_t pid_fils = fork( );

	if(pid_fils < 0 ) {
		printf("Erreur: échec du fork()\n");
		exit(EXIT_FAILURE);
	} else if( pid_fils == 0 ) {
		prime_fils(pipe_fils, n);
	} else {
		int value;
		do
		{
			close(pipe_fils[OUTPUT]);
			if(read(pipe_pere[OUTPUT], &value, sizeof(int)) > 0 ) {
				if(value % prime != 0) {
					write(pipe_fils[INPUT], &value, sizeof(int));
				}
			}

		}while(value > 0);
		wait(NULL);
	}
}

void prime_pere( int pipe[], int n )
{
	printf("Parent process (PID %d)\n", getpid());
	close(pipe[OUTPUT]);

	for(int i = 2; i <= n; i++)
	{
		printf("Writing %d\n", i);
		write(pipe[INPUT], &i, sizeof(int));
	};
	n = -1;
	write(pipe[INPUT], &n, sizeof(int));

	wait(NULL);
	printf("Parent: has received child termination.\n");
}

void prep_fils( int pipe[] )
{
	printf("Child process (PID %d)\n", getpid());
	close(pipe[INPUT]);

	int value;
	do
	{
		if(read(pipe[OUTPUT], &value, sizeof(int)) > 0 && value > 0)
		{
			printf("Value through pipe = %d\n", value);
		}

	}while(value > 0);

	printf("End of child.\n");
}

void prep_pere( int pipe[], int n )
{
	printf("Parent process (PID %d)\n", getpid());
	close(pipe[OUTPUT]);

	while(n)
	{
		write(pipe[INPUT], &n, sizeof(int));
		n--;
	};
	n = -1;
	write(pipe[INPUT], &n, sizeof(int));

	wait(NULL);
	printf("Parent: has received child termination.\n");

}
