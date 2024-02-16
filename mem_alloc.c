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

pthread_t	*ft_mem_alloc_threads(t_args *args, pthread_t *t, int philo_nb)
{
	t = malloc(sizeof(t) * philo_nb);
	if (!t)
		exit_error(args, "Error malloc args->t");
	return (t);
}

t_philo	*ft_mem_alloc_philo_ptr(t_args *args, t_philo *philo, int philo_nb)
{
	philo = malloc(sizeof(philo) * philo_nb);
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

t_philo	*ft_mem_alloc_philo(t_args *args, t_philo *philo)
{
	philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philo)
		exit_error(args, "Error malloc philo");
	return (philo);
}
