#include "ping.h"

static double absd(double x)
{
	return x < 0 ? -x : x;
}

double sqrt(double n)
{
	if (n < 0)
		return -1;
	if (n == 0)
		return 0;

	double x = n * 0.5;
	double x_prev;

	do
	{
		x_prev = x;
		x = 0.5 * (x + n / x);
	} while (absd((x - x_prev) / x) >= __DBL_EPSILON__);

	return x;
}

bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

struct timespec timespec_subtract(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if (end.tv_nsec < start.tv_nsec)
	{
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	}
	else
	{
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}

	if (temp.tv_sec < 0)
	{
		temp.tv_sec = 0;
		temp.tv_nsec = 0;
	}

	return temp;
}

void set_signal_handler(int sig, void (*handler)(int))
{
	struct sigaction sa = {.sa_handler = handler};
	if (sigaction(sig, &sa, NULL) < 0)
		error("Setting signal handler failed", NULL);
}

void create_timer(ping *ping)
{
	struct itimerspec its = {.it_interval = ping->interval, .it_value = ping->interval};

	if (timer_create(CLOCK_MONOTONIC, NULL, &ping->timerid) < 0)
		error("Creating timer failed", ping);
	ping->timer_initialized = true;
	if (timer_settime(ping->timerid, 0, &its, NULL) < 0)
		error("Setting timer failed", ping);
}