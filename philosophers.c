#include "philo.h"

/* Ressources :
 *	https://www.youtube.com/watch?v=o_GbRujGCnM
 *	https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
 *	Differences entre threads et processus : https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2
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

/*void	*func1(void *arg)
{
	for(int	i = 0; i < 100; i++)
	{
		pthread_mutex_lock(&mutex);
		printf("\033[91m%s\033[0m\n", (char *)arg);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(arg);
}

void	*func2(void *arg)
{
	for(int	i = 0; i < 100; i++)
	{
		pthread_mutex_lock(&mutex);
		printf("\033[95m%s\033[0m\n", (char *)arg);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(arg);
}*/

/*void	test_thread(void *) // Mettre le mutex (&mtx) en parametre d'entree
{
	char	*s1, *s2;

	pthread_t	p1;
	pthread_t	p2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&p1, NULL, &func1, "Hello 1") != 0)
		exit(1);
	if (pthread_create(&p2, NULL, &func2, "Hello 2") != 0)
		exit(1);
	pthread_join(p1, (void **)&s1);
	pthread_join(p2, (void **)&s2);
	pthread_mutex_destroy(&mutex);
	printf("%s %s\n", s1, s2);
}*/

void	philosophers(void *mtx, t_args args) // philosophers(&mtx, args)
{
	int		i;
	int		*p;

	i = 0;
	pthread_mutex_init(&mtx, NULL)

//	1. Creation loop pour la creation des threads (1 thread = 1 philosophe)
	while (++i <= args.philo->number_of_philosophers)
	{
		p = malloc(sizeof(int)); // p sera libere dans la fonction &routine
		if (p == NULL)
		{
			printf("Erreur allocation dynamique\n");
			exit(EXIT_FAILURE);
		}
		if (pthread_create(args.(&philo[i]), NULL, &philo_routine, p) != 0)
		{
			printf("Failure : creation thread\n");
			exit(1);
		}
		printf("Thread %d has started\n", i);<function>
	}
	i = 0;

//	2. Creation loop pour les join
	while (++i <= args.philo->number_of_philosophers)
	{
		if (pthread_join(philo[i], NULL) != 0)
			exit(1);
		printf("Thread %d has finished execution\n");
	}
	pthread_mutex_destroy(&mtx);
}

void	philo_routine(void *mtx, void *arg)
{
	while (!philo.dead)
	{
		ft_eat(&mtx, args, philo);
		ft_sleep(&mtx, args, philo);
		ft_think(&mtx, args, philo);
	}
	free(arg);
}
