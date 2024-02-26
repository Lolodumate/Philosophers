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
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->time_start_diner = get_time(args, US);
	args->nb_of_locked_forks = 0;
	args->end_of_diner = 0;
	args->target_nb_meals = -1;
	if (argc == 6)
		args->target_nb_meals = ft_atoi(argv[5]);
	args->forks = NULL;
//	args->mtx_forks = mem_alloc_mtx_forks(args);
//	args->mtx_philo = mem_alloc_mtx(args, ft_atoi(argv[1]));
//	args->mtx_args = mem_alloc_mtx(args, 3);
	return (args);
}

/* Si le philo[i] a un voisin a sa droite philo[i - 1] alors :
 * - La fourchette droite de philo[i] correspond a la fourchette gauche de philo[i - 1].
 * - Donc la fourchette gauche de philo[i - 1] est un pointeur vers la fourchette droite de philo[i].
 */

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
		args->philo_ptr[i].nb_of_fork_to_drop = 0;
		args->philo_ptr[i].death_time = 0;
		args->philo_ptr[i].main_fork = NULL;
		args->philo_ptr[i].aux_fork = NULL;
		args->philo_ptr[i].mtx = mem_alloc_mtx(args, args->mtx, 2);
		ft_mutex(args, &args->philo_ptr[i].mtx[MTX], INIT);
		ft_mutex(args, &args->philo_ptr[i].mtx[ROUTINE], INIT);
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
