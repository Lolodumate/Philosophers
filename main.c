/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:34:19 by laroges           #+#    #+#             */
/*   Updated: 2024/01/25 17:15:21 by laroges          ###   ########.fr       */
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
	t_philo		*philo;

	args = NULL;
	philo = NULL;
	compliance_args(argc, argv);
	// Initialisation des data.
	args = init_args(argc, argv, args);
//	args->philo_ptr = philo;
	philo = init_philo(args);
	// Threads
	philosophers(args, philo);
	free(args);
	return (0);
}
