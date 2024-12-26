/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:20:56 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 18:22:01 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_childreen(void)
{
	int	pid;
	int	exit_s;

	pid = waitpid(-1, &exit_s, 0);
	while (pid != -1)
	{
		pid = waitpid(-1, &exit_s, 0);
	}
}

void	kill_process(int *ids, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		kill(ids[i], SIGKILL);
		i++;
	}
	wait_childreen();
	free(ids);
}

void	*watcher1(void *arg)
{
	int			i;
	t_watcher	*watcher_d;

	i = 0;
	watcher_d = (t_watcher *)arg;
	while (i < watcher_d->sim_d->num_philos)
	{
		sem_wait(watcher_d->sim_d->full);
		i++;
		if (watcher_d->sim_state == DEAD)
			return (NULL);
		if (i == watcher_d->sim_d->num_philos)
		{
			watcher_d->full = FULL;
			sem_post(watcher_d->sim_d->dead);
			return (NULL);
		}
	}
	return (NULL);
}

void	*watcher2(void *arg)
{
	int			i;
	t_watcher	*watcher_d;

	i = 0;
	watcher_d = (t_watcher *)arg;
	sem_wait(watcher_d->sim_d->dead);
	watcher_d->sim_state = DEAD;
	while (i < watcher_d->sim_d->num_philos)
	{
		sem_post(watcher_d->sim_d->full);
		i++;
	}
	return (NULL);
}

void	watchers(t_data *sim_d, int *ids)
{
	t_watcher	watcher_d1;
	t_watcher	watcher_d2;
	pthread_t	watcher_th[2];

	watcher_d1.sim_state = ALIVE;
	watcher_d2.sim_state = ALIVE;
	watcher_d1.full = HUNGRY;
	watcher_d2.full = HUNGRY;
	watcher_d1.sim_d = sim_d;
	watcher_d2.sim_d = sim_d;
	watcher_d1.ids = ids;
	watcher_d2.ids = ids;
	pthread_create(watcher_th, NULL, watcher1, &watcher_d1);
	pthread_create(watcher_th + 1, NULL, watcher2, &watcher_d2);
	pthread_join(watcher_th[0], NULL);
	pthread_join(watcher_th[1], NULL);
	kill_process(ids, sim_d->num_philos);
	release_semaphores(sim_d);
}
