/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:31:36 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/10 15:29:18 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	philo_kill(t_philo *target)
{
	pthread_mutex_lock(&(target->philo_state_lock));
	if (simulation_ended() || target->state == DEAD)
		return ;
	target->state = DEAD;
	pthread_mutex_unlock(&(target->philo_state_lock));
	simulation_stop();
	pthread_mutex_lock(&cluster_get()->outlock);
	printf("%ld %zu died\n",
		(get_timestamp() - cluster_get()->ts_start), target->id);
	pthread_mutex_unlock(&cluster_get()->outlock);
}

void	philo_think(t_philo *target)
{
	t_philo_cluster	*cluster;

	pthread_mutex_lock(&(target->philo_state_lock));
	if (simulation_ended() || target->state == DEAD)
		return ;
	target->state = THINKING;
	pthread_mutex_unlock(&(target->philo_state_lock));
	cluster = cluster_get();
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu is thinking\n",
		(get_timestamp() - cluster->ts_start), target->id);
	pthread_mutex_unlock(&cluster->outlock);
}

void	philo_eat(t_philo *target)
{
	t_philo_cluster	*cluster;

	cluster = cluster_get();
	pthread_mutex_lock(&(target->philo_state_lock));
	if (simulation_ended() || target->state == DEAD)
		return ;
	target->state = EATING;
	pthread_mutex_unlock(&(target->philo_state_lock));
	take_forks(target);
	if (cluster->count == 1)
	{
		release_forks(target);
		philo_kill(target);
		return ;
	}
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu is eating\n",
		(get_timestamp() - cluster->ts_start), target->id);
	pthread_mutex_unlock(&cluster->outlock);
	sleep_(target->configuration[TIME_TO_EAT]);
	pthread_mutex_lock(&target->philo_ts_lock);
	target->last_meal_ts = get_timestamp();
	pthread_mutex_unlock(&target->philo_ts_lock);
	release_forks(target);
	target->meal_count++;
}

void	philo_sleep(t_philo *target)
{
	t_philo_cluster	*cluster;

	pthread_mutex_lock(&(target->philo_state_lock));
	if (simulation_ended() || target->state == DEAD)
		return ;
	target->state = SLEEPING;
	pthread_mutex_unlock(&(target->philo_state_lock));
	cluster = cluster_get();
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu is sleeping\n",
		(get_timestamp() - cluster->ts_start), target->id);
	pthread_mutex_unlock(&cluster->outlock);
	sleep_(target->configuration[TIME_TO_SLEEP]);
}
