#include "philo.h"

int	philo_ends_meals(t_args *args, t_philo *philo)
{
	if (args->target_nb_meals > 0)
	{
        	args->meals[philo->id - 1]++;
        	if (args->meals[philo->id - 1] >= args->target_nb_meals)
                {
        		args->meals[philo->id - 1] = args->target_nb_meals;
        		args->philo_ptr[philo->id - 1].meal_complete = TRUE;
			return (TRUE);
        	}
	}
	return (FALSE);
}

int	all_meals_complete(t_args *args)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (++i < args->number_of_philosophers)
	{
		if (args->philo_ptr[i].meal_complete == TRUE)
			n++;
	}
	if (n == args->number_of_philosophers)
		return (TRUE);
	return (FALSE);
}

int	stop_routine(t_philo *philo)
{
	if (philo->is_dead == TRUE)
		return (TRUE);
	if (philo->meal_complete == TRUE)
		return (TRUE);
	return (FALSE);
}
