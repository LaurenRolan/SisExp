/* Author: Lauren Sampaio
 * File: messages.h
 */
 
#ifndef MESSAGES_H
#define MESSAGES_H

#define MAX_LETTRES 5
#define CLE "grandcle"

typedef struct message_struct {
	char agent[20];
	char message[256];
} message_struct;

typedef struct boite_struct
{
	message_struct messages[MAX_LETTRES];
	int a;
	int b;
} boite_struct;

int is_important(char * imp);
void get_importance(char * imp);

void create_message(char * msg, char * imp);
void code_message(char * msg);
void decode_message(char * msg);

#endif