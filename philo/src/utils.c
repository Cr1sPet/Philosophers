/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:53:10 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/01 13:53:10 by jchopped         ###   ########.fr       */
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

void	print_info(t_philo *philo, char *out, int index)
{
	pthread_mutex_lock(&philo->print);
	printf(out, get_time(philo->start_time), index);
	pthread_mutex_unlock(&philo->print);
}
