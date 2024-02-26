#include "philo.h"

void	*threads_create(void *args)
{
	t_args	*a;
	int		i;

	a = (t_args *)args;
	i = -1;
	while (++i < a->number_of_philosophers)
	{
		if (pthread_create(&a->t[i], NULL, &diner_routine, &a->philo_ptr[i]) != 0)
			exit_error(a, "Failure thread creation");
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
	printf("diner_routine : p->args_ptr->stop_routine[%d] = TRUE\n", a->philo_ptr->id - 1);
	while (n < a->number_of_philosophers)
	{
		while (++i < a->number_of_philosophers)
		{
			if (a->stop_routine[i] == TRUE && a->join_threads_monitor[i] == FALSE)
			{
				if (pthread_join(a->t[i], NULL) != 0)
					exit_error(args, "Error pthread_join");
				a->join_threads_monitor[i] = TRUE;
				n++;
			}
		}
		i =- 1;
	}
}
