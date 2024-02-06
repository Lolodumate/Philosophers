/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:16:28 by laroges           #+#    #+#             */
/*   Updated: 2024/02/06 11:02:31 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

// https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
// https://github.com/TommyJD93/Philosophers

typedef struct	s_args	t_args;

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}		t_time_code;

typedef struct s_philo
{
	t_args		*args_ptr; // malloc
	pthread_t		thread;
	int					id;
	int					is_eating;
	int					is_dead;
	int					meal_complete;
	int					meal_number;
	long					start_time;
	long					death_time;
	pthread_mutex_t		*right_fork; // malloc
	pthread_mutex_t		*left_fork; // pointeur
	pthread_mutex_t		mtx;
}		t_philo;

typedef struct s_args
{
	pthread_t		*t; // malloc
	pthread_mutex_t		mtx_check;
	pthread_mutex_t		mtx;
	pthread_mutex_t		mtx_printf;
	pthread_mutex_t		*forks;
	int				number_of_philosophers;
	int				meals_complete;
	int				deaths;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int				target_nb_meals;
	long		time_start_diner;
	int		end_of_diner;
	t_philo		*philo_ptr; // malloc
}               t_args;

long				get_time(t_time_code time_code);
int			ft_atoi(char *str);
void	exit_error(const char *error);
void	strisdigit(char *str);
void	compliance_args(int argc, char **argv);
void	*routine(void *philo);
void	*check_philos(void *args);
void	*check_meals(void *args);
void	create_threads(t_args *args);
void	philosophers(t_args *args);
void	ft_usleep(long usec, t_args *args);
void	ft_pick_forks(t_philo *philo, int i);
void	ft_drop_forks(t_philo *philo, int i);
void	ft_output(t_philo *philo, char *task, int color);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_clean(t_args *args, t_philo *philo);
t_args	*init_args(int argc, char **argv, t_args *args);
t_philo	*init_philo(t_args *args, t_philo *philo, int index);
t_philo	*set_philos(t_args *args, t_philo *philo);
void	init_forks(t_args *args, t_philo *philo);

#endif
