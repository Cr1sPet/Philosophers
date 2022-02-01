/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:53:10 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/01 22:32:52 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(long align)
{
	long			ret;
	struct timeval	c_time;

	if (-1 == gettimeofday(&c_time, NULL))
		return (0);
	ret = (c_time.tv_sec % 1000000) * 1000;
	ret += c_time.tv_usec / 1000;
	return (ret - align);
}

void	ft_sleep(t_philo *philo, long limit)
{
	long	i;
	long	this_start;

	i = 0;
	this_start = get_time(philo->start_time);
	while (get_time (philo->start_time) - this_start < limit)
		usleep(3 * limit);
}

void	print_info(t_philo *philo, char *out, int index, int flag)
{
	pthread_mutex_lock(&philo->print);
	// if (0 == philo->stop || flag)
	// {
		printf(out, get_time(philo->members[index].start_time), index + 1);
	// }
	pthread_mutex_unlock(&philo->print);
}

int	clear_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	pthread_mutex_unlock(&philo->set);
	pthread_mutex_destroy(&philo->set);
	pthread_mutex_unlock(&philo->print);
	pthread_mutex_destroy(&philo->print);
	if (philo->locks)
	{
		while (i < philo->nmb)
		{
			pthread_mutex_destroy(&philo->locks[i]);
			pthread_mutex_unlock(&philo->members[i].time_lock);
			pthread_mutex_destroy(&philo->members[i].time_lock);
			i++;
		}
		free(philo->locks);
	}
	if (philo->members)
		free (philo->members);
	return (1);
}
