/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:23:27 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/21 16:24:14 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int			i;
	t_monitor	monitor_d;
	pthread_t	monitor_th;

	i = 0;
	if (check_args(ac, av))
		return (1);
	if (init_monitor(ac, av, &monitor_d))
		return (2);
	if (philo_mutex_init(&monitor_d))
		return (3);
	init_philo_time(&monitor_d);
	i = 0;
	while (i < monitor_d.num_philos)
	{
		monitor_d.philos[i].last_meal = elapsed_time(monitor_d.start);
		pthread_create(monitor_d.philos_th + i, NULL,
			philo_routine, monitor_d.philos + i);
		i++;
	}
	pthread_create(&monitor_th, NULL, monitor, &monitor_d);
	join_clean(&monitor_d, monitor_th);
}
