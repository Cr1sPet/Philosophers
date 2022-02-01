/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:54:16 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/01 17:28:25 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_member *member)
{
	pthread_mutex_lock(member->first);
	print_info(member->philo, "%12ld %lu has taken a fork\n",
		member->index + 1);
	pthread_mutex_lock(member->second);
	print_info(member->philo, "%12ld %lu has taken a fork\n",
		member->index + 1);
}

void	eating(t_member	*member, int *i)
{
	print_info(member->philo, "%12ld %lu is eating\n", member->index + 1);
	pthread_mutex_lock(&member->time_lock);
	member->last_eat = get_time(0);
	pthread_mutex_unlock(&member->time_lock);
	ft_sleep(member->philo, member->philo->time_to_eat);
	pthread_mutex_unlock(member->first);
	pthread_mutex_unlock(member->second);
	if (++(*i) == member->philo->nmb_eats)
			member->philo->counter++;
}

void	sleeping(t_member *member)
{
	print_info(member->philo, "%12ld %lu is sleeping\n", member->index + 1);
	ft_sleep(member->philo, member->philo->time_to_sleep);
	print_info(member->philo, "%12ld %lu is thinking\n",
		member->index + 1);
}

void	*thread_func(void	*imember)
{
	int				i;
	t_member		*member;

	i = 0;
	member = (t_member *)imember;
	while (!member->stop)
	{
		taking_forks(member);
		eating(member, &i);
		sleeping(member);
	}
	return (NULL);
}

int	work_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->start_time = get_time(0);
	while (i < philo->nmb)
	{
		pthread_create(&philo->members[i].mem_thread, NULL, thread_func, \
			(void *)&philo->members[i]);
		pthread_detach(philo->members[i].mem_thread);
		i++;
	}
	i = 0;
	death_monitor(philo);
	return (1);
}
