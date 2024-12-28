/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:44:34 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/28 10:52:59 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	int		*ids;
	t_data	sim_d;

	memset(&sim_d, 0, sizeof(sim_d));
	if (check_args(ac, av))
		return (1);
	if (struct_init(ac, av, &sim_d))
		return (2);
	if (init_semaphore(&sim_d))
		return (3);
	ids = make_childreen(&sim_d, 0);
	watchers(&sim_d, ids);
}
