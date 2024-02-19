#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_user_name[100];

int verify_user_name(void)
{
	puts("verifying username....\n");
	return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *passwordInput)
{
	return strncmp(passwordInput, "admin", 5);
}

int main(void)
{
	char passwordInput[64] = {0};
	int result;

	puts("********* ADMIN LOGIN PROMPT *********\n");
	printf("Enter Username: ");
	fgets(a_user_name, 0x100, stdin);

	result = verify_user_name();
	if (result == 0)
	{
		puts("Enter Password: \n");
		fgets(passwordInput, 100, stdin);

		result = verify_user_pass(passwordInput);
		if (result == 0 || result != 0)
		{
			puts("nope, incorrect password...\n");
			return EXIT_FAILURE;
		}
		else
			return EXIT_SUCCESS;
	}
	else
	{
		puts("nope, incorrect username...\n");
		return EXIT_FAILURE;
	}
}