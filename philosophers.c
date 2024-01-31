/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:13:56 by laroges           #+#    #+#             */
/*   Updated: 2024/01/31 08:56:12 by laroges          ###   ########.fr       */
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
	unsigned int		i;
	pthread_t		t_meal;

	i = 0;
	if (args->number_of_times_each_philosopher_must_eat > 0)
	{
		if (pthread_create(&t_meal, NULL, &check_meals, &args) != 0)
		{
			printf("Failure thread creation\n");
			exit(1);
		}
	}
	while (i < args->number_of_philosophers)
	{
	//	printf("args->time_to_eat = %d\n", args->time_to_eat);
		if (pthread_create(&args->t[i], NULL, &routine, &args->philo_ptr[i]) != 0)
		{
			printf("Failure thread creation\n");
			exit(1);
		}
		i++;
		ft_usleep(10);
	}
	if (args->number_of_times_each_philosopher_must_eat > 0)
	{
		if (pthread_join(t_meal, NULL) != 0)
			exit(1);
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
	if (pthread_create(&p->thread, NULL, &check_philos, &p) != 0)
	{
		printf("Failure thread creation (routine)\n");
		ft_clean(p->args_ptr, philo);
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
void	*check_philos(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->is_dead == 0 && p->meal_complete == 0)
	{
		pthread_mutex_lock(&p->mtx);
// 1. Verifier que l'heure courante est inferieure a l'heure prevue de la mort du philosophe
		if (p->is_eating == 0 && (get_time() >= p->death_time))
		{
			print_countdown(p);
			printf("%d died\n", p->id);
			p->is_dead = 1;
		}
// 2. Verifier le nombre de repas pris et le cas echeant mettre a jour le status "meal_complete"
		pthread_mutex_unlock(&p->mtx);
	}
	return (NULL);
}

void	*check_meals(void *args)
{
	unsigned int		i;
	unsigned int		check_meals;
	t_args	*a;

	i = 0;
	check_meals = 0;
	a = (t_args *)args;
	pthread_mutex_lock(&a->mtx_check);
	while (check_meals < a->number_of_philosophers)
	{
		check_meals = 0;
		while (i < a->number_of_philosophers)
		{
			check_meals += a->philo_ptr[i].meal_complete;
			i++;
		}
		i = 0;
	}
	pthread_mutex_unlock(&a->mtx_check);
	return (NULL);
}
