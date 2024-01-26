/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/01/26 18:17:44 by laroges          ###   ########.fr       */
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
 * 
 */
// pthread_mutex_t = PTHREAD_MUTEX_INITIALIZER;

void	create_philo_threads(t_args *args, t_philo *philo) // philosophers(&mtx, args)
{
	unsigned int		i;
	pthread_t	*t;
	i = 0;

	pthread_mutex_init(&args->mtx, NULL);
	while (i < args->number_of_philosophers)
	{
		args->philo_ptr[i] = philo[i];
		philo[i] = init_philo(args, philo, i);
		t = &philo[i].thread;
		if (pthread_create(t, NULL, routine, philo[i]) != 0)
		{
			printf("Failure thread creation\n");
			exit(1);
		}
/* Si le philo[i] a un voisin a sa droite philo[i - 1] alors :
 * - La fourchette droite de philo[i] correspond a la fourchette gauche de philo[i - 1].
 * - Donc la fourchette gauche de philo[i - 1] est un pointeur vers la fourchette droite de philo[i].
 */
		pthread_mutex_init(&philo[i].mtx, NULL); // 1 philosophe = 1 thread
		printf("Thread %d has started\n", i);
		if (i > 0)
		{
			philo[i - 1].left_fork = &philo[i].right_fork;
			printf("philo[%d].left_fork = &philo[%d].right_fork\n", i - 1, i);
		}
		i++;
		if (i == args->number_of_philosophers)
		{
			philo[i - 1].left_fork = &philo[0].right_fork;
			printf("philo[%d].left_fork = &philo[%d].right_fork\n", i - 1, 0);
		}
	}
}

// Thread routine avec boucle !dead
void	*routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	if (pthread_create(&p->thread, NULL, &checker, p->args_ptr) != 0)
	{
		printf("Erreur creation thread routine\n");
		exit(1);
	}
	while (p->is_dead == 0)
	{
		pthread_mutex_lock(&p->mtx);
		ft_eat(p);
		ft_think(p);
		//if (p->args_ptr->number_of_dead == p->args_ptr->number_of_philosophers)
		if (get_time() >= p->death_time && p->is_eating == 0)
			p->is_dead = 1;
		p->args_ptr->number_of_dead++;
		pthread_mutex_unlock(&p->mtx);
	}
	if (pthread_join(p->thread, NULL) != 0)
		exit(1);
	return (NULL);
}

// Verifier l'etat si les philosophes sont toujours en vie
void	*checker(void *args)
{
	t_args	*a;

	a = (t_args *)args;
	pthread_mutex_lock(&a->mtx);
	//while (a->philo_ptr->is_dead == 0)
	while (a->number_of_dead < a->number_of_philosophers)
	{
// 1. Verifier que l'heure courante est inferieure a l'heure prevue de la mort du philosophe
		if (get_time() >= a->philo_ptr->death_time)
			ft_exit(a, a->philo_ptr, a->philo_ptr->id, "died");
// 2. Verifier le nombre de repas pris et le cas echeant mettre a jour le status "meal_complete"
		if (a->philo_ptr->meal_number >= a->number_of_times_each_philosopher_must_eat)	
		{
			pthread_mutex_lock(&a->mtx);
			a->philo_ptr->meal_complete = 1;
			pthread_mutex_unlock(&a->mtx);
		}
	}
	pthread_mutex_unlock(&a->mtx);
	return (NULL);
}

void	join_philo_threads(t_philo *philo)
{
	unsigned int		i;

	i = 0;
	while (i++ < philo->args_ptr->number_of_philosophers)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			ft_exit(philo->args_ptr, philo, philo->id, "has finished execution");
	}
	pthread_mutex_destroy(&philo->args_ptr->mtx);
}

void	philosophers(t_args *args, t_philo *philo)
{
	create_philo_threads(args, philo);
	join_philo_threads(args->philo_ptr);
}
