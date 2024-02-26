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
	return (args);
}

pthread_t	*mem_alloc_threads(t_args *args, pthread_t *t, int philo_nb)
{
	t = malloc(sizeof(pthread_t) * philo_nb);
	if (!t)
		exit_error(args, "Error malloc args->t");
	return (t);
}

t_philo	*mem_alloc_philo_ptr(t_args *args, t_philo *philo, int n)
{
	philo = malloc(sizeof(t_philo) * n);
	if (!philo)
		exit_error(args, "Error malloc args->philo_ptr");
	return (philo);
}

pthread_mutex_t	*mem_alloc_mtx(t_args *args, pthread_mutex_t *mtx, int n)
{
	mtx = malloc(sizeof(pthread_mutex_t) * n);
	if (!mtx)
		exit_error(args, "Error malloc args->forks");
	return (mtx);
}

// int array to record the number of meals eaten by each philosophers
int	*mem_alloc_tab(t_args *args, int n)
{
	int		*tab;
	int		i;

	tab = malloc(sizeof(int) * n);
	if (!tab)
		exit_error(args, "Error malloc meals");
	i = -1;
	while (++i < n)
	{
		tab[i] = 0;
	}
	return (tab);
}
