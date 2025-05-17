/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_health.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:28:39 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/16 15:47:49 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	philo_check(t_philo *target, size_t *done)
{
	pthread_mutex_lock(&(target->philo_state_lock));
	if (target->state == DONE_)
		(*done)++;
	else if (target->state != EATING)
	{
		if (philo_is_starved(target))
		{
			pthread_mutex_unlock(&(target->philo_state_lock));
			log_action(target, "died", NONE);
			return (0);
		}
	}
	pthread_mutex_unlock(&(target->philo_state_lock));
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
