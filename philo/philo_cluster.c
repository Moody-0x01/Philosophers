/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cluster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:44 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/02 15:01:51 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

static t_philo_cluster	*cluster_station(t_cluster_action a, long *stats, typeof(void *(void *)) *func)
{
	static	t_philo_cluster	cluster;

	if (a == CGET)
		return (&cluster);
	else if (a == CINIT)
	{
		cluster.count = stats[NUMBER_OF_PHILOSOPHERS];
		cluster.philos = malloc(sizeof(*cluster.philos) * cluster.count);
		cluster.forks = malloc(sizeof(*cluster.forks) * cluster.count);
		cluster.threads = malloc(sizeof(*cluster.threads) * cluster.count);
		for (size_t i = 0; i < cluster.count; ++i)
		{
			(cluster.philos + i)->state = NONE;
			(cluster.philos + i)->configuration = stats;
			(cluster.philos + i)->id = (i + 1);
			pthread_mutex_init(cluster.forks + i, NULL);
		}
		pthread_mutex_init(&cluster.outlock, NULL);
	} else if (a == CFREE)
	{
		for (size_t i = 0; i < cluster.count; ++i)
			pthread_mutex_destroy(cluster.forks + i);
		pthread_mutex_destroy(&cluster.outlock);
		free(cluster.philos);
		free(cluster.forks);
		free(cluster.threads);
	} else if (a == SPAWN_THREADS)
	{
		for (size_t i = 0; i < cluster.count; ++i)
			pthread_create(cluster.threads + i, NULL, func, &((cluster.philos + i)->id));
		for (size_t i = 0; i < cluster.count; ++i)
			pthread_join(cluster.threads[i], NULL);
	}
	return (NULL);
}

void	cluster_init(long *stats)
{
	cluster_station(CINIT, stats, NULL);
}

void	cluster_free(void)
{
	cluster_station(CFREE, NULL, NULL);
}


void	cluster_start_threads(void *f)
{
	cluster_station(SPAWN_THREADS, NULL, f);
}

t_philo_cluster	*cluster_get(void)
{
	return (cluster_station(CGET, NULL, NULL));
}
