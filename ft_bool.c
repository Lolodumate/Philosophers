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

int	philo_is_dead(t_args *args, t_philo *philo)
{
	ft_mutex(args, &args->mtx, LOCK);
	if (get_time(args, MS) >= (philo->last_meal_time + args->time_to_die))
	{
		ft_write_task(args, philo, DEAD);
		philo->is_dead = TRUE;
		args->end_of_diner = TRUE;
		ft_mutex(args, &args->mtx, UNLOCK);
		return (TRUE);
	}	
	ft_mutex(args, &args->mtx, UNLOCK);
	return (FALSE);
}

int	philo_ends_meals(t_args *args, t_philo *philo)
{
	ft_mutex(args, &args->mtx_meal, LOCK);
	if (args->target_nb_meals > 0)
	{
		args->meals[philo->id - 1]++;
		if (args->meals[philo->id - 1] >= args->target_nb_meals)
		{
			args->philo_ptr[philo->id - 1].meal_complete = TRUE;
			ft_mutex(args, &args->mtx_meal, UNLOCK);
			return (TRUE);
		}
	}
	ft_mutex(args, &args->mtx_meal, UNLOCK);
	return (FALSE);
}

int	all_meals_complete(t_args *args)
{
	int             i;
	int             n;

        i = -1;
	n = 0;
	ft_mutex(args, &args->mtx_meal, LOCK);
	if (args->target_nb_meals < 0)
	{
		ft_mutex(args, &args->mtx_meal, UNLOCK);
			return (FALSE);
	}
	while (++i < args->number_of_philosophers)
	{
		if (args->meals[i] >= args->target_nb_meals)
			n++;
	}
	if (n == args->number_of_philosophers)
	{
		ft_mutex(args, &args->mtx_meal, UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &args->mtx_meal, UNLOCK);
	return (FALSE);
}

int	all_philo_are_alive(t_args *args)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (args->philo_ptr[i].is_dead == TRUE)
		{
			printf("ft_bool.c : fct all_philo_are_alive args->philo_ptr[%d].is_dead = %d\n", i, args->philo_ptr[i].is_dead);
			return (FALSE);
		}
	}
	return (TRUE);
}

int	stop_routine(t_args *args)
{
	ft_mutex(args, &args->mtx, LOCK);
	if (args->end_of_diner == TRUE)
	{
		printf("ft_bool.c : end_of_diner == TRUE\n");
		ft_mutex(args, &args->mtx, UNLOCK);
		return (TRUE);
	}
	if (all_philo_are_alive(args) == FALSE)
	{
		printf("ft_bool.c : all_philo_are_alive == FALSE\n");
		ft_mutex(args, &args->mtx, UNLOCK);
		return (TRUE);
	}
	if (all_meals_complete(args) == TRUE)
	{
		printf("ft_bool.c : all_meals_complete == TRUE\n");
		ft_mutex(args, &args->mtx, UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &args->mtx, UNLOCK);
	return (FALSE);
}
