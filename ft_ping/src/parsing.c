#include "ping.h"

const opt valid_opt[] = {
	{OPT_COUNT, 'c', "count", true},
	{OPT_DEBUG, 'd', "debug", false},
	{OPT_INTERVAL, 'i', "interval", true},
	{OPT_NUMERIC, 'n', "numeric", false},
	{OPT_IGNORE, 'r', "ignore-routing", false},
	{OPT_TTL, 0, "ttl", true},
	{OPT_TOS, 'T', "tos", true},
	{OPT_VERBOSE, 'v', "verbose", false},
	{OPT_TIMEOUT, 'w', "timeout", true},
	{OPT_LINGER, 'W', "linger", true},
	{OPT_FLOOD, 'f', "flood", false},
	{OPT_PRELOAD, 'l', "preload", true},
	{OPT_PATTERN, 'p', "pattern", true},
	{OPT_QUIET, 'q', "quiet", false},
	{OPT_SIZE, 's', "size", true},
	{OPT_HELP, '?', "help", false},
	{OPT_USAGE, 0, "usage", false},
	{OPT_VERSION, 'V', "version", false},
	{0, 0, NULL, false}};

void args_error(void)
{
	fprintf(stderr, "Try 'ping --help' or 'ping --usage' for more information.\n");
	exit(EXIT_ARGS);
}

int atoi_check(char *s, int max, char *opt_name, bool zero_allowed)
{
	int n = 0;
	int modulo = max % 10;
	int limit = max / 10;
	bool is_negative = s[0] == '-';

	for (int i = is_negative; s[i]; i++)
		if (!is_digit(s[i]))
			fprintf(stderr, "ping: invalid %s value (`%s' near `%s')\n", opt_name, s, s + i), exit(EXIT_FAILURE);

	if (is_negative)
		fprintf(stderr, "ping: %s value too small: %s\n", opt_name, s), exit(EXIT_FAILURE);

	for (int i = 0; s[i]; i++)
	{
		if ((n == limit && s[i] > modulo + '0') || n > limit)
			fprintf(stderr, "ping: %s value too big: %s\n", opt_name, s), exit(EXIT_FAILURE);
		n = n * 10 + s[i] - '0';
	}

	if (!zero_allowed && n == 0)
		fprintf(stderr, "ping: %s value too small: 0\n", opt_name), exit(EXIT_FAILURE);

	return n;
}

bool handle_arg(int opt, char *value, char short_opt, char *long_opt, ping *ping)
{
	if (value == NULL)
	{
		if (long_opt)
			fprintf(stderr, "ping: option '--%s' requires an argument\n", long_opt), args_error();
		else
			fprintf(stderr, "ping: option requires an argument -- '%c'\n", short_opt), args_error();
	}

	ping->opt |= opt;

	switch (opt)
	{
	case OPT_PRELOAD:
		ping->preload = atoi_check(value, INT_MAX, "preload", true);
		break;
	case OPT_TIMEOUT:
		ping->timeout = (struct timespec){.tv_sec = atoi_check(value, INT_MAX, "timeout", false)};
		break;
	case OPT_LINGER:
		ping->linger.tv_sec = atoi_check(value, INT_MAX, "linger", false);
		break;
	case OPT_SIZE:
		ping->size = atoi_check(value, PING_MAX_DATA_SIZE, "size", true);
		break;
	case OPT_PATTERN:
		int i, c, offset = 0;
		for (i = 0; value[offset] && i < PATTERN_MAX; i++)
		{
			int n;
			if (sscanf(value + offset, "%2x%n", &c, &n) != 1)
				fprintf(stderr, "ping: error in pattern near %s\n", value + i), exit(EXIT_FAILURE);
			ping->pattern[i] = c;
			offset += n;
		}
		ping->pattern_len = i;
		break;
	case OPT_TOS:
		ping->tos = atoi_check(value, UINT8_MAX, "tos", true);
		break;
	case OPT_TTL:
		ping->ttl = atoi_check(value, UINT8_MAX, "ttl", false);
		break;
	case OPT_INTERVAL:
		ping->interval.tv_sec = atoi_check(value, INT_MAX, "interval", false);
		break;
	case OPT_COUNT:
		ping->count = atoi_check(value, INT_MAX, "count", true);
		break;
	}
	return true;
}

bool handle_long_opt(char *opt, int i, int *index, char **argv, ping *ping)
{
	char *equal_sign = strchr(opt, '=');
	size_t len = equal_sign != NULL ? (size_t)(equal_sign - opt) : strlen(opt);
	bool ambiguous = false;
	if (strncmp(opt, valid_opt[i].long_opt, len) == 0)
	{
		for (int j = i + 1; valid_opt[j].opt; j++)
			if (strncmp(opt, valid_opt[j].long_opt, len) == 0)
			{
				if (!ambiguous)
					fprintf(stderr, "ping: option '--%s' is ambiguous; possibilities: '--%s'", opt, valid_opt[i].long_opt), ambiguous = true;
				fprintf(stderr, " '--%s'", valid_opt[j].long_opt);
			}
		if (ambiguous)
			fprintf(stderr, "\n"), args_error();

		if (valid_opt[i].has_arg == false)
		{
			if (equal_sign)
				fprintf(stderr, "ping: option '--%s' doesn't allow an argument\n", valid_opt[i].long_opt), args_error();
			ping->opt |= valid_opt[i].opt;
			ping->opt &OPT_HELP ? print_help() : ping->opt &OPT_USAGE ? print_usage()
											 : ping->opt &OPT_VERSION ? print_version()
																	  : 0;
		}
		else
		{
			if (equal_sign == NULL)
				(*index)++;
			handle_arg(valid_opt[i].opt, equal_sign ? equal_sign + 1 : *(++argv), 0, valid_opt[i].long_opt, ping);
		}
		return true;
	}
	return false;
}

bool is_valid_opt(char **arg, int *index, ping *ping)
{
	bool is_long_opt = *(*arg + 1) == '-';
	bool valid = true;
	bool found_long_opt = false;

	do
		for (int i = 0; valid_opt[i].opt; i++)
		{
			if (is_long_opt)
				if ((found_long_opt = handle_long_opt(*arg + 2, i, index, arg, ping)) == true)
					return true;
			if (!is_long_opt && *(*arg + 1) == valid_opt[i].short_opt)
			{
				if (valid_opt[i].has_arg == false)
					ping->opt |= valid_opt[i].opt;
				else
				{
					if (*(*arg + 2) == '\0')
						(*index)++;
					return handle_arg(valid_opt[i].opt, *(*arg + 2) ? *arg + 2 : *(++arg), valid_opt[i].short_opt, NULL, ping);
				}
				ping->opt &OPT_HELP ? print_help() : ping->opt &OPT_USAGE ? print_usage()
												 : ping->opt &OPT_VERSION ? print_version()
																		  : 0;
				break;
			}
			if (valid_opt[i + 1].opt == 0)
				valid = false;
		}
	while (*(*arg + 2) && valid && (*arg)++);

	return valid;
}

void handle_unrecognized_opt(char *arg)
{
	if (*arg == '-')
		fprintf(stderr, "ping: unrecognized option '%s'\n", arg);
	else
		fprintf(stderr, "ping: invalid option -- '%c'\n", *(arg + 1));
	args_error();
}

void verify_arguments(int argc, char *argv[], ping *ping)
{
	int hostname_index = 0;
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--") == 0)
		{
			for (i++; i < argc && hostname_index < MAX_HOSTNAMES; i++)
				ping->hostnames[hostname_index++] = argv[i];
			break;
		}
		else if (argv[i][0] == '-' && argv[i][1])
		{
			if (!is_valid_opt(&argv[i], &i, ping))
				handle_unrecognized_opt(argv[i]);
		}
		else if (hostname_index < MAX_HOSTNAMES)
			ping->hostnames[hostname_index++] = argv[i];
	}

	if (!ping->hostnames[0])
		fprintf(stderr, "ping: missing host operand\n"), args_error();

	if (ping->opt & OPT_FLOOD && ping->opt & OPT_INTERVAL)
		fprintf(stderr, "ping: -f and -i options are incompatible\n"), exit(EXIT_FAILURE);
}
