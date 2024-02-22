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

int	*mem_alloc_mtx_forks(t_args *args)
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

int	check_mutex_forks(t_args *args)
{
	int		i;
	int		res;
	int		*tab;

	i = -1;
	res = 0;
	tab = args->mtx_forks;
//	printf("Check check_mtx_forks\n");
	while (++i < args->number_of_philosophers)
	{
//		printf("check_mtx_forks[%d] = %d\n", i, tab[i]);
		res += tab[i];
	}
	if (res == 0)
	{
		printf("check_mutex_forks res == 0 OK\n");
		return (TRUE);
	}
	return (FALSE);
}

int	check_mutex_philo(t_args *args)
{
	int		i;
	int		res;
	int		*tab;

	i = -1;
	res = 0;
	tab = args->mtx_philo;
//	printf("Check check_mtx_philo\n");
	while (++i < args->number_of_philosophers)
	{
//		printf("check_mtx_philo[%d] = %d\n", i, tab[i]);
		res += tab[i];
	}
	if (res == 0)
	{
		printf("check_mutex_forks res == 0 OK\n");
		return (TRUE);
	}
	return (FALSE);
}
