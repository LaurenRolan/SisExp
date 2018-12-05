/* Author: Lauren Sampaio
 * File: matrix_product.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	/* Utiliser DUP */
	FILE *fp;
	int plot;
	char line[1035];
	char path[1035];

	snprintf(path, sizeof(path), "/tmp/data%s.txt", argv[1]);


	/* Open the command for reading. */
	fp = popen("last | grep -v \"^reboot\" | grep -v \"^wtmp\" | sed 's/[\t ][\t ]*/ /g' | cut -d' ' -f6,7 | cut -d':' -f1", "r");
	plot = open(path, O_RDWR | O_CREAT, 0644);
	
	if (fp == NULL || plot < 0) {
		printf("Failed to run command open\n" );
		exit(1);
	}

	if(dup2(plot, 1) < 0)
	{
		fprintf(stderr, "Failed to run command dup\n" );
		exit(1);
	}
	
	while (fgets(line, sizeof(line)-1, fp) != NULL && strcmp(line, "\n")) {
		
		char * p = strtok (line, " \n");
		char * access = p;
		p = strtok(NULL, " \n");
		char * hour = p;
		
		printf("%s %s\n", hour, access);
		fprintf(stderr, "%s %s\n", hour, access);
	}

	fprintf(stderr, "Current pid %s\n", argv[1]);

	/* close */
	pclose(fp);
	close(plot);

	return 0;
}
