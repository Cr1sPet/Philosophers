#include "philo.h"

void	*eat_check(void *iphilo)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)iphilo;
	while (i < philo->nmb)
	{
		sem_wait (philo->count);
		i++;
	}
	print_info(philo, "eat nmb reached\n");
	sem_wait(philo->time);
	sem_wait(philo->print);
	sem_post (philo->all);
	return (NULL);
}

static int eat_checker(t_philo *philo)
{
	pthread_t	eat_monitor;

	if (-1 == philo->nmb_eats)
		return (0);
	pthread_create(&eat_monitor, NULL, eat_check, (void *)philo);
	pthread_detach (eat_monitor);
	return (0);
}

void child_process(t_philo *philo)
{
	int i;

	i = 0;
	philo->start_time = get_time(0);
	philo->last_eat = get_time(philo->start_time);
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
			sem_post (philo->count);
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
	eat_checker(philo);
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
