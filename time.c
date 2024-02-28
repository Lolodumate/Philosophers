/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:38:02 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 16:32:50 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_args *args, t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_error(args, "gettimeofday failed");
	if (time_code == MS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == US)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		exit_error(args, "Error get_time");
	return (0);
}

void	ft_usleep(long time, t_args *args, int i)
{
	long	start;

	start = get_time(args, US);
	while (get_time(args, US) - start < time)
	{
		if (philo_is_dead(args, args->philo_ptr, i) == TRUE)
			break ;
		usleep(10);
	}
}

long	get_timestamp(t_philo *philo)
{
	int             timestamp;

	timestamp = get_time(philo->args_ptr, MS) - philo->args_ptr->time_start_dinner;
	return (timestamp);
}
