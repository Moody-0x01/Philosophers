/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:37:27 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/04 16:38:21 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	*thread_monitor(void *data)
{
	(void)data;
	while (philo_check_hp() || !should_sim_stop())
	{
	}
	return (NULL);
}

int	should_sim_stop(void)
{
	size_t	count;
	size_t	index;
	t_philo	*all;

	all = cluster_get()->philos;
	count = cluster_get()->count;
	index = 0;
	while (index < count)
	{
		if (all[index].state != DONE_)
			return (0);
		index++;
	}
	pthread_mutex_lock(&cluster_get()->state_lock);
	cluster_get()->cluster_state = STOPPED;
	pthread_mutex_unlock(&cluster_get()->state_lock);
	return (1);
}
