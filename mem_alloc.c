/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:57:22 by laroges           #+#    #+#             */
/*   Updated: 2024/02/19 09:00:39 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*ft_mem_alloc_args(t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args)
	{
		printf("Error malloc args");
		exit(EXIT_FAILURE);
	}
	return (args);
}

pthread_t	*ft_mem_alloc_threads(t_args *args, pthread_t *t, int philo_nb)
{
	t = malloc(sizeof(t) * philo_nb);
	if (!t)
		exit_error(args, "Error malloc args->t");
	return (t);
}

t_philo	*ft_mem_alloc_philo_ptr(t_args *args, t_philo *philo, int philo_nb)
{
	philo = malloc(sizeof(t_philo) * philo_nb);
	if (!philo)
		exit_error(args, "Error malloc args->philo_ptr");
	return (philo);
}

pthread_mutex_t	*ft_mem_alloc_forks(t_args *args, pthread_mutex_t *forks)
{
	forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	if (!forks)
		exit_error(args, "Error malloc args->forks");
	return (forks);
}
