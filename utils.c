/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:22:45 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 20:12:24 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
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
	{
		printf("Arguments must be < INT_MAX");
		exit(0);
	}
	return ((int)res);
}

void	strisdigit(char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		exit(0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i])
	{
		printf("Only digits are allowed");
		exit(0);
	}
}

void	compliance_args(int argc, char **argv)
{
	int		j;

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

long	get_timestamp(t_philo *philo)
{
	int		timestamp;

	timestamp = get_time(philo->args_ptr, MS) - philo->start_time;
	return (timestamp);
}

void	ft_output(t_philo *philo, const char *task, int color)
{
	printf("%-6ld \033[1;3%dm%d %s\033[0m\n", get_timestamp(philo), color, philo->id, task);
}

int	odd_or_even(int n)
{
	if (n % 2 == 0)
		return (EVEN);
	return (ODD);
}
