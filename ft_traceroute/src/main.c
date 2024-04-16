#include "traceroute.h"

volatile sig_atomic_t run = true;

static void handle_sigint(int sig)
{
	(void)sig;
	run = false;
}

int main(int argc, char *argv[])
{
	traceroute_t traceroute = {0};

	set_signal_handler(SIGINT, handle_sigint);

	verify_arguments(argc, argv, &traceroute);
	init(&traceroute);

	while (run)
	{
		if (traceroute.current_hop > traceroute.max_hop)
			exit(EXIT_FAILURE);

		send_and_receive_probe(&traceroute, traceroute.current_hop++);
	}

	close(traceroute.fd_icmp);
	if (traceroute.fd)
		close(traceroute.fd);
	return EXIT_SUCCESS;
}