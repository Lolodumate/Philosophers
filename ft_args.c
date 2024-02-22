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
	}
}
/*
int	check_all_meals_complete(t_args *args)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	if (!args)
		exit(EXIT_FAILURE);
	while (++i < args->number_of_philosophers)
		n += args->meals[i];
	if (n == args->number_of_philosophers * args->time_to_eat)
		return (TRUE);
	return (FALSE);
}*/
