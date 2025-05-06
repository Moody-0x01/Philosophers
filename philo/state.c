/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:29:55 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/05 16:35:51 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

t_philo_state	get_philo_state(t_philo *target)
{
	t_philo_state	copy;

	pthread_mutex_lock(&target->philo_state_lock);
	copy = target->state;
	pthread_mutex_unlock(&target->philo_state_lock);
	return (copy);
}

void	set_philo_state(t_philo *target, t_philo_state new)
{
	pthread_mutex_lock(&target->philo_state_lock);
	target->state = new;
	pthread_mutex_unlock(&target->philo_state_lock);
}
