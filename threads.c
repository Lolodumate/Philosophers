#include "philo.h"

int	threads_create(t_args *a)
{
	int		i;

	i = -1;
	printf("Check TTTTTTTTTTT\n");
	while (++i < a->number_of_philosophers)
	{
		if (pthread_create(&a->t[i], NULL, &diner_routine, &a->philo_ptr[i]) != 0)
			exit_error(a, "Error pthread_creation");
	}
	return (0);
}

int	threads_join(void *args)
{
	int		i;
	int		n;
	t_args	*a;

	i = -1;
	n = 0;
	a = (t_args *)args;
	ft_mutex(a, &a->philo_ptr[i].mtx[ROUTINE], LOCK);
	while (n < a->number_of_philosophers)
	{
		i = -1;
		while (++i < a->number_of_philosophers)
		{
			if (a->join_threads_monitor[i] == 0)
			{
				if (a->philo_ptr[i].stop_routine == TRUE)
				{
					n++;
					a->join_threads_monitor[i] = TRUE;
					if (pthread_join(a->t[i], (void *) &a->philo_ptr[i]) != 0)
						exit_error(args, "Error pthread_join");
					else
						printf("thread_join[%d] OK\n", i);
				}
			}
			printf("a->philo_ptr[%d].stop_routine = %d\n", i, a->philo_ptr[i].stop_routine);
			printf("a->join_monitor[%d] = %d\n", i, a->join_threads_monitor[i]);
		}
	}
	ft_mutex(a, &a->philo_ptr[i].mtx[ROUTINE], UNLOCK);
	return (n);
}
