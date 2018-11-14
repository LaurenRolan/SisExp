/* Author: Lauren Sampaio
 * File: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "matrix.h"

#define CLOCKS_PER_SEC 1000

int main( )
{
	int rows1, rows2, cols1, cols2, seed1, seed2;

	printf("Type the size of the first matrix:\n");
	printf("Rows:\t");
	scanf("%d", &rows1);
	printf("Cols:\t");
	scanf("%d", &cols1);
	printf("Type the size of the second matrix:\n");
	printf("Rows:\t");
	scanf("%d", &rows2);
	printf("Cols:\t");
	scanf("%d", &cols2);

	seed1 = 2;
	seed2 = 5;

	double * matrix1;
	double * matrix2;

	matrix1 = alloc_matrix( rows1, cols1);
	matrix2 = alloc_matrix( rows2, cols2);

	if(matrix1 == NULL || matrix2 == NULL) {
		fprintf(stderr, "Error at malloc\n");
		exit(1);
	}

	//random_matrix(matrix1, rows1, cols1, seed1);
	//random_matrix(matrix2, rows2, cols2, seed2);

	ordered_matrix(matrix1, rows1, cols1);
	ordered_matrix(matrix2, rows2, cols2);

	printf("Matrix 1\n");
	print_matrix(matrix1, rows1, cols1);
	printf("Matrix 2\n");
	print_matrix(matrix2, rows2, cols2);

	double * matrix_result;

	printf("----------------Normal product----------------\n");
	clock_t c_before, c_after;
	time_t t_before, t_after;
	c_before = clock();
	t_before = time(NULL);

	matrix_result = product_matrix(matrix1, rows1, cols1, matrix2, rows2, cols2);

	t_after = time(NULL);
	c_after = clock();
	printf("\nClock_t -> %5.3f ticks (%f seconds)\n",
	(float) (c_after - c_before),
	(double) (c_after - c_before) / CLOCKS_PER_SEC);
	printf("Time_t  -> %5.3f seconds\n", difftime(t_after, t_before));

	//print_matrix(matrix_result, rows1, cols2);


	printf("----------------Thread product----------------\n");
	c_before = clock();
	t_before = time(NULL);

	matrix_result = product_matrix_thread(matrix1, rows1, cols1, matrix2, rows2, cols2);

	t_after = time(NULL);
	c_after = clock();
	printf("\nClock_t -> %5.3f ticks (%f seconds)\n",
	(float) (c_after - c_before),
	(double) (c_after - c_before) / CLOCKS_PER_SEC);
	printf("Time_t  -> %5.3f seconds\n", difftime(t_after, t_before));

	//print_matrix(matrix_result, rows1, cols2);

	return 0;
}
