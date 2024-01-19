/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:16:28 by laroges           #+#    #+#             */
/*   Updated: 2024/01/19 16:51:49 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

// https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2

typedef enum	s_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef struct	s_philo
{
	pthread_t		thread;
	unsigned int		id;
	int			life;
	int			dead;
	unsigned int		meal_number;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fort;
	pthread_mutex_t *write_lock;
	pthread_mutex_t *dead_lock;
	pthread_mutex_t *meal_lock;
}		t_philo;

typedef struct	s_args
{
	unsigned int		number_of_philosophers;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		number_of_times_each_philosopher_must_eat;
	t_philo		*philo;
}               t_args;

// Verification de la conformite des arguments
unsigned int			ft_atoi(char *str);
void	strisdigit(char *str);
void	compliance_args(int argc, char **argv);
void	check_forks(); // Verifie la disponibilite des fourchettes.
void	check_nbphilo(unsigned int n);
void	take_forks(); // Prend les fourchettes apres avoir verifie leur disponibilite.
void	take_back_forks(); // Remet les fourchettes en place une fois le repas termine.
void	philo_routine(t_philo philo, int id);
void	monitoring();
void	seconde(unsigned int n);
t_args	*ft_eat(t_args args);
t_args	*ft_sleep(t_args args);
t_args	*ft_think(t_args args);
t_args	*philo_is_dead(t_args args);
t_args	init(t_args args);

#endif

