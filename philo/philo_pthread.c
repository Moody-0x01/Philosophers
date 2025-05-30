/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pthread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:51:16 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/18 19:02:35 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

bool	philo_thread_create(pthread_t *t, size_t *id, void *f)
{
	if (pthread_create(t, NULL, f, id))
	{
		printf("Failed to create a thread\n");
		return (false);
	}
	return (true);
}

bool	philo_mutex_init(pthread_mutex_t *m)
{
	if (pthread_mutex_init(m, NULL) == 0)
		return (true);
	printf("Failed to create a mutex\n");
	return (false);
}
