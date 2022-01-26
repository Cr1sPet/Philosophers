#include "philo.h"

static int init_lock (t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->locks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * (philo->nmb));
	if (NULL == philo->locks)
		return (0);
	while (i < philo->nmb)
	{
		if (0 != pthread_mutex_init(&philo->locks[i++], NULL))
			return (0);
	}
	if (0 != pthread_mutex_init(&philo->print, NULL))
			return (0);
	return (1);
}

int	init_member(t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->members = (t_member *) malloc (philo->nmb);
	if (NULL == philo->members)
		return (0);
	while (i < philo->nmb)
	{
		philo->members[i].index = i;
		philo->members[i].last_eat = 0;
		philo->members[i].left = philo->locks[i];
		if (i == philo->nmb - 1)
			philo->members[i].right = philo->locks[0];
		else
			philo->members[i].right = philo->locks[i + 1];
		i++;
	}
	philo->members->inf = philo;
	return (1);
}

int	init_philo(t_philo *philo, int argc, char **argv)
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
	if (!init_lock(philo))
		return (0);
	if (!init_member(philo))
		return (0);
	return (1);
}
