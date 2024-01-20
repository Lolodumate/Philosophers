/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:34:02 by laroges           #+#    #+#             */
/*   Updated: 2024/01/20 13:46:16 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	seconde(unsigned int n)
{
	usleep(n * 1000000);
}

t_args	ft_eat(void *mtx, t_args args, t_philo philo)
{
	unsigned int		i;

	i = 0;
	args.philo_ptr = &philo;
	pthread_mutex_lock(args.philo_ptr->right_fork);
	printf("%d has taken a fork\n");
	pthread_mutex_unlock(args.philo_ptr->right_fork);
	pthread_mutex_lock(args.philo_ptr->left_fork);
	printf("%d has taken a fork\n");
	pthread_mutex_unlock(args.philo_ptr->left_fork);
	pthread_mutex_lock(args.philo_ptr->meal_lock);
	printf("%d is eating\n", args.philo_ptr->id);
	seconde(args.time_to_eat);
	pthread_mutex_unlock(args.philo_ptr->meal_lock);			
//	pthread_mutex_exit(args);
	return (args);
}

t_args	ft_sleep(void *mtx, t_args args, t_philo philo)
{
	args.philo_ptr = &philo;
	pthread_mutex_lock(args.philo_ptr->meal_lock);
	printf("%d is sleeping\n", args.philo_ptr->id);
	seconde(args.time_to_sleep);
	pthread_mutex_unlock(args.philo_ptr->meal_lock);			
//	pthread_mutex_exit(args);
	return (args);
}

t_args	ft_think(void *mtx, t_args args, t_philo philo)
{
	unsigned int		i;

	i = 0;
	args.philo_ptr = &philo;
	printf("%d is thinking\n", args.philo_ptr->id);
//	pthread_mutex_exit(args);
	return (args);
}

t_args	philo_is_dead(t_args args, t_philo philo)
{
	args.philo_ptr = &philo;
	if (args.philo_ptr->dead)
		printf("%d died\n", args.philo_ptr->id);
	return (args);
}
