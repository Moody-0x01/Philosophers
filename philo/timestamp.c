/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:56:09 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/04 13:59:45 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	sleep_(long ms)
{
	long	start_time;
	long	end_time;

	start_time = get_timestamp();
	end_time = (start_time + ms);
	while (1)
	{
		if (get_timestamp() >= end_time)
			break ;
		if (simulation_ended())
			break ;
		usleep(50);
	}
}
