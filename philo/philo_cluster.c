/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cluster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:44 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/10 18:53:31 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

t_philo_cluster	*cluster_get(void)
{
	static t_philo_cluster	cluster;

	if (!cluster.init_success)
		memset(&cluster, 0, sizeof(cluster));
	return (&cluster);
}

int	cluster_init(long *stats)
{
	t_philo_cluster	*cluster;
	size_t			count;

	cluster = cluster_get();
	cluster->count = 0;
	count = stats[NUMBER_OF_PHILOSOPHERS];
	cluster->philos = malloc(sizeof(*cluster->philos) * count);
	if (!cluster->philos)
		return (0);
	cluster->forks = malloc(sizeof(*cluster->forks) * count);
	if (!cluster->forks)
	{
		cluster_free();
		return (cluster->init_success);
	}
	cluster->threads = malloc(sizeof(*cluster->threads) * (count + 1));
	if (!cluster->threads)
	{
		cluster_free();
		return (cluster->init_success);
	}
	if (!init_philosophers(cluster, stats))
		return (cluster->init_success);
	cluster->cluster_state = STILL_GOING;
	if (pthread_mutex_init(&cluster->outlock, NULL) != 0)
	{
		cluster_free();
		return (cluster->init_success);
	}
	if (pthread_mutex_init(&cluster->state_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&cluster->outlock);
		cluster_free();
		return (cluster->init_success);
	}
	cluster->init_success = 1;
	return (cluster->init_success);
}

void	cluster_free(void)
{
	t_philo_cluster	*cluster;
	size_t			i;

	cluster = cluster_get();
	i = 0;
	while (i < cluster->count)
	{
		pthread_mutex_destroy(cluster->forks + i);
		pthread_mutex_destroy(&(cluster->philos + i)->philo_state_lock);
		pthread_mutex_destroy(&(cluster->philos + i)->philo_ts_lock);
		i++;
	}
	if (cluster->init_success)
	{
		pthread_mutex_destroy(&cluster->outlock);
		pthread_mutex_destroy(&cluster->state_lock);
	}
	free(cluster->philos);
	free(cluster->forks);
	free(cluster->threads);
}

void	cluster_start_threads(void *f)
{
	t_philo_cluster	*cluster;
	size_t			i;

	cluster = cluster_get();
	cluster->ts_start = get_timestamp();
	i = 0;
	while (i < cluster->count)
	{
		pthread_create(cluster->threads + i,
			NULL,
			f, &((cluster->philos + i)->id));
		i++;
	}
	pthread_create(cluster->threads + cluster->count,
		NULL,
		thread_monitor,
		NULL);
	i = 0;
	while (i < cluster->count)
	{
		pthread_join(cluster->threads[i], NULL);
		i++;
	}
	pthread_join(cluster->threads[i], NULL);
}

int	init_philosophers(t_philo_cluster *cluster, long *stats)
{
	size_t	count;

	count = stats[NUMBER_OF_PHILOSOPHERS];
	while (cluster->count < count)
	{
		stats_copy((cluster->philos + cluster->count)->configuration, stats);
		(cluster->philos + cluster->count)->state = NONE;
		(cluster->philos + cluster->count)->lfork = cluster->count;
		(cluster->philos + cluster->count)->rfork = (cluster->count + 1) % count;
		(cluster->philos + cluster->count)->id = (cluster->count + 1);
		(cluster->philos + cluster->count)->last_meal_ts = -1;
		(cluster->philos + cluster->count)->meal_count = 0;
		if (pthread_mutex_init(cluster->forks + cluster->count, NULL) != 0)
		{
			cluster_free();
			return (0);
		}
		if (pthread_mutex_init(&(cluster->philos[cluster->count].philo_state_lock), NULL) != 0)
		{
			pthread_mutex_destroy(cluster->forks + cluster->count);
			cluster_free();
			return (0);
		}
		if (pthread_mutex_init(&(cluster->philos[cluster->count].philo_ts_lock), NULL) != 0)
		{
			pthread_mutex_destroy(cluster->forks + cluster->count);
			pthread_mutex_destroy(&(cluster->philos[cluster->count].philo_state_lock));
			cluster_free();
			return (0);
		}
		cluster->count++;
	}
	return (1);
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

	cluster = cluster_get();
	for (size_t i = 0; i < cluster->count; i++)
	{
		printf("Id: %zu\n", (cluster->philos + i)->id);
		printf("Latest state: %s\n", str_state((cluster->philos + i)->state));
		printf("Forks: L => %zu R => %zu\n", (cluster->philos + i)->lfork, (cluster->philos + i)->rfork);
		printf("Meal count: %zu\n", (cluster->philos + i)->meal_count);
	}
}
