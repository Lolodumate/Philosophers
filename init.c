/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:27:46 by laroges           #+#    #+#             */
/*   Updated: 2024/01/26 20:20:35 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*init_args(int argc, char **argv, t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->number_of_dead = 0;
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	args->t = malloc(sizeof(pthread_t) * args->number_of_philosophers);
	if (!args->t)
	{
		free(args);
		return (NULL);
	}
	args->philo_ptr = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!args->philo_ptr)
	{
		free(args);
		free(args->t);
		return (NULL);
	}
	pthread_mutex_init(&args->mtx, NULL);
	pthread_mutex_init(&args->mtx_printf, NULL);
	return (args);
}

t_philo	init_philo(t_args *args, t_philo *philo, int index)
{
	philo->id = index;
	philo->args_ptr = args;
	philo->start_time = get_time();
	philo->is_eating = 0;
	philo->is_dead = 0;
	philo->meal_complete = 0;
	philo->meal_number = 0;
	philo->death_time = philo->start_time + args->time_to_die;
	pthread_mutex_init(&philo->mtx, NULL);
	pthread_mutex_init(&philo->right_fork, NULL);
	return (&philo);
}

t_philo	*create_philos_and_forks(t_args *args)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philo)
		exit(1);
	while (i < args->number_of_philosophers)
	{
		philo[i] = init_philo(args, philo, i);
		args->philo_ptr[i] = &philo[i];
		i++;
	}
	return (philo);
}
