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
		printf("Number of arguments must be 5 or 6.\n");
		exit(0);
	}
	while (argv[j] && j <= argc)
	{
		strisdigit(argv[j]);
		j++;
	}
	compliance_values(argv);
}

void	compliance_values(char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		printf("Philosophers number must be >0 and <= 200.\n");
		exit(0);
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
	{
		printf("Arguments must be > 0.\n");
		exit(0);
	}
}
