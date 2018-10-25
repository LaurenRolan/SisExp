/* Author: Lauren Sampaio
 * File: matrix.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include "matrix.h"


/* Essayer de faire avec fork, et comparer avec le multithread */

int alloc_matrix( double * matrix, int rows, int cols )
{
	matrix = malloc((rows * cols) * sizeof(double));
	fprintf(stderr, "Malloc successful\n");
	return 0;
}

int random_matrix( double * matrix, int rows, int cols )
{
	double range = (MAX - MIN); 
    double div = RAND_MAX / range;
    for(int row = 0; row < rows; row++) {
    	for(int col = 0; col < cols; col++) {
    		matrix[row * cols + col] = MIN + (rand() / div);
    	}
    }
    return 0;
}

double * product_matrix( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 )
{
	double * result;
	alloc_matrix(result, rows1, cols2);
	for( int row = 0; row < rows1; row++ ){
		for(int col = 0; col < cols2; col++)
		{	
			int cell = 0;
			for( int c = 0; c < cols2; c++ )
				cell += matrix1[row * cols2 + col] * matrix2[row * cols2 + col];
			result[row * cols2 + col] = cell;
		} 
	}
	return result;
}

double * product_matrix_thread(  double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 )
{
	return NULL;
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
			printf("%d ", matrix[row * cols + col]);	
		}
		printf("]\n");
	}
}