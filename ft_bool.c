/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:14:12 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 18:23:08 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_args *args, t_philo *philo, int i)
{
	ft_mutex(args, &args->mtx[0], LOCK);
	if (get_time(args, MS) >= (philo[i].last_meal_time + args->time_to_die))
	{
		ft_write_task(args, philo, DEAD);
//		ft_mutex(args, &args->mtx_write, LOCK);
//		args->is_dead = TRUE;
		ft_mutex(args, &args->mtx[MONITOR], LOCK);
		args->end_of_diner = TRUE;
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
//		ft_mutex(args, &args->mtx_write, UNLOCK);
		ft_mutex(args, &args->mtx[0], UNLOCK);
		return (TRUE);
	}	
	ft_mutex(args, &args->mtx[0], UNLOCK);
	return (FALSE);
}

int	all_meals_complete(t_args *args)
{
	int             i;
	int             n;

        i = -1;
	n = 0;
	ft_mutex(args, &args->mtx[MEAL], LOCK);
	if (args->target_nb_meals < 0)
	{
		ft_mutex(args, &args->mtx[MEAL], UNLOCK);
			return (FALSE);
	}
	while (++i < args->number_of_philosophers)
	{
		if (args->meals[i] >= args->target_nb_meals)
			n++;
	}
	if (n == args->number_of_philosophers)
	{
		ft_mutex(args, &args->mtx[MEAL], UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &args->mtx[MEAL], UNLOCK);
	return (FALSE);
}

int	check_all_philos_finished_routine(t_args *args, t_philo *philo)
{
	int		i;
	int		n;

	i = -1;
	n = 0;

	while (++i < args->number_of_philosophers)
	{
		ft_mutex(args, &philo[i].mtx[MTX], LOCK);
		if (args->philo_ptr[i].stop_routine == TRUE)
			n++;
//		printf("args->philo_ptr[%d].stop_routine = %d\n", i, args->philo_ptr[i].stop_routine);
		ft_mutex(args, &philo[i].mtx[MTX], UNLOCK);
	}
	if (n == args->number_of_philosophers)
		return (TRUE);
	return (FALSE);
}

int	stop_routine(t_args *args)
{
	ft_mutex(args, &args->mtx[MONITOR], LOCK);
	if (args->end_of_diner == TRUE)
	{
//		printf("ft_bool.c : end_of_diner == TRUE\n");
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
		return (TRUE);
	}
	if (args->is_dead == TRUE)
	{
//		printf("ft_bool.c : all_philo_are_alive == FALSE\n");
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
		return (TRUE);
	}
	if (all_meals_complete(args) == TRUE)
	{
//		printf("ft_bool.c : all_meals_complete == TRUE\n");
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
	return (FALSE);
}
