/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:18:49 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 18:19:16 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_usleep(t_data *sim_d, size_t duration_ms)
{
	size_t	start;
	size_t	elapsed;

	start = elapsed_time(sim_d->start);
	while (1)
	{
		elapsed = elapsed_time(sim_d->start) - start;
		if (elapsed >= duration_ms)
			break ;
		usleep(500);
	}
	return (0);
}

size_t	elapsed_time(size_t start)
{
	struct timeval	tim;
	size_t			now;

	gettimeofday(&tim, NULL);
	now = (tim.tv_sec * 1000) + (tim.tv_usec / 1000);
	return (now - start);
}
