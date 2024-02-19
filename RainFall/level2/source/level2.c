#include <stdio.h>
#include <string.h>
#include <unistd.h>

void p(void)
{
	void *retAddress;
	char buffer[76];

	fflush(stdout);
	gets(buffer);

	if (((unsigned int)retAddress & 0xb0000000) == 0xb0000000)
	{
		printf("(%p)\n", retAddress);
		_exit(1);
	}

	puts(buffer);
	strdup(buffer);
	return;
}

void main(void)
{
	p();
	return;
}