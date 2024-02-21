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
	ft_destroy_mutex(args);
	if (args->meals)
		free(args->meals);
	if (args->t)
		free(args->t);
	if (args->philo_ptr)
	{
	//	ft_destroy_mutex(args);
		free(args->philo_ptr);
	}
	if (args->forks)
		free(args->forks);
	if (args->forks_to_drop)
		free(args->forks_to_drop);
	free(args);
}

void	ft_destroy_mutex(t_args *args)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		ft_mutex(args, &args->philo_ptr[i].mtx, DESTROY);
		ft_mutex(args, &args->forks[i], DESTROY);
		ft_mutex(args, args->philo_ptr[i].main_fork, DESTROY);
		ft_mutex(args, args->philo_ptr[i].aux_fork, DESTROY);
		ft_mutex(args, &args->philo_ptr[i].mtx, DESTROY);
	}
	ft_mutex(args, &args->mtx_check_ending, DESTROY);
	ft_mutex(args, &args->mtx, DESTROY);
	ft_mutex(args, &args->mtx_write, DESTROY);
}

void	ft_exit(t_args *args)
{
//	printf("%ld %u\n", get_time(MS), philo_id);
	ft_clean(args);
	exit(1);
}

void	exit_error(t_args *args, const char *error)
{
	ft_clean(args);
	printf("%s\n", error);
	exit(1);
}
