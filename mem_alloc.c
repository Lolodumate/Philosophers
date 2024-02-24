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

t_args	*mem_alloc_args(t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args)
	{
		printf("Error malloc args");
		exit(EXIT_FAILURE);
	}
	else
		printf("malloc args OK\n");
	return (args);
}

pthread_t	*mem_alloc_threads(t_args *args, pthread_t *t, int philo_nb)
{
	t = malloc(sizeof(pthread_t) * philo_nb);
	if (!t)
		exit_error(args, "Error malloc args->t");
	else
		printf("malloc threads OK\n");
	return (t);
}

t_philo	*mem_alloc_philo_ptr(t_args *args, t_philo *philo, int n)
{
	philo = malloc(sizeof(t_philo) * n);
	if (!philo)
		exit_error(args, "Error malloc args->philo_ptr");
	else
		printf("malloc args->philo_ptr OK\n");
	return (philo);
}

pthread_mutex_t	*mem_alloc_forks(t_args *args, pthread_mutex_t *forks)
{
	forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	if (!forks)
		exit_error(args, "Error malloc args->forks");
	else
		printf("malloc args->forks OK\n");
	return (forks);
}

// int array to record the number of meals eaten by each philosophers
int	*mem_alloc_meals(t_args *args)
{
	int		*meals;
	int		i;

	meals = malloc(sizeof(int) * args->number_of_philosophers);
	if (!meals)
		exit_error(args, "Error malloc meals");
	else
		printf("malloc args->meals OK\n");
	i = -1;
	while (++i < args->number_of_philosophers)
	{
		meals[i] = 0;
	}
	return (meals);
}
