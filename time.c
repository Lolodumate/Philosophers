/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:38:02 by laroges           #+#    #+#             */
/*   Updated: 2024/02/15 16:26:36 by laroges          ###   ########.fr       */
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
/*		if (args->deaths > 0)
		{
			printf("\n****************************************time.c : args->deaths = %d\n\n", args->deaths);
			exit(1);
		}
*/		elapsed = get_time(args, US) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(usec / 2);
		else
		{
			while (get_time(args, US) - start < usec)
				;
		}
	}
}

void	update_death_time(t_philo *philo)
{
	philo->death_time = get_time(philo->args_ptr, US) + philo->args_ptr->time_to_die;
}
