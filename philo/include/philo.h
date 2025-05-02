#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define BASE_10 "0123456789"
# define MAX_LONG 9223372036854775807

typedef enum e_cluster_action
{
	CINIT,
	CGET,
	SPAWN_THREADS,
	CFREE,
}	t_cluster_action;

typedef enum e_state
{
	NONE = 0,
	EATING = 1 << 0,
	THINKING = 1 << 1,
	SLEEPING = 1 << 2,
} t_philo_state;

typedef struct s_philo
{
	t_philo_state	state;
	long			*configuration;
	size_t			id;
} t_philo;

typedef struct s_philo_cluster
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t	outlock;
	size_t			count;
}	t_philo_cluster;

typedef enum e_result
{
	DONE = 0x0,
	SUCCESS,
	NAN,
	OVER_FLOW_DETECTED,
	RESULT_SIZE
}	t_result;

typedef enum e_philosopher_stats {
	NUMBER_OF_PHILOSOPHERS=0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT, // [OPTIONAL] STAT
	STAT_COUNT
}	t_philosopher_stats;

typedef struct s_num
{
	int						sign;
	const char				*base;
	long					*number;
}							t_num;

int			ft_isspace(int c);
size_t		ft_strlen(char *s);
t_result	ft_atol_base(const char *str, const char *base, long *where);
void		parse_stats(int ac, char **av, long out[STAT_COUNT]);
char		*t_stat_as_cstr(t_philosopher_stats r);
char		*t_result_as_cstr(t_result r);

// THE CLUSTER INTERFACE
//
void			*default_routine(void *index_ptr);
void			cluster_init(long *stats);
void			cluster_free(void);
void			cluster_start_threads(void *f);
t_philo_cluster	*cluster_get(void);
#endif // !PHILO_H
