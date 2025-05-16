/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cluster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:44 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/16 15:38:20 by lazmoud          ###   ########.fr       */
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

int	cluster_init_data(t_philo_cluster *cluster, long *stats, size_t count)
{
	cluster->threads = malloc(sizeof(*cluster->threads) * (count + 1));
	if (!cluster->threads)
	{
		cluster_free();
		return (cluster->init_success);
	}
	if (!init_philosophers(cluster, stats))
		return (cluster->init_success);
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

int	cluster_init(long *stats)
{
	t_philo_cluster	*cluster;
	size_t			count;

	cluster = cluster_get();
	cluster->count = 0;
	count = stats[NUMBER_OF_PHILOSOPHERS];
	cluster->cluster_state = STILL_GOING;
	cluster->philos = malloc(sizeof(*cluster->philos) * count);
	if (!cluster->philos)
		return (0);
	cluster->forks = malloc(sizeof(*cluster->forks) * count);
	if (!cluster->forks)
	{
		cluster_free();
		return (cluster->init_success);
	}
	return (cluster_init_data(cluster, stats, count));
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
		pthread_mutex_destroy(&(cluster->philos[i]
				.meal_count_lock));
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
