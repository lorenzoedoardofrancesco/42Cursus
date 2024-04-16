#include "ping.h"

void print_help(void)
{
	fprintf(stdout,
			"Usage: ping [OPTION...] HOST ...\n"
			"Send ICMP ECHO_REQUEST packets to network hosts.\n"
			"\n"
			"  -c, --count=NUMBER         stop after sending NUMBER packets\n"
			"  -d, --debug                set the SO_DEBUG option\n"
			"  -i, --interval=NUMBER      wait NUMBER seconds between sending each packet\n"
			"  -n, --numeric              do not resolve host addresses\n"
			"  -r, --ignore-routing       send directly to a host on an attached network\n"
			"      --ttl=N                specify N as time-to-live\n"
			"  -T, --tos=NUM              set type of service (TOS) to NUM\n"
			"  -v, --verbose              verbose output\n"
			"  -w, --timeout=N            stop after N seconds\n"
			"  -W, --linger=N             number of seconds to wait for response\n"
			"  -f, --flood                flood ping (root only)\n"
			"  -l, --preload=NUMBER       send NUMBER packets as fast as possible before\n"
			"                             falling into normal mode of behavior (root only)\n"
			"  -p, --pattern=PATTERN      fill ICMP packet with given pattern (hex)\n"
			"  -q, --quiet                quiet output\n"
			"  -s, --size=NUMBER          send NUMBER data octets\n"
			"\n"
			"  -?, --help                 give this help list\n"
			"      --usage                give a short usage message\n"
			"  -V, --version              print program version\n"
			"\n"
			"Mandatory or optional arguments to long options are also mandatory or optional\n"
			"for any corresponding short options.\n");

	exit(EXIT_SUCCESS);
}

void print_usage(void)
{
	fprintf(stdout,
			"Usage: ping [-dnrvfq?V] [-c NUMBER] [-i NUMBER] [-T NUM] [-w N] [-W N]\n"
			"            [-l NUMBER] [-p PATTERN] [-s NUMBER] [--count=NUMBER] [--debug]\n"
			"            [--interval=NUMBER] [--numeric] [--ignore-routing] [--ttl=N]\n"
			"            [--tos=NUM] [--verbose] [--timeout=N] [--linger=N] [--flood]\n"
			"            [--preload=NUMBER] [--pattern=PATTERN] [--quiet] [--size=NUMBER]\n"
			"            [--help] [--usage] [--version]\n"
			"            HOST ...\n");

	exit(EXIT_SUCCESS);
}

void print_version(void)
{
	fprintf(stdout,
			"ft_ping 1.0\n"
			"Written by Lorenzo Edoardo Francesco Simanic.\n");
	exit(EXIT_SUCCESS);
}