/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:14:45 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/10 15:16:40 by lazmoud          ###   ########.fr       */
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
	while (!simulation_ended())
	{
		philo_think(target);
		philo_eat(target);
		pthread_mutex_lock(&target->philo_state_lock);
		if (meal_threshhold_reached(target))
		{
			if (target->state != DEAD)
				target->state = DONE_;
			pthread_mutex_unlock(&target->philo_state_lock);
			break ;
		}
		pthread_mutex_unlock(&target->philo_state_lock);
		philo_sleep(target);
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
