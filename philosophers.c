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

void	create_threads(t_args *args) // philosophers(&mtx, args)
{
	int		i;

	i = -1;
	if (pthread_create(&args->t_end, NULL, &check_ending, args) != 0)
		exit_error(args, "Failure thread creation");
	while (++i < args->number_of_philosophers)
	{
		if (pthread_create(&args->t[i], NULL, &diner_routine, &args->philo_ptr[i]) != 0)
			exit_error(args, "Failure thread creation");
	}
/*	while (check_mutex_forks(args) == FALSE)
		usleep(100);
	while (check_mutex_philo(args) == FALSE)
		usleep(100);
*/	join_threads(args);
	destroy_mutex(args, args->number_of_philosophers);
}

void	join_threads(t_args *args)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = args->philo_ptr;
	while (++i < args->number_of_philosophers)
	{
		if (pthread_join(args->t[i], (void **) &philo) != 0)
			exit_error(args, "Error pthread join");
		if (pthread_join(args->philo_ptr[i].thread, (void **) &philo) != 0)
			exit_error(args, "Error pthread join");
	}
	if (pthread_join(args->t_end, (void **) &args) != 0)
			exit_error(args, "Error pthread join");
	printf("END JOIN\n");
}

// Thread routine avec boucle !dead
void	*diner_routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	ft_mutex(p->args_ptr, &p->mtx, LOCK);
	p->death_time = get_time(p->args_ptr, MS) + p->args_ptr->time_to_die;
	ft_mutex(p->args_ptr, &p->mtx, UNLOCK);
	if (pthread_create(&p->thread, NULL, &check_philos, p) != 0)
		exit_error(p->args_ptr, "Error pthread_create");
	while (p->is_dead == FALSE && p->args_ptr->end_of_diner == FALSE)
	{
		if (ft_eat(p) == FALSE || p->args_ptr->end_of_diner == TRUE)
			return (p);
		if (ft_sleep(p) == FALSE || p->args_ptr->end_of_diner == TRUE)
			return (p);
		if (ft_think(p) == FALSE || p->args_ptr->end_of_diner == TRUE)
			return (p);
	}
	return (p);
}

void	*check_philos(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->is_dead == FALSE && p->args_ptr->end_of_diner == FALSE)
	{
		if (philo_is_dead(p->args_ptr, p) == TRUE)
		{
			ft_mutex(p->args_ptr, &p->args_ptr->mtx, LOCK);
			ft_write_task(p->args_ptr, p, DEAD);
			p->args_ptr->end_of_diner = TRUE;
			ft_mutex(p->args_ptr, &p->args_ptr->mtx, UNLOCK);
		}
	}
	return (p);
}

void	*check_ending(void *args)
{
	t_args	*a;

	a = (t_args *)args;
	while (a->end_of_diner == FALSE)
	{
		if (all_meals_complete(a) == TRUE)
		{
			ft_mutex(a, &a->mtx, LOCK);
			a->end_of_diner = TRUE;
			ft_mutex(a, &a->mtx, UNLOCK);
		}
	}
	return (a);
}
