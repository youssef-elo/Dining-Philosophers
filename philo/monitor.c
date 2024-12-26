/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:39:22 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 18:03:02 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	announce_death(t_monitor *monitor_d, int i)
{
	monitor_d->sim_state = ENDED;
	pthread_mutex_lock(monitor_d->writing);
	printf("%ld %d died\n", elapsed_time(monitor_d->start),
		monitor_d->philos[i].id);
	pthread_mutex_unlock(monitor_d->writing);
	pthread_mutex_unlock(monitor_d->philos[i].philo_lock);
	return (1);
}

int	check_death(t_monitor *m, int *meal_maxed)
{
	int	i;

	i = 0;
	while (i < m->num_philos)
	{
		pthread_mutex_lock(m->philos[i].philo_lock);
		if (((elapsed_time(m->start) - m->philos[i].last_meal) >= m->t_die))
			return (announce_death(m, i));
		if (m->meal_max != -1 && m->philos[i].number_of_meals >= m->meal_max)
			(*meal_maxed)++;
		pthread_mutex_unlock(m->philos[i].philo_lock);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	int			meal_maxed;
	t_monitor	*monitor_d;

	monitor_d = (t_monitor *)arg;
	if (monitor_d->t_die < (size_t)monitor_d->t_eat)
		ft_usleep(&monitor_d->philos[0], monitor_d->t_die / 2);
	else
		ft_usleep(&monitor_d->philos[0], monitor_d->t_eat / 2);
	while (1)
	{
		meal_maxed = 0;
		if (check_death(monitor_d, &meal_maxed))
			return (NULL);
		if (monitor_d->meal_max != -1 && meal_maxed == monitor_d->num_philos)
		{
			monitor_d->satisfied = FULL;
			return (NULL);
		}
	}
	return (NULL);
}
