#include <philo.h>

// TODO: process args
//		number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
//		1					   2           3           4              5

void	usage(const char *program)
{
	printf("usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", program);
}

void	invalid_args(const char *program, const char *reason)
{
	printf("%s", reason);
	usage(program);
	exit(1);
}

char	*t_result_as_cstr(t_result r)
{
	char *rs[RESULT_SIZE];

	rs[DONE] = "DONE";
	rs[SUCCESS] = "SUCCESS";
	rs[NAN] = "NAN";
	rs[OVER_FLOW_DETECTED] = "OVER_FLOW_DETECTED";
	return rs[r];
}

char	*t_stat_as_cstr(t_philosopher_stats r)
{
	char *rs[STAT_COUNT];

	rs[NUMBER_OF_PHILOSOPHERS] = "NUMBER_OF_PHILOSOPHERS";
	rs[TIME_TO_DIE] = "TIME_TO_DIE";
	rs[TIME_TO_EAT] = "TIME_TO_EAT";
	rs[TIME_TO_SLEEP] = "TIME_TO_SLEEP";
	rs[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT] = "NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT";
	return rs[r];
}
// NUMBER_OF_PHILOSOPHERS=1,
// TIME_TO_DIE,
// TIME_TO_EAT,
// TIME_TO_SLEEP,
// NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT, // [OPTIONAL] STAT
// TODO: Parse each number correctly
void	parse_stats(int ac, char **av, long out[STAT_COUNT])
{
	t_result		res;
	if ((ac - 1) < NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT) invalid_args(av[0], "expected more arguments\n");
;
	// if ((ac - 1) < STAT_COUNT) printf("Defaulted\n");
	
	for (int i = 0; i + 1 < ac && i <= NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT; ++i)
	{
		res = ft_atol_base(av[i + 1], BASE_10, (out + i));
		if (res == NAN)
		{
			printf("`%s` is Not a number\n", av[i + 1]);
			invalid_args(av[0], "Only numeric arguments are allowed\n");
		}
	}
}

int main(int ac, char **av)
{
	long		out[STAT_COUNT];
	parse_stats(ac, av, out);
	for (int i = 0; i + 0 < ac && i <= NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT; ++i)
		printf("%-41s | %s => %ld\n", t_stat_as_cstr(i), av[i + 1], out[i]);
	return (0);
}
