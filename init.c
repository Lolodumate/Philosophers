/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:27:46 by laroges           #+#    #+#             */
/*   Updated: 2024/01/27 15:46:56 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*init_args(int argc, char **argv, t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->death = 0;
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
	printf("philo->death_time = %ld\n", philo->death_time);
	pthread_mutex_init(&philo->mtx, NULL);
	philo->right_fork = malloc(sizeof(pthread_mutex_t));
	if (!philo->right_fork)
	{
		printf("Erreur allocation dynamique phil->right_fork\n");
		exit(1);
	}
	pthread_mutex_init(philo->right_fork, NULL);
	return (philo[index]);
}
/*
t_philo	*create_philos_and_forks(t_args *args)
{
	unsigned int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philo)
		exit(1);
	while (i < args->number_of_philosophers)
	{
		philo[i] = init_philo(args, philo, i);
		args->philo_ptr[i] = philo[i];
		i++;
	}
	return (philo);
}*/
