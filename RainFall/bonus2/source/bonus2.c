int language = 0;

int greetuser(char *name)
{
	char greeting[76];

	if (language == 1)
		strcpy(greeting, "Goedemiddag! ");
	else if (language == 2)
		strcpy(greeting, "Hyvää päivää ");
	else if (language == 0)
		strcpy(greeting, "Hello ");

	strcat(greeting, name);

	return puts(greeting);
}

int main(int argc, char **argv)
{
	char buffer1[40];
	char buffer2[32];

	if (argc != 3)
		return 1;

	strncpy(buffer1, argv[1], 40);
	strncpy(buffer2, argv[2], 32);

	char *lang_ptr = getenv("LANG");
	if (lang_ptr)
	{
		if (memcmp(lang_ptr, "fi", 2) == 0)
			language = 1;
		else if (memcmp(lang_ptr, "nl", 2) == 0)
			language = 2;
	}

	return greetuser(buffer1);
}