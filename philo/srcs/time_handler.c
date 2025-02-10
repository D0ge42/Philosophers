#include "philosophers.h"

/*Get current time in millisecond. Time is expressed in epoch time, which
 * is basically seconds passed since 1970-01-01 00:00:00
 * Returns time value */

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

time_t	time_to_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
