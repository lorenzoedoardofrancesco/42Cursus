#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>
#include <unistd.h>

int auth(char *username, unsigned int serial)
{
	username[strcspn(username, "\n")] = '\0';
	size_t len = strnlen(username, 32);

	if (len < 6)
		return 1;

	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
	{
		puts("\x1b[32m.---------------------------.");
		puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m\'---------------------------\'");
		return 1;
	}

	unsigned int checksum = (username[3] ^ 0x1337) + 0x5eeded;
	for (int i = 0; i < len; i++)
	{
		if (username[i] < ' ')
			return 1;
		checksum += (username[i] ^ checksum) % 0x539;
	}

	if (serial != checksum)
		return 1;
	return 0;
}

int main(void)
{
	unsigned int serial;
	char username[32];

	puts("***********************************");
	puts("*               level06           *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(username, 32, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &serial);

	int ret = auth(username, serial);
	if (ret == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
	}

	return ret != 0;
}