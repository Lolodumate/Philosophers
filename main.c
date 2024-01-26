/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:34:19 by laroges           #+#    #+#             */
/*   Updated: 2024/01/26 17:31:08 by laroges          ###   ########.fr       */
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
	args = init_args(argc, argv, args);
	philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!philo)
		exit(1);
	philosophers(args, philo);
	free(args);
	free(philo);
	return (0);
}
