/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:57:41 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/21 16:00:01 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_monitor(int ac, char **av, t_monitor *monitor_data)
{
	int	tmp;

	monitor_data->num_philos = ft_atoi(av[1]);
	if (monitor_data->num_philos > 600
		|| monitor_data->num_philos == -1 || monitor_data->num_philos == 0)
		return (put_err("Invalid number of philosophers\n", 31));
	tmp = ft_atoi(av[2]);
	if (tmp == -1 || tmp < 60)
		return (put_err("time to die is invalid\n", 23));
	monitor_data->t_die = tmp;
	monitor_data->t_eat = ft_atoi(av[3]);
	if (monitor_data->t_eat == -1 || monitor_data->t_eat < 60)
		return (put_err("time to eat is invalid\n", 23));
	monitor_data->t_sleep = ft_atoi(av[4]);
	if (monitor_data->t_sleep == -1 || monitor_data->t_sleep < 60)
		return (put_err("time to sleep is invalid\n", 25));
	if (ac == 6)
	{
		monitor_data->meal_max = ft_atoi(av[5]);
		if (monitor_data->meal_max == -1)
			return (put_err("Number of meals is too big\n", 27));
	}
	else
		monitor_data->meal_max = -1;
	return (0);
}
