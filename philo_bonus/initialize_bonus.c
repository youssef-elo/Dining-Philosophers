/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:18:33 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/25 19:39:39 by yel-ouaz         ###   ########.fr       */
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
	sem_unlink(WRITESM);
	sem_unlink(DEADSM);
	sem_unlink(FORKSM);
	sem_unlink(FULLSM);
	sem_unlink(PHILOSM);
	sem_unlink(GREEN);
	sim_d->writing = sem_open(WRITESM, O_CREAT, 0666, 1);
	sim_d->forks = sem_open(FORKSM, O_CREAT, 0666, sim_d->num_philos);
	sim_d->dead = sem_open(DEADSM, O_CREAT, 0666, 0);
	sim_d->full = sem_open(FULLSM, O_CREAT, 0666, 0);
	sim_d->philo_lock = sem_open(PHILOSM, O_CREAT, 0666, 0);
	sim_d->green_light = sem_open(GREEN, O_CREAT, 0666, 0);
	if (sim_d->writing == SEM_FAILED || sim_d->forks == SEM_FAILED	
		|| sim_d->dead == SEM_FAILED || sim_d->full == SEM_FAILED 
		|| sim_d->philo_lock == SEM_FAILED || sim_d->green_light == SEM_FAILED)
	{
		release_semaphores(sim_d);
		return (1);
	}
	sim_d->satisfied = HUNGRY;
	sim_d->philo_state = ALIVE;
	return (0);
}
