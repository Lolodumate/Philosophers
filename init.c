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
	args->is_dead = FALSE;
	args->nphilo = ft_atoi(argv[1]);
	if (ft_atoi(argv[1]) == 1)
		args->solo_dinner = TRUE;
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->threads_created = 0;
	args->go = FALSE;
	args->nb_of_locked_forks = 0;
	args->end_of_diner = 0;
	args->target_nb_meals = -1;
	args->solo_dinner = FALSE;
	if (argc == 6)
		args->target_nb_meals = ft_atoi(argv[5]);
	args->forks = NULL;
	args->time_start_dinner = get_time(args, MS);
	return (args);
}

t_philo	*init_philos(t_args *args, int n)
{
	int             i;

	i = -1;
	while (++i < n)
	{
		args->philo_ptr[i].id = i + 1;
		args->philo_ptr[i].stop_routine = FALSE;
		args->philo_ptr[i].mtx_is_unlocked = FALSE;
		args->philo_ptr[i].args_ptr = args;
		args->philo_ptr[i].meal_complete = FALSE;
		args->philo_ptr[i].meal_number = 0;
		args->philo_ptr[i].start_time = get_time(args, MS);
		args->philo_ptr[i].last_meal_time = 0;
		args->philo_ptr[i].death_time = 0;
		args->philo_ptr[i].main_fork = NULL;
		args->philo_ptr[i].aux_fork = NULL;
		args->philo_ptr[i].mtx = mem_alloc_mtx(args, args->philo_ptr[i].mtx, 1);
		ft_mutex(args, &args->philo_ptr[i].mtx[MTX], INIT);
	}
	return (args->philo_ptr);
}

t_args	*init_forks(t_args *args, pthread_mutex_t *forks, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		if (odd_or_even(args->philo_ptr[i].id) == ODD)
		{
			args->philo_ptr[i].main_fork = &forks[(i + 1) % n];
			args->philo_ptr[i].aux_fork = &forks[i % n];
		}
		else if (odd_or_even(args->philo_ptr[i].id) == EVEN)
		{
			args->philo_ptr[i].main_fork = &forks[i % n];
			args->philo_ptr[i].aux_fork = &forks[(i + 1) % n];
		}
	}
	return (args);
}

void	init_tab(int* tab, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
}

void	*set_data(t_args *args, int argc, char **argv)
{
	args = mem_alloc_args(args);
	args = init_args(argc, argv, args);
	args->philo_ptr = mem_alloc_philo_ptr(args, args->philo_ptr, args->nphilo);
	args->philo_ptr = init_philos(args, args->nphilo);
	args->forks = mem_alloc_mtx(args, args->forks, args->nphilo);;
	args = init_forks(args, args->forks, args->nphilo);
	args->meals = mem_alloc_tab(args, args->nphilo);
	init_tab(args->meals, args->nphilo);
	args->mtx = mem_alloc_mtx(args, args->mtx, 5);
	if (mutex_init(args, args->forks) != args->nphilo)
		exit_error(args, "Error initialisation mutex args->forks");
	args->t = mem_alloc_threads(args, args->t, args->nphilo);
	return (args);
}
