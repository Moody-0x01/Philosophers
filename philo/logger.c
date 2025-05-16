/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:54:24 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/16 15:40:26 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	log_action(t_philo *target, const char *action, t_philo_state new)
{
	t_philo_cluster	*cluster;

	cluster = cluster_get();
	pthread_mutex_lock(&cluster->outlock);
	if (new == FORK_TAKE)
	{
		if (!simulation_ended())
			printf("%ld %zu %s\n",
				(get_timestamp() - cluster->ts_start), target->id, action);
	}
	else if (set_if(target, new))
	{
		printf("%ld %zu %s\n",
			(get_timestamp() - cluster->ts_start), target->id, action);
		if (new == NONE)
			simulation_stop();
	}
	pthread_mutex_unlock(&cluster->outlock);
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

char	*str_state(t_philo_state r)
{
	char	*rs[SCOUNT];

	rs[NONE] = "Bro is Doing nothing";
	rs[EATING] = "Bro is EATING";
	rs[THINKING] = "Bro is THINKING";
	rs[SLEEPING] = "Bro is SLEEPING";
	rs[DONE_] = "Bro is DONE_";
	rs[FORK_TAKE] = "Bro is Taking a fork";
	return (rs[r]);
}

void	cluster_print_stats(void)
{
	t_philo_cluster	*cluster;
	size_t			i;

	cluster = cluster_get();
	i = 0;
	while (i < cluster->count)
	{
		printf("Id: %zu\n", (cluster->philos + i)->id);
		printf("Latest state: %s\n", str_state((cluster->philos + i)->state));
		printf("Forks: L => %zu R => %zu\n",
			(cluster->philos + i)->lfork, (cluster->philos + i)->rfork);
		printf("Meal count: %zu\n", (cluster->philos + i)->meal_count);
	}
}
