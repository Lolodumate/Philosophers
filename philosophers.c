/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 20:38:17 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Ressources :
 *      https://www.youtube.com/watch?v=o_GbRujGCnM
 *      https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
 *      Differences entre threads et processus : https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2
 * 
 * - Contrairement aux processus parent/enfant (fork), les threads partagent les memes variables.
 * - N threads au sein d'un programme = un seul processus id (pid).
 *
 * Compiler avec le flag -lpthread
 * Instruction usleep(<millisecondes>) permet de temporiser un thread.
 * usleep : 1 seconde = 1000000 microsecondes
 *
 * Tuto : https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
 * Vizualizer : https://nafuka11.github.io/philosophers-visualizer/
 */
// pthread_mutex_t = PTHREAD_MUTEX_INITIALIZER;
// *************************************************************
// *************************************************************

// CFLAGS = -Wall -Werror -Wextra -g -pthread -fsanitize=thread

// *************************************************************
// *************************************************************
//

void	philosophers_dinner(t_args *args) // philosophers(&mtx, args)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (pthread_create(&args->t[i], NULL, &diner_routine, &args->philo_ptr[i]) != 0)
			exit_error(args, "Failure thread creation");
	}
	join_threads(args);
	destroy_mutex(args, args->number_of_philosophers);
}

void	join_threads(t_args *args)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (pthread_join(args->t[i], (void **) &args->philo_ptr[i]) != 0)
			exit_error(args, "Error pthread join");
	}
	printf("END JOIN\n");
}

// Thread routine avec boucle !dead
void	*diner_routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	ft_mutex(p->args_ptr, &p->args_ptr->mtx, LOCK);
	p->death_time = get_time(p->args_ptr, MS) + p->args_ptr->time_to_die;
	ft_mutex(p->args_ptr, &p->args_ptr->mtx, UNLOCK);
//	while (1)
	while (stop_routine(p->args_ptr) == FALSE)
	{
		if (ft_eat(p) == TRUE || stop_routine(p->args_ptr) == TRUE)
			return (p);
		if (ft_sleep(p) == TRUE || stop_routine(p->args_ptr) == TRUE)
			return (p);
		if (ft_think(p) == TRUE || stop_routine(p->args_ptr) == TRUE)
			return (p);
	}
	return (p);
}
