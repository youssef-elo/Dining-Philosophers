/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:14:01 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/23 16:12:51 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_clean(t_monitor *monitor_d, pthread_t monitor_th, int c, int m)
{
	int	i;

	i = 0;
	while (i < c)
	{
		pthread_join(monitor_d->philos_th[i], NULL);
		i++;
	}
	if (m)
		pthread_join(monitor_th, NULL);
	cleanup(monitor_d);
}

void	clean_philos(t_monitor *monitor_d)
{
	int	i;

	i = 0;
	while (i < monitor_d->num_philos)
	{
		if ((monitor_d->philos)[i].philo_lock)
		{
			pthread_mutex_destroy((monitor_d->philos)[i].philo_lock);
			free((monitor_d->philos)[i].philo_lock);
		}
		i++;
	}
	free(monitor_d->philos);
}

void	cleanup(t_monitor *monitor_d)
{
	int	i;

	i = 0;
	if (monitor_d->writing)
	{
		pthread_mutex_destroy(monitor_d->writing);
		free(monitor_d->writing);
	}
	if (monitor_d->forks)
	{
		while (i < monitor_d->num_philos)
		{
			pthread_mutex_destroy(&(monitor_d->forks[i]));
			i++;
		}
		free(monitor_d->forks);
	}
	if (monitor_d->philos)
		clean_philos(monitor_d);
	free(monitor_d->philos_th);
}

void	init_forks(t_monitor *monitor_d)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (i < monitor_d->num_philos)
	{
		if (pthread_mutex_init(monitor_d->forks + i, NULL))
		{
			while (f < i)
			{
				pthread_mutex_destroy(monitor_d->forks + i);
				f++;
			}
			free(monitor_d->forks);
			monitor_d->forks = NULL;
			return ;
		}
		i++;
	}
}

void	monitor_alloc(t_monitor *monitor_d)
{
	int	i;

	i = 0;
	monitor_d->writing = ft_calloc(sizeof(pthread_mutex_t));
	if (monitor_d->writing)
	{
		if (pthread_mutex_init(monitor_d->writing, NULL))
		{
			free(monitor_d->writing);
			monitor_d->writing = NULL;
			return ;
		}
	}
	monitor_d->philos = ft_calloc(sizeof(t_philo)
			* monitor_d->num_philos);
	monitor_d->forks = ft_calloc(sizeof(pthread_mutex_t)
			* monitor_d->num_philos);
	monitor_d->philos_th = ft_calloc(sizeof(pthread_t)
			* monitor_d->num_philos);
	if (monitor_d->forks)
		init_forks(monitor_d);
}
