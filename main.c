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
	
	// Philosophes
	args->philo_ptr = mem_alloc_philo_ptr(args, args->philo_ptr, args->number_of_philosophers);
	args->philo_ptr = init_philos(args, args->number_of_philosophers);

	// Fourchettes
	args->forks = mem_alloc_forks(args, args->forks);

	args = init_forks(args, args->forks, args->number_of_philosophers);

	// Repas
	args->meals = mem_alloc_tab(args, args->number_of_philosophers);
	init_tab(args->meals, args->number_of_philosophers);

	// Mutex
	ft_mutex(args, &args->monitor, INIT);
	ft_mutex(args, &args->mtx, INIT);
	ft_mutex(args, &args->mtx_meal, INIT);
	ft_mutex(args, &args->mtx_write, INIT);
	if (mutex_init(args, args->forks) != args->number_of_philosophers)
		exit_error(args, "Error initialisation mutex args->forks");
	
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
	printf("***********************END************************\n");
	return (0);
}
