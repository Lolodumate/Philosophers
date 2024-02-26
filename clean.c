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

void	free_mutex(t_args *args, pthread_mutex_t *mtx)
{
	if (!args)
		return ;
	if (!mtx)
		return ;
	free(mtx);
}

void	destroy_mutex(t_args *args, int n)
{
	int		i;

	i = -1;
	if (!args)
		return ;
	i = -1;
	while (++i < n)
		ft_mutex(args, &args->forks[i], DESTROY);
	while (++i < n)
	{
		ft_mutex(args, &args->philo_ptr[i].mtx[MTX], DESTROY);
		ft_mutex(args, &args->philo_ptr[i].mtx[ROUTINE], DESTROY);
	}
	ft_mutex(args, &args->mtx[MTX], DESTROY);
	ft_mutex(args, &args->mtx[MASTER], DESTROY);
	ft_mutex(args, &args->mtx[MONITOR], DESTROY);
	ft_mutex(args, &args->mtx[MEAL], DESTROY);
	ft_mutex(args, &args->mtx[WRITE], DESTROY);
}

void	exit_error(t_args *args, const char *error)
{
	destroy_mutex(args, args->number_of_philosophers);
	free_mutex(args, args->philo_ptr->mtx);
	free_mutex(args, args->mtx);
	ft_clean(args);
	printf("%s\n", error);
	exit(1);
}
