#include "philo.h"

int	threads_create(t_args *args)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (pthread_create(&args->t[i], NULL, &diner_routine, &args->philo_ptr[i]) != 0)
			exit_error(args, "Failure thread creation");
	}
	return (1);
}

int	threads_join(t_args *args)
{
	int             i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (pthread_join(args->t[i], (void **) &args->philo_ptr[i]) != 0)
			exit_error(args, "Error pthread join");
	}
	return (1);
}
