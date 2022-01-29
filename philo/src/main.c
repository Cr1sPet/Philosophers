/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:47:05 by jchopped          #+#    #+#             */
/*   Updated: 2022/01/29 19:10:20 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (!validation(argc, argv))
		return (EXIT_FAILURE);
	if (!init_philo (&philo, argc, argv))
		return (EXIT_FAILURE);
	work_philo(&philo);
	
	return (EXIT_SUCCESS);
}
