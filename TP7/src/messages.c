/* Author: Lauren Rolan
 * File: message.c
 */

#include "messages.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_important(char * msg)
{
	if(strstr(msg, "OSS") != NULL)
		return 1;
	return 0;
}

void get_importance(char * imp)
{
	if(rand() % 100 > 85) {
		strcpy(imp, "OSS");
	} else {
		strcpy(imp, "NUL");
	}
}

void create_message(char * msg, char * imp) {
	FILE * fp;
	fp = popen("date", "r");
	char date[100];
	fgets(date, sizeof(date), fp);

	size_t ln = strlen(date)-1;
	if (date[ln] == '\n')
    	date[ln] = '\0';
		
	if (strcmp(imp, "OSS")==0)
		sprintf(msg, "[%s] %s/He is going to be there at 4 o'clock.", date, imp);
	else
		sprintf(msg, "[%s] %s/Not an important message.", date, imp);
}

void code_message(char * msg)
{
	int i;
	int len = strlen(msg);
	
	for(i = 0; i < len; i++)
	{
		msg[i] = 31 + (msg[i] ^ CLE[i%8]);
	}
}

void decode_message(char * msg)
{
	int i;
	int len = strlen(msg);
	
	for(i = 0; i < len; i++)
	{
		msg[i] = (msg[i] - 31) ^ CLE[i%8];
	}
}