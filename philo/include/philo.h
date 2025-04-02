#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define BASE_10 "0123456789"
# define MAX_LONG 9223372036854775807

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
#endif // !PHILO_H
