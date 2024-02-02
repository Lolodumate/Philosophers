/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:38:02 by laroges           #+#    #+#             */
/*   Updated: 2024/02/02 13:05:46 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
//	printf("%ld\n", tv.tv_usec);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}*/
/*
void	*ft_usleep(long requested_sleep_time)
{
	struct timeval		start;
	struct timeval		end;
	long				time;
	long				actual_sleep_time;

	time = get_time(MICROSECOND);
	gettimeofday(&start, NULL);
	while ((get_time(MICROSECOND) - time) < (long)requested_sleep_time)
	{
		usleep(requested_sleep_time);
	}
	gettimeofday(&end, NULL);
	actual_sleep_time = (end.tv_sec - start.tv_sec) * 100000 + (end.tv_usec - start.tv_usec);
	return ((void *)actual_sleep_time);
}*/

//*******************************************************************************************

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_error("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		exit_error("Wrong input to gettime");
	return (1337);
}

void	ft_usleep(long usec, t_args *args)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (args->deaths == 1)
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}
