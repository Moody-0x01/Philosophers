/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:05:15 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/04 16:38:09 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	meal_threshhold_reached(t_philo *philo)
{
	long	count;
	long	threshh;

	threshh = philo->configuration[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT];
	count = philo->meal_count;
	if (threshh == -1)
		return (false);
	return (count >= threshh);
}

void	*default_routine(void *id_ptr)
{
	size_t	index;
	t_philo	*all;
	t_philo	*target;

	all = cluster_get()->philos;
	index = ((*(size_t *)id_ptr)) - 1;
	target = &all[index];
	if (index % 2 == 0)
		sleep_(1);
	target->last_meal_ts = get_timestamp();
	while (!simulation_ended())
	{
		philo_think(target);
		philo_eat(target);
		if (meal_threshhold_reached(target))
		{
			target->state = DONE_;
			break ;
		}
		philo_sleep(target);
	}
	return (NULL);
}

int	philo_is_starved(t_philo *target)
{
	long	last_meal_ts;
	long	time_to_die;

	last_meal_ts = target->last_meal_ts;
	time_to_die = target->configuration[TIME_TO_DIE];
	return (last_meal_ts != -1 && get_timestamp() - last_meal_ts > time_to_die);
}

int	simulation_ended(void)
{
	int	ended;

	pthread_mutex_lock(&cluster_get()->state_lock);
	ended = (cluster_get()->cluster_state == STOPPED);
	pthread_mutex_unlock(&cluster_get()->state_lock);
	return (ended);
}
