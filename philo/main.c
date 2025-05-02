#include <philo.h>

// TODO: process args
//		number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
//		1					   2           3           4              5

// NUMBER_OF_PHILOSOPHERS=1,
// TIME_TO_DIE,
// TIME_TO_EAT,
// TIME_TO_SLEEP,
// NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT, // [OPTIONAL] STAT
// TODO: Parse each number correctly
// int pthread_mutex_init(pthread_mutex_t *mutex,
//                        const pthread_mutexattr_t *mutexattr);
// int pthread_mutex_lock(pthread_mutex_t *mutex);
// int pthread_mutex_trylock(pthread_mutex_t *mutex);
// int pthread_mutex_unlock(pthread_mutex_t *mutex);
// int pthread_mutex_destroy(pthread_mutex_t *mutex);
// 5 5
// 2 2 | 1
//

int main(int ac, char **av)
{
	long		out[STAT_COUNT];
	parse_stats(ac, av, out);

	cluster_init(out);
	cluster_start_threads(default_routine);
	cluster_free();
	return (0);
}
