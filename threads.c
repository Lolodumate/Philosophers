#include "philo.h"

int	threads_create(t_args *a)
{
	int		i;

	i = -1;
	while (++i < a->number_of_philosophers)
	{
		if (pthread_create(&a->t[i], NULL, &dinner_routine, &a->philo_ptr[i]) != 0)
			exit_error(a, "Error pthread_creation");
	}
	return (0);
}

int	threads_join(void *args)
{
	int		i;
	t_args	*a;

	i = -1;
	a = (t_args *)args;
	while (++i < a->number_of_philosophers)
	{
		if (a->join_threads_monitor[i] == 0)
		{
			ft_mutex(a, &a->philo_ptr[i].mtx[ROUTINE], LOCK);
			if (a->philo_ptr[i].stop_routine == TRUE)
			{
				a->join_threads_monitor[i] = TRUE;
				ft_mutex(a, &a->philo_ptr[i].mtx[ROUTINE], UNLOCK);
				if (pthread_join(a->t[i], NULL /* (void **) &a->philo_ptr[i]*/) != 0)
					exit_error(args, "Error pthread_join");
			}
		}
	}
	return (0);
}
