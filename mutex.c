/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:42:08 by laroges           #+#    #+#             */
/*   Updated: 2024/03/02 17:45:16 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_mutex(args, &args->mtx[MONITOR], INIT);
	ft_mutex(args, &args->mtx[MEAL], INIT);
	ft_mutex(args, &args->mtx[WRITE], INIT);
	return (args);
}

void	*set_philo_mutex(t_philo *philo)
{
	ft_mutex(philo->args_ptr, &philo->mtx[MTX], INIT);
	return (philo);
}

void	destroy_mutex(t_args *args, int n)
{
	int		i;

	i = -1;
	if (!args)
		return ;
	i = -1;
	while (++i < n)
		ft_mutex(args, &args->forks[i], DESTROY);
	i = -1;
	while (++i < n)
		ft_mutex(args, &args->philo_ptr[i].mtx[MTX], DESTROY);
	ft_mutex(args, &args->mtx[MTX], DESTROY);
	ft_mutex(args, &args->mtx[MONITOR], DESTROY);
	ft_mutex(args, &args->mtx[MEAL], DESTROY);
	ft_mutex(args, &args->mtx[WRITE], DESTROY);
}
