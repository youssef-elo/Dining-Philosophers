/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:50:56 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/21 15:50:57 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo)
{
	if (philo->monitor->sim_state == ENDED)
		return (1);
	pthread_mutex_lock(philo->monitor->writing);
	if (philo->monitor->sim_state == ENDED)
	{
		pthread_mutex_unlock(philo->monitor->writing);
		return (1);
	}
	printf("%ld %d is thinking\n",
		elapsed_time(philo->monitor->start), philo->id);
	pthread_mutex_unlock(philo->monitor->writing);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->monitor->satisfied == FULL)
			return (NULL);
		if (philo->id % 2)
			usleep(30 * 100);
		if (philo->monitor->sim_state == ENDED)
			return (NULL);
		if (get_forks(philo))
			return (NULL);
		if (philo_eat(philo))
			return (NULL);
		if (philo_sleep(philo))
			return (NULL);
		if (philo_think(philo))
			return (NULL);
	}
}
