/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/01/21 11:15:52 by laroges          ###   ########.fr       */
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

void	philosophers(void *mtx, t_args args) // philosophers(&mtx, args)
{
	int		i;

	i = 0;

//      1. Creation loop pour la creation des threads (1 thread = 1 philosophe)
	while (++i <= args.philo_ptr->number_of_philosophers)
	{
		if (pthread_create(args.&i(philo[i]->thread), NULL, &routine, philo[i]) != 0)
		{
			printf("Failure : creation thread\n");
			exit(1);
		}
		args.philo[i]->is_eating = 0;
		args.philo[i]->dead = 0;
		args.philo[i]->meal_number = 0;
		printf("Thread %d has started\n", i);
	}
	i = 0;

//      2. Creation loop pour les join
	while (++i <= args.philo->number_of_philosophers)
	{
		if (pthread_join(philo[i], NULL) != 0)
			exit(1);
		printf("Thread %d has finished execution\n");
	}
	pthread_mutex_destroy(&mtx);
}

void	routine(t_philo *philo)
{
	while (!philo.dead)
	{
		pthread_mutex_lock(&philo, NULL);

		pthread_mutex_unlock(&philo, NULL);
	}
}
