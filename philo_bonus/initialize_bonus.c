/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:18:33 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/24 16:26:54 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	put_err(char *str, int len)
{
	write(2, str, len);
	return (1);
}

int	struct_init(int ac, char **av, t_data *sim_d)
{
	int	tmp;

	sim_d->num_philos = ft_atoi(av[1]);
	if (sim_d->num_philos <= 0)
		return (put_err("Invalid number of philosophers\n", 31));
	tmp = ft_atoi(av[2]);
	if (tmp <= 0)
		return (put_err("time to die is invalid\n", 23));
	sim_d->t_die = tmp;
	sim_d->t_eat = ft_atoi(av[3]);
	if (sim_d->t_eat <= 0)
		return (put_err("time to eat is invalid\n", 23));
	sim_d->t_sleep = ft_atoi(av[4]);
	if (sim_d->t_sleep <= 0)
		return (put_err("time to sleep is invalid\n", 25));
	if (ac == 6)
	{
		sim_d->meal_max = ft_atoi(av[5]);
		if (sim_d->meal_max <= 0)
			return (put_err("Number of meals is invalid\n", 27));
	}
	else
		sim_d->meal_max = -1;
	return (0);
}

int	init_semaphore(t_data *sim_d)
{
	sem_unlink("/lektaba");
	sim_d->writing = sem_open("/lektaba", O_CREAT, 0666, 1);
	if (sim_d->writing == SEM_FAILED)
		return (1);
	sem_unlink("/forks");
	sim_d->forks = sem_open("/forks", O_CREAT, 0666, sim_d->num_philos);
	if (sim_d->forks == SEM_FAILED)
	{
		sem_close(sim_d->writing);
		sem_unlink("/lektaba");
		return (1);
	}
	sim_d->satisfied = HUNGRY;
	sim_d->philo_state = ALIVE;
	return (0);
}
