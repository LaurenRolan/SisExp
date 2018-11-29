/* Author: Lauren Sampaio
 * File: iplot.c
 */

#include <stdlib.h>
#include <stdio.h>
#include "iplot.h"

void writeCommand(int b)
{
	FILE *gnuCommand;
	gnuCommand = fopen("commandes.gp", "w");

	if(!gnuCommand)	/* Si ce n'est pas possible d'ouvrir le fichier */
		exit(EXIT_FAILURE);
	
	/* Récrire le fichier <<commande.gp>> */
	/* Faire une ammostrage 10 fois le nombre de l'interval */
	fprintf(gnuCommand, "set samples %d\n", b * 10); 
	fprintf(gnuCommand, "set title \"Sinus cardinal in [0, %d]\"\n", b);
	fprintf(gnuCommand, "set xlabel \"x\"\n");
	fprintf(gnuCommand, "set xlabel \"sin(x)/x\"\n");
	fprintf(gnuCommand, "set xrange [0: %d]\n", b);
	fprintf(gnuCommand, "set grid\n");
	fprintf(gnuCommand, "plot sin(x)/x\n");

	fclose(gnuCommand);
}
