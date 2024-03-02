/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:14:12 by laroges           #+#    #+#             */
/*   Updated: 2024/03/02 17:13:27 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_args *args, t_philo *philo, int i)
{
	ft_mutex(args, &args->mtx[MTX], LOCK);
	if (get_time(args, MS) >= (philo[i].last_meal + args->time_to_die))
	{
		ft_write_task(args, philo, DEAD);
		ft_mutex(args, &args->mtx[MONITOR], LOCK);
		args->end_of_diner = TRUE;
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
		ft_mutex(args, &args->mtx[MTX], UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &args->mtx[MTX], UNLOCK);
	return (FALSE);
}

int	should_even_philos_die(t_args *args, t_philo *p)
{
	long		n;
	long		wait_til_die;

	n = 0;
	wait_til_die = 0;
	if (odd_or_even(args->nphilo) == ODD)
		return (FALSE);
	if (args->time_to_sleep > args->time_to_eat)
		n = args->time_to_eat + args->time_to_sleep;
	else
		n = args->time_to_eat * 2;
	if (n > args->time_to_die)
	{
		wait_til_die = (p->last_meal + args->time_to_die) - get_time(args, MS);
		usleep(wait_til_die * 1000);
		ft_write_task(args, p, DEAD);
		ft_mutex(args, &args->mtx[MONITOR], LOCK);
		args->end_of_diner = TRUE;
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
		return (TRUE);
	}
	return (FALSE);
}

int	all_meals_complete(t_args *args)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	ft_mutex(args, &args->mtx[MEAL], LOCK);
	if (args->target_nb_meals < 0)
	{
		ft_mutex(args, &args->mtx[MEAL], UNLOCK);
		return (FALSE);
	}
	while (++i < args->nphilo)
	{
		if (args->meals[i] >= args->target_nb_meals)
			n++;
	}
	if (n >= args->nphilo)
	{
		ft_mutex(args, &args->mtx[MEAL], UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &args->mtx[MEAL], UNLOCK);
	return (FALSE);
}

int	check_all_philos_finished_routine(t_args *args)
{
	int		i;
	int		n;
	t_philo	*philo;

	i = -1;
	n = 0;
	philo = args->philo_ptr;
	while (++i < args->nphilo)
	{
		ft_mutex(args, &philo[i].mtx[MTX], LOCK);
		if (args->philo_ptr[i].stop_routine == TRUE)
			n++;
		ft_mutex(args, &philo[i].mtx[MTX], UNLOCK);
	}
	if (n >= args->nphilo)
		return (TRUE);
	return (FALSE);
}

int	stop_routine(t_args *args)
{
	ft_mutex(args, &args->mtx[MONITOR], LOCK);
	if (args->end_of_diner == TRUE)
	{
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
		return (TRUE);
	}
	if (args->is_dead == TRUE)
	{
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
		return (TRUE);
	}
	if (all_meals_complete(args) == TRUE)
	{
		ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &args->mtx[MONITOR], UNLOCK);
	return (FALSE);
}
