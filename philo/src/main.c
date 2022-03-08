/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:47:05 by jchopped          #+#    #+#             */
/*   Updated: 2022/03/08 17:33:03 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	for_one_philo(t_philo *philo)
{
	philo->start_time = get_time(0);
	print_info(philo, "%12ld %d is thinking\n", 0);
	ft_sleep(philo, philo->time_to_die);
	print_info(philo, "%12ld %d is died\n", 0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (!validation(argc, argv))
	{
		return (EXIT_FAILURE);
	}
	if (!init_philo (&philo, argc, argv))
	{
		clear_philo(&philo);
		return (EXIT_FAILURE);
	}
	if (philo.nmb == 1)
		for_one_philo(&philo);
	else
		work_philo(&philo);
	clear_philo(&philo);
	return (EXIT_SUCCESS);
}
