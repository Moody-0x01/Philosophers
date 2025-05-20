/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cluster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:44 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/20 10:12:46 by lazmoud          ###   ########.fr       */
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
	cluster->threads = xmalloc(sizeof(*cluster->threads) * (count + 1));
	if (!cluster->threads)
	{
		cluster_free();
		return (cluster->init_success);
	}
	if (!init_philosophers(cluster, stats))
		return (cluster->init_success);
	if (!philo_mutex_init(&cluster->outlock))
	{
		cluster_free();
		return (cluster->init_success);
	}
	if (!philo_mutex_init(&cluster->state_lock))
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
	cluster->philos = xmalloc(sizeof(*cluster->philos) * count);
	if (!cluster->philos)
		return (0);
	cluster->forks = xmalloc(sizeof(*cluster->forks) * count);
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
	size_t			created;
	size_t			index;

	cluster = cluster_get();
	cluster->ts_start = get_timestamp();
	created = 0;
	index = 0;
	while (created < cluster->count)
	{
		if (!philo_thread_create(cluster->threads + created,
				&((cluster->philos + created)->id), f))
		{
			simulation_stop();
			break ;
		}
		created++;
	}
	if (!philo_thread_create(cluster->threads + created, NULL, thread_monitor))
		simulation_stop();
	else
		created++;
	while (index < created)
		pthread_join(cluster->threads[index++], NULL);
}
