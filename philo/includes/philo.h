#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philo
{
	int				nmb_eats;
	size_t			nmb;
	size_t			index;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_t		*philos;
	pthread_mutex_t	*locks;

}   			t_philo;

int		work_philo (t_philo *philo);
int		ft_isdigit(int ch);
int		ft_atoi(const char *str);
int		validation (int argc, char **argv);
int		init_philo (t_philo *philo, int argc, char **argv);
size_t	ft_strlen(const char *str);

# endif