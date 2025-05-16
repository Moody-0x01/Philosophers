/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:05:15 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/10 18:08:12 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	meal_threshhold_reached(t_philo *philo)
{
	long	cond;
	long	threshh;

	threshh = philo->configuration[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT];
	if (threshh == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_count_lock);
	cond = (philo->meal_count >= threshh);
	pthread_mutex_unlock(&philo->meal_count_lock);
	return (cond);
}

void	*default_routine(void *id_ptr)
{
	size_t	index;
	t_philo	*all;
	t_philo	*target;

	all = cluster_get()->philos;
	index = ((*(size_t *)id_ptr)) - 1;
	target = &all[index];
	if (index % 2 != 0)
		usleep(500);
	return (simulation_start(target));
}

int	philo_is_starved(t_philo *target)
{
	long	has_not_eaten_since;
	long	time_to_die;

	pthread_mutex_lock(&(target->philo_ts_lock));
	time_to_die = target->configuration[TIME_TO_DIE];
	if (target->last_meal_ts == -1)
		has_not_eaten_since = (get_timestamp() - cluster_get()->ts_start);
	else
		has_not_eaten_since = (get_timestamp() - target->last_meal_ts);
	pthread_mutex_unlock(&(target->philo_ts_lock));
	return (has_not_eaten_since > time_to_die);
}
