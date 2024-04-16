#include "traceroute.h"

extern volatile sig_atomic_t run;

void init(traceroute_t *traceroute)
{
	if (getuid() != 0)
	{
		fprintf(stderr, "This program requires root privileges for raw socket creation.\n");
		exit(EXIT_FAILURE);
	}

	traceroute->fd_icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (traceroute->fd_icmp < 0)
		error("Socket creation failed", traceroute);

	if (!(traceroute->opt & OPT_ICMP))
	{
		traceroute->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // faire bien les erreurs regarder void trace_init(trace_t *t, const struct sockaddr_in to,
		if (traceroute->fd < 0)
			error("Socket creation failed", traceroute);
	}
	else
		traceroute->fd = traceroute->fd_icmp;

	if (!(traceroute->opt & OPT_FIRST_HOP))
		traceroute->current_hop = 1;

	if (!(traceroute->opt & OPT_MAX_HOP))
		traceroute->max_hop = DEFAULT_MAX_HOP;

	if (traceroute->current_hop > traceroute->max_hop)
		fprintf(stderr, "traceroute: first hop out of range: %d\n", traceroute->current_hop), exit(EXIT_FAILURE);

	if (!(traceroute->opt & OPT_PORT) || traceroute->port < IPPORT_RESERVED)
		traceroute->port = DEFAULT_PORT;

	if (!(traceroute->opt & OPT_QUERIES))
		traceroute->queries = DEFAULT_QUERIES;

	if (!(traceroute->opt & OPT_WAIT))
		traceroute->wait = (struct timeval){.tv_sec = DEFAULT_WAIT};

	if (traceroute->opt & OPT_INTERFACE)
	{
		if (setsockopt(traceroute->fd, SOL_SOCKET, SO_BINDTODEVICE, traceroute->interface, ft_strlen(traceroute->interface)) < 0 ||
			(traceroute->fd_icmp != traceroute->fd && setsockopt(traceroute->fd_icmp, SOL_SOCKET, SO_BINDTODEVICE, traceroute->interface, ft_strlen(traceroute->interface)) < 0))
			error("Setting interface failed", traceroute);
	}

	if (traceroute->opt & OPT_SOURCE)
	{
		struct sockaddr_in source_addr = {
			.sin_family = AF_INET,
			.sin_addr.s_addr = traceroute->source_addr,
		};
		if (bind(traceroute->fd, (struct sockaddr *)&source_addr, sizeof(source_addr)) < 0)
			error("Binding source address failed", traceroute);
	}

	if (traceroute->opt & OPT_TOS)
		if (setsockopt(traceroute->fd, IPPROTO_IP, IP_TOS, &traceroute->tos, sizeof(traceroute->tos)) < 0)
			error("Setting TOS failed", traceroute);

	hostname_to_ip(traceroute);

	printf("traceroute to %s (%s), %d hops max\n", traceroute->hostname, traceroute->hostip, traceroute->max_hop);
	fflush(stdout);
}

static uint16_t calculate_checksum(uint16_t *packet, int length)
{
	uint32_t sum = 0;

	while (length > 1)
	{
		sum += *packet++;
		length -= 2;
	}

	if (length)
		sum += *(uint8_t *)packet;

	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return (uint16_t)~sum;
}

static void send_probe(traceroute_t *traceroute, int ttl, int query)
{
	struct sockaddr_in host = {
		.sin_family = AF_INET,
		.sin_port = htons(traceroute->port + ttl - 1),
	};
	uint8_t packet[STD_DATA_SIZE];

	if (inet_pton(AF_INET, traceroute->hostip, &host.sin_addr) <= 0)
		error("inet_pton failed", traceroute);

	struct timeval tv;
	gettimeofday(&tv, NULL);
	traceroute->probe_time[ttl - 1][query] = tv;

	if (traceroute->opt & OPT_ICMP)
	{
		struct icmphdr icmphdr = {
			.type = ICMP_ECHO,
			.code = 0,
			.checksum = 0,
			.un.echo.id = htons(getpid() & 0xFFFF),
			.un.echo.sequence = query,
		};

		memcpy(packet, &icmphdr, ICMP_HDR_SIZE);

		for (int i = ICMP_HDR_SIZE; i < STD_DATA_SIZE; i++)
			packet[i] = i & 0xFF;

		icmphdr.checksum = calculate_checksum((uint16_t *)packet, STD_DATA_SIZE);
		memcpy(packet, &icmphdr, ICMP_HDR_SIZE);
	}
	else
		for (int i = 0; i < STD_DATA_SIZE; i++)
			packet[i] = i & 0xFF;

	if (sendto(traceroute->fd, packet, STD_DATA_SIZE, 0, (struct sockaddr *)&host, sizeof(host)) < 0)
		error("Sending probe failed", traceroute);
}

static void receive_probe(traceroute_t *traceroute, bool *print_host)
{
	struct sockaddr_in reply_addr;
	socklen_t reply_addr_len = sizeof(struct sockaddr_in);
	uint8_t reply_packet[IP_MAXPACKET];

	int bytes_recv = recvfrom(traceroute->fd_icmp, reply_packet, IP_MAXPACKET, 0, (struct sockaddr *)&reply_addr, &reply_addr_len);
	if (bytes_recv < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;
		error("Receiving probe failed", traceroute);
	}
	if (bytes_recv >= ICMP_HDR_SIZE)
	{
		struct iphdr *ip_hdr = (struct iphdr *)reply_packet;
		int ip_hdr_len = ip_hdr->ihl * 4;
		struct icmphdr *icmp_hdr = (struct icmphdr *)(reply_packet + ip_hdr_len);

		if (*print_host)
		{
			char host[NI_MAXHOST];
			if (traceroute->opt & OPT_NUMERIC || !ip_to_hostname(reply_addr.sin_addr, host, sizeof(host)))
				printf("%s ", inet_ntoa(reply_addr.sin_addr));
			else
				printf("%s (%s) ", inet_ntoa(reply_addr.sin_addr), host);
			fflush(stdout);
			*print_host = false;
		}

		switch (icmp_hdr->type)
		{
		case ICMP_ECHOREPLY:
			if (icmp_hdr->un.echo.id == htons(getpid() & 0xFFFF))
			{
				run = false;
				return;
			}
			break;
		case ICMP_TIME_EXCEEDED:
			break;
		case ICMP_DEST_UNREACH:
			run = false;
			switch (icmp_hdr->code)
			{
			case ICMP_UNREACH_NET:
				printf(" !N");
				break;
			case ICMP_UNREACH_HOST:
				printf(" !H");
				break;
			case ICMP_UNREACH_PROTOCOL:
				printf(" !P");
				break;
			case ICMP_UNREACH_PORT:
				break;
			case ICMP_UNREACH_NEEDFRAG:
				printf(" !F");
				break;
			case ICMP_UNREACH_SRCFAIL:
				printf(" !S");
				break;
			}
			break;
		default:
			break;
		}
		return;
	}

	printf("Request too short: %d\n", bytes_recv);
	return;
}

void send_and_receive_probe(traceroute_t *traceroute, int ttl)
{
	fd_set readfds;
	bool print_host = true;

	if (setsockopt(traceroute->fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		error("setsockopt failed", traceroute);

	for (int query = 0; query < traceroute->queries; query++)
	{
		FD_ZERO(&readfds);
		FD_SET(traceroute->fd_icmp, &readfds);

		send_probe(traceroute, ttl, query);

		struct timeval timeout = traceroute->wait;
		int ret = select(traceroute->fd_icmp + 1, &readfds, NULL, NULL, &timeout);
		if (ret < 0)
		{
			if (errno != EINTR)
				fprintf(stderr, "select failed: %s\n", strerror(errno));
			if (!run)
				return;
			continue;
		}
		else if (ret == 0)
		{
			if (query == 0)
				printf("%3d   ", ttl);
			printf(" * "), fflush(stdout);
		}
		else if (FD_ISSET(traceroute->fd_icmp, &readfds))
		{
			if (query == 0)
				printf("%3d   ", ttl);
			struct timeval recv_time;
			gettimeofday(&recv_time, NULL);

			receive_probe(traceroute, &print_host);

			struct timeval diff = timeval_subtract(traceroute->probe_time[ttl - 1][query], recv_time);
			printf(" %.3f ms ", diff.tv_sec * 1000.0 + diff.tv_usec / 1000.0), fflush(stdout);
		}
	}
	printf("\n");
}
