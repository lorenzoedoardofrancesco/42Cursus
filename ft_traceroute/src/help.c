#include "traceroute.h"

void print_help(void)
{
	fprintf(stdout,
			"Usage: traceroute [OPTION...] HOST\n"
			"Print the route packets trace to network host.\n"
			"\n"
			"  -f, --first-hop=NUM        set initial hop distance, i.e., time-to-live\n"
			"  -I, --icmp                 use ICMP ECHO as probe\n"
			"  -i, --interface=IFACE      specify a network interface\n"
			"  -m, --max-hop=NUM          set maximal hop count (default: 64)\n"
			"  -n, --numeric              do not resolve host addresses\n"
			"  -p, --port=PORT            use destination PORT port (default: 33434)\n"
			"  -q, --queries=NUM          send NUM probe packets per hop (default: 3)\n"
			"  -s, --source=ADDR          use source address ADDR for outgoing packets\n"
			"  -t, --tos=NUM              set type of service (TOS) to NUM\n"
			"  -w, --wait=NUM             wait NUM seconds for response (default: 3)\n"
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
            "Usage: traceroute [-In?V] [-f NUM] [-i IFACE] [-m NUM] [-p PORT]\n"
            "                  [-q NUM] [-s ADDR] [-t NUM] [-w NUM] [--first-hop=NUM]\n"
            "                  [--icmp] [--interface=IFACE] [--max-hop=NUM] [--numeric]\n"
            "                  [--port=PORT] [--queries=NUM] [--source=ADDR] [--tos=NUM]\n"
            "                  [--wait=NUM] [--help] [--usage] [--version]\n"
			"                  HOST ...\n");

    exit(EXIT_SUCCESS);
}

void print_version(void)
{
	fprintf(stdout,
			"ft_traceroute 1.0\n"
			"Written by Lorenzo Edoardo Francesco Simanic.\n");
	exit(EXIT_SUCCESS);
}