/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:38:02 by laroges           #+#    #+#             */
/*   Updated: 2024/03/05 19:34:52 by laroges          ###   ########.fr       */
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
		usleep(3000);
	}
}

long	get_timestamp(t_philo *philo)
{
	int		timestamp;

	timestamp = get_time(philo->args_ptr, MS) - philo->args_ptr->time_start;
	return (timestamp);
}

void	thinking_time(t_args *a, t_philo *p)
{
	long		t;

	t = 5000;
	if (a->time_to_eat > a->time_to_sleep)
		ft_usleep(a->time_to_eat - a->time_to_sleep + t, a, p->id - 1);
	else
		ft_usleep(5000, a, p->id - 1);
}
