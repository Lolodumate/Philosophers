/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:05:25 by laroges           #+#    #+#             */
/*   Updated: 2024/03/02 17:13:39 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_pick_forks(t_args *args, t_philo *p)
{
	ft_mutex(args, p->main_fork, LOCK);
	ft_write_task(args, p, FORK);
	ft_mutex(args, p->aux_fork, LOCK);
	ft_write_task(args, p, FORK);
}

void	ft_drop_forks(t_args *args, t_philo *p)
{
	ft_mutex(args, p->main_fork, UNLOCK);
	ft_mutex(args, p->aux_fork, UNLOCK);
}

int	ft_sleep(t_philo *p)
{
	ft_write_task(p->args_ptr, p, SLEEP);
	ft_usleep(p->args_ptr->time_to_sleep * 1000, p->args_ptr, p->id - 1);
	return (stop_routine(p->args_ptr));
}

int	ft_eat(t_philo *p)
{
	ft_pick_forks(p->args_ptr, p);
	ft_write_task(p->args_ptr, p, EAT);
	ft_mutex(p->args_ptr, &p->args_ptr->mtx[MTX], LOCK);
	p->last_meal = get_time(p->args_ptr, MS);
	ft_mutex(p->args_ptr, &p->args_ptr->mtx[MTX], UNLOCK);
	ft_mutex(p->args_ptr, &p->mtx[MTX], LOCK);
	if (p->args_ptr->target_nb_meals > 0)
	{
		ft_mutex(p->args_ptr, &p->args_ptr->mtx[MEAL], LOCK);
		p->args_ptr->meals[p->id - 1]++;
		ft_mutex(p->args_ptr, &p->args_ptr->mtx[MEAL], UNLOCK);
	}
	ft_usleep(p->args_ptr->time_to_eat * 1000, p->args_ptr, p->id - 1);
	ft_mutex(p->args_ptr, &p->mtx[MTX], UNLOCK);
	ft_drop_forks(p->args_ptr, p);
	return (stop_routine(p->args_ptr));
}

int	ft_think(t_philo *p)
{
	ft_write_task(p->args_ptr, p, THINK);
	return (should_even_philos_die(p->args_ptr, p));
}
