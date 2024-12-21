/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:54:50 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/21 16:07:37 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo, size_t duration_ms)
{
	size_t	start;
	size_t	elapsed;

	start = elapsed_time(philo->monitor->start);
	while (1)
	{
		if (philo->monitor->sim_state == ENDED)
			return (1);
		elapsed = elapsed_time(philo->monitor->start) - start;
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

void	init_philo_time(t_monitor *monitor_d)
{
	int	i;

	i = 0;
	monitor_d->start = elapsed_time(0);
	monitor_d->sim_state = STILL;
	monitor_d->satisfied = HUNGRY;
	while (i < monitor_d->num_philos)
	{
		monitor_d->philos[i].id = i + 1;
		monitor_d->philos[i].right_fork = i;
		monitor_d->philos[i].left_fork = (i + 1) % monitor_d->num_philos;
		monitor_d->philos[i].number_of_meals = 0;
		monitor_d->philos[i].monitor = monitor_d;
		monitor_d->philos[i].last_meal = elapsed_time(monitor_d->start);
		i++;
	}
}
