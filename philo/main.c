/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:46:42 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/02 16:47:12 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	main(int ac, char **av)
{
	long		out[STAT_COUNT];

	parse_stats(ac, av, out);
	cluster_init(out);
	cluster_start_threads(default_routine);
	cluster_free();
	return (0);
}
