/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:02:47 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/16 15:40:11 by lazmoud          ###   ########.fr       */
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
}

static bool	validate_stat(t_result res, char *program, char *arg, long out)
{
	if (res == NAN)
	{
		printf("`%s` is Not a number\n", arg);
		invalid_args(program, "Only numeric arguments are allowed\n");
		return (false);
	}
	if (res == OVER_FLOW_DETECTED || out > INT_MAX || out < INT_MIN)
	{
		printf("`%s` overflew\n", arg);
		invalid_args(program, "please use a reasonable number,"
			" which does not overflow an int type\n");
		return (false);
	}
	if (out < 0)
	{
		printf("`%s` is not a valid number\n", arg);
		invalid_args(program, "please use a positive number\n");
		return (false);
	}
	return (true);
}

bool	parse_stats(int ac, char **av, long out[STAT_COUNT])
{
	t_result		res;
	int				i;

	if ((ac - 1) < NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT)
	{
		invalid_args(av[0], "expected more arguments\n");
		return (false);
	}
	if ((ac - 1) > STAT_COUNT)
	{
		invalid_args(av[0], "expected less arguments\n");
		return (false);
	}
	if ((ac - 1) < STAT_COUNT)
		out[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT] = -1;
	i = 0;
	while (i + 1 < ac && i <= NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT)
	{
		res = ft_atol_base(av[i + 1], BASE_10, (out + i));
		if (!validate_stat(res, av[0], av[i + 1], out[i]))
			return (false);
		i++;
	}
	return (true);
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
