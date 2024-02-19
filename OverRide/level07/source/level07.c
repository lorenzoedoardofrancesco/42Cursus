#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int store_number(unsigned int *data)
{
	printf(" Number: ");
	unsigned int input = get_unum();
	printf(" Index: ");
	unsigned int index = get_unum();

	if (index % 3 == 0 || (input >> 0x18) == 0xb7)
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}

	data[index] = input;
	return 0;
}

int read_number(unsigned int *data)
{
	printf(" Index: ");
	unsigned int index = get_unum();
	printf(" Number at data[%u] is %u\n", index, data[index]);
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	char command[20] = {0};
	unsigned int data[100] = {0};
	int ret;

	for (int i = 0; envp[i] != NULL; i++)
		memset(envp[i], 0, strlen(envp[i]));
	for (int i = 0; argv[i] != NULL; i++)
		memset(argv[i], 0, strlen(argv[i]));

	puts("----------------------------------------------------");
	puts("  Welcome to wil's crappy number storage service!   ");
	puts("----------------------------------------------------");
	puts(" Commands:                                          ");
	puts("    store - store a number into the data storage    ");
	puts("    read  - read a number from the data storage     ");
	puts("    quit  - exit the program                        ");
	puts("----------------------------------------------------");
	puts("   wil has reserved some storage :>                 ");
	puts("----------------------------------------------------");

	while (1)
	{
		printf("Input command: ");
		fgets(command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = '\0';

		if (!strncmp(command, "store", 5))
			ret = store_number(data);
		else if (!strncmp(command, "read", 4))
			ret = read_number(data);
		else if (!strncmp(command, "quit", 4))
			break;

		if (ret)
			printf(" Failed to do %s command\n", command);
		else
			printf(" Completed %s command successfully\n", command);

		memset(command, 0, sizeof(command));
	}
	return EXIT_SUCCESS;
}