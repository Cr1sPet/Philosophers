#include "philo.h"

void child_process(t_philo *philo)
{
	int i;

	i = 0;
	death_monitor(philo);
	while (1)
	{
		print_info (philo, "%06ld %d is thinking\n");
		sem_wait(philo->sem);
		print_info (philo, "%06ld %d has taken a fork\n");
		sem_wait(philo->sem);
		print_info (philo, "%06ld %d has taken a fork\n");
		// sem_wait(philo->sem);
		philo->last_eat = get_time(philo->start_time);
		// sem_post(philo->sem);
		print_info (philo, "%06ld %d is eating\n");
		ft_sleep(philo, philo->time_to_eat);
		if (++i == philo->nmb_eats)
		{
			philo->counter++;
			sem_post(philo->sem);
			sem_post(philo->sem);
			sem_post(philo->all);
			break;
		}
		sem_post(philo->sem);
		sem_post(philo->sem);
		print_info (philo, "%06ld %d is sleeping\n");
		ft_sleep(philo, philo->time_to_sleep);
	}
	exit(EXIT_SUCCESS);
}

int work_philo(t_philo *philo)
{
	int i;

	i = 0;
	death_monitor(philo);
	printf("hello\n");
	while (i < philo->nmb)
	{
		philo->philos[i] = fork();
		philo->index = i;
		if (-1 == philo->philos[i])
			while (--i)
			{
				printf("OHOHOHOHOHOHHO\n");
				kill(philo->philos[i], SIGKILL);
				return (0);
			}

		if (0 == philo->philos[i])
			child_process(philo);
		i++;
	}
	sem_wait(philo->all);
	return (1);
}
