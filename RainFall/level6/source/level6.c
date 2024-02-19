#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void n(void)
{
	system("/bin/cat /home/user/level7/.pass");
	return;
}

void m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
{
	puts("Nope");
	return;
}

void main(int argc, char **argv)
{
	char *buffer;
	void (**funcPtr)();

	buffer = (char *)malloc(64);
	funcPtr = (void (**)())malloc(4);
	*funcPtr = m;
	strcpy(buffer, argv[1]);
	(**funcPtr)();
	return;
}