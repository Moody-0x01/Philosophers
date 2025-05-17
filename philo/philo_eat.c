/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:31:36 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/17 14:53:35 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	philo_eat(t_philo *target)
{
	take_forks(target);
	if (cluster_get()->count == 1)
	{
		release_forks(target);
		log_action(target, "died", NONE);
		return ;
	}
	pthread_mutex_lock(&target->philo_ts_lock);
	target->last_meal_ts = get_timestamp();
	pthread_mutex_unlock(&target->philo_ts_lock);
	log_action(target, "is eating", EATING);
	sleep_(target->configuration[TIME_TO_EAT]);
	release_forks(target);
	pthread_mutex_lock(&target->meal_count_lock);
	target->meal_count++;
	pthread_mutex_unlock(&target->meal_count_lock);
}
