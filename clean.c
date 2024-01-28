/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:28:04 by laroges           #+#    #+#             */
/*   Updated: 2024/01/28 15:10:00 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_args *args, t_philo *philo)
{
	unsigned int		i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[i].mtx);
		pthread_mutex_destroy(&philo[i].right_fork);
		pthread_mutex_destroy(philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&args->mtx);
	pthread_mutex_destroy(&args->mtx_printf);
	free(args->t);
	free(args->philo_ptr);
	free(args);
	free(philo->left_fork);
	free(philo);
}

void	ft_exit(struct s_args *args, t_philo *philo, unsigned int philo_id, char *exit_message)
{
	printf("%ld %u %s\n", get_time(), philo_id, exit_message);
	ft_clean(args, philo);
/*	pthread_mutex_destroy(&args->mtx);
	pthread_mutex_destroy(&args->mtx_printf);
	pthread_mutex_destroy(&philo->mtx);
	pthread_mutex_destroy(philo->right_fork);
	pthread_mutex_destroy(&args->philo_ptr[i].mtx);
	free(philo);
	free(args);
*/
	exit(1);
}
