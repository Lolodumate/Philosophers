/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:57:22 by laroges           #+#    #+#             */
/*   Updated: 2024/02/15 20:36:06 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc_protect(t_args *args, size_t size)
{
	void	*p;

	p = malloc(sizeof(size));
	if (!p)
		exit_error(args, "Error malloc");
	else
		printf("Malloc OK\n");
	return (p);
}

t_args	*ft_mem_alloc_args(char **argv, t_args *args)
{
//	args = ft_malloc_protect(args, sizeof(t_args));
	args = malloc(sizeof(t_args));
	if (!args)
		exit_error(args, "Error malloc args");
	args->number_of_philosophers = ft_atoi(argv[1]);
//	args->t = ft_malloc_protect(args, sizeof(pthread_t) * args->number_of_philosophers);
	args->t = malloc(sizeof(args->t) * args->number_of_philosophers);
	if (!args->t)
		exit_error(args, "Error malloc args->t");
//	args->philo_ptr = ft_malloc_protect(args, sizeof(t_philo) * args->number_of_philosophers);
	args->philo_ptr = malloc(sizeof(args->philo_ptr) * args->number_of_philosophers);
	if (!args->philo_ptr)
		exit_error(args, "Error malloc args->philo_ptr");
//	args->forks = ft_malloc_protect(args, sizeof(pthread_mutex_t) * args->number_of_philosophers);
	args->forks = malloc(sizeof(args->forks) * args->number_of_philosophers);
	if (!args->forks)
		exit_error(args, "Error malloc args->forks");
	return (args);
}

t_philo	*ft_mem_alloc_philo(t_args *args, t_philo *philo)
{
	philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philo)
		exit_error(args, "Error malloc philo");
	return (philo);
}
