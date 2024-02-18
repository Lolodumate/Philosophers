/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:43:17 by laroges           #+#    #+#             */
/*   Updated: 2024/02/13 16:49:02 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_end_of_diner(t_args *args)
{
	if (args->deaths > 0)
		return (TRUE);
	if (args->meals_complete >= args->number_of_philosophers)
		return (TRUE);
//	if (args->end_of_diner > 0)
//		return (TRUE);
	return (FALSE);
}

void	update_meals_complete(t_philo *philo)
{
	if (philo->meal_number >= philo->args_ptr->target_nb_meals/* && philo->args_ptr->target_nb_meals != 0*/)
	{
		philo->meal_complete = 1;
		philo->args_ptr->meals_complete++;
	}
}
