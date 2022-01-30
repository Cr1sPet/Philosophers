/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:48:44 by jchopped          #+#    #+#             */
/*   Updated: 2022/01/30 13:38:00 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	init_time(t_philo *philo)
// {
// 	size_t	i;

// 	i = 0;
// 	philo->cur_time = (long *)malloc(sizeof (long) * philo->nmb);
// 	if (NULL == philo->cur_time)
// 		return (0);
// 	philo->start_time = get_time(0);
// 	while (i < philo->nmb)
// 	{
// 		philo->cur_time[i] = get_time(philo->start_time);
// 		i++;
// 	}
// 	return (1);
// }

// static int	init_lock(t_philo *philo)
// {
// 	size_t	i;

// 	i = 0;
// 	philo->locks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * (philo->nmb));
// 	if (NULL == philo->locks)
// 		return (0);
// 	while (i < philo->nmb)
// 	{
// 		if (0 != pthread_mutex_init(&philo->locks[i++], NULL))
// 			return (0);
// 	}
// 	philo->times = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * (philo->nmb));
// 	if (NULL == philo->times)
// 		return (0);
// 	i = 0;
// 	while (i < philo->nmb)
// 	{
// 		if (0 != pthread_mutex_init(&philo->times[i++], NULL))
// 			return (0);
// 	}
// 	if (0 != pthread_mutex_init(&philo->print, NULL))
// 		return (0);
// 	return (1);
// }

int	init_members(t_philo *philos)
{
	int	i;

	i = 0;
	philos->members = (t_member *)malloc(sizeof(t_member) * philos->nmb);
	if (NULL == philos->members)
		return (0);
	while (i < philos->nmb)
	{
		philos->members[i].index = i;
		philos->members[i].last_eat = get_time(philos->start_time);
		if (0 != pthread_mutex_init(&philos->members[i].time_lock, NULL))
			return (0);
		if (0 != pthread_mutex_init(&philos->members[i].mem_lock, NULL))
			return (0);
		philos->members[i].philo = philos;
		i++;
	}
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
	philo->start_time = get_time(0);
	if (!init_members(philo))
		return (0);
	if (0 != pthread_mutex_init(&philo->print, NULL))
		return (0);
	return (1);
}
