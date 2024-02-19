#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
    size_t len = strlen(av[1]);
    unsigned int checksum = (av[1][3] ^ 0x1337) + 0x5eeded;
	for (int i = 0; i < len; i++)
	{
		if (av[1][i] < ' ')
			return 1;
		checksum += (av[1][i] ^ checksum) % 0x539;
	}

    printf("%u\n", checksum);
}