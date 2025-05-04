/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:35:47 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/02 18:46:47 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

size_t	left(size_t i)
{

	size_t	count;

	count = cluster_get()->count;
	return ((i - 1 + count) % count);
}

size_t	right(size_t i)
{
	size_t	count;

	count = cluster_get()->count;
	return ((i + 1) % count);
}

t_philo *get_left_philo(size_t i)
{
	t_philo	*philos;

	philos = cluster_get()->philos;
	return (&philos[left(i)]);
}

t_philo	*get_right_philo(size_t i)
{
	t_philo	*philos;

	philos = cluster_get()->philos;
	return (&philos[right(i)]);
}

void	take_forks(size_t index)
{
	size_t	l;
	size_t	r;

	l = left(index);
	r = right(index);
	if (l <= r)
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
	if (l <= r)
	{
		pthread_mutex_unlock(get_fork(l));
		pthread_mutex_unlock(get_fork(r));
		return ;
	}
	pthread_mutex_unlock(get_fork(r));
	pthread_mutex_unlock(get_fork(l));
}
