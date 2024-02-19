#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
	int inputValue;

	puts("***********************************");
	puts("*           -Level00 -            *");
	puts("***********************************");
	printf("Password: ");

	scanf("%d", &inputValue);

	if (inputValue != 0x149c) // 5276
	{
		puts("\nInvalid Password!");
	}
	else
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
	}

	return inputValue != 0x149c;
}