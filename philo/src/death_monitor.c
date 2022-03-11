/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:48:52 by jchopped          #+#    #+#             */
/*   Updated: 2022/03/11 15:04:35 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	work_died(t_philo *philo, int i)
{
	print_info(philo, "%12ld %d died\n", i);
	philo->stop = 1;
}

int	check_stop(t_philo *philo)
{
	size_t	i;

	i = 0;
	if (philo->stop == 1)
		return (1);
	if (philo->nmb_eats != -1)
	{
		while (i < philo->nmb)
		{
			if (philo->members[i].eated == 0)
				return (0);
			i++;
		}
		philo->stop = 1;
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
			if (philo->stop)
				return (NULL);
			pthread_mutex_lock(&philo->members[i].time_lock);
			if ((get_time(0) - philo->members[i].last_eat)
				> (long)philo->time_to_die)
			{
				work_died(philo, i);
				pthread_mutex_unlock(&philo->members[i].time_lock);
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
	pthread_detach(monitor);
	// pthread_join(monitor, NULL);
	return (1);
}
