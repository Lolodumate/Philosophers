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
		exit_error(args, "Gettimeofday failed");
	if (time_code == MS)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == US)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		exit_error(args, "Wrong input to get_time");
	return (0);
}

void	ft_usleep(long usec, t_args *args)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(args, US);
	while (get_time(args, US) - start < usec)
	{
		if (args->end_of_diner == TRUE)
			exit(0);
		elapsed = get_time(args, US) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (get_time(args, US) - start < usec)
				;
		}
	}
}

long	get_timestamp(t_philo *philo)
{
	int             timestamp;

	timestamp = get_time(philo->args_ptr, MS) - philo->start_time;
	return (timestamp);
}

void	update_death_time(t_args *args, t_philo *philo)
{
	philo->death_time = get_time(args, MS) + args->time_to_die;
}
