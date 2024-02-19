/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:27:46 by laroges           #+#    #+#             */
/*   Updated: 2024/02/19 11:15:14 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*init_args(int argc, char **argv, t_args *args)
{
	args->meals_complete = 0;
	args->deaths = 0;
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->time_start_diner = get_time(args, MS);
	args->end_of_diner = 0;
	args->target_nb_meals = 0;
	if (argc == 6)
		args->target_nb_meals = ft_atoi(argv[5]);
	args->forks = ft_mem_alloc_forks(args, args->forks);
	args->t = ft_mem_alloc_threads(args, args->t, args->number_of_philosophers);
	ft_mutex(args, &args->mtx_check_ending, INIT);
	ft_mutex(args, &args->mtx, INIT);
	ft_mutex(args, &args->mtx_write, INIT);
	ft_mutex(args, args->forks, INIT);
	return (args);
}

void	init_philo(t_args *args, t_philo *philo, int index)
{
	philo->id = index;
	philo->args_ptr = args;
	philo->is_eating = FALSE;
	philo->is_dead = FALSE;
	philo->meal_complete = FALSE;
	philo->meal_number = 0;
	philo->start_time = get_time(args, MS);
	philo->death_time = args->philo_ptr->start_time + args->time_to_die;
	philo->main_fork = &args->forks[philo->id - 1];
	philo->aux_fork = &args->forks[philo->id % args->number_of_philosophers];
	ft_mutex(args, philo->main_fork, INIT);
	ft_mutex(args, philo->aux_fork, INIT);
	ft_mutex(args, &philo->mtx, INIT);
}

/* Si le philo[i] a un voisin a sa droite philo[i - 1] alors :
 * - La fourchette droite de philo[i] correspond a la fourchette gauche de philo[i - 1].
 * - Donc la fourchette gauche de philo[i - 1] est un pointeur vers la fourchette droite de philo[i].
 */

t_philo	*set_philos_and_forks(t_args *args)
{
	int             i;

	i = -1;
	while (++i < args->number_of_philosophers)
		init_philo(args, &args->philo_ptr[i], i + 1);
	return (args->philo_ptr);
}
