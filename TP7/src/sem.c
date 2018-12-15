/* Author: Lauren Rolan
 * File: sem.c
 */

#include "sem.h"
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_fatal_error(char message[]) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

semaphore_t *open_semaphore(char *name) {
	semaphore_t *sem = NULL;

	sem = sem_open(name, O_RDWR);
	if (sem == NULL) {
		sem_unlink(name);
		handle_fatal_error("Error trying to open semaphore\n");
	}
	return sem;
}

semaphore_t *create_and_open_semaphore(char *name) {
	semaphore_t *sem = NULL;

	sem = sem_open(name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR, 1);
	if (sem == SEM_FAILED) {
		handle_fatal_error("Error trying to create semaphore\n");
	}
	return sem;
}

void destroy_semaphore(semaphore_t *sem, char *name) {
	int r = 0;

	r = sem_close(sem);
	if (r < 0) {
		handle_fatal_error("Error trying to destroy semaphore\n");
	}
	r = sem_unlink(name);
	if (r < 0) {
		perror("Error trying to unlink semaphore\n");
	}
}

void P(semaphore_t *sem) {
	int r = 0;

	r = sem_wait(sem);
	if (r < 0) {
		handle_fatal_error("Error with P() operation\n");
	}
}

void V(semaphore_t *sem) {
	int r = 0;

	sem_post(sem);
	if (r < 0) {
		handle_fatal_error("Error with V() operation\n");
	}
}

int get_semaphore_value(semaphore_t *sem)
{
	int value;
	sem_getvalue(sem, &value);
	return value;
}