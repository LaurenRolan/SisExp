/* Author: Lauren Sampaio
 * File: sin_cos.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sin_cos.h"

void sinus(int pid, double angle)
{
	double seno = sin(angle * M_PI / 180.0);
	printf("Fils 1 (%d) : sinus(%.0f) = \t %.2f\n", pid, angle, seno);
}

void cosinus(int pid, double angle)
{
	double cosseno = cos(angle * M_PI / 180.0);
	printf("Fils 2 (%d) : cosinus(%.0f) = \t %.2f\n", pid, angle, cosseno);
}
