#include "traceroute.h"

static void cleanup_and_exit(traceroute_t *traceroute)
{
	if (traceroute)
	{
		if (traceroute->fd_icmp > 2)
			close(traceroute->fd_icmp);
		if (traceroute->fd > 2 && traceroute->fd != traceroute->fd_icmp)
			close(traceroute->fd);
	}

	exit(EXIT_SUCCESS);
}

void error(char *message, traceroute_t *traceroute)
{
	fprintf(stderr, "traceroute: %s: %s\n", message, strerror(errno));
	cleanup_and_exit(traceroute);
}

static void g_error(int status, traceroute_t *traceroute)
{
	if (status != EAI_NONAME)
		fprintf(stderr, "traceroute: %s\n", gai_strerror(status));
	else
		fprintf(stderr, "traceroute: unknown host\n");

	cleanup_and_exit(traceroute);
}

void hostname_to_ip(traceroute_t *traceroute)
{
	struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_flags = AI_CANONNAME,
	};
	struct addrinfo *res = NULL;

	int status = getaddrinfo(traceroute->hostname, NULL, &hints, &res);
	if (status != 0 || res == NULL)
		g_error(status, traceroute);

	traceroute->hostaddr = *(struct sockaddr_in *)res->ai_addr;
	if (inet_ntop(AF_INET, &traceroute->hostaddr.sin_addr, traceroute->hostip, INET_ADDRSTRLEN) == NULL)
	{
		freeaddrinfo(res);
		error("inet_ntop failed", traceroute);
	}

	if (res->ai_canonname)
	{
		ft_strncpy(traceroute->hostname, res->ai_canonname, HOST_NAME_MAX);
		traceroute->hostname[HOST_NAME_MAX] = '\0';
	}

	freeaddrinfo(res);
}

bool ip_to_hostname(struct in_addr ip_address, char *host, size_t hostlen)
{
	struct sockaddr_in sa = {
		.sin_family = AF_INET,
		.sin_addr = ip_address,
	};

	return getnameinfo((struct sockaddr *)&sa, sizeof(sa), host, hostlen, NULL, 0, NI_NAMEREQD) == 0;
}