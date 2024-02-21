/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:01:43 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 19:30:17 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*mem_alloc_forks_to_drop(t_args *args)
{
	int		i;
	int		*forks;

	i = -1;
	forks = malloc(sizeof(int) * args->number_of_philosophers);
	if (!forks)
		exit_error(args, "Error malloc forks to drop");
	while (++i < args->number_of_philosophers)
		forks[i] = 0;
	return (forks);
}

int	*mem_alloc_mtx(t_args *args, int n)
{
	int             i;
	int             *tab;

	i = -1;
	tab = malloc(sizeof(int) * n);
	if (!tab)
		exit_error(args, "Error malloc forks to drop");
	while (++i < n)
		tab[i] = 0;
	return (tab);
}

int	unlock_mutex_forks(t_args *args)
{
	int		i;
	int		*tab;

	i = -1;
	tab = args->forks_to_drop;
	printf("Check unlock_mtx_forks\n");
//	ft_mutex(args, philo, &args->mtx, LOCK);
	while (++i < args->number_of_philosophers)
	{
		printf("tab[%d] = %d\n", i, tab[i]);
		if (tab[i] == LOCK)
		{
			printf("unlocking mtx_forks[%d]\n", i);
			ft_mutex(args, &args->forks[i], UNLOCK);
			tab[i] = UNLOCK;
		}
		printf("unlock_mtx_fork[%d] = %d\n", i, tab[i]);
	}
//	ft_mutex(args, philo, &args->mtx, UNLOCK);
	return (TRUE);
}

int	unlock_mutex_philo(t_args *args, t_philo *philo)
{
	int		i;
	int		*tab;

	i = -1;
	tab = args->mtx_philo;
	printf("Check unlock_mtx_philo\n");
//	ft_mutex(args, philo, &args->mtx, LOCK);
	while (++i < args->number_of_philosophers)
	{
		printf("unlock_mtx_philo[%d] = %d\n", i, tab[i]);
		if (tab[i] == LOCK)
		{
			printf("unlocking mtx_philo[%d]\n", i);
			ft_mutex(args, &philo[i].mtx, UNLOCK);
			tab[i] = UNLOCK;
		}
		printf("unlock_mtx_philo[%d] = %d\n", i, tab[i]);
	}
//	ft_mutex(args, philo, &args->mtx, UNLOCK);
	return (TRUE);
}
