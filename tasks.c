/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:34:02 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 20:28:56 by laroges          ###   ########.fr       */
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
	ft_write_task(args, philo, FORK);
	ft_mutex(args, philo->aux_fork, LOCK);
	ft_write_task(args, philo, FORK);
}

void	ft_drop_forks(t_args *args, t_philo *philo)
{
	ft_mutex(args, philo->main_fork, UNLOCK);
	ft_mutex(args, philo->aux_fork, UNLOCK);
	ft_mutex(args, &philo->mtx, LOCK);
	philo->meal_complete = philo_ends_meals(args, philo);
	ft_mutex(args, &philo->mtx, UNLOCK);
}

int	ft_sleep(t_philo *philo)
{
	ft_write_task(philo->args_ptr, philo, SLEEP);
	ft_usleep(philo->args_ptr->time_to_sleep * 1000, philo->args_ptr);
	return (philo_is_alive(philo->args_ptr, philo));
}

int	ft_eat(t_philo *philo)
{
	ft_pick_forks(philo->args_ptr, philo);
	ft_write_task(philo->args_ptr, philo, EAT);
	ft_mutex(philo->args_ptr, &philo->mtx, LOCK);
	update_death_time(philo->args_ptr, philo);
	ft_mutex(philo->args_ptr, &philo->mtx, UNLOCK);
	ft_usleep(philo->args_ptr->time_to_eat * 1000, philo->args_ptr);
	ft_drop_forks(philo->args_ptr, philo);
	if (philo->args_ptr->target_nb_meals > 0)
	{
		ft_mutex(philo->args_ptr, &philo->mtx, LOCK);
		philo->meal_number++;
		ft_mutex(philo->args_ptr, &philo->mtx, UNLOCK);
		update_meals_complete(philo);
	}
	return (philo_is_alive(philo->args_ptr, philo));
}

int	ft_think(t_philo *philo)
{ 
	ft_write_task(philo->args_ptr, philo, THINK);
	return (philo_is_alive(philo->args_ptr, philo));
}
