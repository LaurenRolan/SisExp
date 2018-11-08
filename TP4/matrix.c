/* Author: Lauren Sampaio
 * File: matrix.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <pthread.h>
#include "matrix.h"

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

double * product_matrix( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 )
{
	double * result;
	result = alloc_matrix( rows1, cols2);
	for( int row = 0; row < rows1; row++ ){
		for(int col = 0; col < cols2; col++)
		{	
			double cell = 0;
			for( int c = 0; c < cols2; c++ ) {
				fprintf(stderr, "Index = %d\tInit = %.3f\t", row * cols2 + col, cell); 
				cell += matrix1[row * cols2 + col] * matrix2[row * cols2 + col];
				fprintf(stderr, "Res = %.3f\tA = %.3f\tB = %.3f\n", cell, matrix1[row * cols2 + col], matrix2[row * cols2 + col]);
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
	return NULL;
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
	thread_struct * current = (thread_struct * ) arg;
    for (int i = sector * current->rows1 / 4; i < (sector + 1) * current->rows1 / 4; i++) {
    	for(int j = sector * current->cols2 / 4; j < (sector + 1) * current->cols2 / 4; j++) {
    		for (int l = 0; l < current->rows1; l++) {
	        	for (int k = 0; k < current->cols2; k++) {
	        		fprintf(stderr, "Index = %d\tInit = %.3f\t", sector, current->result[i * current->cols2 + j]); 
	                current->result[i * current->cols2 + j] += current->matrix1[i * current->cols1 + k] * current->matrix2[k * current->cols2 + l];
	                fprintf(stderr, "Res = %.3f\tA = %.3f\tB = %.3f\n", current->result[i * current->cols2 + j], current->matrix1[i * current->cols1 + k], current->matrix2[k * current->cols2 + l]);
	            } 
	        }
        }
    }
} 