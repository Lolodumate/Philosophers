/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:43:17 by laroges           #+#    #+#             */
/*   Updated: 2024/02/19 14:00:01 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meals_complete(t_philo *philo)
{
	if (philo->meal_complete == TRUE || philo->args_ptr->target_nb_meals < 0)
		return ;
	if (philo->meal_number >= philo->args_ptr->target_nb_meals)
	{
		philo->meal_complete = TRUE;
		philo->args_ptr->meals_complete++;
		printf("update_meals_comple : philo->args_ptr->meals_complete = %d\n", philo->args_ptr->meals_complete);
	}
}
