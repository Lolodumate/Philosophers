/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:22:45 by laroges           #+#    #+#             */
/*   Updated: 2024/02/02 13:22:33 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(const char *error)
{
	printf("%s\n", error);
	exit(1);
}

unsigned int	ft_atoi(char *str)
{
	unsigned int		i;
	long			res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		exit_error("Arguments must be < INT_MAX");
	return (res);
}

void	strisdigit(char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		exit(0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] && str[i] == '-')
		exit_error("Negatives are not allowed");
	if (str[i])
		exit_error("Only digits are allowed");
}

void	compliance_args(int argc, char **argv)
{
	int		j;

	j = 1;
	if (argc < 5 || argc > 6)
		exit_error("Number of arguments must be 5 or 6");
	while (argv[j] && j <= argc)
	{
		strisdigit(argv[j]);
		j++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		exit_error("Philosophers number must be > 0 and <= 200");
}

void	ft_output(t_philo *philo, char *task)
{
	long	time;

	time = get_time(MILLISECOND) - philo->start_time;
	printf("%ld %d %s\n", time, philo->id, task);	
}
