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
	pthread_t	master;
	pthread_mutex_t	master_mtx;

	ft_mutex(args, &master_mtx, INIT);
	if (pthread_create(&master, NULL, &threads_create, (void **) args))
		exit_error(args, "'Error Master thread creation");
	ft_mutex(args, &master_mtx, LOCK);
	
	threads_create(args);

	mutex_unlock_forks(args, args->number_of_philosophers);

	ft_mutex(args, &master_mtx, UNLOCK);
	if (pthread_join(master, (void **) args))
		exit_error(args, "Error Naster thread join)");
//	mutex_unlock_forks(args, args->number_of_philosophers);
	destroy_mutex(args, args->number_of_philosophers);
	ft_mutex(args, &master_mtx, DESTROY);
	ft_clean(args);
}

// Thread routine avec boucle !dead
void	*diner_routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	ft_mutex(p->args_ptr, &p->args_ptr->mtx, LOCK);
	p->death_time = get_time(p->args_ptr, MS) + p->args_ptr->time_to_die;
	ft_mutex(p->args_ptr, &p->args_ptr->mtx, UNLOCK);
	while (stop_routine(p->args_ptr) == FALSE)
	{
		if (ft_eat(p) == TRUE)
			return (NULL);
		if (ft_sleep(p) == TRUE)
			return (NULL);
		if (ft_think(p) == TRUE)
			return (NULL);
	}
	return (NULL);
}
