#include "ping.h"

extern volatile sig_atomic_t run;

void init(ping *ping)
{
	if (geteuid() != 0)
	{
		fprintf(stderr, "This program requires root privileges for raw socket creation.\n");
		exit(EXIT_FAILURE);
	}

	ping->fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ping->fd < 0)
		error("Socket creation failed", ping);

	if (!(ping->opt & OPT_LINGER))
		ping->linger = (struct timespec){MAXWAIT, 0};
	if (!(ping->opt & OPT_SIZE))
		ping->size = STD_DATA_SIZE;
	if (ping->size >= (int)sizeof(struct timespec))
		ping->timing = true;
	if (!(ping->opt & OPT_INTERVAL))
		ping->interval = (struct timespec){INTERVAL, 0};

	if (ping->opt & OPT_FLOOD)
		ping->interval = (struct timespec){0, 10000000};
	if (ping->opt & OPT_IGNORE)
		if (setsockopt(ping->fd, SOL_SOCKET, SO_DONTROUTE, &(int){1}, sizeof(int)) < 0)
			error("Setting SO_DONTROUTE failed", ping);
	if (ping->opt & OPT_TOS)
		if (setsockopt(ping->fd, IPPROTO_IP, IP_TOS, &ping->tos, sizeof(ping->tos)) < 0)
			error("Setting IP_TOS failed", ping);
	if (ping->opt & OPT_TTL)
		if (setsockopt(ping->fd, IPPROTO_IP, IP_TTL, &ping->ttl, sizeof(ping->ttl)) < 0)
			error("Setting IP_TTL failed", ping);
	if (ping->opt & OPT_DEBUG)
		if (setsockopt(ping->fd, SOL_SOCKET, SO_DEBUG, &(int){1}, sizeof(int)) < 0)
			error("Setting SO_DEBUG failed", ping);

	struct timespec current_time;
	clock_gettime(CLOCK_MONOTONIC, &current_time);
	ping->start_time = current_time;
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

static void fill_data(uint8_t *data, int length, char *pattern, int pattern_len)
{
	if (pattern)
		for (int i = 0; i < length; i++)
			data[i] = pattern[i % pattern_len];
	else
		for (int i = 0; i < length; i++)
			data[i] = i & 0xFF;
}

void send_ping(ping *ping)
{
	struct icmphdr icmphdr = {
		.type = ICMP_ECHO,
		.code = 0,
		.checksum = 0,
		.un.echo.id = htons(getpid() & 0xFFFF),
		.un.echo.sequence = htons(ping->stats.packets_transmitted++),
	};

	int icmp_packet_size = ICMP_HDR_SIZE + ping->size;
	uint8_t packet[icmp_packet_size];

	memcpy(packet, &icmphdr, ICMP_HDR_SIZE);

	if (ping->timing)
	{
		struct timespec start_time;
		clock_gettime(CLOCK_MONOTONIC, &start_time);
		memcpy(packet + ICMP_HDR_SIZE, &start_time, sizeof(start_time));
		fill_data(packet + ICMP_HDR_SIZE + sizeof(start_time), ping->size - (int)sizeof(start_time), ping->opt & OPT_PATTERN ? ping->pattern : NULL, ping->pattern_len);
	}
	else
		fill_data(packet + ICMP_HDR_SIZE, ping->size, ping->opt & OPT_PATTERN ? ping->pattern : NULL, ping->pattern_len);

	icmphdr.checksum = calculate_checksum((uint16_t *)packet, icmp_packet_size);
	memcpy(packet, &icmphdr, ICMP_HDR_SIZE);

	int bytes_sent = sendto(ping->fd, packet, icmp_packet_size, 0, (struct sockaddr *)&ping->hostaddr, sizeof(struct sockaddr_in));
	if (bytes_sent < 0)
		error("Sending ping failed", ping);

	if (!(ping->opt & OPT_QUIET) && ping->opt & OPT_FLOOD)
		putc('.', stdout), fflush(stdout);
}

static bool set_bitmap(ping *ping, int seqNum)
{
	int index = seqNum / INT_SIZE;
	int bit = seqNum % INT_SIZE;
	int nextSeqNum = (seqNum + 1) % MAX_SEQ_NUM;
	int nextIndex = nextSeqNum / INT_SIZE;
	int nextBit = nextSeqNum % INT_SIZE;

	ping->bitmap[nextIndex] &= ~(1 << nextBit);

	if (ping->bitmap[index] & (1 << bit))
	{
		ping->stats.packets_duplicated++;
		return true;
	}

	ping->bitmap[index] |= (1 << bit);
	ping->stats.packets_received++;
	ping->stats.responses_received++;
	return false;
}

static void handle_echo_reply(ping *ping, ping_stats *stats, struct iphdr *ip_hdr, int ip_hdr_len, struct icmphdr *icmp_hdr, struct sockaddr_in reply_addr, uint8_t *reply_packet, int bytes_recv)
{
	double rtt;

	if (icmp_hdr->un.echo.id != htons(getpid() & 0xFFFF))
		return;

	bool duplicate = set_bitmap(ping, ntohs(icmp_hdr->un.echo.sequence));

	if (ping->timing && !duplicate)
	{
		struct timespec start_time, end_time, delta_time;
		memcpy(&start_time, reply_packet + ip_hdr_len + ICMP_HDR_SIZE, sizeof(start_time));
		clock_gettime(CLOCK_MONOTONIC, &end_time);

		delta_time = timespec_subtract(start_time, end_time);

		rtt = delta_time.tv_sec * 1000.0 + delta_time.tv_nsec / 1000000.0;

		if (rtt < stats->min_rtt || stats->min_rtt == 0)
			stats->min_rtt = rtt;
		if (rtt > stats->max_rtt)
			stats->max_rtt = rtt;
		stats->sum_rtt += rtt;
		stats->sum_rtt_sq += rtt * rtt;
	}

	if (ping->opt & OPT_QUIET)
		return;
	if (ping->opt & OPT_FLOOD)
	{
		putc('\b', stdout), fflush(stdout);
		return;
	}

	char host[NI_MAXHOST];
	if (ping->opt & OPT_NUMERIC || !ip_to_hostname(reply_addr.sin_addr, host, sizeof(host)))
		printf("%d bytes from %s:", bytes_recv - ip_hdr_len, inet_ntoa(reply_addr.sin_addr));
	else
		printf("%d bytes from %s (%s):", bytes_recv - ip_hdr_len, host, inet_ntoa(reply_addr.sin_addr));

	printf(" icmp_seq=%d ttl=%d", ntohs(icmp_hdr->un.echo.sequence), ip_hdr->ttl);
	if (ping->timing)
		printf(" time=%.3f ms", rtt);
	if (duplicate)
		printf(" (DUP!)");
	printf("\n");
}

static void print_verbose(struct iphdr *ip_hdr, int ip_hdr_len, struct icmphdr *icmp_hdr, uint8_t *reply_packet)
{
	printf("IP Hdr Dump:\n ");
	for (int i = 0; i < ip_hdr_len; i++)
		printf("%02x%s", reply_packet[IP_HDR_SIZE + ICMP_HDR_SIZE + i], i % 2 ? " " : "");
	printf("\n");

	printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
	printf(" %1x  %1x  %02x %04x %04x   %1x %04x  %02x  %02x %04x",
		   ip_hdr->version,
		   ip_hdr->ihl,
		   ip_hdr->tos,
		   ntohs(ip_hdr->tot_len),
		   ntohs(ip_hdr->id),
		   (ntohs(ip_hdr->frag_off) & 0xE000) >> 13,
		   ntohs(ip_hdr->frag_off) & 0x1FFF,
		   ip_hdr->ttl,
		   ip_hdr->protocol,
		   ntohs(ip_hdr->check));

	printf(" %s ", inet_ntoa(*(struct in_addr *)&ip_hdr->saddr));
	printf(" %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr->daddr));

	printf("ICMP: type %u, code %u, size %u, id 0x%04x, seq 0x%04x\n",
		   icmp_hdr->type,
		   icmp_hdr->code,
		   ntohs(ip_hdr->tot_len) - ip_hdr_len,
		   ntohs(icmp_hdr->un.echo.id),
		   ntohs(icmp_hdr->un.echo.sequence));
}

static void handle_icmp(ping *ping, int ip_hdr_len, struct sockaddr_in reply_addr, struct icmphdr *icmp_hdr, uint8_t *reply_packet, int bytes_recv)
{
	struct iphdr *ip_hdr_error = (struct iphdr *)(reply_packet + ip_hdr_len + ICMP_HDR_SIZE);
	int ip_hdr_error_len = ip_hdr_error->ihl * 4;
	struct icmphdr *icmp_hdr_original = (struct icmphdr *)(reply_packet + ip_hdr_len + ICMP_HDR_SIZE + ip_hdr_error_len);

	if (icmp_hdr_original->un.echo.id != htons(getpid() & 0xFFFF))
		return;

	char host[NI_MAXHOST];
	if (ping->opt & OPT_NUMERIC || !ip_to_hostname(reply_addr.sin_addr, host, sizeof(host)))
		printf("%d bytes from %s:", bytes_recv - ip_hdr_error_len, inet_ntoa(reply_addr.sin_addr));
	else
		printf("%d bytes from %s (%s):", bytes_recv - ip_hdr_error_len, host, inet_ntoa(reply_addr.sin_addr));

	switch (icmp_hdr->type)
	{
	case ICMP_DEST_UNREACH:
		if (icmp_hdr->code > 15)
			printf(" Unknown code %d", icmp_hdr->code);
		else
			printf(" %s", icmp_dest_unreach[icmp_hdr->code]); // a tester et trouver un example concret a l'ecole
		break;
	case ICMP_TIME_EXCEEDED:
		printf(" Time to live exceeded");
		break;
	}
	printf("\n");

	if (ping->opt & OPT_VERBOSE)
		print_verbose(ip_hdr_error, ip_hdr_error_len, icmp_hdr_original, reply_packet);

	ping->stats.responses_received++;
}

void receive_ping(ping *ping, ping_stats *stats)
{
	struct sockaddr_in reply_addr;
	socklen_t reply_addr_len = sizeof(struct sockaddr_in);
	uint8_t reply_packet[IP_MAXPACKET];

	int bytes_recv = recvfrom(ping->fd, reply_packet, IP_MAXPACKET, 0, (struct sockaddr *)&reply_addr, &reply_addr_len);
	if (bytes_recv < 0)
	{
		if (errno == EINTR)
			return;
		error("Receiving ping failed", ping);
	}
	if (bytes_recv >= ICMP_HDR_SIZE)
	{
		struct iphdr *ip_hdr = (struct iphdr *)reply_packet;
		int ip_hdr_len = ip_hdr->ihl * 4;
		struct icmphdr *icmp_hdr = (struct icmphdr *)(reply_packet + ip_hdr_len);

		switch (icmp_hdr->type)
		{
		case ICMP_ECHOREPLY:
			handle_echo_reply(ping, stats, ip_hdr, ip_hdr_len, icmp_hdr, reply_addr, reply_packet, bytes_recv);
			break;
		case ICMP_DEST_UNREACH:
		case ICMP_TIME_EXCEEDED:
			handle_icmp(ping, ip_hdr_len, reply_addr, icmp_hdr, reply_packet, bytes_recv);
			break;
		default:
			break;
		}
	}
}

void print_header(ping *ping)
{
	ping->stats = (ping_stats){0};
	ping->bitmap[0] = 0;
	printf("PING %s (%s): %d data bytes", ping->hostname, ping->hostip, ping->size);
	if (ping->opt & OPT_VERBOSE)
		printf(", id 0x%04x = %u", getpid() & 0xFFFF, getpid() & 0xFFFF);
	printf("\n");
}

void print_statistics(ping *ping, ping_stats *stats)

{
	fflush(stdout);
	printf("--- %s ping statistics ---\n", ping->hostname);
	printf("%zu packets transmitted, %zu packets received", stats->packets_transmitted, stats->packets_received);
	if (stats->packets_duplicated)
		printf(", +%zu duplicates", stats->packets_duplicated);
	if (stats->packets_transmitted)
	{
		if (stats->packets_received > stats->packets_transmitted)
			printf(" -- somebody is printing forged packets!");
		else
			printf(", %d%% packet loss", (int)((stats->packets_transmitted - stats->packets_received) * 100 / stats->packets_transmitted));
	}
	printf("\n");

	if (stats->packets_received && ping->timing)
	{
		double avg_rtt = ping->stats.sum_rtt / stats->packets_received;
		double variance_rtt = ping->stats.sum_rtt_sq / stats->packets_received - avg_rtt * avg_rtt;
		double stddev_rtt = sqrt(variance_rtt);
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
			   ping->stats.min_rtt, avg_rtt, ping->stats.max_rtt, stddev_rtt);
	}
}