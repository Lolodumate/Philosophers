/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:37:37 by laroges           #+#    #+#             */
/*   Updated: 2024/03/04 17:24:41 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_create(t_args *a)
{
	int		i;

	i = -1;
	while (++i < a->nphilo)
	{
		if (pthread_create(&a->t[i], NULL, &dinner, &a->philo_ptr[i]) != 0)
		{
			printf("exit_error pthread_create\n");
			exit_error(a, "Error pthread_creation");
		}
		else
			printf("Thread[%d] created\n", i);
	}
	return (0);
}

int	wait_threads_creation_to_finish(t_args *args, t_philo *philo)
{
	ft_mutex(args, &philo->mtx[MONITOR], LOCK);
	if (args->threads_created == args->nphilo)
	{
		ft_mutex(args, &philo->mtx[MONITOR], UNLOCK);
		return (TRUE);
	}
	ft_mutex(args, &philo->mtx[MONITOR], UNLOCK);
	return (FALSE);
}

void	set_start_time_of_dinner(t_args *args, t_philo *philo)
{
	ft_mutex(args, &args->mtx[MTX], LOCK);
	if (args->time_start == 0)
		args->time_start = get_time(args, MS);
	ft_mutex(args, &args->mtx[MTX], UNLOCK);
	ft_mutex(args, &philo->mtx[MTX], LOCK);
	philo->death_time = args->time_start + args->time_to_die;
	ft_mutex(args, &philo->mtx[MTX], UNLOCK);
}

int	threads_join(void *args)
{
	int		i;
	t_args	*a;

	i = -1;
	a = (t_args *)args;
	while (++i < a->nphilo)
	{
		if (pthread_join(a->t[i], NULL) != 0)
			exit_error(a, "Error pthread_join");
	}
	return (0);
}
