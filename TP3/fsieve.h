/* Author: Lauren Sampaio
 * File: fsieve.h
 */

#define INPUT 1
#define OUTPUT 0

void prime_fils( int pipe[], int n );
void prime_pere( int pipe[], int n );
void prep_pere( int pipe[], int n );
void prep_fils( int pipe[] );
void write_on_file( int number );