/* Author: Lauren Sampaio
 * File: messages.h
 */

#define MAX_LETTRES 5

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
