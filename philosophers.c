/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/01/27 15:59:33 by laroges          ###   ########.fr       */
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
	i = 0;

	while (i < args->number_of_philosophers)
	{
		philo[i] = init_philo(args, philo, i);
		args->philo_ptr[i].args_ptr = args;
		printf("args->time_to_eat = %d\n", args->time_to_eat);
		if (pthread_create(&args->t[i], NULL, &routine, &args->philo_ptr[i]) != 0)
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
			philo[i - 1].left_fork = philo[i].right_fork;
			printf("philo[%d].left_fork = &philo[%d].right_fork\n", i - 1, i);
		}
		if ((i + 1) == args->number_of_philosophers)
		{
			philo[i].left_fork = philo[0].right_fork;
			printf("philo[%d].left_fork = &philo[%d].right_fork\n", i, 0);
		}
		i++;
//		usleep(10);
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_join(args->t[i], NULL) != 0)
			exit(1);
		i++;
	}
}

// Thread routine avec boucle !dead
void	*routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	p->death_time = get_time() + p->args_ptr->time_to_die;
	if (pthread_create(&p->thread, NULL, &checker, &p) != 0)
	{
		printf("Erreur creation thread routine\n");
		exit(1);
	}
	while (p->args_ptr->death == 0)
	{
		ft_eat(p);
		ft_think(p);
		if (get_time() >= p->death_time && p->is_eating == 0)
			p->args_ptr->death = 1;
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
	while (a->death == 0)
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
	return (NULL);
}

void	philosophers(t_args *args, t_philo *philo)
{
	create_philo_threads(args, philo);
}
