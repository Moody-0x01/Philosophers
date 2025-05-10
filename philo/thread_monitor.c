/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:17 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/06 16:01:41 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	*thread_monitor(void *data)
{
	(void)data;
	while (philo_check_hp() || !simulation_ended())
		sleep_(10);
	return (NULL);
}
