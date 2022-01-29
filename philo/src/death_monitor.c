/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:48:52 by jchopped          #+#    #+#             */
/*   Updated: 2022/01/29 19:13:11 by jchopped         ###   ########.fr       */
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
	int			ok;
	t_philo		*philo;

	philo = (t_philo *)iphilo;
	i = 0;
	ok = 1;
	while (1 && ok)
	{
		i = 0;
		while (i < philo->nmb && ok)
		{
			if (philo->nmb == philo->counter)
				ok = 0;
			pthread_mutex_lock(&philo->times[i]);
			if ((long)(get_time(philo->start_time) - philo->time_to_die) > philo->cur_time[i])
			{
				pthread_mutex_lock(&philo->print);
				printf("%12ld %lu died\n", get_time(philo->start_time), i + 1);
				ok = 0;
			}
			pthread_mutex_unlock(&philo->times[i]);
			i++;
			usleep(500);
		}
	}
	return (NULL);
}

int	death_monitor(t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, death_mon, (void *)philo);
	pthread_join(monitor, NULL);
	// pthread_detach(monitor);
	return (1);
}
