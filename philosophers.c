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
 *
 * pthread_mutex_t = PTHREAD_MUTEX_INITIALIZER;
 *************************************************************
 *************************************************************
 * CFLAGS = -Wall -Werror -Wextra -g -pthread -fsanitize=thread
 *
 *************************************************************
 *************************************************************
 */

void	philosophers_dinner(t_args *args)
{
	thread_create_monitor(args->monitor_ptr);

	printf("philosophers_dinner : args->monitor_ptr = %p\n", args->monitor_ptr);
	if (threads_create(args) != 0)
		exit_error(args, "Error threads creation");

	monitor_threads_creation(args->monitor_ptr);

	// Attendre la fin du diner avant de lancer la fonction threads_join !!

	threads_join(args);
	destroy_mutex(args, args->number_of_philosophers);
	thread_join_monitor(args->monitor_ptr);
}

void	*dinner_routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	ft_mutex(p->args_ptr, &p->args_ptr->mtx[MTX], LOCK);
	p->death_time = p->args_ptr->monitor_ptr->time_start_dinner + p->args_ptr->time_to_die;
	ft_mutex(p->args_ptr, &p->args_ptr->mtx[MTX], UNLOCK);
	ft_mutex(p->args_ptr, &p->mtx[ROUTINE], LOCK);
	while (stop_routine(p->args_ptr) == FALSE)
	{
		if (ft_eat(p) == TRUE)
			break ;
		if (ft_sleep(p) == TRUE)
			break ;
		if (ft_think(p) == TRUE)
			break ;
	}
	ft_mutex(p->args_ptr, &p->mtx[MTX], LOCK);
	p->stop_routine = TRUE;
	ft_mutex(p->args_ptr, &p->mtx[MTX], UNLOCK);
	ft_mutex(p->args_ptr, &p->mtx[ROUTINE], UNLOCK);
	return (NULL);
}

void	solo_dinner(t_philo *philo)
{
	philo->start_time = get_time(philo->args_ptr, MS);
	philo->death_time = philo->args_ptr->monitor_ptr->time_start_dinner + philo->args_ptr->time_to_die;
	ft_write_task(philo->args_ptr, philo, FORK);
	usleep(philo->args_ptr->time_to_die * 1000);
	ft_write_task(philo->args_ptr, philo, DEAD);
}
