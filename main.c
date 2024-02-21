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

void	diner(t_args *args)
{
	create_threads(args);
}

int	main(int argc, char **argv)
{
	t_args		*args;

	args = NULL;
	compliance_args(argc, argv);
/* 1. Initialisation des donnees de la structure args :
 *	- Structure args
 *	- Pointeurs args->philos
 * 2. Initialisation des forks et philos (en liant les philos aux pointeurs args->philos).
 *
 * Note : initialisation = malloc, <donnee> = 0, et pthread_mutex_init.
 */
	args = mem_alloc_args(args);
	args = init_args(argc, argv, args);
	args->philo_ptr = mem_alloc_philo_ptr(args, args->philo_ptr, args->number_of_philosophers);
	args->philo_ptr = set_philos_and_forks(args);
/*
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		printf("&philo[%d].main_fork = %p\n", i, args->philo_ptr[i].main_fork);
		printf("&philo[%d].aux_fork  = %p\n", i, args->philo_ptr[i].aux_fork);
	}
	exit_error(args, "END");
*/
/* Creation des threads.
 */
	diner(args);

/* Liberation de la memoire (free & destroy mutex).
 */
//	ft_clean(args);
	printf("***********************END************************\n");
	return (0);
}
