/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:02:47 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/10 18:14:30 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

static void	usage(const char *program)
{
	printf("usage: %s number_of_philosophers time_to_die "
		"time_to_eat time_to_sleep "
		"[number_of_times_each_philosopher_must_eat]\n", program);
}

static void	invalid_args(const char *program, const char *reason)
{
	printf("%s", reason);
	usage(program);
	exit(1);
}

void	parse_stats(int ac, char **av, long out[STAT_COUNT])
{
	t_result		res;
	int				i;

	if ((ac - 1) < NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT)
		invalid_args(av[0], "expected more arguments\n");
	if ((ac - 1) < STAT_COUNT)
		out[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT] = -1;
	i = 0;
	while (i + 1 < ac && i <= NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT)
	{
		res = ft_atol_base(av[i + 1], BASE_10, (out + i));
		if (res == NAN)
		{
			printf("`%s` is Not a number\n", av[i + 1]);
			invalid_args(av[0], "Only numeric arguments are allowed\n");
		}
		i++;
	}
}

void	stats_copy(long out[STAT_COUNT], long in[STAT_COUNT])
{
	int	i;

	i = 0;
	while (i < STAT_COUNT)
	{
		out[i] = in[i];
		i++;
	}
}

char	*t_result_as_cstr(t_result r)
{
	char	*rs[RESULT_SIZE];

	rs[DONE] = "DONE";
	rs[SUCCESS] = "SUCCESS";
	rs[NAN] = "NAN";
	rs[OVER_FLOW_DETECTED] = "OVER_FLOW_DETECTED";
	return (rs[r]);
}

char	*t_stat_as_cstr(t_philosopher_stats r)
{
	char	*rs[STAT_COUNT];

	rs[NUMBER_OF_PHILOSOPHERS] = "NUMBER_OF_PHILOSOPHERS";
	rs[TIME_TO_DIE] = "TIME_TO_DIE";
	rs[TIME_TO_EAT] = "TIME_TO_EAT";
	rs[TIME_TO_SLEEP] = "TIME_TO_SLEEP";
	rs[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT] = "NUMBER_OF_"
		"TIMES_EACH_PHILOSOPHER_MUST_EAT";
	return (rs[r]);
}
