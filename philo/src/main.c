/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:47:05 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/01 21:39:27 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (!validation(argc, argv))
	{
		clear_philo(&philo);
		return (EXIT_FAILURE);
	}
	if (!init_philo (&philo, argc, argv))
	{
		clear_philo(&philo);
		return (EXIT_FAILURE);
	}
	work_philo(&philo);
	size_t i = philo.nmb;
	while (i)
	{
		i--;
		pthread_join(philo.members[i].mem_thread, NULL);
		printf("%zu THREAD JOINED\n", i);
	}
	clear_philo(&philo);
	return (EXIT_SUCCESS);
}
