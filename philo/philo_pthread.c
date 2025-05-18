/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pthread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:51:16 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/18 18:52:22 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

bool	philo_thread_create(pthread_t *t, size_t *id, void *f)
{
	return (pthread_create(t, NULL, f, id) == 0);
}
