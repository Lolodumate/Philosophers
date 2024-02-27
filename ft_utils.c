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
	if (mtx_return != 0)
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
	ft_mutex(args, &args->mtx[WRITE], LOCK);
	if (stop_routine(args) == FALSE)
	{
		if (task == DEAD)
			ft_output(philo, " died", 1);
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
			ft_mutex(args, &args->mtx[WRITE], UNLOCK);
			exit_error(philo->args_ptr, "Error task");
		}
	}
	ft_mutex(args, &args->mtx[WRITE], UNLOCK);
}

void	ft_output(t_philo *philo, const char *task, int color)
{
	printf("%-6ld \033[1;3%dm%d %s\033[0m\n", get_timestamp(philo), color, philo->id, task);
}
