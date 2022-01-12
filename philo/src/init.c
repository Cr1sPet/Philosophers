#include "philo.h"

int	init_philo (t_philo *philo, int argc, char **argv)
{
	philo->philos = (pthread_t *)malloc(sizeof (pthread_t) * (argc - 1));
	if (NULL == philo->philos)
		return (0);
	philo->locks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * (argc - 1));
	if (NULL == philo)
		return (0);
	philo->nmb = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (6 == argc)
		philo->nmb_eats = ft_atoi(argv[5]);
	else
		philo->nmb_eats = -1;
	return (1);
}