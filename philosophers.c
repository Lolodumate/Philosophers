/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/02/19 15:20:23 by laroges          ###   ########.fr       */
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
	join_threads(args);
}

void	join_threads(t_args *args)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (pthread_join(args->t[i], NULL) != 0)
			exit_error(args, "Error pthread join");
	}
	i = -1;
	while (++i < args->number_of_philosophers)
	{
		if (pthread_join(args->philo_ptr[i].thread, NULL) != 0)
			exit_error(args, "Error pthread join");
	}
	if (pthread_join(args->t_end, NULL) != 0)
		exit_error(args, "Error pthread_join");
}

// Thread routine avec boucle !dead
void	*diner_routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	ft_mutex(p->args_ptr, &p->mtx, LOCK);
	p->death_time =  get_time(p->args_ptr, MS) + p->args_ptr->time_to_die;
	ft_mutex(p->args_ptr, &p->mtx, UNLOCK);
	if (pthread_create(&p->thread, NULL, &check_philos, p) != 0)
		exit_error(p->args_ptr, "Error pthread_create");
	while (stop_routine(philo) == FALSE)
	{
		/*	1. Chaque fonction eat, sleep et think doit renvoyer un booleen et mettre a jour args->end_of_diner.
		 *	2. Ajouter la condition fct == TRUE dans la boucle.
		 */
		ft_eat(p);
		if (stop_routine(philo) == TRUE)
			break ;
		ft_think(p);
	}
	return (NULL);
}

// Verifier l'etat si les philosophes sont toujours en vie
void	*check_philos(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->args_ptr->end_of_diner == FALSE && p->is_dead == FALSE)
	{
		if (p->is_eating == FALSE && (get_time(p->args_ptr, MS) >= p->death_time))
		{
			ft_write_task(p, DEAD);
			ft_mutex(p->args_ptr, &p->mtx, LOCK);
			p->args_ptr->end_of_diner = TRUE;
			p->is_dead = TRUE;
			p->args_ptr->deaths++;
			ft_mutex(p->args_ptr, &p->mtx, UNLOCK);
		}
	}
//	printf("Check ****** %ld philo->id[%d] is dead [%d]\n", get_time(p->args_ptr, MS), p->id, p->is_dead);
	return (NULL);
}

void	*check_ending(void *args)
{
	t_args	*a;

	a = (t_args *)args;
	while (a->end_of_diner == FALSE)
	{
		ft_mutex(a, &a->mtx_check_ending, LOCK);
		if (a->deaths > 0)
			a->end_of_diner = TRUE;
		else if (all_meals_complete(a))
			a->end_of_diner = TRUE;
		ft_mutex(a, &a->mtx_check_ending, UNLOCK);
	}
	return (NULL);
}
