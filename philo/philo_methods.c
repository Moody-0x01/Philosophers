/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:35:47 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/06 16:09:12 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

static void	__take_fork(pthread_mutex_t	*fork, size_t id)
{
	t_philo_cluster	*cluster;

	cluster = cluster_get();
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu has taken a fork\n",
		(get_timestamp() - cluster->ts_start), id);
	pthread_mutex_unlock(&cluster->outlock);
}

pthread_mutex_t	*get_fork(size_t i)
{
	return (cluster_get()->forks + i);
}

void	take_forks(t_philo *target)
{
	if (target->lfork == target->rfork)
	{
		__take_fork(get_fork(target->lfork), target->id);
		return ;
	}
	if (target->lfork < target->rfork)
	{
		__take_fork(get_fork(target->lfork), target->id);
		__take_fork(get_fork(target->rfork), target->id);
		return ;
	}
	__take_fork(get_fork(target->rfork), target->id);
	__take_fork(get_fork(target->lfork), target->id);
}

void	release_forks(t_philo *target)
{
	if (target->lfork == target->rfork)
	{
		pthread_mutex_unlock(get_fork(target->lfork));
		return ;
	}
	if (target->lfork < target->rfork)
	{
		pthread_mutex_unlock(get_fork(target->lfork));
		pthread_mutex_unlock(get_fork(target->rfork));
		return ;
	}
	pthread_mutex_unlock(get_fork(target->rfork));
	pthread_mutex_unlock(get_fork(target->lfork));
}
