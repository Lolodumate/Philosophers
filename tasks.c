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

void	ft_pick_forks(t_philo *philo, int i)
{
	if (i % 2 != 0)
		usleep(10);
	ft_mutex(philo->args_ptr, philo->main_fork, LOCK);
	ft_write_task(philo, FORK);
	ft_mutex(philo->args_ptr, philo->aux_fork, LOCK);
	ft_write_task(philo, FORK);
}

void	ft_drop_forks(t_philo *philo, int i)
{
	ft_mutex(philo->args_ptr, &philo->args_ptr->forks[i], UNLOCK); //****************MUTEX UNLOCK
	if (i == (philo->args_ptr->number_of_philosophers - 1))
		ft_mutex(philo->args_ptr, &philo->args_ptr->forks[0], UNLOCK); //******************MUTEX UNLOCK
	else
		ft_mutex(philo->args_ptr, &philo->args_ptr->forks[i + 1], UNLOCK); //*******************MUTEX UNLOCK
}

void	ft_sleep(t_philo *philo)
{
	long		i;

	i = 0;
	ft_mutex(philo->args_ptr, &philo->mtx, LOCK);
	ft_write_task(philo, SLEEPING);
	if (philo->is_dead == FALSE)
	{
		while (i < philo->args_ptr->time_to_sleep)
		{
			ft_usleep(5, philo->args_ptr);
			if (philo->args_ptr->end_of_diner == TRUE)
			{
				ft_mutex(philo->args_ptr, &philo->mtx, UNLOCK); //*****************MUTEX UNLOCK
				break ;
			}
			i += 1;
		}
//		ft_clean(philo->args_ptr, philo);
	}
	ft_mutex(philo->args_ptr, &philo->mtx, UNLOCK); //*****************MUTEX UNLOCK
}

void	ft_eat(t_philo *philo)
{
	if (philo->is_dead == 1)
		return ;
	ft_pick_forks(philo, philo->id);
	ft_mutex(philo->args_ptr, &philo->mtx, LOCK);
	ft_write_task(philo, EATING);
//	philo->is_eating = TRUE; // So the monitor knows that this philosopher is eating.
	update_death_time(philo);
	ft_usleep(philo->args_ptr->time_to_eat * 1000, philo->args_ptr);
	ft_drop_forks(philo, philo->id);
//	philo->is_eating = FALSE; // So the monitor knows that this philosopher is not eating any more.
	philo->meal_number++;
	update_meals_complete(philo);
	ft_mutex(philo->args_ptr, &philo->mtx, UNLOCK);
	ft_sleep(philo);
}

void	ft_think(t_philo *philo)
{ 
	if (philo->is_dead == FALSE && philo->args_ptr->end_of_diner == FALSE)
		ft_write_task(philo, THINKING);
}
