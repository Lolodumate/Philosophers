/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:16:28 by laroges           #+#    #+#             */
/*   Updated: 2024/03/05 19:49:51 by laroges          ###   ########.fr       */
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

typedef struct s_args	t_args;

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef enum e_oddeven
{
	EVEN,
	ODD
}		t_oddeven;

typedef enum e_mtx
{
	MTX,
	MONITOR,
	MEAL,
	WRITE,
	FORKS,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}		t_mtx;

typedef enum e_tasks
{
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK
}		t_tasks;

typedef enum e_time_code
{
	MS,
	US
}		t_time_code;

typedef struct s_philo
{
	pthread_mutex_t			*main_fork;
	pthread_mutex_t			*aux_fork;
	pthread_mutex_t			*mtx;
	int						id;
	int						stop_routine;
	int						mtx_is_unlocked;
	int						meal_complete;
	int						meal_number;
	long					start_time;
	long					last_meal;
	long					death_time;
	t_args					*args_ptr;
}		t_philo;

typedef struct s_args
{
	pthread_t				*t;
	pthread_mutex_t			*mtx;
	pthread_mutex_t			*forks;
	int						threads_created;
	int						go;
	int						nb_of_locked_forks;
	int						nphilo;
	int						meals_complete;
	int						end_of_diner;
	int						*meals;
	int						target_nb_meals;
	int						solo_dinner;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					time_start;
	t_philo					*philo_ptr;
}	t_args;

// utils.c
int			ft_atoi(char *str);
int			strisdigit(char *str);
int			odd_or_even(int n);

// ft_utils.c
void		ft_mutex_protect(t_args *args, int mtx_return);
void		ft_mutex(t_args *args, pthread_mutex_t *mtx, int m);
void		ft_write_task(t_args *args, t_philo *philo, int task);
void		ft_output(t_philo *philo, const char *task);

// mem_alloc.c
int			*mem_alloc_tab(t_args *args, int n);
void		*mem_alloc_mtx(t_args *args, pthread_mutex_t *mtx, int n);
t_args		*mem_alloc_args(t_args *args);
t_philo		*mem_alloc_philo_ptr(t_args *args, t_philo *philo, int n);
pthread_t	*mem_alloc_threads(t_args *args, pthread_t *t, int philo_nb);

// init.c
t_args		*init_args(int argc, char **argv, t_args *args);
t_philo		*init_philos(t_args *args, int n);
t_args		*init_forks(t_args *args, pthread_mutex_t *forks, int n);
void		init_tab(int *tab, int size);
void		*set_data(t_args *args, int argc, char **argv);

// threads.c
int			threads_create(t_args *args);
int			wait_threads_creation_to_finish(t_args *args, t_philo *philo);
void		set_start_time_of_dinner(t_args *args, t_philo *philo);
int			threads_join(void *args);

// mutex.c
int			mutex_init(t_args *args, pthread_mutex_t *mtx);
int			mutex_destroy(t_args *args, pthread_mutex_t *mtx);
void		*set_mutex(t_args *args);
void		*set_philo_mutex(t_philo *philo);
void		destroy_mutex(t_args *args, int n);

// bool.c
int			philo_is_dead(t_args *args, t_philo *philo, int i);
int			should_even_philos_die(t_args *args, t_philo *p);
int			all_meals_complete(t_args *args);
int			check_all_philos_finished_routine(t_args *args);
int			stop_routine(t_args *args);

// ft_args.c
int			compliance_args(int argc, char **argv);
int			compliance_values(char **argv);

// time.c
long		get_time(t_args *args, t_time_code time_code);
void		ft_usleep(long usec, t_args *args, int i);
long		get_timestamp(t_philo *philo);
void		update_death_time(t_args *args, t_philo *philo);
void		thinking_time(t_args *a, t_philo *p);

// clean.c
void		ft_clean(t_args *args);
void		free_mutex(t_args *args, pthread_mutex_t *mtx);
void		exit_error(t_args *args, const char *error);
void		free_philo_ptr(t_args *args);

// philosophers.c
void		philosophers_dinner(t_args *args);
void		*dinner(void *philo);
void		solo_dinner(t_philo *p);

// tasks.c
int			ft_eat(t_philo *p);
int			ft_sleep(t_philo *p);
int			ft_think(t_philo *p);
void		ft_pick_forks(t_args *args, t_philo *p);
void		ft_drop_forks(t_args *args, t_philo *p);

#endif
