/* Author: Lauren Rolan
 * File: sem_stuff.h
 */

#include <ctype.h>
#include <semaphore.h>

#define SEM_COURRIEL "tp7"

typedef sem_t semaphore_t;

void handle_fatal_error(char message[]);
semaphore_t *create_and_open_semaphore(char *name);
semaphore_t *open_semaphore(char *name);
void destroy_semaphore(semaphore_t *sem, char *name);
void P(semaphore_t *sem);
void V(semaphore_t *sem);