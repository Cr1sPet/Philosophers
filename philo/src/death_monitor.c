#include "philo.h"

long	get_abs(long a)
{
	if (a >= 0)
		return (a);
	else
		return (-a);
}

void *death_mon(void *iphilo)
{
	size_t		i;
	t_philo *philo;

	philo = (t_philo *)iphilo;
	while (1)
	{
		i = 0;
		while (i < philo->nmb)
		{
			if (get_abs((long)(get_time() - philo->time_to_die)) >= philo->cur_time[i])
			{
				philo->ok = 0;
				printf("%ld %lu died\n", philo->cur_time[i], i);
			}
			i++;
		}
	}
}

int death_monitor(t_philo *philo)
{
	pthread_t monitor;


	pthread_create(&monitor, NULL, death_mon, (void *)philo);
	return (1);
}