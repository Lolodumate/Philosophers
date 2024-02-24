/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:18:12 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 13:59:04 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_protect(t_args *args, int mtx_return)
{
	if (mtx_return == 0)
		return ;
	exit_error(args, "Error mutex");
}

void	ft_mutex(t_args *args, pthread_mutex_t *mtx, int m)
{
	if (m == LOCK)
		ft_mutex_protect(args, pthread_mutex_lock(mtx));
	else if (m == UNLOCK)
		ft_mutex_protect(args, pthread_mutex_unlock(mtx));
	else if (m == DESTROY)
		ft_mutex_protect(args, pthread_mutex_destroy(mtx));
	else if (m == INIT)
		ft_mutex_protect(args, pthread_mutex_init(mtx, NULL));
	else
		exit_error(args, "Wrong mutex input");
}

void	ft_write_task(t_args *args, t_philo *philo, int task)
{
	ft_mutex(args, &args->mtx_write, LOCK);
	if (/*args->end_of_diner == TRUE ||*/ philo->meal_complete == TRUE)
	{
		ft_mutex(args, &args->mtx_write, UNLOCK);
		return ;
	}
	if (philo->is_dead == FALSE || args->end_of_diner == FALSE)
	{
		if (task == DEAD)
		{
			ft_output(philo, " died", 1);
			philo->is_dead = TRUE;
		}
		else if (task == FORK && args->end_of_diner == FALSE)
			ft_output(philo, " has taken a fork", 5);
		else if (task == EAT && args->end_of_diner == FALSE)
			ft_output(philo, " is eating", 2);
		else if (task == SLEEP && args->end_of_diner == FALSE)
			ft_output(philo, " is sleeping", 4);
		else if (task == THINK && args->end_of_diner == FALSE)
			ft_output(philo, " is thinking", 3);
		else
		{
			ft_mutex(args, &args->mtx_write, UNLOCK);
			exit_error(philo->args_ptr, "Error task");
		}
	}
	ft_mutex(args, &args->mtx_write, UNLOCK);
}
/*
void	fill_mtx_forks_tab(t_args *args, t_philo *philo, pthread_mutex_t *mtx, int m)
{
	if (mtx == philo->main_fork)
	{
		if (odd_or_even(philo->id) == ODD)
			args->mtx_forks[philo->id % args->number_of_philosophers] = m;
		else if (odd_or_even(philo->id) == EVEN)
			args->mtx_forks[(philo->id - 1) % args->number_of_philosophers] = m;
	}
	if (mtx == philo->aux_fork)
	{
		if (odd_or_even(philo->id) == ODD)
			args->mtx_forks[(philo->id - 1) % args->number_of_philosophers] = m;
		else if (odd_or_even(philo->id) == EVEN)
			args->mtx_forks[philo->id % args->number_of_philosophers] = m;
	}
}

int	*fill_mtx_tab(t_args *args, t_philo *philo, pthread_mutex_t *mtx, int m)
{
	int		*tab;

	tab = 0;
	if (mtx == philo->main_fork || mtx == philo->aux_fork)
		return (NULL);
	if (mtx == &args->mtx_check_ending)
	{
		tab = args->mtx_args;
		tab[0] = m;
	}
	else if (mtx == &args->mtx)
	{
		tab = args->mtx_args;
		tab[1] = m;
	}
	else if (mtx == &args->mtx_write)
	{
		tab = args->mtx_args;
		tab[2] = m;
	}
	if (mtx == &philo[philo->id - 1].mtx)
	{
		tab = args->mtx_philo;
		tab[philo->id - 1] = m;
	}
	return (tab);
}*/
