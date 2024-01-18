#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/* Ressources :
 *	https://www.youtube.com/watch?v=o_GbRujGCnM
 *	https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
 *	Differences entre threads et processus : https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2
 * 
 * - Contrairement aux processus parent/enfant (fork), les threads partagent les memes variables.
 * - N threads au seins d'un programme = un seul processus id (pid).
 *
 * Compiler avec le flag -lpthread
 * Instruction sleep(<duree>) permet de temporiser un thread.
 *
 * Tuto : https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
 * usleep : 1 seconde = 1000000 microsecondes
 * 
 */
// pthread_mutex_t = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t	mutex;

void	*func1(void *arg)
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
}

void	test_thread(void)
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
}

int	main(int argc, char **argv)
{
	/* Verification de la conformite des arguments :
	 * 	1. number_of_philosophers (doit etre > 0 et <= 200)
	 * 	2. time_to_die (doit etre > 0)
	 * 	3. time_to_eat (doit etre > 0)
	 * 	4. time_to_sleep (doit etre > 0)
	 * 	5. number_of_times_each_philosophers_must_eat (optionnal) (doit etre >= 0) 
	 *
	 * Verifier :
	 * 	- Le nombre d'arguments.
	 * 	- Le contenu des arguments (ils ne doivent comporter que les caracteres numeriques.
	 */

	if (argc == 5 || argc == 6)
	{
		compliance_args(char **argv);
	}
	else
		exit(1);

	/* Initialisation des data :
	 * 	- Creation d'un tableau *t_philo
	 * 
	 */
	t_args		args;
	t_philo		philo[200];

	args->number_of_philosopers = argv[1];
	args->time_to_die = argv[2];
	args->time_to_eat = argv[3];
	args->time_to_sleep = argv[4];
	if (argc == 6)
		args->number_of_times_each_philosophers_must_eat = argv[5];

	int		i;
	pthread	monitor;

	i = 0;
	while (++i <= 200)
	{
		philo[i]->thread = i;
		if (pthread_create(&i, NULL, /**/ , /**/))
			exit(1);
		philo[i].id = i;
		philo[i].life = ft_atoi(argv[2]);
		philo[i]->dead = NULL;
		philo[i].meal_number = 0;
		philo[i]->right_fork = TRUE;
		philo[i]->left_fork = FALSE;
		philo[i]->write_lock = NULL;
		philo[i]->dead_lock = NULL;
		philo[i]->meal_lock = NULL;
	}
	pthread_create(&monitor, NULL, /**/, /**/);
	i = 0;
	while (++i <= 200)
		pthread_join(philo[i], /**/);
	
	
	// 
	test_thread();
	return (0);
}
