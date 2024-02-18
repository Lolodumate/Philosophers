/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:18:12 by laroges           #+#    #+#             */
/*   Updated: 2024/02/15 20:55:48 by laroges          ###   ########.fr       */
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

void	ft_write_task(t_philo *philo, int task)
{
	if (!philo)
		return ;
	else if (task == DEAD)
		ft_output(philo, " died", 1);
	else if (task == FORK)
		ft_output(philo, " has taken a fork", 5);
	else if (task == EATING)
		ft_output(philo, " is eating", 2);
	else if (task == SLEEPING)
		ft_output(philo, " is sleeping", 4);
	else if (task == THINKING)
		ft_output(philo, " is thinking", 3);
	else
		exit_error(philo->args_ptr, "Error task");
}

void	ft_mutex_write(pthread_mutex_t *mtx, t_args *args, t_philo *philo, int task)
{
	ft_mutex(args, mtx, LOCK);
	ft_write_task(philo, task);
	if (task == EATING)
		philo->is_eating = TRUE;
	ft_mutex(args, mtx, UNLOCK);
}

int	ft_mutex_increment_int(pthread_mutex_t *mtx, t_args *args, int data)
{
	int	res;

	ft_mutex(args, mtx, LOCK);
	res = data + 1;
	ft_mutex(args, mtx, UNLOCK);
	return (res);
}
