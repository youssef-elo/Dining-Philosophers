/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:44:34 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 12:39:12 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	wait_childreen(void)
{
	int pid;
	int exit_s;

	pid = waitpid(-1, &exit_s, 0);
	while (pid != -1)
	{
		pid = waitpid(-1, &exit_s, 0);
	}
}

void kill_process(int *ids, int number)
{
	int i;

	i = 0;
	while (i < number)
	{
		kill(ids[i], SIGKILL);
		i++;
	}
	wait_childreen();
	free(ids);
}

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

void	*watcher1(void *arg)
{
	int				i;
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
	int i;
	t_watcher *watcher_d;

	i = 0;
	watcher_d = (t_watcher *)arg;
	sem_wait(watcher_d->sim_d->dead);
	watcher_d->sim_state = DEAD;
	while(i < watcher_d->sim_d->num_philos)
	{
		sem_post(watcher_d->sim_d->full);
		i++;
	}
	return (NULL);
}

void	watchers(t_data *sim_d, int *ids)
{
	t_watcher watcher_d1;
	t_watcher watcher_d2;
	pthread_t watcher_th[2];

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

void	forking_fail(t_data *sim_d, int *ids, int fail_i)
{
	kill_process(ids, fail_i);
	release_semaphores(sim_d);
	exit(1);
}

int	*make_childreen(t_data *sim_d, int i)
{
	int	f;
	int *ids;

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

int main(int ac, char **av)
{
	int *ids;
	t_data sim_d;

	int fd =open("f", O_RDWR);
	if ( fd == -1)
		exit(1);
	setbuf(stdout , NULL);
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
