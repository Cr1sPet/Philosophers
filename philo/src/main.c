/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:47:05 by jchopped          #+#    #+#             */
/*   Updated: 2022/01/30 17:28:17 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clear (t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&philo->print);
	pthread_mutex_destroy(&philo->main_lock);
	if (philo->locks)
	{
		i = 0;
		while (i < philo->nmb)
		{
			pthread_mutex_destroy(&philo->locks[i]);
			i++;
		}
		// free (philo->locks);
	}
	if (philo->members)
	{
		i = 0;
		while (i < philo->nmb)
		{
			pthread_mutex_destroy(&philo->members[i].mem_lock);
			pthread_mutex_destroy(&philo->members[i].time_lock);
			i++;
		}
		// free (philo->members);
	}
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (!validation(argc, argv))
		return (EXIT_FAILURE);
	if (!init_philo (&philo, argc, argv))
		return (EXIT_FAILURE);
	work_philo(&philo);
	pthread_mutex_lock(&philo.main_lock);
	// pthread_mutex_unlock(&philo.main_lock);
	// clear(&philo);
	return (EXIT_SUCCESS);
}
