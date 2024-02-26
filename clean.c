/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:28:04 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 20:46:38 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_args *args)
{
	if (!args)
		return ;
//	while (check_all_philos_finished_routine(args) == FALSE)
//		usleep(100);
	if(args->stop_routine)
	{
		free(args->stop_routine);
		args->stop_routine = NULL;
	}
	if (args->join_threads_monitor)
	{
		free(args->join_threads_monitor);
		args->join_threads_monitor = NULL;
	}
	if (args->meals)
	{
		free(args->meals);
		args->meals = NULL;
	}
	if (args->philo_ptr)
	{
		free(args->philo_ptr);
		args->philo_ptr = NULL;
	}
	if (args->forks)
	{
		free(args->forks);
		args->forks = NULL;
	}
	if (args->t)
	{
		free(args->t);
		args->t = NULL;
	}
	free(args);
	args = NULL;
}

void	mutex_unlock_forks(t_args *args, int n)
{
	int		i;
	int		f;

	i = -1;
	f = 0;
	while (++i < n)
	{
		ft_mutex(args, &args->philo_ptr[i].mtx, LOCK);
		f = args->philo_ptr[i].nb_of_fork_to_drop;
		ft_mutex(args, &args->philo_ptr[i].mtx, UNLOCK);
		if (f > 0)
		{
			if (odd_or_even(i + 1) == ODD)
			{
				ft_mutex(args, args->philo_ptr[(i + 1) % n].main_fork, UNLOCK);
				if (--f > 0)	
					ft_mutex(args, args->philo_ptr[i % n].aux_fork, UNLOCK);
			}
			else
			{
				ft_mutex(args, args->philo_ptr[i % n].main_fork, UNLOCK);
				if (--f > 0)
					ft_mutex(args, args->philo_ptr[(i + 1) % n].aux_fork, UNLOCK);
			}
		}
	//	ft_mutex(args, &args->forks[i], DESTROY);
	}
}

void	destroy_mutex(t_args *args, int n)
{
	int		i;

	i = -1;
	if (!args)
		return ;
	while (++i < n)
		ft_mutex(args, &args->philo_ptr[i].mtx, DESTROY);
	i = -1;
	while (++i < n)
		ft_mutex(args, &args->forks[i], DESTROY);
	ft_mutex(args, &args->monitor, DESTROY);
	ft_mutex(args, &args->mtx, DESTROY);
	ft_mutex(args, &args->mtx_meal, DESTROY);
	ft_mutex(args, &args->mtx_write, DESTROY);
}

void	exit_error(t_args *args, const char *error)
{
//	mutex_unlock_forks(args, args->number_of_philosophers);
//	destroy_mutex(args, args->number_of_philosophers);
	ft_clean(args);
	printf("%s\n", error);
	exit(1);
}
