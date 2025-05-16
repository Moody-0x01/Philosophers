/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:47:51 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/15 15:09:15 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define BASE_10 "0123456789"
# define MAX_LONG 9223372036854775807

typedef enum e_philo_state
{
	NONE = 0,
	EATING,
	THINKING,
	SLEEPING,
	DONE_,
	FORK_TAKE,
	SCOUNT
}	t_philo_state;

typedef enum s_cl_state
{
	STILL_GOING,
	STOPPED
}	t_cl_state;

typedef enum e_philosopher_stats
{
	NUMBER_OF_PHILOSOPHERS=0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT, // [OPTIONAL] STAT
	STAT_COUNT
}	t_philosopher_stats;

typedef struct s_philo
{
	t_philo_state	state;
	pthread_mutex_t	philo_state_lock;
	pthread_mutex_t	philo_ts_lock;
	long			configuration[STAT_COUNT];
	size_t			id;
	size_t			lfork;
	size_t			rfork;
	long			last_meal_ts;
	long			meal_count;
}	t_philo;

typedef struct s_philo_cluster
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t	outlock;
	pthread_mutex_t	state_lock;
	t_cl_state		cluster_state;
	size_t			count;
	long			ts_start;
	int				init_success;
}	t_philo_cluster;

typedef enum e_result
{
	DONE = 0x0,
	SUCCESS,
	NAN,
	OVER_FLOW_DETECTED,
	RESULT_SIZE
}	t_result;

typedef struct s_num
{
	int						sign;
	const char				*base;
	long					*number;
}							t_num;

int				ft_isspace(int c);
size_t			ft_strlen(char *s);
t_result		ft_atol_base(const char *str, const char *base, long *where);
void			parse_stats(int ac, char **av, long out[STAT_COUNT]);
char			*t_stat_as_cstr(t_philosopher_stats r);
char			*t_result_as_cstr(t_result r);
void			*default_routine(void *index_ptr);
void			*thread_monitor(void *data);
int				cluster_init(long *stats);
void			cluster_free(void);
void			cluster_start_threads(void *f);
t_philo_cluster	*cluster_get(void);
size_t			left(size_t i);
size_t			right(size_t i);
long			get_timestamp(void);
void			sleep_(long ms);
pthread_mutex_t	*get_fork(size_t i);
void			release_forks(t_philo *target);
void			take_forks(t_philo *target);
int				simulation_ended(void);
void			simulation_stop(void);
void			*simulation_start(t_philo *target);
void			philo_kill(t_philo *target);
void			philo_sleep(t_philo *target);
void			philo_eat(t_philo *target);
void			philo_think(t_philo *target);
int				philo_check_hp(void);
int				philo_is_starved(t_philo *target);
int				should_sim_stop(void);
int				init_philosophers(t_philo_cluster *cluster, long *stats);
int				meal_threshhold_reached(t_philo *philo);
void			stats_copy(long out[STAT_COUNT], long in[STAT_COUNT]);
void			cluster_print_stats(void);
t_philo_state	get_philo_state(t_philo *target);
void			set_philo_state(t_philo *target, t_philo_state s);
void			log_action(t_philo *target, const char *action, t_philo_state new);
int				set_if(t_philo *target, t_philo_state s);
#endif // !PHILO_H
