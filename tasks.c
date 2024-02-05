/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:34:02 by laroges           #+#    #+#             */
/*   Updated: 2024/02/05 13:45:54 by laroges          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->args_ptr->forks[i]); //****************MUTEX LOCK
	ft_output(philo, " \033[0mhas taken a fork", 5);
	if (i == (philo->args_ptr->number_of_philosophers - 1))
		pthread_mutex_lock(&philo->args_ptr->forks[0]); //***************MUTEX LOCK
	else
		pthread_mutex_lock(&philo->args_ptr->forks[i + 1]); //*************MUTEX LOCK
	ft_output(philo, " \033[0mhas taken a fork", 5);
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
	ft_usleep(philo->args_ptr->time_to_sleep, philo->args_ptr);
}

void	ft_eat(t_philo *philo)
{
// 1. Picking forks : right one, then left one.
	ft_pick_forks(philo, philo->id);
// 2. Eating
	pthread_mutex_lock(&philo->mtx);
	ft_output(philo, " is eating", 2);
	philo->is_eating = 1; // So the monitor knows that this philosopher is eating.
	philo->death_time = get_time(MILLISECOND) + (philo->args_ptr->time_to_die / 1000);
//	printf("UPDATE philo[%d]->death_time = %ld\n", philo->id, philo->death_time);
	ft_usleep(philo->args_ptr->time_to_eat, philo->args_ptr);
	philo->is_eating = 0; // So the monitor knows that this philosopher is not eating any more.
	//Ajouter booleen philo->last_meal
	philo->meal_number++;
	if (philo->meal_number == philo->args_ptr->number_of_times_each_philosopher_must_eat && philo->args_ptr->number_of_times_each_philosopher_must_eat != 0)
	{
		philo->meal_complete = 1;
		philo->args_ptr->meals_complete++;
		printf("philo[%d].meal_complete = 1\n", philo->id);
		printf("philo->args_ptr->meals_complete = %d\n", philo->args_ptr->meals_complete);
	}
//	printf("philo->meal_number = %d\n", philo->meal_number);
//	printf("philo->meal_complete = %d\n", philo->meal_complete);
	pthread_mutex_unlock(&philo->mtx);
// 3. Dropping forks and sleep.
	ft_drop_forks(philo, philo->id);
	ft_sleep(philo); // After eating, philosopher is sleeping.
}

void	ft_think(t_philo *philo)
{ 
	ft_output(philo, " is thinking", 3);
}
