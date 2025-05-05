/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:35:47 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/04 18:59:04 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	take_forks(t_philo *target)
{
	if (target->lfork == target->rfork)
	{
		pthread_mutex_lock(get_fork(target->lfork));
		return ;
	}
	if (target->lfork < target->rfork)
	{
		pthread_mutex_lock(get_fork(target->lfork));
		pthread_mutex_lock(get_fork(target->rfork));
		return ;
	}
	pthread_mutex_lock(get_fork(target->rfork));
	pthread_mutex_lock(get_fork(target->lfork));
}

void	release_forks(t_philo *target)
{
	if (target->lfork == target->rfork)
	{
		pthread_mutex_unlock(get_fork(target->lfork));
		return ;
	}
	if (target->lfork < target->rfork)
	{
		pthread_mutex_unlock(get_fork(target->lfork));
		pthread_mutex_unlock(get_fork(target->rfork));
		return ;
	}
	pthread_mutex_unlock(get_fork(target->rfork));
	pthread_mutex_unlock(get_fork(target->lfork));
}
