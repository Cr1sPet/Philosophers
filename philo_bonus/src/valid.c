/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:45:52 by jchopped          #+#    #+#             */
/*   Updated: 2022/02/24 14:45:58 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_atoi(char *str)
{
	int			i;
	long long	res;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	res = ft_atoi(str);
	if ((2 < ft_strlen(str)) && (-1 == res || 0 == res))
		return (0);
	return (1);
}

int	validation(int argc, char **argv)
{
	int	i;

	i = 1;
	if (5 != argc && 6 != argc)
		return (0);
	while (i < argc)
		if (!check_atoi(argv[i++]))
			return (0);
	return (1);
}
