/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:34:19 by laroges           #+#    #+#             */
/*   Updated: 2024/01/31 16:01:24 by laroges          ###   ########.fr       */
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

void	philosophers(t_args *args)
{
	create_threads(args);
}

int	main(int argc, char **argv)
{
	t_args		*args;
	t_philo		*philo;

	args = NULL;
	philo = NULL;
	if (compliance_args(argc, argv))
	{

/* 1. Initialisation des donnees de la structure args :
 *	- Structure args
 *	- Pointeurs args->philos
 * 2. Initialisation des forks et philos (en liant les philos aux pointeurs args->philos).
 *
 * Note : initialisation = malloc, <donnee> = 0, et pthread_mutex_init.
 */
		args = init_args(argc, argv, args);
		philo = set_philos(args, philo);
		init_forks(args, philo);
		
/* Creation des threads.
 */
		philosophers(args);

/* Liberation de la memoire (free & destroy mutex).
 */
		ft_clean(args, philo);
	}
	return (0);
}
