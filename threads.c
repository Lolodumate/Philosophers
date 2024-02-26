#include "philo.h"

void	*threads_create(void *args)
{
	t_args	*a;
	int		i;

	a = (t_args *)args;
	i = -1;
	while (++i < a->number_of_philosophers)
	{
		if (pthread_create(&a->t[i], NULL, &diner_routine, (void **) &a->philo_ptr[i]) != 0)
			exit_error(a, "Error pthread_creation");
	}
	return (NULL);
}

void	threads_join(void *args)
{
	int		i;
	int		n;
	t_args	*a;

	i = -1;
	n = 0;
	a = (t_args *)args;
	while (n < a->number_of_philosophers)
	{
		while (++i < a->number_of_philosophers)
		{
			if (a->join_threads_monitor[i] == 0)
			{
				ft_mutex(a, &a->philo_ptr[i].mtx[ROUTINE], LOCK);
				if (a->philo_ptr[i].stop_routine == TRUE)
				{
					n++;
					a->join_threads_monitor[i] = TRUE;
					ft_mutex(a, &a->philo_ptr[i].mtx[ROUTINE], UNLOCK);
					if (pthread_join(a->t[i], (void **) &a) != 0)
						exit_error(args, "Error pthread_join");
				}
				else
					ft_mutex(a, &a->philo_ptr[i].mtx[ROUTINE], UNLOCK);
			}
//			printf("a->philo_ptr[%d].stop_routine = %d\n", i, a->philo_ptr[i].stop_routine);
//			printf("a->join_monitor[%d] = %d\n", i, a->join_threads_monitor[i]);
		}
		i =- 1;
	}
}
