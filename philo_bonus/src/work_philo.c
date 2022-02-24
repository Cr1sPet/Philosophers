/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:57:43 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/24 16:10:14 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat_check(void *iphilo)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)iphilo;
	while (i < philo->nmb)
	{
		sem_wait (philo->count);
		i++;
	}
	sem_wait(philo->print);
	sem_wait(philo->time);
	sem_post (philo->all);
	return (NULL);
}

static int	eat_checker(t_philo *philo)
{
	pthread_t	eat_monitor;

	if (-1 == philo->nmb_eats)
		return (0);
	pthread_create(&eat_monitor, NULL, eat_check, (void *)philo);
	pthread_detach (eat_monitor);
	return (0);
}

void	process_cycle(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		print_info (philo, "%06ld %d is thinking\n");
		sem_wait(philo->sem);
		print_info (philo, "%06ld %d has taken a fork\n");
		sem_wait(philo->sem);
		print_info (philo, "%06ld %d has taken a fork\n");
		sem_wait(philo->time);
		philo->last_eat = get_time(philo->start_time);
		sem_post(philo->time);
		print_info (philo, "%06ld %d is eating\n");
		ft_sleep(philo, philo->time_to_eat);
		if (++i == philo->nmb_eats)
			sem_post (philo->count);
		sem_post(philo->sem);
		sem_post(philo->sem);
		print_info (philo, "%06ld %d is sleeping\n");
		ft_sleep(philo, philo->time_to_sleep);
	}
}

void	child_process(t_philo *philo)
{
	philo->start_time = get_time(0);
	philo->last_eat = get_time(philo->start_time);
	death_monitor(philo);
	process_cycle(philo);
}

int	work_philo(t_philo *philo)
{
	int	i;

	i = 0;
	eat_checker(philo);
	while (i < philo->nmb)
	{
		philo->philos[i] = fork();
		philo->index = i;
		if (-1 == philo->philos[i])
		{
			while (--i)
			{
				kill(philo->philos[i], SIGKILL);
				return (0);
			}
		}
		if (0 == philo->philos[i])
			child_process(philo);
		i++;
	}
	sem_wait(philo->all);
	return (1);
}
