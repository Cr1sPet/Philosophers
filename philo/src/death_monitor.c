/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:48:52 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/01 17:33:24 by jchopped         ###   ########.fr       */
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

void	set_stop(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->nmb)
	{
		philo->members[i].stop = 1;
		i++;
	}
}

void	work_died(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->print);
	set_stop(philo);
	printf("%12ld %d died\n", get_time(philo->start_time), i + 1);
}

int	check_eat_nmb(t_philo *philo)
{
	if (philo->nmb == philo->counter)
	{
		set_stop(philo);
		return (1);
	}
	return (0);
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
			if (check_eat_nmb(philo))
				return (NULL);
			pthread_mutex_lock(&philo->members[i].time_lock);
			if ((get_time(0) - philo->members[i].last_eat) >
				(long)philo->time_to_die)
			{
				work_died(philo, i);
				// pthread_mutex_unlock(&philo->print);
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
