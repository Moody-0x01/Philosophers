/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:31:36 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/15 17:25:50 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	philo_kill(t_philo *target)
{
	if (simulation_ended() || get_philo_state(target) == DEAD)
		return ;
	log_action(target, "died", DEAD);
}

void	philo_think(t_philo *target)
{
	if (simulation_ended() || get_philo_state(target) == DEAD)
		return ;
	log_action(target, "is thinking", THINKING);
}

void	philo_eat(t_philo *target)
{
	if (simulation_ended() || get_philo_state(target) == DEAD)
		return ;
	take_forks(target);
	if (cluster_get()->count == 1)
	{
		philo_kill(target);
		simulation_stop();
		return ;
	}
	log_action(target, "is eating", EATING);
	pthread_mutex_lock(&target->philo_ts_lock);
	target->last_meal_ts = get_timestamp();
	pthread_mutex_unlock(&target->philo_ts_lock);
	sleep_(target->configuration[TIME_TO_EAT]);
	release_forks(target);
	target->meal_count++;
}

void	philo_sleep(t_philo *target)
{
	if (simulation_ended() || get_philo_state(target) == DEAD)
		return ;
	log_action(target, "is sleeping", SLEEPING);
	sleep_(target->configuration[TIME_TO_SLEEP]);
}
