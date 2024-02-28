#include "philo.h"

int	threads_create(t_args *a)
{
	int		i;

	i = -1;
	while (++i < a->number_of_philosophers)
	{
		if (pthread_create(&a->t[i], NULL, &dinner_routine, &a->philo_ptr[i]) != 0)
			exit_error(a, "Error pthread_creation");
		ft_mutex(a, &a->mtx[MTX], LOCK);
		a->monitor_ptr->threads_created++;
		ft_mutex(a, &a->mtx[MTX], UNLOCK);
	}
	return (0);
}

int	wait_threads_creation_to_finish(t_args *args)
{
	ft_mutex(args, &args->mtx[MTX], LOCK);
	if (args->monitor_ptr->threads_created == args->number_of_philosophers)
	{
		ft_mutex(args, &args->mtx[MTX], UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &args->mtx[MTX], UNLOCK);
	return (FALSE);
}

void	set_start_time_of_dinner(t_args *args, t_philo *philo)
{
	ft_mutex(args, &args->mtx[MTX], LOCK);
	if (args->time_start_dinner == 0)
	       	args->time_start_dinner = get_time(args, MS);
	ft_mutex(args, &args->mtx[MTX], UNLOCK);
	ft_mutex(args, &philo->mtx[MTX], LOCK);
	philo->death_time = args->time_start_dinner + args->time_to_die;
	ft_mutex(args, &philo->mtx[MTX], UNLOCK);
}

int	threads_join(void *args)
{
	int		i;
	t_args	*a;

	i = 0;
	a = (t_args *)args;
	while (a->t[i] && i < a->number_of_philosophers)
	{
//		if (a->join_threads_monitor[i] == 0)
		{
//			if (a->philo_ptr[i].stop_routine == TRUE)
			{
				a->join_threads_monitor[i] = TRUE;
				if (pthread_join(a->t[i], NULL /* (void **) &a->philo_ptr[i]*/) != 0)
					exit_error(a, "Error pthread_join");
			}
		}
		i++;
	}
	return (0);
}
