/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:16:28 by laroges           #+#    #+#             */
/*   Updated: 2024/01/22 16:48:42 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
// https://github.com/TommyJD93/Philosophers

typedef struct	s_args	t_args;

typedef enum s_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef struct s_philo
{
	t_args		*args;
	pthread_t						thread;
	unsigned int					id;
	int					is_eating;
	int					is_dead;
	int					meal_complete;
	unsigned int					meal_number;
	long					start_time;
	long					death_time;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		mtx;
}		t_philo;
/*
typedef struct s_forks
{
	pthread_mutex_t		*rf;
	pthread_mutex_t		*lf;
}	t_forks;*/

typedef struct s_args
{
	pthread_mutex_t		mtx;
	unsigned int				number_of_philosophers;
	unsigned int				number_of_dead;
	unsigned int				time_to_die;
	unsigned int				time_to_eat;
	unsigned int				time_to_sleep;
	unsigned int				number_of_times_each_philosopher_must_eat;
	long		time_start;
	t_philo		*philo_ptr;
//	t_forks		*forks_ptr;
}               t_args;

long				get_time(void);
unsigned int			ft_atoi(char *str);
void	strisdigit(char *str);
void	compliance_args(int argc, char **argv);
void	check_nbphilo(unsigned int n);
void	check_forks(); // Verifie la disponibilite des fourchettes.
void	take_forks(); // Prend les fourchettes apres avoir verifie leur disponibilite.
void	take_back_forks(); // Remet les fourchettes en place une fois le repas termine.
void	routine(t_philo *philo);
void	create_philo_threads(t_args args);
void	create_forks_ptr(t_args args);
void	join_philo_threads(t_philo *philo);
void	philosophers(t_args args);
void	seconde(unsigned int n);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_exit(struct s_args *args, unsigned int philo_id, char *exit_message);
t_args	init_args(int argc, char **argv, t_args args);


#endif
