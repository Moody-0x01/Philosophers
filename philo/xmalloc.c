/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:08:26 by lazmoud           #+#    #+#             */
/*   Updated: 2025/05/20 10:12:03 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	*xmalloc(size_t nbytes)
{
	void	*ptr;

	ptr = malloc(nbytes);
	if (!ptr)
		printf("Malloc failed, buy more ram\n");
	return (ptr);
}
