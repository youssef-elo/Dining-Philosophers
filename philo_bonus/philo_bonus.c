/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:44:34 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/24 11:18:06 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	struct_init(t_child *philo_d)
{
	
}

int main(int ac, char **av)
{
	t_child philo_d;
	sem_t	writing;
	sem_t	forks;

	if (check_args(ac, av))
		return (1);
	if (struct_init(philo_d))
		return (2);
}