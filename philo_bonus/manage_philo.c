/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:22:35 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 18:23:12 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_calloc(int size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	memset(ret, 0, size);
	return (ret);
}

void	release_semaphores(t_data *sim_d)
{
	if (sim_d->writing)
	{
		sem_close(sim_d->writing);
		sem_unlink(WRITESM);
	}
	if (sim_d->forks)
	{
		sem_close(sim_d->forks);
		sem_unlink(FORKSM);
	}
	if (sim_d->dead)
	{
		sem_close(sim_d->dead);
		sem_unlink(DEADSM);
	}
	if (sim_d->full)
	{
		sem_close(sim_d->full);
		sem_unlink(FULLSM);
	}
	if (sim_d->philo_lock)
	{
		sem_close(sim_d->philo_lock);
		sem_unlink(PHILOSM);
	}
}

void	forking_fail(t_data *sim_d, int *ids, int fail_i)
{
	kill_process(ids, fail_i);
	release_semaphores(sim_d);
	exit(1);
}

int	*make_childreen(t_data *sim_d, int i)
{
	int	f;
	int	*ids;

	i = 0;
	ids = ft_calloc(sizeof(int) * sim_d->num_philos);
	if (!ids)
	{
		release_semaphores(sim_d);
		exit(1);
	}
	sim_d->number_of_meals = 0;
	sim_d->start = elapsed_time(0);
	while (i < sim_d->num_philos)
	{
		sim_d->id = i + 1;
		f = fork();
		if (f == -1)
			forking_fail(sim_d, ids, i);
		if (f == 0)
			philo(sim_d);
		else
			ids[i] = f;
		i++;
	}
	return (ids);
}
