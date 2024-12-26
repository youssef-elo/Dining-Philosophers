/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:40:06 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 12:38:07 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_usleep(t_data *sim_d, size_t duration_ms)
{
	size_t	start;
	size_t	elapsed;

	start = elapsed_time(sim_d->start);
	while (1)
	{
		elapsed = elapsed_time(sim_d->start) - start;
		if (elapsed >= duration_ms)
			break ;
		usleep(500);
	}
	return (0);
}

size_t	elapsed_time(size_t start)
{
	struct timeval	tim;
	size_t			now;

	gettimeofday(&tim, NULL);
	now = (tim.tv_sec * 1000) + (tim.tv_usec / 1000);
	return (now - start);
}

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
	while(1)
	{
		elapsed = elapsed_time(sim_d->start) - sim_d->last_meal;
		if ((elapsed != 0) && (elapsed >= sim_d->t_die))
		{
			announce_death(sim_d);
		}
		usleep(500);
	}
}

void	*philo(t_data *sim_d)
{
	pthread_t monitor_th;

	// sem_wait(sim_d->green_light);
	pthread_create(&monitor_th, NULL, monitor, sim_d);
	pthread_detach(monitor_th);

	sim_d->last_meal = elapsed_time(sim_d->start);
	if ((sim_d->id % 2 == 0) && sim_d->t_die <= (size_t)sim_d->t_eat)
		ft_usleep(sim_d, sim_d->t_die / 2);
	if ((sim_d->id % 2 == 0) && sim_d->t_die >= (size_t)sim_d->t_eat)
		ft_usleep(sim_d, sim_d->t_eat / 2);
	while (1)
	{
		sem_wait(sim_d->forks);
		sem_wait(sim_d->writing);
		printf("%ld %d has taken a fork\n", elapsed_time(sim_d->start), sim_d->id);
		sem_post(sim_d->writing);

		if (sim_d->num_philos == 1)
			ft_usleep(sim_d, sim_d->t_die + 10000);

		sem_wait(sim_d->forks);

		sim_d->last_meal = elapsed_time(sim_d->start);
		sim_d->number_of_meals++;
		sem_wait(sim_d->writing);

		printf("%ld %d has taken a fork\n", elapsed_time(sim_d->start), sim_d->id);

		printf("%ld %d is eating\n", elapsed_time(sim_d->start), sim_d->id);
////		if (sim_d->meal_max != -1 && sim_d->meal_max == sim_d->number_of_meals)
//		{
//			sem_post(sim_d->full);
			// usleep(200);
			// exit(0);
//		}
		sem_post(sim_d->writing);
		ft_usleep(sim_d, sim_d->t_eat);

		sem_post(sim_d->forks);
		sem_post(sim_d->forks);

		sem_wait(sim_d->writing);
		printf("%ld %d is sleeping\n", elapsed_time(sim_d->start), sim_d->id);
		sem_post(sim_d->writing);
		ft_usleep(sim_d, sim_d->t_sleep);

		sem_wait(sim_d->writing);
		printf("%ld %d is thinking\n", elapsed_time(sim_d->start), sim_d->id);
		sem_post(sim_d->writing);

		if ( sim_d->meal_max != -1 && sim_d->meal_max == sim_d->number_of_meals)
		{
			sem_post(sim_d->full);
			exit(0);
		}
	}
}

// 5 800 200 200 dies prematurelly
