#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


typedef struct s_member
{
	size_t			index;
	long			last_eat;
	pthread_t		mem_thread;
	pthread_mutex_t	mem_lock;
	pthread_mutex_t	time_lock;
	struct s_philo	*philo;
}				t_member;
typedef struct s_philo
{
	t_member		*members;
	long			start_time;
	size_t			counter;
	int				nmb_eats;
	size_t			nmb;
	// size_t			index;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	// pthread_t		*philos;
	pthread_mutex_t	*locks;
	pthread_mutex_t print;
	// pthread_mutex_t *times;
	// long			*cur_time;
}   			t_philo;

long	get_time();
void	ft_sleep(t_philo *philo, long limit);
int		death_monitor(t_philo *philo);
int		work_philo (t_philo *philo);
int		ft_isdigit(int ch);
int		ft_atoi(const char *str);
int		validation (int argc, char **argv);
int		init_philo (t_philo *philo, int argc, char **argv);
size_t	ft_strlen(const char *str);
void	print_info (t_philo *philo, char *out, int index);

# endif