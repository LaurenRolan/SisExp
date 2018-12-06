/* Author: Lauren Sampaio
 * File: messages.h
 */


typedef struct message_struct {
	char agent[20];
	char message[256];
} message_struct;

typedef struct boite_struct
{
	message_struct messages[3];
	int a;
	int b;
} boite_struct;