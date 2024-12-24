/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:23:27 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/24 12:53:20 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sim(t_monitor *monitor_d, pthread_t *monitor_th)
{
	int	i;
	int	monitor_fail;

	i = 0;
	monitor_fail = 1;
	while (i < monitor_d->num_philos)
	{
		monitor_d->philos[i].last_meal = elapsed_time(monitor_d->start);
		if (pthread_create(monitor_d->philos_th + i, NULL,
				philo_routine, monitor_d->philos + i))
		{
			break ;
			monitor_d->sim_state = ENDED;
		}
		i++;
	}
	if (pthread_create(monitor_th, NULL, monitor, monitor_d))
	{
		monitor_fail = 0;
		monitor_d->sim_state = ENDED;
	}
	join_clean(monitor_d, *monitor_th, i, monitor_fail);
}

int	main(int ac, char **av)
{
	t_monitor	monitor_d;
	pthread_t	monitor_th;

	if (check_args(ac, av))
		return (1);
	if (init_monitor(ac, av, &monitor_d))
		return (2);
	if (philo_mutex_init(&monitor_d))
		return (3);
	init_philo_time(&monitor_d);
	start_sim(&monitor_d, &monitor_th);
}
