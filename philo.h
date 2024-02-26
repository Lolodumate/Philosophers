/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:16:28 by laroges           #+#    #+#             */
/*   Updated: 2024/02/20 19:21:07 by laroges          ###   ########.fr       */
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

typedef enum	e_oddeven
{
	EVEN,
	ODD
}		t_oddeven;

typedef enum e_mtx
{
	PHILO_MTX,
	ARGS_MTX,
	MTX_WRITE,
	FORKS,
	ALL_MTX_LOCKED,
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
	t_args		*args_ptr;
	int					id;
	int					stop_routine;
	int					mtx_is_unlocked;
//	int					is_dead;
	int					meal_complete;
	int					meal_number;
	int					nb_of_fork_to_drop;
	long					start_time;
	long					last_meal_time;
	long					death_time;
	pthread_mutex_t		*main_fork;
	pthread_mutex_t		*aux_fork;
	pthread_mutex_t		mtx;
	pthread_mutex_t		mtx_routine;
}		t_philo;

typedef struct s_args
{
	pthread_t		*t;
	pthread_mutex_t		master;
	pthread_mutex_t		monitor;
	pthread_mutex_t		mtx;
	pthread_mutex_t		mtx_meal;
	pthread_mutex_t		mtx_write;
	pthread_mutex_t		*forks;
	int				*join_threads_monitor;
	int				nb_of_locked_forks;
//	int				*mtx_forks;
//	int				*mtx_philo;
//	int				*mtx_args;
	int				number_of_philosophers;
	int				meals_complete;
	int				is_dead;
	int				*meals;
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
void	ft_output(t_philo *philo, const char *task, int color);
int	odd_or_even(int n);

// ft_utils.c
void	ft_mutex_protect(t_args *args, int mtx_return);
int	mtx_tab_update(t_args *args, int i, pthread_mutex_t *mtx, int m);
void	ft_mutex(t_args *args, pthread_mutex_t *mtx, int m);
void	ft_write_task(t_args *args, t_philo *philo, int task);
void	ft_output(t_philo *philo, const char *task, int color);

// mem_alloc.c
t_args		*mem_alloc_args(t_args *args);
pthread_mutex_t	*mem_alloc_forks(t_args *args, pthread_mutex_t *forks);
t_philo		*mem_alloc_philo_ptr(t_args *args, t_philo *philo, int n);
pthread_t	*mem_alloc_threads(t_args *args, pthread_t *t, int philo_nb);
int	*mem_alloc_tab(t_args *args, int n);

// init.c
t_args		*init_args(int argc, char **argv, t_args *args);
t_philo		*init_philos(t_args *args, int n);
t_args		*init_forks(t_args *args, pthread_mutex_t *forks, int n);
void	init_tab(int *tab, int size);

// threads.c
void	*threads_create(void *args);
void	threads_join(void *args);

// mutex.c
int	mutex_init(t_args *args, pthread_mutex_t *mtx);
int	mutex_destroy(t_args *args, pthread_mutex_t *mtx);

// bool.c
int	philo_is_dead(t_args *args, t_philo *philo, int i);
int	all_meals_complete(t_args *args);
int	all_philo_are_alive(t_args *args);
int	check_all_philos_finished_routine(t_args *args, t_philo *philo);
int	stop_routine(t_args *args);

// ft_args.c
void	compliance_args(int argc, char **argv);
void	update_meals_complete(t_philo *philo);

// time.c
long				get_time(t_args *args, t_time_code time_code);
void	ft_usleep(long usec, t_args *args, int i);
long	get_timestamp(t_philo *philo);
void	update_death_time(t_args *args, t_philo *philo);

// clean.c
void	exit_error(t_args *args, const char *error);
void	ft_clean(t_args *args);
void	mutex_unlock_forks(t_args *args, int n);
void	destroy_mutex(t_args *args, int n);

// philosophers.c
void		philosophers_dinner(t_args *args);
void		*diner_routine(void *philo);

// handle_mutex.c
int	*mem_alloc_mtx_forks(t_args *args);
int	*mem_alloc_mtx(t_args *args, int n);
int	check_mutex_forks(t_args *args);
int	check_mutex_philo(t_args *args);

// tasks.c
int	ft_eat(t_philo *philo);
int	ft_sleep(t_philo *philo);
int	ft_think(t_philo *philo);
void	ft_pick_forks(t_args *args, t_philo *philo);
void	ft_drop_forks(t_args *args, t_philo *philo);

#endif
