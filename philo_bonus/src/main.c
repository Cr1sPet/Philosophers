/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:45:21 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/24 14:57:35 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_kill_philosophers(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nmb)
		kill(philo->philos[i++], SIGKILL);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (!validation(argc, argv))
		return (EXIT_FAILURE);
	if (!init_philo (&philo, argc, argv))
		return (EXIT_FAILURE);
	work_philo(&philo);
	clear_philo(&philo);
	ft_kill_philosophers(&philo);
	return (EXIT_SUCCESS);
}
