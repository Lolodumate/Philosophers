/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:38:02 by laroges           #+#    #+#             */
/*   Updated: 2024/01/25 14:20:04 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
//	printf("%ld\n", tv.tv_usec);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	*ft_usleep(long requested_sleep_time)
{
	struct timeval	start_time;
	struct timeval	end_time;
	long	actual_sleep_time;

	gettimeofday(&start_time, NULL);
	usleep(requested_sleep_time);
	gettimeofday(&end_time, NULL);
	actual_sleep_time = (end_time.tv_sec - start_time.tv_sec) * 100000 + (end_time.tv_usec - start_time.tv_usec);
	return ((void *)actual_sleep_time);
}
