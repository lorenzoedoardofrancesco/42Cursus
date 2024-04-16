#pragma once

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/file.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <limits.h>
#include <time.h>
#include <string.h>

#define MAX_HOSTNAMES 64
#define MAXWAIT 10
#define INTERVAL 1
#define INT_SIZE (sizeof(int) * 8)
#define MAX_SEQ_NUM 1024

#define EXIT_ARGS 64
#define STD_DATA_SIZE 56
#define ICMP_HDR_SIZE 8
#define IP_HDR_SIZE 20
#define PATTERN_MAX 16
#define PING_MAX_DATA_SIZE IP_MAXPACKET - ICMP_HDR_SIZE - IP_HDR_SIZE

#define OPT_COUNT 0x0001
#define OPT_DEBUG 0x0002
#define OPT_INTERVAL 0x0004
#define OPT_NUMERIC 0x0008
#define OPT_IGNORE 0x0010
#define OPT_TTL 0x0020
#define OPT_TOS 0x0040
#define OPT_VERBOSE 0x0080
#define OPT_TIMEOUT 0x0100
#define OPT_LINGER 0x0200
#define OPT_FLOOD 0x0400
#define OPT_PRELOAD 0x0800
#define OPT_PATTERN 0x1000
#define OPT_QUIET 0x2000
#define OPT_SIZE 0x4000
#define OPT_HELP 0x8000
#define OPT_USAGE 0x10000
#define OPT_VERSION 0x20000

static const char icmp_dest_unreach[][44] = {
	{"Destination Net Unreachable"},
	{"Destination Host Unreachable"},
	{"Destination Protocol Unreachable"},
	{"Destination Port Unreachable"},
	{"Frag needed and DF set"},
	{"Source Route Failed"},
	{"Network Unknown"},
	{"Host Unknown"},
	{"Host Isolated"},
	{"Network Prohibited"},
	{"Host Prohibited"},
	{"Destination Network Unreachable At This TOS"},
	{"Destination Host Unreachable At This TOS"},
	{"Packet Filtered"},
	{"Precedence Violation"},
	{"Precedence Cutoff"},
};
typedef struct
{
	int opt;
	char short_opt;
	char *long_opt;
	bool has_arg;
} opt;

typedef struct
{
	size_t packets_transmitted;
	size_t packets_received;
	size_t packets_duplicated;
	size_t responses_received;
	double min_rtt;
	double max_rtt;
	double sum_rtt;
	double sum_rtt_sq;
} ping_stats;

typedef struct
{
	int fd;
	char *hostnames[MAX_HOSTNAMES - 1];
	char hostname[HOST_NAME_MAX + 1];
	int current_hostname;
	char hostip[INET_ADDRSTRLEN + 1];
	struct sockaddr_in hostaddr;
	timer_t timerid;
	bool timer_initialized;
	int bitmap[MAX_SEQ_NUM / INT_SIZE];

	int opt;
	int preload;
	struct timespec timeout;
	struct timespec linger;
	struct timespec interval;
	int size;
	char pattern[PATTERN_MAX + 1];
	size_t pattern_len;
	int tos;
	int ttl;
	size_t count;
	bool timing;
	struct timespec start_time;

	ping_stats stats;
} ping;

// help.c
void print_help(void);
void print_usage(void);
void print_version(void);

// parsing.c
void verify_arguments(int argc, char *argv[], ping *flags);

// ping.c
void init(ping *ping);
void send_ping(ping *ping);
void receive_ping(ping *ping, ping_stats *stats);
void print_header(ping *ping);
void print_statistics(ping *ping, ping_stats *stats);

// ping_utils.c
void error(char *message, ping *ping);
void hostname_to_ip(ping *ping);
bool ip_to_hostname(struct in_addr ip_address, char *host, size_t hostlen);
bool ping_timeout(ping *ping);

// utils.c
double sqrt(double n);
bool is_digit(char c);
struct timespec timespec_subtract(struct timespec start, struct timespec end);
void set_signal_handler(int sig, void (*handler)(int));
void create_timer(ping *ping);