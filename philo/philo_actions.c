/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:31:36 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/10 18:57:55 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>
t_philo_state	get_philo_state(t_philo *target);
void			set_philo_state(t_philo *target, t_philo_state s);

void	philo_kill(t_philo *target)
{
	if (simulation_ended() || get_philo_state(target) == DEAD)
		return ;
	set_philo_state(target, DEAD);
	simulation_stop();
	pthread_mutex_lock(&cluster_get()->outlock);
	printf("%ld %zu died\n",
		(get_timestamp() - cluster_get()->ts_start), target->id);
	pthread_mutex_unlock(&cluster_get()->outlock);
}

void	philo_think(t_philo *target)
{
	t_philo_cluster	*cluster;

	if (simulation_ended() || get_philo_state(target) == DEAD)
		return ;
	set_philo_state(target, THINKING);
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
	if (simulation_ended() || get_philo_state(target) == DEAD)
		return ;
	if (cluster->count == 1)
	{
		philo_kill(target);
		return ;
	}
	set_philo_state(target, EATING);
	take_forks(target);
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu is eating\n",
		(get_timestamp() - cluster->ts_start), target->id);
	pthread_mutex_unlock(&cluster->outlock);
	pthread_mutex_lock(&target->philo_ts_lock);
	target->last_meal_ts = get_timestamp();
	pthread_mutex_unlock(&target->philo_ts_lock);
	sleep_(target->configuration[TIME_TO_EAT]);
	release_forks(target);
	target->meal_count++;
}

void	philo_sleep(t_philo *target)
{
	t_philo_cluster	*cluster;

	if (simulation_ended() || get_philo_state(target) == DEAD)
		return ;
	set_philo_state(target, SLEEPING);
	cluster = cluster_get();
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu is sleeping\n",
		(get_timestamp() - cluster->ts_start), target->id);
	pthread_mutex_unlock(&cluster->outlock);
	sleep_(target->configuration[TIME_TO_SLEEP]);
}
