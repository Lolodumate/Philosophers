/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:14:12 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 17:19:07 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_args *args, t_philo *philo)
{
	if ((philo_has_enough_time_to_eat(args, philo) == FALSE)
		|| (get_time(philo->args_ptr, MS) >= philo->death_time))
	{
		ft_mutex(args, &philo->mtx, LOCK);
		philo->is_dead = TRUE;
		ft_mutex(args, &philo->mtx, UNLOCK);
/*		ft_mutex(args, &args->mtx, LOCK);
		args->end_of_diner = TRUE;
		printf("fct philo_is_dead : philo->is_dead== TRUE\n");
		ft_mutex(args, &args->mtx, UNLOCK);
*/		return (TRUE);
	}
	return (FALSE);
}

int	philo_ends_meals(t_args *args, t_philo *philo)
{
	if (args->target_nb_meals > 0)
	{
		ft_mutex(args, &args->mtx, LOCK);
		args->meals[philo->id - 1]++;
		ft_mutex(args, &args->mtx, UNLOCK);
		if (args->meals[philo->id - 1] >= args->target_nb_meals)
		{
			ft_mutex(args, &args->mtx, LOCK);
			args->meals[philo->id - 1] = args->target_nb_meals;
			args->philo_ptr[philo->id - 1].meal_complete = TRUE;
			ft_mutex(args, &args->mtx, UNLOCK);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	all_meals_complete(t_args *args)
{
	int             i;
	int             n;

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
	if (philo->args_ptr->end_of_diner == TRUE)
		return (TRUE);
	return (FALSE);
}

int	philo_has_enough_time_to_eat(t_args *args, t_philo *philo)
{
	if (philo->death_time - get_time(args, MS) > args->time_to_die)
		return (FALSE);
	return (TRUE);
}
