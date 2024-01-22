/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/01/22 15:34:49 by laroges          ###   ########.fr       */
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

void	create_philo_threads(t_args args) // philosophers(&mtx, args)
{
	int		i;

	i = 0;
	args.start_time = get_time();
	pthread_mutex_init(&args.mtx, NULL);
	while (i++ < args.philo_ptr->number_of_philosophers)
	{
		if (pthread_create(&args.philo_ptr[i]->thread, NULL, &routine, philo_ptr[i]) != 0)
		{
			printf("Failure : creation thread\n");
			exit(1);
		}
		args.philo[i].is_eating = 0;
		args.philo[i].is_dead = 0;
		args.philo[i].meal_complete = 0;
		args.philo[i].meal_number = 0;
		args.philo[i].start_time = get_time();
		args.philo[i].death_time = args.philo_ptr[i]->start_time + args.time_to_die;
		/* Si le philo[i] a un voisin a sa droite philo[i - 1] alors :
		 * - La fourchette droite de philo[i] correspond a la fourchette gauche de philo[i - 1].
		 * - Donc la fourchette gauche de philo[i- 1] est un pointeur vers la fourchette droite de philo[i].
		 */
		if (args.philo_ptr[i - 1])
			args.philo_ptr[i - 1].left_fork = &args.philo_ptr[i].right_fork;
		pthread_mutex_init(&args.philo_ptr->mtx, NULL); // 1 philosophe = 1 thread
		printf("Thread %d has started\n", i);
	}
	create_forks_ptr(args);
}

// Thread routine avec boucle !dead
void	routine(t_philo *philo)
{
	if (pthread_create(&philo, NULL, &checker, philo) != 0)
	{
		printf("Erreur creation thread routine\n");
		exit(1);
	}
	while (!philo.dead)
	{
		pthread_mutex_lock(&philo->mtx);
		if (philo->number_of_dead == philo->number_of_philosophers)
			philo.dead = 1;
		pthread_mutex_unlock(&philo->mtx);
	}
	if (pthread_join(&philo, NULL) != 0)
		exit(1);
}

// Verifier l'etat si les philosophes sont toujours en vie
void	checker(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx);
	while (!philo->is_dead)
	{
		
		// 1. Verifier que l'heure courante est inferieure a l'heure prevue de la mort du philosophe
		if (get_time >= args.philo_ptr->death_time)
			ft_exit(args, args.philo_ptr->id, "died");

		// 2. Verifier le nombre de repas pris et le cas echeant mettre a jour le status "meal_complete"
		if (philo->meal_number >= philo->args->number_of_times_philosopher_must_eat)	
		{
			pthread_mutex_lock(&philo->mtx);
			philo->meal_complete = 1;
			pthread_mutex_unlock(&philo->mtx);
		}
	}
	pthread_mutex_unlock(&philo->mtx);
}

void	join_philo_thread(t_args args)
{
	int		i;

	i = 0;
	while (i++ < args.philo->number_of_philosophers)
	{
		if (pthread_join(philo[i], NULL) != 0)
			ft_exit(args,args.philo_ptr->id, "has finished execution");
	}
	pthread_mutex_destroy(&args.mtx);
}

void	philosophers(t_args args)
{
	create_philo_threads(t_args args);
	join_philo_threads(t_args args);
}
