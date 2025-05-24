/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:14:45 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/17 17:40:31 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	simulation_stop(void)
{
	pthread_mutex_lock(&cluster_get()->state_lock);
	cluster_get()->cluster_state = STOPPED;
	pthread_mutex_unlock(&cluster_get()->state_lock);
}

static long	get_time_left_to_die(t_philo *target)
{
	long	t;

	t = target->configuration[TIME_TO_DIE];
	return (t - get_has_not_eaten_since(target));
}

void	*simulation_start(t_philo *target)
{
	int		is_even;
	long	left;

	is_even = (target->id - 1) % 2;
	if (is_even == 0)
		usleep(500);
	pthread_mutex_lock(&target->philo_ts_lock);
	target->last_meal_ts = get_timestamp();
	pthread_mutex_unlock(&target->philo_ts_lock);
	while (!simulation_ended())
	{
		philo_eat(target);
		if (meal_threshhold_reached(target))
		{
			set_if(target, DONE_);
			break ;
		}
		log_action(target, "is sleeping", SLEEPING);
		sleep_(target->configuration[TIME_TO_SLEEP]);
		log_action(target, "is thinking", THINKING);
		if ((cluster_get()->count % 2) != 0)
		{
			left = get_time_left_to_die(target);
			if (left > 0)
				usleep(1000 * left);
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
