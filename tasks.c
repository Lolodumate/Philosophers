/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:34:02 by laroges           #+#    #+#             */
/*   Updated: 2024/01/31 12:49:47 by laroges          ###   ########.fr       */
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

void	ft_pick_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	ft_output(philo, " has taken a fork");
	pthread_mutex_lock(&philo->left_fork);
	ft_output(philo, " has taken a fork");
}

void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx);
	ft_output(philo, " is sleeping");
	pthread_mutex_unlock(&philo->mtx);
	ft_usleep(philo->args_ptr->time_to_sleep);
}

void	ft_eat(t_philo *philo)
{
// 1. Picking forks : right one, then left one.
	ft_pick_forks(philo);
// 2. Eating
	pthread_mutex_lock(&philo->mtx);
	ft_output(philo, " is eating");
	philo->is_eating = 1; // So the monitor knows that this philosopher is eating.
	philo->death_time = get_time() + philo->args_ptr->time_to_die;
	ft_usleep(philo->args_ptr->time_to_eat);
	philo->is_eating = 0; // So the monitor knows that this philosopher is not eating any more.
	philo->meal_number++;
	if (philo->meal_number >= philo->args_ptr->number_of_times_each_philosopher_must_eat && philo->args_ptr->number_of_times_each_philosopher_must_eat != 0)
	{
		philo->meal_complete = 1;
		printf("philo[%d].meal_complete = 1\n", philo->id);
	}
//	printf("philo->meal_number = %d\n", philo->meal_number);
//	printf("philo->meal_complete = %d\n", philo->meal_complete);
	pthread_mutex_unlock(&philo->mtx);
// 3. Dropping forks and sleep.
	ft_drop_forks(philo);
	ft_sleep(philo); // After eating, philosopher is sleeping.
}

void	ft_think(t_philo *philo)
{ 
	pthread_mutex_lock(&philo->mtx);
	ft_output(philo, " is thinking");
	pthread_mutex_unlock(&philo->mtx);
}
