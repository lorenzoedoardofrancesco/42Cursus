#include "ping.h"

volatile sig_atomic_t run = true;
volatile sig_atomic_t ping_alarm = true;

static void handle_sigint(int sig)
{
	(void)sig;
	run = false;
}

static void handle_sigalrm(int sig)
{
	(void)sig;
	ping_alarm = true;
}

int main(int argc, char *argv[])
{
	ping ping = {0};
	bool finishing = false;

	set_signal_handler(SIGINT, &handle_sigint);
	set_signal_handler(SIGALRM, &handle_sigalrm);

	verify_arguments(argc, argv, &ping);
	init(&ping);

	for (; ping.hostnames[ping.current_hostname] && run; ping.current_hostname++)
	{
		hostname_to_ip(&ping);
		print_header(&ping);

		for (size_t i = 0; i < (size_t)ping.preload; i++)
			send_ping(&ping);

		create_timer(&ping);

		while (run)
		{
			if (ping_alarm && (!ping.count || ping.stats.packets_transmitted < ping.count))
			{
				send_ping(&ping);
				ping_alarm = false;
				if (ping.stats.packets_transmitted == ping.count)
				{
					struct itimerspec its = {.it_value = ping.linger};
					if (timer_settime(ping.timerid, 0, &its, NULL) < 0)
						error("Setting timer failed", &ping);
					finishing = true;
				}
			}

			receive_ping(&ping, &ping.stats);

			if ((ping.count && ping.stats.responses_received >= ping.count) || finishing)
				break;

			if (ping.opt & OPT_TIMEOUT && ping_timeout(&ping))
				break;
		}

		print_statistics(&ping, &ping.stats);
		timer_delete(&ping.timerid);
	}

	close(ping.fd);
	return EXIT_SUCCESS;
}