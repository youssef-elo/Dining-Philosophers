/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:14:01 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/21 16:21:44 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(int size)
{
	void	*ret;

	ret = malloc(size);
	memset(ret, 0, size);
	return (ret);
}

void	join_clean(t_monitor *monitor_d, pthread_t monitor_th)
{
	int	i;

	i = 0;
	while (i < monitor_d->num_philos)
	{
		pthread_join(monitor_d->philos_th[i], NULL);
		i++;
	}
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

void	monitor_alloc(t_monitor *monitor_d)
{
	int	i;

	i = 0;
	monitor_d->writing = ft_calloc(sizeof(pthread_mutex_t));
	if (monitor_d->writing)
		pthread_mutex_init(monitor_d->writing, NULL);
	monitor_d->philos = ft_calloc(sizeof(t_philo)
			* monitor_d->num_philos);
	monitor_d->forks = ft_calloc(sizeof(pthread_mutex_t)
			* monitor_d->num_philos);
	monitor_d->philos_th = ft_calloc(sizeof(pthread_t)
			* monitor_d->num_philos);
	if (monitor_d->forks)
	{
		while (i < monitor_d->num_philos)
		{
			pthread_mutex_init(monitor_d->forks + i, NULL);
			i++;
		}
	}
}
