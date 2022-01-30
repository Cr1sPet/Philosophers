#include "philo.h"

void	*threadFunc(void* imember)
{
	int		i;
	size_t		p_indx;
	int			left;
	int			right;
	t_member	*member;

	i = 0;
	member = (t_member *)imember;
	if (member->index == member->philo->nmb - 1)
		right = 0;
	else
	 	right = member->index + 1;
	while (1)
	{
		print_info(member->philo, "%12ld %lu is thinking\n", member->index + 1);
		pthread_mutex_lock(&member->mem_lock);
		print_info(member->philo, "%12ld %lu has taken a fork\n", member->index + 1);
		pthread_mutex_lock(&member->philo->members[right].mem_lock);
		print_info(member->philo, "%12ld %lu has taken a fork\n", member->index + 1);
		pthread_mutex_lock(&member->time_lock);
		member->last_eat = get_time(member->philo->start_time);
		pthread_mutex_unlock(&member->time_lock);
		print_info(member->philo, "%12ld %lu is eating\n", member->index + 1);
		// usleep(philo->time_to_eat * 1000);
		ft_sleep(member->philo, member->philo->time_to_eat);
		if (++i == member->philo->nmb_eats)
		{
			member->philo->counter++;
			pthread_mutex_unlock(&member->philo->members[right].mem_lock);
			pthread_mutex_unlock(&member->mem_lock);
			break ;
		}
		pthread_mutex_unlock(&member->philo->members[right].mem_lock);
			pthread_mutex_unlock(&member->mem_lock);
		print_info(member->philo, "%12ld %lu is sleeping\n", p_indx + 1);
		ft_sleep(member->philo, member->philo->time_to_sleep);
		// usleep(philo->time_to_sleep * 1000);
	}
	pthread_exit(0);
}

int	work_philo (t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->nmb)
	{
		pthread_create(&philo->members[i].mem_thread, NULL, threadFunc, (void *)&philo->members[i]);
		// usleep(100);
		i++;
	}
	i = 0;
	while (i < philo->nmb)
	{
		pthread_detach(philo->members[i].mem_thread);
		i++;
	}
	death_monitor(philo);
	return (1);
}