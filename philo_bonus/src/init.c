#include "philo.h"

static int init_sem (t_philo *philo)
{
	sem_unlink("sem");
	sem_unlink("all");
	sem_unlink("print");
	sem_unlink("time");
	sem_unlink("count");
	philo->sem = sem_open("sem", O_CREAT | O_EXCL, 0644, philo->nmb);
	philo->all = sem_open("all", O_CREAT | O_EXCL, 0644, 0);
	philo->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	philo->time = sem_open("time", O_CREAT | O_EXCL, 0644, 1);
	philo->count = sem_open("count", O_CREAT | O_EXCL, 0644, 0);
	if (SEM_FAILED == philo->sem || (SEM_FAILED == philo->all) || 
	SEM_FAILED == philo->print || SEM_FAILED == philo->time ||
	SEM_FAILED == philo->count)
	{
		perror("ERROR");
		return (0);
	}	
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
	philo->philos = (pid_t *)malloc(sizeof (pid_t) * (philo->nmb));
	if (NULL == philo->philos)
		return (0);
	philo->start_time = get_time(0);
	philo->last_eat = get_time(0);
	printf ("hello\n");
	if (!init_sem(philo))
		return (0);
	return (1);
}