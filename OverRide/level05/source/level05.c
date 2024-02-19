#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int i = 0;
	char buffer[100];

	fgets(buffer, 100, stdin);

	int len = strlen(buffer);
	for (i = 0; i < len; i++)
		if (buffer[i] >= 'A' && buffer[i] <= 'Z')
			buffer[i] = buffer[i] ^ 0x20;

	printf(buffer);
	exit(EXIT_SUCCESS);
}