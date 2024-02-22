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
	if (args->meals)
		free(args->meals);
	if (args->t)
		free(args->t);
	if (args->philo_ptr)
		free(args->philo_ptr);
	if (args->forks)
		free(args->forks);
	if (args->mtx_forks)
		free(args->mtx_forks);
	if (args->mtx_philo)
		free(args->mtx_philo);
	if (args->mtx_args)
		free(args->mtx_args);
	free(args);
}

void	destroy_mutex(t_args *args, int n)
{
	int		i;

	i = -1;
	if (!args)
		return ;
	while (++i < n)
	{
		ft_mutex(args, &args->philo_ptr[i].mtx, DESTROY);
	}
	i = -1;
	while (++i < n)
	{
		ft_mutex(args, &args->forks[i], DESTROY);
	}
	ft_mutex(args, &args->mtx, DESTROY);
	ft_mutex(args, &args->mtx_write, DESTROY);
	ft_mutex(args, &args->mtx_check_ending, DESTROY);
}

void	ft_exit(t_args *args)
{
//	printf("%ld %u\n", get_time(MS), philo_id);
	ft_clean(args);
	exit(1);
}

void	exit_error(t_args *args, const char *error)
{
	join_threads(args);
	destroy_mutex(args, args->number_of_philosophers);
	ft_clean(args);
	printf("%s\n", error);
	exit(1);
}
