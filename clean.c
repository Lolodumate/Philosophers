/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:28:04 by laroges           #+#    #+#             */
/*   Updated: 2024/03/04 12:48:33 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_args *args)
{
	if (!args)
		return ;
	free_mutex(args, args->mtx);
	if (args->meals)
		free(args->meals);
	if (args->philo_ptr)
	{
		free_philo_ptr(args);
		free(args->philo_ptr);
	}
	if (args->forks)
		free(args->forks);
	if (args->t)
		free(args->t);
	free(args);
}

void	free_philo_ptr(t_args *args)
{
	int		i;

	i = -1;
	while (++i < args->nphilo)
	{
		if (&args->philo_ptr[i].mtx)
			free(args->philo_ptr[i].mtx);
	}
}

void	free_mutex(t_args *args, pthread_mutex_t *mtx)
{
	if (!args)
		return ;
	if (!mtx)
		return ;
	free(mtx);
}

void	exit_error(t_args *args, const char *error)
{
	destroy_mutex(args, args->nphilo);
	free_mutex(args, args->philo_ptr->mtx);
	ft_clean(args);
	printf("%s\n", error);
	exit(1);
}
