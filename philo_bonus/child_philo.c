/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:40:06 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 18:19:11 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	announce_death(t_data *sim_d)
{
	sem_wait(sim_d->writing);
	printf("%ld %d died\n", elapsed_time(sim_d->start), sim_d->id);
	sem_post(sim_d->dead);
}

void	*monitor(void *arg)
{
	t_data	*sim_d;
	size_t	elapsed;

	sim_d = (t_data *)arg;
	if (sim_d->t_die <= (size_t)sim_d->t_eat)
		ft_usleep(sim_d, sim_d->t_die / 2);
	else
		ft_usleep(sim_d, sim_d->t_eat / 2);
	while (1)
	{
		elapsed = elapsed_time(sim_d->start) - sim_d->last_meal;
		if ((elapsed != 0) && (elapsed >= sim_d->t_die))
		{
			announce_death(sim_d);
		}
		usleep(500);
	}
}

void	safe_print(char *s, t_data *sim_d)
{
	sem_wait(sim_d->writing);
	printf("%ld %d %s\n", elapsed_time(sim_d->start), sim_d->id, s);
	sem_post(sim_d->writing);
}

void	philo_eat(t_data *sim_d)
{
	sem_wait(sim_d->forks);
	safe_print("has taken a fork", sim_d);
	if (sim_d->num_philos == 1)
		ft_usleep(sim_d, sim_d->t_die + 10000);
	sem_wait(sim_d->forks);
	sim_d->last_meal = elapsed_time(sim_d->start);
	sim_d->number_of_meals++;
	sem_wait(sim_d->writing);
	printf("%ld %d has taken a fork\n", elapsed_time(sim_d->start), sim_d->id);
	printf("%ld %d is eating\n", elapsed_time(sim_d->start), sim_d->id);
	sem_post(sim_d->writing);
	ft_usleep(sim_d, sim_d->t_eat);
	sem_post(sim_d->forks);
	sem_post(sim_d->forks);
}

void	*philo(t_data *sim_d)
{
	pthread_t	monitor_th;

	pthread_create(&monitor_th, NULL, monitor, sim_d);
	pthread_detach(monitor_th);
	sim_d->last_meal = elapsed_time(sim_d->start);
	if ((sim_d->id % 2 == 0) && sim_d->t_die <= (size_t)sim_d->t_eat)
		ft_usleep(sim_d, sim_d->t_die / 2);
	if ((sim_d->id % 2 == 0) && sim_d->t_die >= (size_t)sim_d->t_eat)
		ft_usleep(sim_d, sim_d->t_eat / 2);
	while (1)
	{
		philo_eat(sim_d);
		safe_print("is sleeping", sim_d);
		ft_usleep(sim_d, sim_d->t_sleep);
		safe_print("is thinking", sim_d);
		if (sim_d->meal_max != -1 && sim_d->meal_max == sim_d->number_of_meals)
		{
			sem_post(sim_d->full);
			exit(0);
		}
	}
}
