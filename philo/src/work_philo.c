#include "philo.h"

void	*threadFunc(void *mem)
{
	int			i;
	t_member	*member;

	i = 0;
	member = (t_member *)mem;
	while (1)
	{
		print_info(member->inf, "%06ld %lu is thinking\n", member->index + 1);
		// pthread_mutex_lock(&member->left);
		// print_info(member->inf, "%06ld %lu has taken a fork\n", member->index + 1);
		// pthread_mutex_lock(&member->right);
		// print_info(member->inf, "%06ld %lu has taken a fork\n", member->index + 1);
		// member->last_eat = get_time(member->inf->start_time);
		// print_info(member->inf, "%06ld %lu is eating\n", member->index + 1);
		// usleep(member->inf->time_to_eat * 1000);
		// if (++i == member->inf->nmb_eats)
		// {
		// 	member->inf->counter++;
		// 	pthread_mutex_unlock(&member->right);
		// 	pthread_mutex_unlock(&member->left);
		// 	break ;
		// }
		// pthread_mutex_unlock(&member->right);
		// pthread_mutex_unlock(&member->left);
		// print_info(member->inf, "%06ld %lu is sleeping\n", member->index + 1);
		// usleep(member->inf->time_to_sleep * 1000);
	}
	pthread_exit(0);
}

int	work_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->nmb)
	{
		pthread_create(&philo->members[i].member, NULL, threadFunc, (void *)&philo->members[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < philo->nmb)
	{
		pthread_detach(philo->members[i].member);
		i++;
	}
	death_monitor(philo);
	return (1);
}
