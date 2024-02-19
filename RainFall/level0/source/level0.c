#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int input_val = atoi(argv[1]);

	if (input_val == 423)
	{
		char *cmd = strdup("/bin/sh");

		__gid_t egid = getegid();
		__uid_t euid = geteuid();

		setresgid(egid, egid, egid);
		setresuid(euid, euid, euid);

		execv("/bin/sh", &cmd);
	}
	else
	{
		fwrite("No !\n", 1, 5, stderr);
	}

	return 0;
}