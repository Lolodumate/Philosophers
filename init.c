/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:27:46 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 20:05:12 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*init_args(int argc, char **argv, t_args *args)
{
	args->meals_complete = FALSE;
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->number_of_philo_is_= odd_or_even(ft_atoi(argv[1]));
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->time_start_diner = get_time(args, US);
	args->end_of_diner = 0;
	args->meals = mem_alloc_meals(args);
	args->target_nb_meals = -1;
	if (argc == 6)
		args->target_nb_meals = ft_atoi(argv[5]);
	args->mtx_forks = mem_alloc_mtx_forks(args);
	args->mtx_philo = mem_alloc_mtx(args, ft_atoi(argv[1]));
	args->mtx_args = mem_alloc_mtx(args, 3);
	args->t = mem_alloc_threads(args, args->t, args->number_of_philosophers);
	ft_mutex(args, &args->mtx_check_ending, INIT);
	ft_mutex(args, &args->mtx, INIT);
	ft_mutex(args, &args->mtx_write, INIT);
	return (args);
}

void	init_philo(t_args *args, t_philo *philo, int index)
{
	philo->id = index;
	philo->args_ptr = args;
	philo->is_dead = FALSE;
	philo->meal_complete = FALSE;
	philo->meal_number = 0;
	philo->start_time = get_time(args, MS);
	philo->death_time = philo->args_ptr->time_start_diner + args->time_to_die * 1000;
}

/* Si le philo[i] a un voisin a sa droite philo[i - 1] alors :
 * - La fourchette droite de philo[i] correspond a la fourchette gauche de philo[i - 1].
 * - Donc la fourchette gauche de philo[i - 1] est un pointeur vers la fourchette droite de philo[i].
 */

t_philo	*set_philos(t_args *args, int n)
{
	int             i;
	t_philo	*philo;

	i = -1;
	philo = mem_alloc_philo_ptr(args, n);
	args->philo_ptr = philo;
	while (++i < args->number_of_philosophers)
	{
		ft_mutex(args, &philo[i].mtx, INIT);
		init_philo(args, &philo[i], i + 1);
	}
	return (philo);
}

t_args	*set_forks(t_args *args, pthread_mutex_t *forks, int n)
{
	int		i;

	i = -1;
	forks = mem_alloc_forks(args, forks);
	args->forks = forks;
	while (++i < n)
	{
		ft_mutex(args, &forks[i], INIT);
		if (odd_or_even(args->philo_ptr[i].id) == ODD)
		{
			args->philo_ptr[i].main_fork = &args->forks[(i + 1) % n];
			args->philo_ptr[i].aux_fork = &args->forks[i % n];
		}
		else if (odd_or_even(args->philo_ptr[i].id) == EVEN)
		{
			args->philo_ptr[i].main_fork = &args->forks[i % n];
			args->philo_ptr[i].aux_fork = &args->forks[(i + 1) % n];
		}
	}
	return (args);
}
