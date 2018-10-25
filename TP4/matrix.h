/* Author: Lauren Sampaio
 * File: matrix.h
 */

#define MAX 10
#define MIN -10


int alloc_matrix( double * matrix, int rows, int cols );
int random_matrix( double * matrix, int rows, int cols );
double * product_matrix( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 );
double * product_matrix_thread( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 );
double * product_matrix_fork( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 );
void print_matrix( double * matrix, int rows, int cols );