/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:27:46 by laroges           #+#    #+#             */
/*   Updated: 2024/02/02 08:52:44 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*init_args(int argc, char **argv, t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args)
		exit(1);
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->meals_complete = 0;
	args->deaths = 0;
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
	pthread_mutex_init(&args->mtx_check, NULL);
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
	pthread_mutex_init(&philo->mtx, NULL);
	philo->right_fork = malloc(sizeof(pthread_mutex_t *));
	if (!philo->right_fork)
		exit(1);
	philo->left_fork = malloc(sizeof(pthread_mutex_t *));
	if (!philo->left_fork)
		exit(1);
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
	return (philo);
}

/* Si le philo[i] a un voisin a sa droite philo[i - 1] alors :
 * - La fourchette droite de philo[i] correspond a la fourchette gauche de philo[i - 1].
 * - Donc la fourchette gauche de philo[i - 1] est un pointeur vers la fourchette droite de philo[i].
 */
void	init_forks(t_args *args, t_philo *philo)
{
	unsigned int		i;

	i = 0;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	if (!args->forks)
		exit(1); // ***********************Liberer la memoire !
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		args->philo_ptr[i].right_fork = &args->forks[i];
//		printf("*	args->philo_ptr[%d].right_fork = &args->forks[%d]\n", i, i);
		philo[i].right_fork = &args->forks[i];
		if (i > 0)
		{
			args->philo_ptr[i - 1].left_fork = &args->forks[i];
//			printf("args->philo_ptr[%d].left_fork = &args->forks[%d]\n", i - 1, i);
			philo[i - 1].left_fork = &args->forks[i];
		}
		if ((i + 1) == args->number_of_philosophers)
		{
			args->philo_ptr[i].left_fork = &args->forks[0];
//			printf("	args->philo_ptr[%d].left_fork = &args->forks[%d]\n", i, 0);
			philo[i].left_fork = &args->forks[0];
		}
		i++;
	}
}
