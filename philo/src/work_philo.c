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
		printf("Philo %lu started to think\n", p_indx);
		pthread_mutex_lock(&philo->locks[p_indx]);
		pthread_mutex_lock(&philo->locks[right]);
		printf("Philo %lu started to eat\n", p_indx);
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->locks[p_indx]);
		pthread_mutex_unlock(&philo->locks[right]);
		printf("Philo %lu started to sleep\n", p_indx);
		usleep(philo->time_to_sleep);
		if (i++ == 100)
			break;
	}
	pthread_exit(0);
}

int	work_philo (t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->index = 0;
	while (philo->index < philo->nmb)
	{
		pthread_create(&philo->philos[philo->index], NULL, threadFunc, (void *)philo);
		usleep(500);
		// printf("hello\n");
		philo->index++;
	}
	while (i < philo->nmb)
	{
		pthread_join(philo->philos[i],NULL);
		i++;
	}
	return (1);
}