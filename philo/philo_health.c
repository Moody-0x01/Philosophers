/* ************************************************************************** */
	// pthread_mutex_lock(&cluster_get()->outlock);
	// printf("Has not ate since: %zu\n", get_timestamp() - last_meal_ts);
	// printf("Time to die: %zu\n", time_to_die);
	// pthread_mutex_unlock(&cluster_get()->outlock);
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_health.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:28:39 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/10 19:01:01 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	philo_check(t_philo *target, size_t *done)
{
	t_philo_state	state;

	pthread_mutex_lock(&(target->philo_state_lock));
	state = target->state;
	pthread_mutex_unlock(&(target->philo_state_lock));
	if (state == DONE_)
		(*done)++;
	else if (state != EATING)
	{
		if (philo_is_starved(target))
		{
			philo_kill(target);
			return (0);
		}
	}
	return (1);
}

int	philo_check_hp(void)
{
	t_philo			*all;
	size_t			done;
	size_t			count;
	size_t			index;

	all = cluster_get()->philos;
	count = cluster_get()->count;
	done = 0;
	index = 0;
	while (index < count)
	{
		if (!philo_check(all + index, &done))
			return (0);
		index++;
	}
	if (done == count)
	{
		simulation_stop();
		return (0);
	}
	return (1);
}
