/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:34:02 by laroges           #+#    #+#             */
/*   Updated: 2024/02/15 18:05:22 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	1. Picking the two forks.
 *	2. Eating.
 *	3. Dropping the forks.
 *	4. Sleeping.
 *
 *	Note : 
 *	- Monitor checks the time it takes to a philosopher to die. If the time remaining before his death is smaller than the "time_to_eat" then the philosopher will survive.
 *	- Monitor also checks the number of times a philosopher has eaten and when he reaches it so the philosopher is set as "complete".
 *	- Monitor's thread must be started in first,  before the philosopher's threads.
 *	- When all the philosophers are set as "complete" the program ends.
 */

void	ft_pick_forks(t_args *args, t_philo *philo)
{
	ft_mutex(args, philo->main_fork, LOCK);
	ft_write_task(philo, FORK);
	ft_mutex(args, philo->aux_fork, LOCK);
	ft_write_task(philo, FORK);
}

void	ft_drop_forks(t_args *args, t_philo *philo)
{
	ft_mutex(args, philo->main_fork, UNLOCK);
	ft_mutex(args, philo->aux_fork, UNLOCK);
	ft_mutex(args, &philo->mtx, LOCK);
	philo->is_eating = FALSE;
	ft_mutex(args, &philo->mtx, UNLOCK);
}

void	ft_sleep(t_philo *philo)
{
	ft_write_task(philo, SLEEPING);
	if (philo->is_dead == FALSE)
	{
		ft_mutex(philo->args_ptr, &philo->mtx, LOCK);
		while (philo->death_time > get_time(philo->args_ptr, MS) + 10)
		{
			usleep(2);
			if (philo->args_ptr->end_of_diner == TRUE)
				break ;
		}
		ft_mutex(philo->args_ptr, &philo->mtx, UNLOCK); //*****************MUTEX UNLOCK
	}
}

void	ft_eat(t_philo *philo)
{
	if (philo->is_dead == 1)
		return ;
	ft_pick_forks(philo->args_ptr, philo);
	ft_mutex_write(&philo->args_ptr->mtx_write, philo->args_ptr, philo,  EATING);
	update_death_time(philo->args_ptr, philo);
	ft_usleep(philo->args_ptr->time_to_eat * 1000, philo->args_ptr);
	ft_drop_forks(philo->args_ptr, philo);
	philo->meal_number++;
	update_meals_complete(philo);
	ft_mutex(philo->args_ptr, &philo->mtx, UNLOCK);
	ft_sleep(philo);
}

void	ft_think(t_philo *philo)
{ 
	ft_mutex(philo->args_ptr, &philo->mtx, LOCK);
	printf("philo->args_ptr->end_of_diner = %d\n", philo->args_ptr->end_of_diner);
	ft_mutex(philo->args_ptr, &philo->mtx, UNLOCK);
	if (philo->is_dead == FALSE && philo->args_ptr->end_of_diner == FALSE)
		ft_write_task(philo, THINKING);
}
