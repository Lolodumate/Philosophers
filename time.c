/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:38:02 by laroges           #+#    #+#             */
/*   Updated: 2024/02/13 13:24:03 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_error("Gettimeofday failed");
	if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		exit_error("Wrong input to gettime");
	return (0);
}

void	ft_usleep(long usec/*, t_args *args*/)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
/*		if (args->deaths > 0)
		{
			printf("\n****************************************time.c : args->deaths = %d\n\n", args->deaths);
			exit(1);
		}
*/		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(usec / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	update_death_time(t_philo *philo)
{
	philo->death_time = get_time(MILLISECOND) + philo->args_ptr->time_to_die;
}
