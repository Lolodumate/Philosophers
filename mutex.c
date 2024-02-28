#include "philo.h"

int	mutex_init(t_args *args, pthread_mutex_t *mtx)
{
	int		i;

	i = -1;
	while (++i < args->nphilo)
		ft_mutex(args, &mtx[i], INIT);
	return (i);
}

int	mutex_destroy(t_args *args, pthread_mutex_t *mtx)
{
	int		i;

	i = -1;
	while (++i < args->nphilo)
		ft_mutex(args, &mtx[i], DESTROY);
	return (i);
}

void	*set_mutex(t_args *args)
{
	ft_mutex(args, &args->mtx[MTX], INIT);
	ft_mutex(args, &args->mtx[MASTER], INIT);
	ft_mutex(args, &args->mtx[MONITOR], INIT);
	ft_mutex(args, &args->mtx[MEAL], INIT);
	ft_mutex(args, &args->mtx[WRITE], INIT);
	return (args);
}

void	*set_philo_mutex(t_philo *philo)
{
	ft_mutex(philo->args_ptr, &philo->mtx[MTX], INIT);
	ft_mutex(philo->args_ptr, &philo->mtx[ROUTINE], INIT);
	return (philo);
}
