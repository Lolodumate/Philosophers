/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:16:28 by laroges           #+#    #+#             */
/*   Updated: 2024/02/15 20:46:37 by laroges          ###   ########.fr       */
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

typedef enum e_mtx
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}		t_mtx;

typedef enum e_tasks
{
	DEAD,
	FORK,
	EATING,
	SLEEPING,
	THINKING
}		t_tasks;

typedef enum e_time_code
{
	MS,
	US
}		t_time_code;

typedef struct s_philo
{
	t_args		*args_ptr;
	pthread_t		thread;
	int					id;
	int					is_eating;
	int					is_dead;
	int					meal_complete;
	int					meal_number;
	long					start_time;
	long					death_time;
	pthread_mutex_t		*main_fork;
	pthread_mutex_t		*aux_fork;
	pthread_mutex_t		mtx;
}		t_philo;

typedef struct s_args
{
	pthread_t		t_end;
	pthread_t		*t;
	pthread_mutex_t		mtx_check_ending;
	pthread_mutex_t		mtx;
	pthread_mutex_t		mtx_write;
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
	t_philo		*philo_ptr;
}               t_args;

// main.c
void	diner(t_args *args);

// utils.c
int			ft_atoi(char *str);
void	strisdigit(char *str);
void	compliance_args(int argc, char **argv);
void	ft_output(t_philo *philo, const char *task, int color);
void	ft_mutex_write(pthread_mutex_t *mtx, t_args *args, t_philo *philo, int task);

// ft_utils.c
void	ft_mutex_protect(t_args *args, int mtx_return);
void	ft_mutex(t_args *args, pthread_mutex_t *mtx, int m);
void	ft_write_task(t_philo *philo, int task);
int	ft_mutex_increment_int(pthread_mutex_t *mtx, t_args *args, int data);

// mem_alloc.c
pthread_mutex_t	*ft_mem_alloc_forks(t_args *args, pthread_mutex_t *forks);
t_philo	*ft_mem_alloc_philo_ptr(t_args *args, t_philo *philo, int philo_nb);
pthread_t	*ft_mem_alloc_threads(t_args *args, pthread_t *t, int philo_nb);
t_philo *ft_mem_alloc_philo(t_args *args, t_philo *philo);

// init.c
void	ft_mem_alloc(char **argv, t_args *args, t_philo *philo);
t_args	*init_args(int argc, char **argv, t_args *args);
void	init_philo(t_args *args, t_philo *philo, int index);
t_philo	*set_philos_and_forks(t_args *args);

// ft_args.c
int			ft_end_of_diner(t_args *args);
void	update_meals_complete(t_philo *philo);

// time.c
long				get_time(t_args *args, t_time_code time_code);
void	ft_usleep(long usec, t_args *args);
void	update_death_time(t_args *args, t_philo *philo);

// clean.c
void	exit_error(t_args *args, const char *error);
//void	ft_exit(t_args *args);
void	ft_clean(t_args *args);
void	ft_destroy_mutex(t_args *args, t_philo *philo);

// philosophers.c
void	*diner_routine(void *philo);
void	*check_philos(void *args);
void	*check_ending(void *args);
void	create_threads(t_args *args);
void	join_threads(t_args *args, pthread_t t_meal);


void	ft_output(t_philo *philo, const char *task, int color);

// tasks.c
void	ft_eat(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_pick_forks(t_args *args, t_philo *philo);
void	ft_drop_forks(t_args *args, t_philo *philo, int i);

#endif
