#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#include <sys/file.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/time.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <limits.h>
#include <time.h>
#include <string.h>

#define MAX_WAIT 60
#define MAX_QUERIES 10
#define DEFAULT_MAX_HOP 30
#define DEFAULT_SIM_QUERIES 16
#define DEFAULT_PORT 33434
#define DEFAULT_QUERIES 3
#define DEFAULT_WAIT 3

#define EXIT_ARGS 64
#define STD_DATA_SIZE 56
#define ICMP_HDR_SIZE 8
#define IP_HDR_SIZE 20
#define PATTERN_MAX 16

#define OPT_FIRST_HOP 0x0001
#define OPT_ICMP 0x0002
#define OPT_INTERFACE 0x0004
#define OPT_MAX_HOP 0x0008
#define OPT_NUMERIC 0x0010
#define OPT_PORT 0x0020
#define OPT_QUERIES 0x0040
#define OPT_SOURCE 0x0100
#define OPT_TOS 0x0200
#define OPT_WAIT 0x0400
#define OPT_HELP 0x0800
#define OPT_USAGE 0x1000
#define OPT_VERSION 0x2000

typedef struct
{
	int opt;
	char short_opt;
	char *long_opt;
	bool has_arg;
} opt;

typedef struct
{
	int fd;
	int fd_icmp;
	char hostname[HOST_NAME_MAX + 1];
	char hostip[INET_ADDRSTRLEN + 1];
	struct sockaddr_in hostaddr;

	int opt;
	int current_hop;
	char interface[IFNAMSIZ + 1];
	int max_hop;
	short port;
	int queries;
	in_addr_t source_addr;
	int tos;
	struct timeval wait;

	struct timeval probe_time[UINT8_MAX][MAX_QUERIES];
} traceroute_t;

// help.c
void print_help(void);
void print_usage(void);
void print_version(void);

// parsing.c
void verify_arguments(int argc, char *argv[], traceroute_t *traceroute);

// traceroute.c
void init(traceroute_t *traceroute);
void send_and_receive_probe(traceroute_t *traceroute, int ttl);

// traceroute_utils.c
void error(char *message, traceroute_t *traceroute);
void hostname_to_ip(traceroute_t *traceroute);
bool ip_to_hostname(struct in_addr ip_address, char *host, size_t hostlen);

// utils.c
bool is_digit(char c);
struct timeval timeval_subtract(struct timeval start, struct timeval end);
void set_signal_handler(int sig, void (*handler)(int));
char *ft_strchr(const char *s, int c);
int ft_strcmp(const char *s1, const char *s2);
size_t ft_strlen(const char *s);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strncpy(char *dst, const char *src, size_t n);