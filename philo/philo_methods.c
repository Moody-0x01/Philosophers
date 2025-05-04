/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:35:47 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/04 16:08:16 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

size_t	left(size_t i)
{
	return (i);
}

size_t	right(size_t i)
{
	size_t	count;

	count = cluster_get()->count;
	return ((i + 1) % count);
}

void	take_forks(size_t index)
{
	size_t	l;
	size_t	r;

	l = left(index);
	r = right(index);
	if (l < r)
	{
		pthread_mutex_lock(get_fork(l));
		pthread_mutex_lock(get_fork(r));
		return ;
	}
	pthread_mutex_lock(get_fork(r));
	pthread_mutex_lock(get_fork(l));
}

void	release_forks(size_t index)
{
	size_t	l;
	size_t	r;

	l = left(index);
	r = right(index);
	if (l < r)
	{
		pthread_mutex_unlock(get_fork(l));
		pthread_mutex_unlock(get_fork(r));
		return ;
	}
	pthread_mutex_unlock(get_fork(r));
	pthread_mutex_unlock(get_fork(l));
}
