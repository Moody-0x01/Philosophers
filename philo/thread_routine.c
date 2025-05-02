/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:05:15 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/02 16:47:44 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	*default_routine(void *index_ptr)
{
	size_t	id;

	id = ((*(size_t *)index_ptr));
	pthread_mutex_lock(&cluster_get()->outlock);
	printf("Recevied philo id: %zu\n", id);
	printf("Recevied philo idx: %zu\n", (id - 1));
	printf("Obj: %p\n", &cluster_get()->philos[id - 1]);
	printf("Count: %zu\n", cluster_get()->count);
	pthread_mutex_unlock(&cluster_get()->outlock);
	return (NULL);
}
