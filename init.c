/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:27:46 by laroges           #+#    #+#             */
/*   Updated: 2024/01/25 17:37:17 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*init_args(int argc, char **argv, t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->philo_ptr = malloc(sizeof(t_philo *));
	if (!args->philo_ptr)
		return (NULL);
	args->number_of_dead = 0;
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (args);
}

t_philo	*init_philo(t_args *args)
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philo)
		return (NULL);
	return (philo);
}
/*
void	create_forks_ptr(t_args args)
{
	int		i;

	i = 0;
	while (i++ < args.philo_ptr->number_of_philosophers)
	{
		if (i == 0)
		{
			args.forks_ptr[i].rf = &args.philo_ptr[i].right_fork;
			args.forks_ptr[i].lf = args.philo_ptr[i].left_fork;
		}
		else
		{
			args.forks_ptr[i].rf = args.philo_ptr[i - 1].left_fork;
			args.forks_ptr[i].lf = args.philo_ptr[i].left_fork;
		}
	}
}*/
