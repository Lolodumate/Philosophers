/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:34:02 by laroges           #+#    #+#             */
/*   Updated: 2024/01/20 08:03:01 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	seconde(unsigned int n)
{
	usleep(n * 1000000);
}

t_args	ft_eat(t_args args)
{
	unsigned int		i;

	i = 0;
	while (i++ < args.time_to_eat)
	{
		pthread_mutex_lock(args.philo_ptr->meal_lock);
		printf("%d is eating\n", args.philo_ptr->id);
		seconde(1);
		pthread_mutex_unlock(args.philo_ptr->meal_lock);			
	}
//	pthread_mutex_exit(args);
	return (args);
}

t_args	ft_sleep(t_args args)
{
	unsigned int		i;

	i = 0;
	while (i++ < args.time_to_sleep)
	{
		pthread_mutex_lock(args.philo_ptr->meal_lock);
		printf("%d is sleeping\n", args.philo_ptr->id);
		seconde(1);
		pthread_mutex_unlock(args.philo_ptr->meal_lock);			
	}
//	pthread_mutex_exit(args);
	return (args);
}

t_args	ft_think(t_args args)
{
	unsigned int		i;

	i = 0;
	while (i++ < args.time_to_die)
	{
		pthread_mutex_lock(args.philo_ptr->dead_lock);
		printf("%d is thinking\n", args.philo_ptr->id);
		seconde(1);
		pthread_mutex_unlock(args.philo_ptr->dead_lock);			
	}
//	pthread_mutex_exit(args);
	return (args);
}

t_args	philo_is_dead(t_args args)
{
	if (args.philo_ptr->dead)
		printf("%d died\n", args.philo_ptr->id);
	return (args);
}
