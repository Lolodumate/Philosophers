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

void	compliance_args(int argc, char **argv)
{
	int             j;

	j = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Number of arguments must be 5 or 6");
		exit(0);
	}
	while (argv[j] && j <= argc)
	{
		strisdigit(argv[j]);
		j++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		printf("Philosophers number must be >0 and <= 200");
		exit(0);
	}
}

/*void	update_meals_complete(t_philo *philo)
{
	if (philo->meal_complete == TRUE || philo->args_ptr->target_nb_meals < 0)
		return ;
	if (philo->meal_number >= philo->args_ptr->target_nb_meals)
	{
		philo->meal_complete = TRUE;
		printf("update_meals_complete : philo->args_ptr->meals_complete = %d\n", philo->args_ptr->meals_complete);
		printf("update_meals_complete : philo->args_ptr->meals[%d] = %d\n", philo->id - 1, philo->args_ptr->meals[philo->id - 1]);
	}
}*/
