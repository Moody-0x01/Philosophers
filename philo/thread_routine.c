/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:05:15 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/02 20:07:48 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	*default_routine(void *id_ptr)
{
	size_t	index;
	long	ts_start;
	t_philo	*all;
	t_philo	*target;

	all = cluster_get()->philos;
	index = ((*(size_t *)id_ptr)) - 1;
	ts_start = cluster_get()->ts_start;
	target = &all[index];
	if (index % 2 == 0)
		usleep(1000);
	while (!simulation_ended())
	{
		pthread_mutex_lock(&cluster_get()->outlock);
		target->state = THINKING;
		printf("%ld %zu is thinking\n", (get_timestamp() - ts_start), index + 1);
		pthread_mutex_unlock(&cluster_get()->outlock);
		take_forks(index);
		if ((target->last_meal_ts != -1) && (get_timestamp() - target->last_meal_ts > target->configuration[TIME_TO_SLEEP]))
		{
			target->state = DEAD;
			pthread_mutex_lock(&cluster_get()->outlock);
			printf("%ld %zu died\n", (get_timestamp() - ts_start), index + 1);
			pthread_mutex_unlock(&cluster_get()->outlock);
			release_forks(index);
			break ;
		}
		target->last_meal_ts = get_timestamp();
		target->state = EATING;
		pthread_mutex_lock(&cluster_get()->outlock);
		printf("%ld %zu is eating\n", ((target->last_meal_ts) - ts_start), index + 1);
		pthread_mutex_unlock(&cluster_get()->outlock);
		sleep_(target->configuration[TIME_TO_EAT]);
		release_forks(index);
		target->meal_count++;
		if (target->meal_count == target->configuration[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT])
		{
			target->state = DONE_;
			break ;
		}
		target->state = SLEEPING;
		pthread_mutex_lock(&cluster_get()->outlock);
		printf("%ld %zu is sleeping\n", (get_timestamp() - ts_start), index + 1);
		pthread_mutex_unlock(&cluster_get()->outlock);
		sleep_(target->configuration[TIME_TO_SLEEP]);
	}
	return (NULL);
}

void *thread_monitor(void *data)
{
	(void)data;
	t_philo	*all;
	size_t	count;
	size_t	index;

	all = cluster_get()->philos;
	count = cluster_get()->count;
	while (1)
	{
		index = 0;
		while (index < count)
		{
			if (all[index].state != DONE_
				&& (all[index].last_meal_ts != -1) && (get_timestamp() - all[index].last_meal_ts > all[index].configuration[TIME_TO_SLEEP]))
			{
				all[index].state = DEAD;
				pthread_mutex_lock(&cluster_get()->state_lock);
				cluster_get()->cluster_state = STOPPED;
				pthread_mutex_unlock(&cluster_get()->state_lock);
				pthread_mutex_lock(&cluster_get()->outlock);
				printf("%ld %zu died\n", (get_timestamp() - cluster_get()->ts_start), index + 1);
				pthread_mutex_unlock(&cluster_get()->outlock);
				return (NULL);
			}
			index++;
		}
		index = 0;
		while (index < count)
		{
			if (all[index].state != DONE_)
				break ;
			index++;
		}
		if (index == count)
		{
			pthread_mutex_lock(&cluster_get()->state_lock);
			cluster_get()->cluster_state = STOPPED;
			pthread_mutex_unlock(&cluster_get()->state_lock);
		}
	}
	return (NULL);
}

int	simulation_ended()
{
	int	ended;

	pthread_mutex_lock(&cluster_get()->state_lock);
	ended = (cluster_get()->cluster_state == STOPPED);
	pthread_mutex_unlock(&cluster_get()->state_lock);
	return (ended);
}
