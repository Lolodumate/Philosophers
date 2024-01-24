/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/01/24 14:48:50 by laroges          ###   ########.fr       */
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

void	create_philo_threads(t_args *args) // philosophers(&mtx, args)
{
	unsigned int		i;

	i = 0;
	args->philo_ptr->start_time = get_time();
	pthread_mutex_init(&args->mtx, NULL);
	while (i++ < args->number_of_philosophers)
	{
		if (pthread_create(&args->philo_ptr[i].thread, NULL, &routine, &args->philo_ptr[i]) != 0)
		{
			printf("Failure thread creation\n");
			exit(1);
		}
		args->philo_ptr[i].is_eating = 0;
		args->philo_ptr[i].is_dead = 0;
		args->philo_ptr[i].meal_complete = 0;
		args->philo_ptr[i].meal_number = 0;
		args->philo_ptr[i].start_time = get_time();
		args->philo_ptr[i].death_time = args->philo_ptr[i].start_time + args->time_to_die;
		/* Si le philo[i] a un voisin a sa droite philo[i - 1] alors :
		 * - La fourchette droite de philo[i] correspond a la fourchette gauche de philo[i - 1].
		 * - Donc la fourchette gauche de philo[i- 1] est un pointeur vers la fourchette droite de philo[i].
		 */
		if (&args->philo_ptr[i - 1])
			args->philo_ptr[i - 1].left_fork = &args->philo_ptr[i].right_fork;
		pthread_mutex_init(&args->philo_ptr->mtx, NULL); // 1 philosophe = 1 thread
		printf("Thread %d has started\n", i);
	}
}

// Thread routine avec boucle !dead
void	*routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	if (pthread_create(&p->thread, NULL, &checker, p->args) != 0)
	{
		printf("Erreur creation thread routine\n");
		exit(1);
	}
	pthread_mutex_lock(&p->mtx);
	while (!p->is_dead)
	{
		if (p->args->number_of_dead == p->args->number_of_philosophers)
			p->is_dead = 1;
	}
	pthread_mutex_unlock(&p->mtx);
	if (pthread_join(p->thread, NULL) != 0)
		exit(1);
	return (p);
}

// Verifier l'etat si les philosophes sont toujours en vie
void	*checker(void *args)
{
	t_args	*data;

	data = (t_args *)args;
	pthread_mutex_lock(&data->mtx);
	while (!data->philo_ptr->is_dead)
	{
		
		// 1. Verifier que l'heure courante est inferieure a l'heure prevue de la mort du philosophe
		if (get_time() >= data->philo_ptr->death_time)
			ft_exit(data, &data->philo_ptr, data->philo_ptr->id, "died");

		// 2. Verifier le nombre de repas pris et le cas echeant mettre a jour le status "meal_complete"
		if (data->philo_ptr->meal_number >= data->number_of_times_each_philosopher_must_eat)	
		{
			pthread_mutex_lock(&data->mtx);
			data->philo_ptr->meal_complete = 1;
			pthread_mutex_unlock(&data->mtx);
		}
	}
	pthread_mutex_unlock(&data->mtx);
	return (NULL);
}

void	join_philo_threads(t_philo *philo)
{
	unsigned int		i;

	i = 0;
	while (i++ < philo->args->number_of_philosophers)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			ft_exit(philo->args, &philo, philo->id, "has finished execution");
	}
	pthread_mutex_destroy(&philo->args->mtx);
}

void	philosophers(t_args *args)
{
	create_philo_threads(args);
	join_philo_threads(args->philo_ptr);
}
