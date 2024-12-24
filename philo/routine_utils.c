/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:47:11 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/24 13:05:55 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_first(t_philo *philo, int first)
{
	pthread_mutex_lock(&(philo->monitor->forks[first]));
	if (philo->monitor->sim_state == ENDED || philo->monitor->satisfied == FULL)
	{
		pthread_mutex_unlock(&(philo->monitor->forks[first]));
		return (1);
	}
	pthread_mutex_lock(philo->monitor->writing);
	if (philo->monitor->sim_state == ENDED || philo->monitor->satisfied == FULL)
	{
		pthread_mutex_unlock(&(philo->monitor->forks[first]));
		pthread_mutex_unlock(philo->monitor->writing);
		return (1);
	}
	printf("%ld %d has taken a fork\n",
		elapsed_time(philo->monitor->start), philo->id);
	pthread_mutex_unlock(philo->monitor->writing);
	if (philo->right_fork == philo->left_fork)
	{
		pthread_mutex_unlock(&(philo->monitor->forks[first]));
		return (1);
	}
	return (0);
}

int	lock_forks(t_philo *philo, int first, int second)
{
	if (philo->monitor->sim_state == ENDED || philo->monitor->satisfied == FULL)
		return (1);
	if (lock_first(philo, first))
		return (1);
	pthread_mutex_lock(&(philo->monitor->forks[second]));
	if (philo->monitor->sim_state == ENDED
		|| philo->monitor->satisfied == FULL)
	{
		pthread_mutex_unlock(&(philo->monitor->forks[first]));
		pthread_mutex_unlock(&(philo->monitor->forks[second]));
		return (1);
	}
	pthread_mutex_lock(philo->monitor->writing);
	if (philo->monitor->sim_state == ENDED
		|| philo->monitor->satisfied == FULL)
	{
		pthread_mutex_unlock(&(philo->monitor->forks[first]));
		pthread_mutex_unlock(&(philo->monitor->forks[second]));
		pthread_mutex_unlock(philo->monitor->writing);
		return (1);
	}
	printf("%ld %d has taken a fork\n",
		elapsed_time(philo->monitor->start), philo->id);
	pthread_mutex_unlock(philo->monitor->writing);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_lock);
	philo->last_meal = elapsed_time(philo->monitor->start);
	philo->number_of_meals += 1;
	pthread_mutex_unlock(philo->philo_lock);
	pthread_mutex_lock(philo->monitor->writing);
	if (philo->monitor->sim_state == ENDED || philo->monitor->satisfied == FULL)
	{
		pthread_mutex_unlock(philo->monitor->writing);
		pthread_mutex_unlock(&(philo->monitor->forks[philo->right_fork]));
		pthread_mutex_unlock(&(philo->monitor->forks[philo->left_fork]));
		return (1);
	}
	printf("%ld %d is eating\n", elapsed_time(philo->monitor->start), philo->id);
	pthread_mutex_unlock(philo->monitor->writing);
	ft_usleep(philo, philo->monitor->t_eat);
	pthread_mutex_unlock(&(philo->monitor->forks[philo->right_fork]));
	pthread_mutex_unlock(&(philo->monitor->forks[philo->left_fork]));
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (philo->monitor->sim_state == ENDED)
		return (1);
	pthread_mutex_lock(philo->monitor->writing);
	if (philo->monitor->sim_state == ENDED)
	{
		pthread_mutex_unlock(philo->monitor->writing);
		return (1);
	}
	printf("%ld %d is sleeping\n",
		elapsed_time(philo->monitor->start), philo->id);
	pthread_mutex_unlock(philo->monitor->writing);
	if (philo->monitor->sim_state == ENDED)
		return (1);
	ft_usleep(philo, philo->monitor->t_sleep);
	return (0);
}
