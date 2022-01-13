#include "philo.h"

void	*threadFunc(void* iphilo)
{
	int		i;
	size_t		p_indx;
	int		right;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)iphilo;
	p_indx = philo->index;
	if (p_indx == philo->nmb - 1)
		right = 0;
	else
		right = p_indx + 1;
	while (i++ != philo->nmb_eats)
	{
		printf("%ld %lu is thinking\n", get_time(), p_indx);
		pthread_mutex_lock(&philo->locks[p_indx]);
		if (!philo->death_stat[p_indx])
		{
			pthread_mutex_unlock(&philo->locks[p_indx]);
			break;
		}
		pthread_mutex_lock(&philo->locks[right]);
		if (!philo->death_stat[p_indx])
		{
			pthread_mutex_unlock(&philo->locks[p_indx]);
			pthread_mutex_unlock(&philo->locks[right]);
			break;
		}
		usleep(philo->time_to_eat);
		if (!philo->death_stat[p_indx])
		{
			pthread_mutex_unlock(&philo->locks[p_indx]);
			pthread_mutex_unlock(&philo->locks[right]);
			break;
		}
		philo->cur_time[p_indx] = get_time();
		printf("%ld %lu is eating\n", philo->cur_time[p_indx], p_indx);
		pthread_mutex_unlock(&philo->locks[p_indx]);
		pthread_mutex_unlock(&philo->locks[right]);
		usleep(philo->time_to_sleep);
		if (!philo->death_stat[p_indx])
		{
			break;
		}
		printf("%ld %lu is sleeping\n", get_time(), p_indx);
	}
	pthread_exit(0);
}

int	work_philo (t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->index = 0;
	while (i < philo->nmb)
	{
		philo->index = i;
		pthread_create(&philo->philos[philo->index], NULL, threadFunc, (void *)philo);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < philo->nmb)
	{
		pthread_detach(philo->philos[i]);
		i++;
	}
	death_monitor(philo);
	return (1);
}