#include "ping.h"

static void cleanup_and_exit(ping *ping)
{
	if (ping)
	{
		if (ping->fd > 2)
			close(ping->fd);
		if (ping->timer_initialized && timer_delete(ping->timerid) < 0)
			fprintf(stderr, "ping: %s: %s\n", "timer_delete failed", strerror(errno));
	}

	exit(EXIT_SUCCESS);
}

void error(char *message, ping *ping)
{
	fprintf(stderr, "ping: %s: %s\n", message, strerror(errno));
	cleanup_and_exit(ping);
}

static void g_error(int status, ping *ping)
{
	if (status != EAI_NONAME)
		fprintf(stderr, "ping: %s\n", gai_strerror(status));
	else
		fprintf(stderr, "ping: unknown host\n");

	cleanup_and_exit(ping);
}

void hostname_to_ip(ping *ping)
{
	struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_flags = AI_CANONNAME,
	};
	struct addrinfo *res = NULL;

	int status = getaddrinfo(ping->hostnames[ping->current_hostname], NULL, &hints, &res);
	if (status != 0 || res == NULL)
		g_error(status, ping);

	ping->hostaddr = *(struct sockaddr_in *)res->ai_addr;
	if (inet_ntop(AF_INET, &ping->hostaddr.sin_addr, ping->hostip, INET_ADDRSTRLEN) == NULL)
	{
		freeaddrinfo(res);
		error("inet_ntop failed", ping);
	}

	if (res->ai_canonname)
	{
		strncpy(ping->hostname, res->ai_canonname, HOST_NAME_MAX);
		ping->hostname[HOST_NAME_MAX] = '\0';
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

bool ping_timeout(ping *ping)
{
	struct timespec current_time;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	struct timespec elapsed = timespec_subtract(ping->start_time, current_time);
	return elapsed.tv_sec >= ping->timeout.tv_sec;
}