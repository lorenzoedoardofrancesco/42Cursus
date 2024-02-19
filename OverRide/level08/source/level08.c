#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void log_wrapper(FILE *log_file, char *message, char *filename)
{
	char log_buffer[255] = {0};

	strcpy(log_buffer, message);
	snprintf(log_buffer + strlen(log_buffer), 255 - strlen(log_buffer) - 1, filename);
	log_buffer[strcspn(log_buffer, "\n")] = '\0';
	fprintf(log_file, "LOG: %s\n", log_buffer);
}

int main(int argc, char **argv)
{
	char backup_path[100] = "./backups/";
	FILE *log_file, *source;
	int target;

	if (argc != 2)
		printf("Usage: %s filename\n", argv[0]);

	log_file = fopen("./backups/.log", "w");
	if (log_file == NULL)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(EXIT_FAILURE);
	}

	log_wrapper(log_file, "Starting back up: ", argv[1]);

	source = fopen(argv[1], "r");
	if (source == NULL)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	strncat(backup_path, argv[1], 100 - strlen(backup_path) - 1);
	target = open(backup_path, O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (target < 0)
	{
		printf("ERROR: Failed to open %s\n", backup_path);
		exit(1);
	}

	int ch;
	while ((ch = fgetc(source)) != EOF)
		write(target, &ch, 1);

	log_wrapper(log_file, "Finished back up ", argv[1]);

	fclose(source);
	close(target);

	return EXIT_SUCCESS;
}