/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:22:45 by laroges           #+#    #+#             */
/*   Updated: 2024/02/05 13:31:29 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(const char *error)
{
	printf("%s\n", error);
	exit(1);
}

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
		exit_error("Arguments must be < INT_MAX");
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

void	ft_output(t_philo *philo, char *task, int color)
{
	long	time;

	time = get_time(MILLISECOND) - (philo->start_time / 1000);
	printf("%-6ld \033[1;3%dm%d %s\033[0m\n", time, color, philo->id, task);
}
