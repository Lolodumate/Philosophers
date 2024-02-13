/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:28:04 by laroges           #+#    #+#             */
/*   Updated: 2024/02/13 10:18:13 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_args *args, t_philo *philo)
{
	int		i;

	i = 0;
	if (!args)
		exit(1);
	if (philo)
	{
		while (&philo[i] && i < args->number_of_philosophers)
		{
			pthread_mutex_destroy(&philo[i].args_ptr->forks[i]);
			pthread_mutex_destroy(&philo[i].mtx);
	//		free(philo[i].right_fork);
	//		free(philo[i].left_fork);
			i++;
		}
		free(philo);
	}
	pthread_mutex_destroy(&args->mtx_check);
	pthread_mutex_destroy(&args->mtx);
	pthread_mutex_destroy(&args->mtx_printf);
	if (args->forks)
		free(args->forks);
	if (args->t)
		free(args->t);
	if (args->philo_ptr)
		free(args->philo_ptr);
	free(args);
}

void	ft_exit(t_args *args, t_philo *philo, int philo_id)
{
	printf("%ld %u\n", get_time(MICROSECOND), philo_id);
	ft_clean(args, philo);
/*	pthread_mutex_destroy(&philo->mtx);
	pthread_mutex_destroy(&args->philo_ptr[i].mtx);
*/
	exit(1);
}

void	exit_error(const char *error)
{
	printf("%s\n", error);
	exit(1);
}
