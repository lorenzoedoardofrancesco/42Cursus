#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void decrypt(int key)
{
	char cipher[21] = "Q}|u`sfg~sf{}|a3";
	size_t len = strlen(cipher);

	for (size_t i = 0; i < len; i++)
		cipher[i] ^= key;

	if (!strcmp(cipher, "Congratulations!"))
		system("/bin/sh");
	else
		puts("Invalid Password!");
}

void test(int arg1, int arg2)
{
	int diff = arg2 - arg1;

	if ((diff > 0 && diff < 22))
		decrypt(diff);
	else
	{
		int randomValue = rand();
		decrypt(randomValue);
	}
}

int main(void)
{
	int userInput;
	srand((unsigned)time(NULL));

	puts("***********************************");
	puts("*               level03         **");
	puts("***********************************");
	printf("\nPassword:");
	scanf("%d", &userInput);
	test(userInput, 0x1337d00d);
	return EXIT_SUCCESS;
}