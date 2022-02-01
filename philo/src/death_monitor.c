/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:48:52 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/01 15:22:15 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_abs(long a)
{
	if (a >= 0)
		return (a);
	else
		return (-a);
}

void	*death_mon(void *iphilo)
{
	size_t		i;
	t_philo		*philo;

	philo = (t_philo *)iphilo;
	while (1)
	{
		i = -1;
		while (++i < philo->nmb)
		{
			if (philo->nmb == philo->counter)
			{
				pthread_mutex_lock(&philo->print);
				return (NULL);
			}
			pthread_mutex_lock(&philo->members[i].time_lock);
			if ((get_time(0) - philo->members[i].last_eat) >  (long)philo->time_to_die)
			{
				pthread_mutex_lock(&philo->print);
				printf("%12ld %lu died\n", get_time(philo->start_time), i + 1);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->members[i].time_lock);
		}
	}
	return (NULL);
}

int	death_monitor(t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, death_mon, (void *)philo);
	pthread_join(monitor, NULL);
	return (1);
}
