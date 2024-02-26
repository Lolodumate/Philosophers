/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:34:19 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 20:41:44 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Verification de la conformite des arguments :
 *      1. number_of_philosophers (doit etre > 0 et <= 200)
 *      2. time_to_die (doit etre > 0)
 *      3. time_to_eat (doit etre > 0)
 *      4. time_to_sleep (doit etre > 0)
 *      5. number_of_times_each_philosophers_must_eat (optionnal) (doit etre >= 0) 
 *
 * Verifier :
 *      - Le nombre d'arguments.
 *      - Le contenu des arguments (ils ne doivent comporter que les caracteres numeriques).
*/

int	main(int argc, char **argv)
{
	t_args		*args;

	args = NULL;
	compliance_args(argc, argv);

// Allocations dynamiques et initialisations (avec protections)

	// Structure args
	args = mem_alloc_args(args);
	args = init_args(argc, argv, args);
	
	printf("args = %p\n", &args);

	// Philosophes
	args->philo_ptr = mem_alloc_philo_ptr(args, args->philo_ptr, args->number_of_philosophers);
	args->philo_ptr = init_philos(args, args->number_of_philosophers);

	// Fourchettes
	args->forks = mem_alloc_mtx(args, args->forks, args->number_of_philosophers);;
	args = init_forks(args, args->forks, args->number_of_philosophers);

	// Repas
	args->meals = mem_alloc_tab(args, args->number_of_philosophers);
	init_tab(args->meals, args->number_of_philosophers);

	// Monitor
	args->join_threads_monitor = mem_alloc_tab(args, args->number_of_philosophers);
	init_tab(args->join_threads_monitor, args->number_of_philosophers);
	
	// Mutex
	args->philo_ptr->mtx = mem_alloc_mtx(args, args->mtx, 2);
	args->mtx = mem_alloc_mtx(args, args->mtx, 5);
	if (mutex_init(args, args->forks) != args->number_of_philosophers)
		exit_error(args, "Error initialisation mutex args->forks");
	ft_mutex(args, &args->mtx[MTX], INIT);
	ft_mutex(args, &args->mtx[MASTER], INIT);
	ft_mutex(args, &args->mtx[MONITOR], INIT);
	ft_mutex(args, &args->mtx[MEAL], INIT);
	ft_mutex(args, &args->mtx[WRITE], INIT);

	printf("args->mtx = %p\n", &args->mtx);
	
	// Threads
	args->t = mem_alloc_threads(args, args->t, args->number_of_philosophers);

/*	
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		printf("&philo[%d] = %p\n\n", i, &args->philo_ptr[i]);
		printf("&args->forks[%d] = %p\n", i, &args->forks[i]);
		printf("&philo[%d].main_fork = %p\n", i, args->philo_ptr[i].main_fork);
		printf("&philo[%d].aux_fork  = %p\n\n", i, args->philo_ptr[i].aux_fork);
	}
*/
	philosophers_dinner(args);
	
//	threads_join(args);
	ft_clean(args);
	
	printf("***********************END************************\n");
	return (0);
}
