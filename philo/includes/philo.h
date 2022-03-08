/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:10:12 by jchopped          #+#    #+#             */
/*   Updated: 2022/03/08 17:21:17 by jchopped         ###   ########.fr       */
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

typedef struct s_member
{
	int				eated;
	int				stop;
	long			last_eat;
	long			start_time;
	size_t			index;
	pthread_t		mem_thread;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	time_lock;
	struct s_philo	*philo;
}				t_member;

typedef struct s_philo
{
	int				stop;
	int				nmb_eats;
	long			start_time;
	size_t			nmb;
	t_member		*members;
	size_t			counter;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*locks;
	pthread_mutex_t	check;
	pthread_mutex_t	print;
	pthread_mutex_t	set;
	pthread_mutex_t	all;
}					t_philo;

void	threads_join(t_philo *philo);
int		clear_philo(t_philo *philo);
int		check_stop(t_philo *philo);
long	get_time(long align);
void	ft_sleep(t_philo *philo, long limit);
int		death_monitor(t_philo *philo);
int		work_philo(t_philo *philo);
int		ft_isdigit(int ch);
int		ft_atoi(const char *str);
int		validation(int argc, char **argv);
int		init_philo(t_philo *philo, int argc, char **argv);
void	print_info(t_philo *philo, char *out, int index);
size_t	ft_strlen(const char *str);

#endif