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

int	philo_is_alive(t_args *args, t_philo *philo)
{
	if (philo->death_time < get_time(args, MS))
		return (FALSE);
	return (TRUE);
}

int	philo_is_dead(t_args *args, t_philo *philo)
{
	if(philo_is_alive(args, philo) == FALSE)
	{
		philo->is_dead = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

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

int	all_philo_are_alive(t_args *args)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (args->philo_ptr->is_dead == TRUE)
			return (FALSE);
	}
	return (TRUE);
}

int	stop_routine(t_args *args)
{
	if (all_philo_are_alive(args) == FALSE)
		return (TRUE);
	if (all_meals_complete(args) == TRUE)
		return (TRUE);
	return (FALSE);
}
