#include "philo.h"

t_monitor	*init_monitor(t_args *args, t_monitor *m)
{
	m = malloc(sizeof(t_monitor));
	if (!m)
	{
		printf("Error malloc monitor.");
		exit(1);
	}
	m->t = malloc(sizeof(pthread_t));
	if (!m->t)
	{
		printf("Error malloc monitor thread.");
		free(m);
		exit(1);
	}
	m->start_dinner_signal = 0;
	m->threads_created = 0;
	m->time_start_dinner = 0;
	m->args_ptr = args;
	m->threads_created = 0;
	args->monitor_ptr = m;
	return (m);
}

int	thread_create_monitor(t_monitor *monitor)
{
	if (pthread_create(monitor->t, NULL, &monitor_threads_creation, monitor) != 0)
		exit_error(monitor->args_ptr, "Error creation thread monitor");
	return (0);
}

int	thread_join_monitor(void *monitor)
{
	t_monitor	*m;

	m = (t_monitor *)monitor;
	if (pthread_join(*m->t, NULL) != 0)
		exit_error(m->args_ptr, "Error join thread monitor");
	m->start_dinner_signal = 1;
	return (0);
}

void	*monitor_threads_creation(void *monitor)
{
	t_monitor	*m;

	m = (t_monitor *)monitor;
	ft_mutex(m->args_ptr, &m->args_ptr->mtx[MTX], LOCK);
	m->time_start_dinner = get_time(m->args_ptr, MS);
	ft_mutex(m->args_ptr, &m->args_ptr->mtx[MTX], UNLOCK);
	return (NULL);
}
