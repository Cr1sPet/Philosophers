#include "philo.h"

long	get_time()
{
	struct timeval	c_time;

	if (-1 == gettimeofday(&c_time, NULL))
		return (0);
	return (c_time.tv_usec);
}