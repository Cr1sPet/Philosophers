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
	while (1)
	{
		print_info(philo, "%06ld %lu is thinking\n", p_indx + 1);
		pthread_mutex_lock(&philo->locks[p_indx]);
		print_info(philo, "%06ld %lu has taken a fork\n", p_indx + 1);
		pthread_mutex_lock(&philo->locks[right]);
		print_info(philo, "%06ld %lu has taken a fork\n", p_indx + 1);
		philo->cur_time[p_indx] = get_time(philo->start_time);
		print_info(philo, "%06ld %lu is eating\n", p_indx + 1);
		usleep(philo->time_to_eat * 1000);
		if (++i == philo->nmb_eats)
		{
			philo->counter++;
			pthread_mutex_unlock(&philo->locks[right]);
			pthread_mutex_unlock(&philo->locks[p_indx]);
			break ;
		}
		pthread_mutex_unlock(&philo->locks[right]);
		pthread_mutex_unlock(&philo->locks[p_indx]);
		print_info(philo, "%06ld %lu is sleeping\n", p_indx + 1);
		usleep(philo->time_to_sleep * 1000);
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
		usleep(100);
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