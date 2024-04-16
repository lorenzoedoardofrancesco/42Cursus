#include "traceroute.h"

const opt valid_opt[] = {
	{OPT_FIRST_HOP, 'f', "first-hop", true}, // Set initial hop distance (TTL)
	{OPT_ICMP, 'I', "icmp", false},			 // Use ICMP ECHO as probe
	{OPT_INTERFACE, 'i', "interface", true}, // Specify a network interface
	{OPT_MAX_HOP, 'm', "max-hop", true},	 // Set maximal hop count
	{OPT_NUMERIC, 'n', "numeric", false},	 // Do not resolve host addresses
	{OPT_PORT, 'p', "port", true},			 // Use destination port
	{OPT_QUERIES, 'q', "queries", true},	 // Send NUM probe packets per hop
	{OPT_SOURCE, 's', "source", true},		 // Use source address for outgoing packets
	{OPT_TOS, 't', "tos", true},			 // Set Type of Service (TOS)
	{OPT_WAIT, 'w', "wait", true},			 // Wait NUM seconds for response
	{OPT_HELP, '?', "help", false},			 // Display help information
	{OPT_USAGE, 0, "usage", false},			 // Display usage information
	{OPT_VERSION, 'V', "version", false},	 // Display version information
	{0, 0, NULL, false}						 // End of array
};

void args_error(void)
{
	fprintf(stderr, "Try 'traceroute --help' or 'traceroute --usage' for more information.\n");
	exit(EXIT_ARGS);
}

int atoi_check(char *s, int max, char *opt_name, bool zero_allowed)
{
	int n = 0;
	int modulo = max % 10;
	int limit = max / 10;

	for (int i = 0; s[i]; i++)
	{
		if (!is_digit(s[i]))
			fprintf(stderr, "traceroute: invalid value for the '%s' option (`%s' near `%s')\n", opt_name, s, s + i), exit(EXIT_FAILURE);
		if ((n == limit && s[i] > modulo + '0') || n > limit)
			fprintf(stderr, "traceroute: the value for option '%s' is too big: %s\n", opt_name, s), exit(EXIT_FAILURE);
		n = n * 10 + s[i] - '0';
	}

	if (!zero_allowed && n == 0)
		fprintf(stderr, "traceroute: the value for option '%s' is too small: 0\n", opt_name), exit(EXIT_FAILURE);

	return n;
}

bool handle_arg(int opt, char *value, char short_opt, char *long_opt, traceroute_t *traceroute)
{
	if (value == NULL)
	{
		if (long_opt)
			fprintf(stderr, "traceroute: option '--%s' requires an argument\n", long_opt), args_error();
		else
			fprintf(stderr, "traceroute: option requires an argument -- '%c'\n", short_opt), args_error();
	}

	traceroute->opt |= opt;

	switch (opt)
	{
	case OPT_FIRST_HOP:
		traceroute->current_hop = atoi_check(value, UINT8_MAX, "first-hop", false);
		break;
	case OPT_INTERFACE:
		ft_strncpy(traceroute->interface, value, IFNAMSIZ);
		traceroute->interface[IFNAMSIZ] = '\0';
		break;
	case OPT_MAX_HOP:
		traceroute->max_hop = atoi_check(value, UINT8_MAX, "max-hop", false);
		break;
	case OPT_PORT:
		traceroute->port = atoi_check(value, UINT16_MAX, "port", false);
		break;
	case OPT_QUERIES:
		traceroute->queries = atoi_check(value, MAX_QUERIES, "queries", false);
		break;
	case OPT_SOURCE:
		traceroute->source_addr = inet_addr(value);
		if (traceroute->source_addr == INADDR_NONE)
			fprintf(stderr, "traceroute: invalid source address: %s\n", value), exit(EXIT_FAILURE);
		break;
	case OPT_TOS:
		traceroute->tos = atoi_check(value, UINT8_MAX, "tos", true);
		break;
	case OPT_WAIT:
		traceroute->wait = (struct timeval){.tv_sec = atoi_check(value, MAX_WAIT, "wait", false)};
		break;
	}

	return true;
}

bool handle_long_opt(char *opt, int i, int *index, char **argv, traceroute_t *traceroute)
{
	char *equal_sign = ft_strchr(opt, '=');
	size_t len = equal_sign != NULL ? (size_t)(equal_sign - opt) : ft_strlen(opt);
	bool ambiguous = false;
	if (ft_strncmp(opt, valid_opt[i].long_opt, len) == 0)
	{
		for (int j = i + 1; valid_opt[j].opt; j++)
			if (ft_strncmp(opt, valid_opt[j].long_opt, len) == 0)
			{
				if (!ambiguous)
					fprintf(stderr, "traceroute: option '--%s' is ambiguous; possibilities: '--%s'", opt, valid_opt[i].long_opt), ambiguous = true;
				fprintf(stderr, " '--%s'", valid_opt[j].long_opt);
			}
		if (ambiguous)
			fprintf(stderr, "\n"), args_error();

		if (valid_opt[i].has_arg == false)
		{
			if (equal_sign)
				fprintf(stderr, "traceroute: option '--%s' doesn't allow an argument\n", valid_opt[i].long_opt), args_error();
			traceroute->opt |= valid_opt[i].opt;
			traceroute->opt &OPT_HELP ? print_help() : traceroute->opt &OPT_USAGE ? print_usage()
												   : traceroute->opt &OPT_VERSION ? print_version()
																				  : 0;
		}
		else
		{
			if (equal_sign == NULL)
				(*index)++;
			handle_arg(valid_opt[i].opt, equal_sign ? equal_sign + 1 : *(++argv), 0, valid_opt[i].long_opt, traceroute);
		}
		return true;
	}
	return false;
}

bool is_valid_opt(char **arg, int *index, traceroute_t *traceroute)
{
	bool is_long_opt = *(*arg + 1) == '-';
	bool valid = true;
	bool found_long_opt = false;

	do
		for (int i = 0; valid_opt[i].opt; i++)
		{
			if (is_long_opt)
				if ((found_long_opt = handle_long_opt(*arg + 2, i, index, arg, traceroute)) == true)
					return true;
			if (!is_long_opt && *(*arg + 1) == valid_opt[i].short_opt)
			{
				if (valid_opt[i].has_arg == false)
					traceroute->opt |= valid_opt[i].opt;
				else
				{
					if (*(*arg + 2) == '\0')
						(*index)++;
					return handle_arg(valid_opt[i].opt, *(*arg + 2) ? *arg + 2 : *(++arg), valid_opt[i].short_opt, NULL, traceroute);
				}
				traceroute->opt &OPT_HELP ? print_help() : traceroute->opt &OPT_USAGE ? print_usage()
													   : traceroute->opt &OPT_VERSION ? print_version()
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
		fprintf(stderr, "traceroute: unrecognized option '%s'\n", arg);
	else
		fprintf(stderr, "traceroute: invalid option -- '%c'\n", *(arg + 1));
	args_error();
}

void verify_arguments(int argc, char *argv[], traceroute_t *traceroute)
{
	for (int i = 1; i < argc; i++)
	{
		if (ft_strcmp(argv[i], "--") == 0)
		{
			if (!*traceroute->hostname && i + 1 < argc)
			{
				ft_strncpy(traceroute->hostname, argv[i + 1], HOST_NAME_MAX);
				traceroute->hostname[HOST_NAME_MAX] = '\0';
			}
			break;
		}
		else if (argv[i][0] == '-' && argv[i][1])
		{
			if (!is_valid_opt(&argv[i], &i, traceroute))
				handle_unrecognized_opt(argv[i]);
		}
		else if (!*traceroute->hostname)
		{
			ft_strncpy(traceroute->hostname, argv[i], HOST_NAME_MAX);
			traceroute->hostname[HOST_NAME_MAX] = '\0';
		}
	}

	if (!*traceroute->hostname)
		fprintf(stderr, "traceroute: missing host operand\n"), args_error();
}
