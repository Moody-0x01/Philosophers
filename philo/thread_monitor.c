/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:17 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/10 18:59:45 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	*thread_monitor(void *data)
{
	(void)data;
	while (1)
	{
		sleep_(50);
		if (simulation_ended())
			break ;
		if (!philo_check_hp())
			break ;
	}
	return (NULL);
}
