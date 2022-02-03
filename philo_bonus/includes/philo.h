/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:22:43 by jchopped          #+#    #+#             */
/*   Updated: 2022/01/29 16:22:57 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>



typedef struct s_philo
{
	long			start_time;
	int				counter;
	int				nmb_eats;
	int				nmb;
	int				index;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pid_t			*philos;
	sem_t			*time;
	sem_t			*sem;
	sem_t			*all;
	sem_t			*print;
	pthread_mutex_t	count;
	long			last_eat;
}   			t_philo;

long	get_time();
void	print_info(t_philo *philo, char *out);
void	ft_sleep(t_philo *philo, long limit);
int		death_monitor(t_philo *philo);
int		work_philo (t_philo *philo);
int		ft_isdigit(int ch);
int		ft_atoi(const char *str);
int		validation (int argc, char **argv);
int		init_philo (t_philo *philo, int argc, char **argv);
void	clear_philo(t_philo *philo);
size_t	ft_strlen(const char *str);

#endif