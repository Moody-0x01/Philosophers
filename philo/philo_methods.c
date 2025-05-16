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
	log_action(&cluster->philos[id - 1], "has taken a fork", FORK_TAKE);
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

t_philo_state	get_philo_state(t_philo *target)
{
	t_philo_state	s;

	pthread_mutex_lock(&(target->philo_state_lock));
	s = target->state;
	pthread_mutex_unlock(&(target->philo_state_lock));
	return (s);
}

void	set_philo_state(t_philo *target, t_philo_state s)
{
	pthread_mutex_lock(&(target->philo_state_lock));
	target->state = s;
	pthread_mutex_unlock(&(target->philo_state_lock));
}

int	set_if(t_philo *target, t_philo_state s)
{
	int	set;

	set = 0;
	pthread_mutex_lock(&(target->philo_state_lock));
	if (!simulation_ended())
	{
		target->state = s;
		set = 1;
	}
	pthread_mutex_unlock(&(target->philo_state_lock));
	return (set);
}
