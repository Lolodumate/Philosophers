/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/03/04 16:49:23 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers_dinner(t_args *args)
{
//	if (threads_create(args) != 0)
//		exit_error(args, "Error threads creation");
	threads_create(args);
	threads_join(args);
	destroy_mutex(args, args->nphilo);
}

void	*dinner(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	ft_mutex(p->args_ptr, &p->args_ptr->mtx[MONITOR], LOCK);
	p->death_time = p->args_ptr->time_start + p->args_ptr->time_to_die;
	ft_mutex(p->args_ptr, &p->args_ptr->mtx[MONITOR], UNLOCK);
	while (stop_routine(p->args_ptr) == FALSE)
	{
		if (ft_eat(p) == TRUE)
			break ;
		if (ft_sleep(p) == TRUE)
			break ;
		if (ft_think(p) == TRUE)
			break ;
	}
	ft_mutex(p->args_ptr, &p->mtx[MTX], LOCK);
	p->stop_routine = TRUE;
	ft_mutex(p->args_ptr, &p->mtx[MTX], UNLOCK);
	return (NULL);
}

void	solo_dinner(t_philo *p)
{
	p->args_ptr->time_start = get_time(p->args_ptr, MS);
	p->death_time = p->args_ptr->time_start + p->args_ptr->time_to_die;
	ft_write_task(p->args_ptr, p, FORK);
	usleep(p->args_ptr->time_to_die * 1000);
	ft_write_task(p->args_ptr, p, DEAD);
}
