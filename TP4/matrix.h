/* Author: Lauren Sampaio
 * File: matrix.h
 */

#define MAX 10
#define MIN -10
#define MAX_THREAD 4

typedef struct thread_struct {
	double * matrix1;
	int rows1;
	int cols1;
	double * matrix2;
	int rows2;
	int cols2;
	double * result;
	int sector;
} thread_struct;

double * alloc_matrix( int rows, int cols );
int random_matrix( double * matrix, int rows, int cols, int seed );
double * product_matrix( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 );
double * product_matrix_thread( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 );
double * product_matrix_fork( double * matrix1, int rows1, int cols1, double * matrix2, int rows2, int cols2 );
void print_matrix( double * matrix, int rows, int cols );
void* product_thread(void* arg);