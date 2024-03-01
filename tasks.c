/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2[MTX]24/[MTX]1/19 14:34:[MTX]2 by laroges           #+#    #+#             */
/*   Updated: 2[MTX]24/[MTX]2/2[MTX] 2[MTX]:28:56 by laroges          ###   ########.fr       */
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
}

int	ft_sleep(t_philo *philo)
{
	ft_write_task(philo->args_ptr, philo, SLEEP);
	ft_usleep(philo->args_ptr->time_to_sleep * 1000, philo->args_ptr, philo->id - 1);
	return (stop_routine(philo->args_ptr));
}

int	ft_eat(t_philo *philo)
{
	ft_pick_forks(philo->args_ptr, philo);
	ft_write_task(philo->args_ptr, philo, EAT);
	ft_mutex(philo->args_ptr, &philo->args_ptr->mtx[MTX], LOCK);
	philo->last_meal_time = get_time(philo->args_ptr, MS);
	printf("philo[%d].last_meal_time = %ld\n", philo->id - 1, philo->last_meal_time);
	printf("philo[%d].last_meal_time + args->time_to_die = %ld + %ld = %ld\n", philo->id - 1, philo->last_meal_time, philo->args_ptr->time_to_die, philo->last_meal_time + philo->args_ptr->time_to_die);
	ft_mutex(philo->args_ptr, &philo->args_ptr->mtx[MTX], UNLOCK);
	ft_mutex(philo->args_ptr, &philo->mtx[MTX], LOCK);
	if (philo->args_ptr->target_nb_meals > 0)
	{
		ft_mutex(philo->args_ptr, &philo->args_ptr->mtx[MEAL], LOCK);
		philo->args_ptr->meals[philo->id - 1]++;
		ft_mutex(philo->args_ptr, &philo->args_ptr->mtx[MEAL], UNLOCK);
	}
	ft_usleep(philo->args_ptr->time_to_eat * 1000, philo->args_ptr, philo->id - 1);
	
	// Faire une fonction qui gere la mort pendant le repas et qui unlock les mutex pour nettoyage de la memoire.

	printf("get_time = %ld\n", get_time(philo->args_ptr, MS));

	philo->death_time = philo->last_meal_time + philo->args_ptr->time_to_die;	

	ft_mutex(philo->args_ptr, &philo->mtx[MTX], UNLOCK);
	ft_drop_forks(philo->args_ptr, philo);
	return (stop_routine(philo->args_ptr));
}

int	ft_think(t_philo *philo)
{ 
	ft_write_task(philo->args_ptr, philo, THINK);
	return (stop_routine(philo->args_ptr));
}
