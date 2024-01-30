/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:27:46 by laroges           #+#    #+#             */
/*   Updated: 2024/01/30 15:44:20 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*init_args(int argc, char **argv, t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args)
		exit(1);
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->meal_complete = 0;
	args->death = 0;
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		args->number_of_times_each_philosopher_must_eat = ft_atoi("0");
	args->t = malloc(sizeof(pthread_t) * args->number_of_philosophers);
	if (!args->t)
	{
		free(args);
		exit(1);
	}
	args->philo_ptr = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!args->philo_ptr)
	{
		free(args);
		free(args->t);
		exit(1);
	}
	pthread_mutex_init(&args->mtx, NULL);
	pthread_mutex_init(&args->mtx_printf, NULL);
	return (args);
}

t_philo	*init_philo(t_args *args, t_philo *philo, int index)
{
	philo->id = index;
	philo->args_ptr = args;
	philo->start_time = get_time();
	philo->is_eating = 0;
	philo->is_dead = 0;
	philo->meal_complete = 0;
	philo->meal_number = 0;
	philo->death_time = philo->start_time + args->time_to_die;
	philo->left_fork = malloc(sizeof(pthread_mutex_t *));
	if (!philo->left_fork)
		exit(1);
//	printf("philo->death_time = %ld\n", philo->death_time);
	return (philo);
}

t_philo	*set_philos(t_args *args, t_philo *philo)
{
	unsigned int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philo)
	{
		printf("Erreur allocation dynamique philo\n");
		exit(1); // ************************Liberer la memoire !
	}
	while (i < args->number_of_philosophers)
	{
		init_philo(args, &philo[i], i);
		args->philo_ptr[i] = philo[i];
		pthread_mutex_init(&philo[i].mtx, NULL);
		i++;
	}
	i = 0;
/* Si le philo[i] a un voisin a sa droite philo[i - 1] alors :
 * - La fourchette droite de philo[i] correspond a la fourchette gauche de philo[i - 1].
 * - Donc la fourchette gauche de philo[i - 1] est un pointeur vers la fourchette droite de philo[i].
 */
//	init_forks(args);
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_init(&args->philo_ptr[i].right_fork, NULL);
		if (i > 0)
		{
			philo[i - 1].left_fork = &philo[i].right_fork;
//			printf("philo[%d].left_fork = philo[%d].right_fork\n", i - 1, i);
		}
		if ((i + 1) == args->number_of_philosophers)
		{
			philo[i].left_fork = &philo[0].right_fork;
//			printf("philo[%d].left_fork = philo[%d].right_fork\n", i, 0);
		}
		i++;
	}
	return (philo);
}
