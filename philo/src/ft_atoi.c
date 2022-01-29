/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:46:07 by jchopped          #+#    #+#             */
/*   Updated: 2022/01/29 18:46:08 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int						i;
	int						check_neg;
	long long unsigned int	res;

	i = 0;
	res = 0;
	check_neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			check_neg = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - 48);
		i++;
		if (res > 2147483648 && check_neg == -1)
			return (0);
		if (res >= 2147483647 && check_neg == 1)
			return (-1);
	}
	return (res * check_neg);
}
