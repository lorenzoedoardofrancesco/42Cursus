#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[80];

void m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
{
	time_t currentTime;

	currentTime = time(NULL);
	printf("%s - %d\n", c, currentTime);

	return;
}

int main(int argc, char **argv)
{
	int *intPtr1;
	void *data;
	int *intPtr2;
	FILE *fileStream;

	intPtr1 = (int *)malloc(8);
	*intPtr1 = 1;
	data = malloc(8);
	intPtr1[1] = data;

	intPtr2 = (int *)malloc(8);
	*intPtr2 = 2;
	data = malloc(8);
	intPtr2[1] = data;

	strcpy((char *)intPtr1[1], argv[1]);
	strcpy((char *)intPtr2[1], argv[2]);

	fileStream = fopen("/home/user/level8/.pass", "r");
	fgets(c, 0x44, fileStream);
	puts("~~");

	return 0;
}