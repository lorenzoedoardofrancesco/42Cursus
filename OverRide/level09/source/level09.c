#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MessageData
{
	char msg[140];
	char username[40];
	int msglen;
};

void secret_backdoor(void)
{
	char command[128];

	fgets(command, 128, stdin);
	system(command);
	return;
}

void handle_msg(void)
{
	struct MessageData msgdata;

	memset(msgdata.username, 0, 40);
	msgdata.msglen = 140;

	set_username(&msgdata);
	set_msg(&msgdata);
	puts(">: Msg sent!");
	return;
}

void set_msg(struct MessageData *msgdata)
{
	char message_buffer[1024];
	memset(message_buffer, 0, 1024);

	puts(">: Msg @Unix-Dude");
	printf(">>: ");

	fgets(message_buffer, 1024, stdin);
	strncpy(msgdata->msg, message_buffer, msgdata->msglen);
	return;
}

void set_username(struct MessageData *msgdata)
{
	char username_buffer[128];
	memset(username_buffer, 0, 128);

	puts(">: Enter your username");
	printf(">>: ");

	fgets(username_buffer, 128, stdin);
	for (int i = 0; i < 41 && username_buffer[i] != '\0'; i++)
		msgdata->username[i] = username_buffer[i];

	printf(">: Welcome, %s", msgdata->username);
	return;
}

int main(void)
{
	puts("--------------------------------------------\n");
	puts("|   ~Welcome to l33t-m$n ~    v1337        |\n");
	puts("--------------------------------------------\n");
	handle_msg();
	return EXIT_SUCCESS;
}