#include "philo.h"

long	get_time(long align)
{
	long			ret;
	struct timeval	c_time;

	if (-1 == gettimeofday(&c_time, NULL))
		return (0);
	ret = (c_time.tv_sec % 1000) * 1000;
	ret += c_time.tv_usec / 1000;
	return (ret - align);
}

void	clear_philo(t_philo *philo)
{
	sem_close(philo->sem);
}