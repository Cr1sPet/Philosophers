#include "philo.h"

void	child_process(t_philo *philo, long p_indx)
{
	int	i;

	i = 0;
	while (1)
	{
		printf("%06ld %lu is thinking\n", get_time(philo->start_time), p_indx + 1);
		sem_wait(philo->sem);
		printf("%06ld %lu has taken a fork\n", philo->cur_time[p_indx], p_indx + 1);
		sem_wait(philo->sem);
		printf("%06ld %lu has taken a fork\n", philo->cur_time[p_indx], p_indx + 1);
		philo->cur_time[p_indx] = get_time(philo->start_time);
		printf("%06ld %lu is eating\n", philo->cur_time[p_indx], p_indx + 1);
		usleep(philo->time_to_eat * 1000);
		if (++i == philo->nmb_eats)
		{
			philo->counter++;
			sem_post(philo->sem);
			sem_post(philo->sem);
			break;
		}
		sem_post(philo->sem);
		sem_post(philo->sem);
		printf("%06ld %lu is sleeping\n", get_time(philo->start_time), p_indx + 1);
		usleep(philo->time_to_sleep * 1000);
	}
	exit(EXIT_SUCCESS);
}

int	work_philo (t_philo *philo)
{
	size_t	i;
	pid_t	child;

	i = 0;
	death_monitor(philo);
	printf ("hello\n");
	while (i < philo->nmb)
	{
		child = fork();
		if (-1 == child)
			return (0);
		if (0 == child)
			child_process(philo, i);
		usleep(100);
		i++;
	}
	i = 0;
	return (1);
}