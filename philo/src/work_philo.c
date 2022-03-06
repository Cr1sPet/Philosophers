/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:54:16 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/24 16:12:50 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_join(t_philo *philo)
{
	size_t	i;

	// i = 0;
	// while (i < philo->nmb)
	// 	pthread_mutex_unlock(&philo->locks[i++]);
	// i = 0;
	while (i < philo->nmb)
		pthread_join(philo->members[i++].mem_thread, NULL);
}

void	taking_forks(t_member *member)
{
	pthread_mutex_lock(member->first);
	print_info(member->philo, "%12ld %lu has taken a fork\n", member->index);
	pthread_mutex_lock(member->second);
	print_info(member->philo, "%12ld %lu has taken a fork\n", member->index);
}

void	eating(t_member	*member, int *i)
{
	print_info(member->philo, "%12ld %lu is eating\n", member->index);
	pthread_mutex_lock(&member->time_lock);
	member->last_eat = get_time(0);
	pthread_mutex_unlock(&member->time_lock);
	ft_sleep(member->philo, member->philo->time_to_eat);
	pthread_mutex_unlock(member->first);
	pthread_mutex_unlock(member->second);
	if (++(*i) == member->philo->nmb_eats)
	{
		member->philo->counter++;
		// printf("%zu - HOHOHOHOHOHOHOHOHOHOHOHOHOHOHOHOHO\n", member->philo->counter);
	}
}

void	*thread_func(void	*imember)
{
	int				i;
	t_member		*member;

	i = 0;
	member = (t_member *)imember;
	while (!member->philo->stop && !check_eat_nmb(member->philo))
	{
		if (member->philo->stop || check_eat_nmb(member->philo))
			break ;
		taking_forks(member);
		if (member->philo->stop || check_eat_nmb(member->philo))
			break ;
		eating(member, &i);
		if (member->philo->stop || check_eat_nmb(member->philo))
			break ;
		print_info(member->philo, "%12ld %lu is sleeping\n", member->index);
		ft_sleep(member->philo, member->philo->time_to_sleep);
		if (member->philo->stop || check_eat_nmb(member->philo))
			break ;
		print_info(member->philo, "%12ld %lu is thinking\n", member->index);
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
		i++;
	}
	threads_join(philo);
	death_monitor(philo);
	return (1);
}
