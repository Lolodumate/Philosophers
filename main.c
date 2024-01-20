/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:34:19 by laroges           #+#    #+#             */
/*   Updated: 2024/01/20 10:34:32 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	// Creation du Mutex
	pthread_mutex_t	mtx;

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
	compliance_args(argc, argv);
//-------------------------------------------------------------------------------------------------------------------
	// Initialisation des data.
	t_args          args;

	args = init(args);
//-------------------------------------------------------------------------------------------------------------------
	// Threads
	philosophers(&mtx, args);
/*	int             i;
	pthread monitor;

	i = 0;
	while (++i <= args->number_of_philosophers)
	{
		philo[i]->thread = i;
		if (pthread_create(&i, NULL,  , ))
			exit(1);
		philo[i].id = i;
		philo[i].life = ft_atoi(argv[2]);
		philo[i].dead = 0;
		philo[i].meal_number = 0;
		philo[i]->right_fork = TRUE;
		philo[i]->left_fork = FALSE;
		philo[i]->write_lock = NULL;
		philo[i]->dead_lock = NULL;
		philo[i]->meal_lock = NULL;
	}
	pthread_create(&monitor, NULL, **, *);
	i = 0;
	while (++i <= args->number_of_philosophers)
		pthread_join(philo[i], **);
*/
	// Routine
//	philo_routine();
	return (0);
}
