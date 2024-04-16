#include "traceroute.h"

bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

struct timeval timeval_subtract(struct timeval start, struct timeval end)
{
	struct timeval temp;
	if (end.tv_usec < start.tv_usec)
	{
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_usec = 1000000 + end.tv_usec - start.tv_usec;
	}
	else
	{
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_usec = end.tv_usec - start.tv_usec;
	}
	return temp;
}

void set_signal_handler(int sig, void (*handler)(int))
{
	struct sigaction sa = {.sa_handler = handler};
	if (sigaction(sig, &sa, NULL) < 0)
		error("Setting signal handler failed", NULL);
}


char *ft_strchr(const char *s, int c)
{
	while (*s || !c)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

int ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = -1;
	if (!n)
		return (0);
	while (++i < (n - 1) && s1[i] && s2[i])
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	i = -1;
	while (++i < n && src[i])
		dst[i] = src[i];
	while (i < n)
		dst[i++] = '\0';
	return (dst);
}
