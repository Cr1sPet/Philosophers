#include "philo.h"

static int init_time (t_philo *philo)
{

	size_t				i;

	i = 0;
	philo->cur_time = (long *)malloc(sizeof (long) * philo->nmb);
	if (NULL == philo->cur_time)
		return (0);
	philo->start_time = get_time(0);
	while (i < philo->nmb)
	{
		philo->cur_time[i] = 0;
		i++;
	}
	return (1);
} 

static int init_sem (t_philo *philo)
{
	philo->sem = sem_open("/sem", O_EXCL, 0644, philo->nmb);
	if (SEM_FAILED == philo->sem)
	{
		perror("ERROR");
		return (0);
	}
	// clear_philo(philo);
	printf ("hello\n");
	return (1);
}

int	init_philo (t_philo *philo, int argc, char **argv)
{
	philo->counter = 0;
	philo->nmb = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (6 == argc)
		philo->nmb_eats = ft_atoi(argv[5]);
	else
		philo->nmb_eats = -1;
	philo->philos = (pthread_t *)malloc(sizeof (pthread_t) * (philo->nmb));
	if (NULL == philo->philos)
		return (0);
	if (!init_time(philo))
		return (0);
	printf ("hello\n");
	if (!init_sem(philo))
		return (0);
	return (1);
}