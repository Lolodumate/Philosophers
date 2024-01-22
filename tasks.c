/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:34:02 by laroges           #+#    #+#             */
/*   Updated: 2024/01/22 14:10:27 by laroges          ###   ########.fr       */
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
	printf("%ld %d has taken a fork\n", get_time(), philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("%ld %d has taken a fork\n", get_time(), philo->id);
}

void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time(), philo->id);
	seconde(philo->time_to_sleep);
}

void	ft_eat(t_philo *philo)
{
	// 1. Picking forks : right one, then left one.
	ft_pick_forks(philo);
	// 2. Eating
	pthread_mutex_lock(philo->mtx);
	printf("%ld %d is eating\n", get_time(), philo->id);
	philo.is_eating = 1; // So the monitor knows that this philosopher is eating.
	seconde(philo->time_to_eat);
	philo->is_eating = 0; // So the monitor knows that this philosopher is not eating any more.
	philo->meal_number++;
	pthread_mutex_unlock(philo->mtx);
	// 3. Dropping forks and sleep.
	ft_drop_forks(philo);
	ft_sleep(philo); // After eating, philosopher is sleeping.	
}

void	ft_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time(), philo->id);
}
