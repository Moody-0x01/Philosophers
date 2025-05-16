/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:14:45 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/16 15:44:01 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	simulation_stop(void)
{
	pthread_mutex_lock(&cluster_get()->state_lock);
	cluster_get()->cluster_state = STOPPED;
	pthread_mutex_unlock(&cluster_get()->state_lock);
}

void	*simulation_start(t_philo *target)
{
	pthread_mutex_lock(&target->philo_ts_lock);
	target->last_meal_ts = get_timestamp();
	pthread_mutex_unlock(&target->philo_ts_lock);
	while (!simulation_ended())
	{
		philo_eat(target);
		philo_sleep(target);
		philo_think(target);
		if (meal_threshhold_reached(target))
		{
			set_if(target, DONE_);
			break ;
		}
	}
	return (NULL);
}

int	simulation_ended(void)
{
	int	ended;

	pthread_mutex_lock(&cluster_get()->state_lock);
	ended = (cluster_get()->cluster_state == STOPPED);
	pthread_mutex_unlock(&cluster_get()->state_lock);
	return (ended);
}
