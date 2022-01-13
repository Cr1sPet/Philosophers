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
	int			*ok;
	size_t		counter;
	t_philo *philo;

	counter = 0;
	philo = (t_philo *)iphilo;
	ok = (int *)malloc(sizeof(int) * philo->nmb);
	i = 0;
	while (i < philo->nmb)
		ok[i++] = 0;
	while (counter < philo->nmb)
	{
		i = 0;
		while (i < philo->nmb && counter < philo->nmb)
		{
			if (philo->death_stat[i] && (long)(get_time(philo->start_time) - philo->time_to_die) >= philo->cur_time[i])
			{
				ok[i] = 1;
				printf("%06ld %lu died\n", get_time(philo->start_time), i);
				philo->death_stat[i] = 0;
				counter++;
			}
			if (!ok[i] && !philo->death_stat[i])
			{
				ok[i] = 1;
				counter++;
			}
			i++;
		}
	}
	return (NULL);
}

int death_monitor(t_philo *philo)
{
	pthread_t monitor;
		
	pthread_create(&monitor, NULL, death_mon, (void *)philo);
	pthread_join(monitor, NULL);
	return (1);
}