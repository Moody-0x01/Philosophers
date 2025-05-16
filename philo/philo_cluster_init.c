/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cluster_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:36:42 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/16 15:50:47 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

static	int	init_meal_count_lock(t_philo_cluster *cluster)
{
	if (pthread_mutex_init(&(cluster->philos[cluster->count].meal_count_lock),
			NULL))
	{
		pthread_mutex_destroy(&(cluster->philos[cluster->count].philo_ts_lock));
		pthread_mutex_destroy(cluster->forks + cluster->count);
		pthread_mutex_destroy(&(cluster->philos[cluster->count]
				.philo_state_lock));
		cluster_free();
		return (0);
	}
	return (1);
}

int	init_philosopher_mtxs(t_philo_cluster *cluster)
{
	if (pthread_mutex_init(cluster->forks + cluster->count, NULL))
	{
		cluster_free();
		return (0);
	}
	if (pthread_mutex_init(&(cluster->philos[cluster->count].philo_state_lock),
			NULL))
	{
		pthread_mutex_destroy(cluster->forks + cluster->count);
		cluster_free();
		return (0);
	}
	if (pthread_mutex_init(&(cluster->philos[cluster->count].philo_ts_lock),
			NULL))
	{
		pthread_mutex_destroy(cluster->forks + cluster->count);
		pthread_mutex_destroy(&(cluster->philos[cluster->count]
				.philo_state_lock));
		cluster_free();
		return (0);
	}
	return (init_meal_count_lock(cluster));
}

int	init_philosopher_state(t_philo_cluster *cluster, long *stats)
{
	size_t	count;

	count = stats[NUMBER_OF_PHILOSOPHERS];
	stats_copy((cluster->philos + cluster->count)->configuration, stats);
	(cluster->philos + cluster->count)->state = NONE;
	(cluster->philos + cluster->count)->lfork = cluster->count;
	(cluster->philos + cluster->count)->rfork = (cluster->count + 1) % count;
	(cluster->philos + cluster->count)->id = (cluster->count + 1);
	(cluster->philos + cluster->count)->last_meal_ts = -1;
	(cluster->philos + cluster->count)->meal_count = 0;
	if (!init_philosopher_mtxs(cluster))
		return (0);
	cluster->count++;
	return (1);
}

int	init_philosophers(t_philo_cluster *cluster, long *stats)
{
	size_t	count;

	count = stats[NUMBER_OF_PHILOSOPHERS];
	while (cluster->count < count)
	{
		if (!init_philosopher_state(cluster, stats))
			return (0);
	}
	return (1);
}
