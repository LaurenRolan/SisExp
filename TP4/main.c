/* Author: Lauren Sampaio
 * File: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "matrix.h"

int main( )
{
	int rows1, rows2, cols1, cols2;

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

	double * matrix1;
	double * matrix2;

	alloc_matrix(matrix1, rows1, cols1);
	alloc_matrix(matrix2, rows2, cols2);

	random_matrix(matrix1, rows1, cols1);
	random_matrix(matrix2, rows2, cols2);

	printf("Matrix 1\n");
	print_matrix(matrix1, rows1, cols1);
	printf("Matrix 2\n");
	print_matrix(matrix2, rows2, cols2);

	return 0;
}
