#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	char username[100] = {0};
	char inputPassword[100] = {0};
	char realPassword[41] = {0};
	int bytesRead = 0;
	FILE *passwordFile = NULL;

	passwordFile = fopen("/home/users/level03/.pass", "r");
	if (passwordFile == NULL)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(EXIT_FAILURE);
	}

	bytesRead = fread(realPassword, 1, 41, passwordFile);
	realPassword[strcspn(realPassword, "\n")] = '\0';
	if (bytesRead != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(EXIT_FAILURE);
	}
	fclose(passwordFile);

	puts("| You must login to access this system. |");
	printf("--[ Username: ");
	fgets(username, 100, stdin);
	username[strcspn(username, "\n")] = '\0';

	printf("--[ Password: ");
	fgets(inputPassword, 100, stdin);
	inputPassword[strcspn(inputPassword, "\n")] = '\0';

	puts("*****************************************");

	if (!strncmp(realPassword, inputPassword, 41))
	{
		printf("Greetings, %s!\n", username);
		system("/bin/sh");
	}
	else
	{
		printf(username);
		puts(" does not have access!");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}