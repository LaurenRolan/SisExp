/* Author: Lauren Sampaio
 * File: matrix_product.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <pthread.h>
#include "matrix_product.h"

int step = 0;

/* Essayer de faire avec fork, et comparer avec le multithread */

double * alloc_matrix( int rows, int cols )
{
	double * matrix;
	matrix = (double*) malloc(rows * cols * sizeof(double));
	fprintf(stderr, "Malloc successful\n");
	return matrix;
}

int random_matrix( double * matrix, int rows, int cols, int seed )
{
	srand(seed);
	double range = (MAX - MIN); 
    double div = RAND_MAX / range;
    for(int row = 0; row < rows; row++) {
    	for(int col = 0; col < cols; col++) {
    		double current_value = MIN + (rand() / div);
    		matrix[row * cols + col] = current_value;
    	}
    }
    return 0;
}

int ordered_matrix( double * matrix, int rows, int cols )
{
	for(int row = 0; row < rows; row++) {
    	for(int col = 0; col < cols; col++) {
    		matrix[row * cols + col] = row * cols + col;
    	}
    }
    return 0;
}

double * product_matrix( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 )
{
	double * result;
	result = alloc_matrix( rows1, cols2);
	for( int row = 0; row < rows1; row++ ){
		for(int col = 0; col < cols2; col++)
		{	
			double cell = 0;
			for( int c = 0; c < cols1; c++ ) {
				cell += matrix1[row * cols1 + c] * matrix2[c * cols2 + col];
			}
			result[row * cols2 + col] = cell;
		} 
	}
	return result;
}

double * product_matrix_thread(  double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 )
{
	double * result;
	result = alloc_matrix( rows1, cols2);
	thread_struct current;
	current.matrix1 = matrix1;
	current.rows1 = rows1;
	current.cols1 = cols1;
	current.matrix2 = matrix2;
	current.rows2 = rows2;
	current.cols2 = cols2;
	current.result = result;

    pthread_t threads[MAX_THREAD]; 
  
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_create(&threads[i], NULL, product_thread, (void*)(&current)); 
    } 
  
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL);  
    }

	return current.result;
}

double * product_matrix_fork( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2  )
{
	pid_t pid1, pid2, pid3;
	int sector = 0;
	double * result;
	result = alloc_matrix( rows1, cols2 );

	thread_struct current;
	current.matrix1 = matrix1;
	current.rows1 = rows1;
	current.cols1 = cols1;
	current.matrix2 = matrix2;
	current.rows2 = rows2;
	current.cols2 = cols2;
	current.result = result;

	pid1 = fork( );

	if(pid1 < 0 ) {
		fprintf(stderr, "Erreur: échec du fork()\n");
		exit(EXIT_FAILURE);
	} else if( pid1 == 0 ) {
		//Fils 1
		sector++;
		pid2 = fork();

		if(pid2 < 0) {
			fprintf(stderr, "Erreur: échec du fork()\n");
			exit(EXIT_FAILURE);
		} else if(pid2 == 0) {
			//Fils 2
			sector++;
			pid3 = fork();

			if(pid3 < 0) {
				fprintf(stderr, "Erreur: échec du fork()\n");
				exit(EXIT_FAILURE);
			} else if(pid3 == 0) {
				//Fils 3
				sector++;
				fprintf(stderr, "Fils 3\n");
				product_calcul( &current, sector );
			} else {
				//Fils 2
				fprintf(stderr, "Fils 2\n");
				product_calcul( &current, sector );
				wait(NULL);
			}
		} else {
			//Fils 1
			fprintf(stderr, "Fils 1\n");
			product_calcul( &current, sector );
			wait(NULL);
		}

	} else {
		//Pere
		fprintf(stderr, "Pere\n");
		product_calcul( &current, sector );
		wait(NULL);
	}
	return current.result;
}

void print_matrix( double * matrix, int rows, int cols)
{
	for( int row = 0; row < rows; row++ ){
		printf("[ ");
		for(int col = 0; col < cols; col++) {	
			printf("%3.3f ", matrix[row * cols + col]);	
		}
		printf("]\n");
	}
}

void * product_thread(void* arg) 
{
	int sector = step++;
	thread_struct * current = ( thread_struct * ) arg;
	product_calcul( current, sector );
}

int product_calcul(thread_struct * current, int sector)
{
	int max_i, min_i, max_j, min_j;
	if(sector == 0 || sector == 1) {
		max_i = current->rows1 / 2;
		min_i = 0;
	} else {
		max_i = current->rows1;
		min_i = current->rows1 / 2;
	}

	if(sector % 2 == 0) {
		max_j = current->cols2 / 2;
		min_j = 0;
	} else {
		max_j = current->cols2;
		min_j = current->cols2 / 2;
	}

	for (int i = min_i; i < max_i; i++) {
    	for(int j = min_j; j < max_j; j++) {
			for( int c = 0; c < current->cols1; c++ ) {
				current->result[i * current->cols1 + j] += current->matrix1[i * current->cols1 + c] * current->matrix2[c * current->cols2 + j];
			}
        }
    }
    return 0;
}