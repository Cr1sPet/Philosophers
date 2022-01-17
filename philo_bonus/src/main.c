#include "philo.h"

int main(int argc, char **argv)
{
	t_philo	philo;

	if (!validation(argc, argv))
		return (EXIT_FAILURE);
	if (!init_philo (&philo, argc, argv))
		return (EXIT_FAILURE);
	work_philo(&philo);
	clear_philo(&philo);
	return (EXIT_SUCCESS);
}