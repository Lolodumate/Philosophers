/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:34:02 by laroges           #+#    #+#             */
/*   Updated: 2024/02/13 14:01:03 by laroges          ###   ########.fr       */
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
	if (i % 2 == 0)
		usleep(1);
	pthread_mutex_lock(&philo->args_ptr->forks[i]); //****************MUTEX LOCK
	ft_output(philo, " \033[0mhas taken a fork", 5);
	if (philo[i].is_dead == 0)
	{
		if (i == (philo->args_ptr->number_of_philosophers - 1))
			pthread_mutex_lock(&philo->args_ptr->forks[0]); //***************MUTEX LOCK
		else
			pthread_mutex_lock(&philo->args_ptr->forks[i + 1]); //*************MUTEX LOCK
		ft_output(philo, " \033[0mhas taken a fork", 5);
	}
}

void	ft_drop_forks(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo->args_ptr->forks[i]); //****************MUTEX UNLOCK
	if (i == (philo->args_ptr->number_of_philosophers - 1))
		pthread_mutex_unlock(&philo->args_ptr->forks[0]); //******************MUTEX UNLOCK
	else
		pthread_mutex_unlock(&philo->args_ptr->forks[i + 1]); //*******************MUTEX UNLOCK
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx); //*****************MUTEX LOCK
	ft_output(philo, " is sleeping", 4);
	pthread_mutex_unlock(&philo->mtx); //*****************MUTEX UNLOCK
	ft_usleep(philo->args_ptr->time_to_sleep * 1000/*, philo->args_ptr*/);
}

void	ft_eat(t_philo *philo)
{
	if (philo->is_dead == 1 || philo->args_ptr->end_of_diner == 1)
		return ;
	ft_pick_forks(philo, philo->id);
	if (philo->is_dead == 1 || philo->args_ptr->end_of_diner == 1)
		return ;
	pthread_mutex_lock(&philo->mtx);
	ft_output(philo, " is eating", 2);
	philo->is_eating = 1; // So the monitor knows that this philosopher is eating.
	update_death_time(philo);
	ft_usleep(philo->args_ptr->time_to_eat * 1000/*, philo->args_ptr*/);
	ft_drop_forks(philo, philo->id);
	philo->is_eating = 0; // So the monitor knows that this philosopher is not eating any more.
	philo->meal_number++;
	if (philo->meal_number >= philo->args_ptr->target_nb_meals && philo->args_ptr->target_nb_meals != 0)
	{
		philo->meal_complete = 1;
		philo->args_ptr->meals_complete++;
//		printf("ft_eat : philo[%d].meal_complete = 1\n", philo->id);
//		printf("ft_eat : philo->args_ptr->meals_complete = %d\n", philo->args_ptr->meals_complete);
	}
	pthread_mutex_unlock(&philo->mtx);
	ft_sleep(philo); // After eating, philosopher is sleeping.
}

void	ft_think(t_philo *philo)
{ 
	if (philo->is_dead == 0 && philo->args_ptr->end_of_diner == 0)
		ft_output(philo, " is thinking", 3);
}
