#include "philo.h"

int	mutex_init(t_args *args, pthread_mutex_t *mtx)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
		ft_mutex(args, &mtx[i], INIT);
	return (i);
}

int	mutex_destroy(t_args *args, pthread_mutex_t *mtx)
{
	int		i;

	i = -1;
	while (++i < args->number_of_philosophers)
		ft_mutex(args, &mtx[i], DESTROY);
	return (i);
}
