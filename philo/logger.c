/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:54:24 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/15 15:13:35 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	log_action(t_philo *target, const char *action, t_philo_state new)
{
	t_philo_cluster	*cluster;

	cluster = cluster_get();
	pthread_mutex_lock(&cluster->outlock);
	if (set_if(target, new))
	{
		printf("%ld %zu %s\n",
			(get_timestamp() - cluster->ts_start), target->id, action);
	}
	pthread_mutex_unlock(&cluster->outlock);
}
