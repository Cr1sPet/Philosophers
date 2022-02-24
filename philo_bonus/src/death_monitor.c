/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:00:31 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/24 15:01:35 by jchopped         ###   ########.fr       */
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
	t_philo		*philo;

	philo = (t_philo *)iphilo;
	while (1)
	{
		sem_wait (philo->time);
		if ((long)(get_time(philo->start_time) - philo->time_to_die)
			> philo->last_eat)
		{
			sem_wait(philo->print);
			printf("%06ld last eat: %ld %d died\n",
				get_time(philo->start_time), philo->last_eat, philo->index + 1);
			sem_post(philo->all);
			return (NULL);
		}
		sem_post (philo->time);
	}	
	return (NULL);
}

int	death_monitor(t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, death_mon, (void *)philo);
	pthread_detach(monitor);
	return (1);
}
