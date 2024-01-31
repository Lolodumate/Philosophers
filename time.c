/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:38:02 by laroges           #+#    #+#             */
/*   Updated: 2024/01/31 12:17:52 by laroges          ###   ########.fr       */
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

void	*ft_usleep(u_int64_t requested_sleep_time)
{
	struct timeval		start;
	struct timeval		end;
	u_int64_t				time;
	u_int64_t				actual_sleep_time;

	time = get_time();
	gettimeofday(&start, NULL);
	while ((get_time() - time) < requested_sleep_time)
	{
		usleep(requested_sleep_time);
	}
	gettimeofday(&end, NULL);
	actual_sleep_time = (end.tv_sec - start.tv_sec) * 100000 + (end.tv_usec - start.tv_usec);
	return ((void *)actual_sleep_time);
}
