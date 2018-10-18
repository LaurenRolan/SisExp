/* Author: Lauren Sampaio
 * File: sin_cos_g.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "sin_cos_g.h"

void sinus(double angle)
{
	FILE *sinusFile = fopen("sinus.txt", "a+");
	if(!sinusFile)
		exit(EXIT_FAILURE);
	double seno = sin(angle * M_PI / 180.0);
	fprintf(sinusFile, "%.2f %.2f\n", angle, seno);
	printf("%.2f %.2f\n", angle, seno);
	fclose(sinusFile);
}

void cosinus(double angle)
{

	FILE *cossinusFile = fopen("cosinus.txt", "a+");
	if(!cossinusFile)
		exit(EXIT_FAILURE);
	double cosseno = cos(angle * M_PI / 180.0);
	fprintf(cossinusFile, "%.2f %.2f\n", angle, cosseno);
	printf("%.2f %.2f\n", angle, cosseno);
	fclose(cossinusFile);
}
