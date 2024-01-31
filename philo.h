/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:16:28 by laroges           #+#    #+#             */
/*   Updated: 2024/01/31 12:49:27 by laroges          ###   ########.fr       */
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
	t_args		*args_ptr; // malloc
	pthread_t		thread;
	int					id;
	int					is_eating;
	int					is_dead;
	unsigned int					meal_complete;
	unsigned int					meal_number;
	unsigned long					start_time;
	unsigned long					death_time;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		left_fork; // Pointeur vers la fourchette du philosophe de gauche.
	pthread_mutex_t		mtx;
}		t_philo;

typedef struct s_args
{
	pthread_t		*t; // malloc
	pthread_mutex_t		mtx_check;
	pthread_mutex_t		mtx;
	pthread_mutex_t		mtx_printf;
	unsigned int				number_of_philosophers;
	unsigned int				meals_complete;
	unsigned int				deaths;
	unsigned int				time_to_die;
	unsigned int				time_to_eat;
	unsigned int				time_to_sleep;
	unsigned int				number_of_times_each_philosopher_must_eat;
	long		time_start;
	t_philo		*philo_ptr; // malloc
}               t_args;

u_int64_t			get_time(void);
unsigned int			ft_atoi(char *str);
void	strisdigit(char *str);
int	compliance_args(int argc, char **argv);
void	check_nbphilo(unsigned int n);
void	*routine(void *philo);
void	*check_philos(void *args);
void	*check_ending(void *args);
void	create_forks(t_args *args);
void	create_threads(t_args *args);
void	philosophers(t_args *args);
void	*ft_usleep(u_int64_t requested_sleep_time);
void	ft_pick_forks(t_philo *philo);
void	ft_output(t_philo *philo, char *task);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_clean(t_args *args, t_philo *philo);
void	ft_exit(struct s_args *args, t_philo *philo, unsigned int philo_id);
t_args	*init_args(int argc, char **argv, t_args *args);
t_philo	*init_philo(t_args *args, t_philo *philo, int index);
t_philo	*set_philos(t_args *args, t_philo *philo);

#endif
