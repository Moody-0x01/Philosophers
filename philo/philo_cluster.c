/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cluster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:44 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/04 18:59:47 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

t_philo_cluster	*cluster_get(void)
{
	static t_philo_cluster	cluster;

	return (&cluster);
}

void	cluster_init(long *stats)
{
	t_philo_cluster	*cluster;

	cluster = cluster_get();
	cluster->count = stats[NUMBER_OF_PHILOSOPHERS];
	cluster->philos = malloc(sizeof(*cluster->philos) * cluster->count);
	cluster->forks = malloc(sizeof(*cluster->forks) * cluster->count);
	cluster->threads = malloc(sizeof(*cluster->threads) * (cluster->count + 1));
	init_philosophers(cluster, stats);
	cluster->cluster_state = STILL_GOING;
	pthread_mutex_init(&cluster->outlock, NULL);
	pthread_mutex_init(&cluster->state_lock, NULL);
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
	pthread_mutex_destroy(&cluster->outlock);
	pthread_mutex_destroy(&cluster->state_lock);
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
	pthread_create(cluster->threads + i,
		NULL,
		thread_monitor, &((cluster->philos + i)->id));
	i = 0;
	while (i < cluster->count)
	{
		pthread_join(cluster->threads[i], NULL);
		i++;
	}
	pthread_join(cluster->threads[i], NULL);
}

void	init_philosophers(t_philo_cluster *cluster, long *stats)
{
	size_t	i;

	i = 0;
	while (i < cluster->count)
	{
		(cluster->philos + i)->state = NONE;
		(cluster->philos + i)->configuration = stats;
		(cluster->philos + i)->lfork = i;
		(cluster->philos + i)->rfork = (i + 1) % cluster->count;
		(cluster->philos + i)->id = (i + 1);
		(cluster->philos + i)->last_meal_ts = -1;
		(cluster->philos + i)->meal_count = 0;
		pthread_mutex_init(cluster->forks + i, NULL);
		pthread_mutex_init(&(cluster->philos + i)->philo_state_lock, NULL);
		pthread_mutex_init(&(cluster->philos + i)->philo_ts_lock, NULL);
		i++;
	}
}
