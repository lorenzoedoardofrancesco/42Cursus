#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
	int ret;
	char buffer[16];
	char empty_buffer[66];
	FILE *fd;

	fd = fopen("/home/user/end/.pass", "r");

	bzero(buffer, 33);

	if ((fd == NULL) || (ac != 2))
	{
		return -1;
	}

	fread(buffer, 1, 66, fd);
	ret = atoi(av[1]);
	*(buffer + ret) = 0;
	fread(empty_buffer, 1, 65, fd);
	fclose(fd);
	ret = strcmp(buffer, av[1]);
	if (ret == 0)
	{
		execl("/bin/sh", "sh", 0);
	}
	else
	{
		puts(empty_buffer);
	}

	return 0;
}