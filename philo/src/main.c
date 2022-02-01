/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:47:05 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/01 17:21:06 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clear_philo(t_philo *philo)
{
	size_t	i;

	i = 0;

	pthread_mutex_unlock(&philo->print);
	pthread_mutex_destroy(&philo->print);
	if (philo->locks)
	{
		while (i < philo->nmb)
		{
			pthread_mutex_unlock(&philo->locks[i]);
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

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (!validation(argc, argv))
		return (EXIT_FAILURE);
	if (!init_philo (&philo, argc, argv))
		return (EXIT_FAILURE);
	work_philo(&philo);
	if (!clear_philo(&philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
