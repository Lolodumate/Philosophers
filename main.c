/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:34:19 by laroges           #+#    #+#             */
/*   Updated: 2024/03/02 16:48:36 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Verification de la conformite des arguments :
 *
 *      1. nphilo (doit etre > 0 et <= 200)
 *      2. time_to_die (doit etre > 0)
 *      3. time_to_eat (doit etre > 0)
 *      4. time_to_sleep (doit etre > 0)
 *      5. number_of_times_each_philosophers_must_eat doit etre >= 0) 
 *
 * Verifier :
 *      - Le nombre d'arguments.
 *      - Le contenu des arguments (que les caracteres numeriques).
 *
 *      -pthread -fsanitize=thread
 *
*/

int	main(int argc, char **argv)
{
	t_args		*args;

	args = NULL;
	if (compliance_args(argc, argv) == TRUE)
	{
		args = set_data(args, argc, argv);
		args = set_mutex(args);
		args->time_start = get_time(args, MS);
		if (args->nphilo > 1)
			philosophers_dinner(args);
		else if (args->nphilo == 1)
		{
			solo_dinner(&args->philo_ptr[0]);
			destroy_mutex(args, args->nphilo);
		}
		ft_clean(args);
	}
	return (0);
}
