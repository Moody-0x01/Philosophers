/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:31:36 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/05 17:00:24 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	philo_kill(t_philo *target)
{
	target->state = DEAD;
	pthread_mutex_lock(&cluster_get()->state_lock);
	cluster_get()->cluster_state = STOPPED;
	pthread_mutex_unlock(&cluster_get()->state_lock);
	pthread_mutex_lock(&cluster_get()->outlock);
	printf("%ld %zu died\n",
		(get_timestamp() - cluster_get()->ts_start), target->id);
	pthread_mutex_unlock(&cluster_get()->outlock);
}

void	philo_think(t_philo *target)
{
	t_philo_cluster	*cluster;

	if (should_sim_stop())
		return ;
	cluster = cluster_get();
	target->state = THINKING;
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu is thinking\n",
		(get_timestamp() - cluster->ts_start), target->id);
	pthread_mutex_unlock(&cluster->outlock);
}

void	philo_eat(t_philo *target)
{
	t_philo_cluster	*cluster;

	if (should_sim_stop())
		return ;
	cluster = cluster_get();
	take_forks(target);
	if (cluster->count == 1)
	{
		release_forks(target);
		philo_kill(target);
		return ;
	}
	target->state = EATING;
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu is eating\n",
		(get_timestamp() - cluster->ts_start), target->id);
	pthread_mutex_unlock(&cluster->outlock);
	sleep_(target->configuration[TIME_TO_EAT]);
	target->last_meal_ts = get_timestamp();
	release_forks(target);
	target->meal_count++;
}

void	philo_sleep(t_philo *target)
{
	t_philo_cluster	*cluster;

	if (should_sim_stop())
		return ;
	cluster = cluster_get();
	target->state = SLEEPING;
	pthread_mutex_lock(&cluster->outlock);
	printf("%ld %zu is sleeping\n",
		(get_timestamp() - cluster->ts_start), target->id);
	pthread_mutex_unlock(&cluster->outlock);
	sleep_(target->configuration[TIME_TO_SLEEP]);
}

int	philo_check_hp(void)
{
	t_philo	*all;
	size_t	count;
	size_t	index;

	all = cluster_get()->philos;
	count = cluster_get()->count;
	index = 0;
	while (index < count)
	{
		if (all[index].state != EATING)
		{
			if (all[index].state != DEAD && philo_is_starved(all + index))
			{
				philo_kill(all + index);
				pthread_detach(cluster_get()->threads[index]);
				return (0);
			}
		}
		index++;
	}
	return (1);
}
