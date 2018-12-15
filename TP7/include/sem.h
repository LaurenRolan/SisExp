
#ifndef SEM_H
#define SEM_H
#include <semaphore.h>

#define SEM_COURRIEL "tp7"

typedef sem_t semaphore_t;

int get_semaphore_value(semaphore_t *sem);
void handle_fatal_error(char message[]);
semaphore_t *create_and_open_semaphore(char *name);
semaphore_t *open_semaphore(char *name);
void destroy_semaphore(semaphore_t *sem, char *name);
void P(semaphore_t *sem);
void V(semaphore_t *sem);

#endif