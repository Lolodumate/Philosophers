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
	threads_join(a);
	return (NULL);
}

void	threads_join(t_args *a)
{
	int             i;

	i = -1;
	while (++i < a->number_of_philosophers)
	{
		if (pthread_join(a->t[i], NULL) != 0)
			exit_error(a, "Error pthread join");
	}
}
