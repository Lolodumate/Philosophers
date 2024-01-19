/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:27:46 by laroges           #+#    #+#             */
/*   Updated: 2024/01/19 16:43:23 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	init(t_args args)
{
	t_philo		philo[200];

	args->philo = philo;
	args->number_of_philosopers = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
	args->philo = NULL;
	return (args);
}
