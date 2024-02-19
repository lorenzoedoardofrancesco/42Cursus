#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bool.h>

int *_auth;
int *_service;

int main(void)
{
	char cVar1;
	char *pcVar5;
	char *size;
	char *src;
	char *input;

	do
	{
		printf("%p, %p \n", _auth, _service);
		input = fgets(&var_90h, 0x80, stdin);

		if (!input)
		{
			return 0;
		}

		if (strcmp(input, "auth ") == 0)
		{
			_auth = (int *)malloc(4);
			*_auth = 0;
			if (strlen(input) < 31)
			{
				strcpy(_auth, (int32_t)&src + 1);
			}
		}

		if (strcmp(input, "reset") == 0)
		{
			free(_auth);
		}

		if (strcmp(input, "service") == 0)
		{
			uVar11 = (int32_t *)0xfffffff8 < &var_90h;
			uVar8 = (int32_t)&src + 3 == 0;
			_service = strdup((int32_t)&src + 3);
		}

		if (strcmp(input, "login") == 0)
		{
			if (_auth[8] == 0)
			{
				fwrite("Password:\n", 1, 10, stdout);
			}
			else
			{
				system("/bin/sh");
			}
		}
	} while (true);
}