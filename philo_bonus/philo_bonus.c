/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:44:34 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/24 16:59:57 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	wait_childreen(void)
{
	int pid;
	int exit_s;

	pid = waitpid(-1, &exit_s, 0);
	while(pid != -1)
	{
		pid = waitpid(-1, &exit_s, 0);
	}
}

void kill_process(int *ids, int number)
{
	int i;

	i = 0;
	while(i < number)
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
	sem_close(sim_d->writing);
	sem_close(sim_d->forks);
	sem_unlink("/lektaba");
	sem_unlink("/forks");
}

int	*start_sim(t_data *sim_d)
{
	int i;
	int	f;
	int *ids;
	
	i = 0;
	ids = ft_calloc(sizeof(int) * sim_d->num_philos);
	while(i < sim_d->num_philos)
	{
		sim_d->id = i + 1;
		f = fork();
		if ( f == -1)
		{
			kill_process(ids, i);
			release_semaphores(sim_d);
			exit(1);	
		}
		if (f == 0)
			philo(sim_d);
		else
			ids[i] = f;
	}
	return (ids);
}


void	watcher(t_data	*sim_d)
{
	
}

int main(int ac, char **av)
{
	t_data sim_d;

	if (check_args(ac, av))
		return (1);
	if (struct_init(ac, av, &sim_d))
		return (2);
	if (init_semaphore(&sim_d))
		return (3);
	start_sim(&sim_d);
	watcher(&sim_d);
}