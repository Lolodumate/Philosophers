/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:22:45 by laroges           #+#    #+#             */
/*   Updated: 2024/01/31 12:15:13 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoi(char *str)
{
	unsigned int		i;
	unsigned int		res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
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
	{
		printf("Les nombres negatifs ne sont pas autorises.\n");
		exit(1);
	}
	if (str[i])
	{
		printf("Les arguments contiennent des caracteres non numeriques.\n");
		exit(1);
	}
}

void	check_nbphilo(unsigned int n)
{
	if (n < 1 || n > 200)
	{
		printf("Le nombre de philosophes doit etre compris entre 1 et 200.\n");
		exit(1);
	}
}

int	compliance_args(int argc, char **argv)
{
	int		j;

	j = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Le nombre d'arguments saisi est incorrect.\n");
		return (FALSE);
	}
	while (argv[j] && j <= argc)
	{
		strisdigit(argv[j]);
		j++;
	}
	check_nbphilo(ft_atoi(argv[1]));
	return (TRUE);
}

void	ft_output(t_philo *philo, char *task)
{
	u_int64_t	time;

	time = get_time() - philo->start_time;
	printf("%ld %d %s\n", time, philo->id, task);	
}
