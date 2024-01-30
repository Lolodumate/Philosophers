/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:38:02 by laroges           #+#    #+#             */
/*   Updated: 2024/01/30 13:34:40 by laroges          ###   ########.fr       */
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
void	print_countdown(t_philo *philo)
{
	u_int64_t	cd;

	cd = get_time() - philo->start_time;
	pthread_mutex_lock(&philo->args_ptr->mtx_printf);
	printf("%ld", cd);
	pthread_mutex_unlock(&philo->args_ptr->mtx_printf);
}

void	*ft_usleep(long requested_sleep_time)
{
	struct timeval		start;
	struct timeval		end;
	long				actual_sleep_time;

	gettimeofday(&start, NULL);
	usleep(requested_sleep_time);
	gettimeofday(&end, NULL);
	actual_sleep_time = (end.tv_sec - start.tv_sec) * 100000 + (end.tv_usec - start.tv_usec);
	return ((void *)actual_sleep_time);
}
