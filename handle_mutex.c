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

void	unlock_mutex_forks(t_args *args, int *forks)
{
	int		i;

	i = -1;
	printf("Check unlock_mutex_forks\n");
	while (++i < args->number_of_philosophers)
	{
		if (forks[i] == LOCK)
		{
			printf("unlocking forks[%d]\n", i);
			ft_mutex(args, &args->forks[i], UNLOCK);
		}
	}
}
