/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:48:44 by jchopped          #+#    #+#             */
/*   Updated: 2022/03/08 17:13:08 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_lock(t_philo *philo)
{
	size_t	i;

	i = 0;
	if (0 != pthread_mutex_init(&philo->print, NULL))
		return (0);
	if (0 != pthread_mutex_init(&philo->all, NULL))
		return (0);
	if (0 != pthread_mutex_init(&philo->set, NULL))
		return (0);
	philo->locks = (pthread_mutex_t *) \
		malloc(sizeof (pthread_mutex_t) * (philo->nmb));
	if (NULL == philo->locks)
		return (0);
	while (i < philo->nmb)
	{
		if (0 != pthread_mutex_init(&philo->locks[i++], NULL))
			return (0);
	}
	return (1);
}

void	init_forks(t_member *member, t_philo *philo)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	left = &philo->locks[member->index];
	right = &philo->locks[(member->index + 1) % philo->nmb];
	if (member->index % 2 == 0 && member->index != member->philo->nmb - 1)
	{
		member->first = right;
		member->second = left;
	}
	else
	{
		member->first = left;
		member->second = right;
	}
}

int	init_members(t_philo *philos)
{
	size_t	i;

	i = 0;
	philos->members = (t_member *)malloc(sizeof(t_member) * philos->nmb);
	if (NULL == philos->members)
		return (0);
	while (i < philos->nmb)
	{
		philos->members[i].eated = 0;
		philos->members[i].stop = 0;
		philos->members[i].index = i;
		philos->members[i].start_time = get_time(0);
		philos->members[i].last_eat = get_time(0);
		if (0 != pthread_mutex_init(&philos->members[i].time_lock, NULL))
			return (0);
		philos->members[i].philo = philos;
		init_forks(&philos->members[i], philos);
		i++;
	}
	return (1);
}

int	init_philo(t_philo *philo, int argc, char **argv)
{
	philo->stop = 0;
	philo->counter = 0;
	philo->start_time = get_time(0);
	philo->nmb = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (6 == argc)
	{
		philo->nmb_eats = ft_atoi(argv[5]);
		if (0 == philo->nmb_eats)
			return (0);
	}
	else
		philo->nmb_eats = -1;
	if (!init_lock(philo))
		return (0);
	if (!init_members(philo))
		return (0);
	return (1);
}
