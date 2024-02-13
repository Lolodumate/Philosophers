/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/02/13 14:01:50 by laroges          ###   ########.fr       */
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
	pthread_t		t_meal;

	i = -1;
	if (pthread_create(&t_meal, NULL, &check_ending, args) != 0)
	{
		printf("Failure thread creation\n");
		exit(1); // Liberer la memoire
	}
	while (++i < args->number_of_philosophers)
	{
		if (pthread_create(&args->t[i], NULL, &routine, &args->philo_ptr[i]) != 0)
			exit_error("Failure thread creation");
	}
	args->time_start_diner = get_time(MILLISECOND);
	i = -1;
	while (++i < args->number_of_philosophers)
	{
		args->philo_ptr[i].death_time = args->time_start_diner + args->time_to_die;
	}
	join_threads(args, t_meal);
}

void	join_threads(t_args *args, pthread_t t_meal)
{
	int		i;

	i = -1;
	if (args->target_nb_meals > 0)
	{
		if (pthread_join(t_meal, NULL) != 0)
			exit(1); // Liberer la memoire
	}
	while (++i < args->number_of_philosophers)
	{
		if (pthread_join(args->t[i], NULL) != 0)
			exit(1); // Liberer la memoire
	}
}

// Thread routine avec boucle !dead
void	*routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	p->death_time = get_time(MILLISECOND) + p->args_ptr->time_to_die;
	if (pthread_create(&p->thread, NULL, &check_philos, p) != 0)
	{
		printf("Failure thread creation (routine)\n");
		ft_clean(p->args_ptr, philo);
		exit(1);
	}
	while (p->is_dead == 0 && p->args_ptr->end_of_diner == 0)
	{
		ft_eat(p);
		ft_think(p);
	}
	if (pthread_join(p->thread, NULL) != 0)
		exit(1);
	return (NULL);
}

// Verifier l'etat si les philosophes sont toujours en vie
void	*check_philos(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->args_ptr->end_of_diner == 0 && p->is_dead == 0)
	{
		pthread_mutex_lock(&p->mtx);
		if (p->is_eating == 0 && (get_time(MILLISECOND) >= p->death_time))
		{
			p->is_dead = 1;
			p->args_ptr->end_of_diner = 1;
			p->args_ptr->deaths++;
			ft_output(philo, " died", 1);
		}
		pthread_mutex_unlock(&p->mtx);
	}
	return (NULL);
}

void	*check_ending(void *args)
{
	t_args	*a;

	a = (t_args *)args;
	while (a->end_of_diner == 0)
	{
		pthread_mutex_lock(&a->mtx_check);
		if (a->deaths > 0)
			a->end_of_diner = 1;
		if (a->meals_complete >= a->number_of_philosophers)
		{
//			printf("meals complete - args->end_of_diner = 1\n");
			a->end_of_diner = 1;
		}
		pthread_mutex_unlock(&a->mtx_check);
	}
	return (NULL);
}
