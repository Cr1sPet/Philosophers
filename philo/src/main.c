#include "philo.h"

void	*threadFunc(void* lock){
	pthread_exit(0);
}
 

int main(int argc, char **argv)
{
	t_philo	philo;

	if (!validation(argc, argv))
		return (EXIT_FAILURE);
	if (!init_philo (&philo, argc, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}