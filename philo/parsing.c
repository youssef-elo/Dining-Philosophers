/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:53:30 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 17:49:35 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isallnum(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' && s[i + 1])
		i++;
	while (s[i])
	{
		if (!(s[i] <= '9' && s[i] >= '0'))
			return (0);
		i++;
	}
	return (1);
}

void	invalid_args(void)
{
	write(2, "Invalid arguments, Required arguments :\n", 40);
	write (2, "number_of_philosophers\ntime_to_die\n", 35);
	write(2, "time_to_eat\ntime_to_sleep\nnumber_o", 34);
	write(2, "f_times_each_philosopher_must_eat (optional)\n", 45);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		invalid_args();
		return (1);
	}
	while (i < ac)
	{
		if (!ft_isallnum(av[i]))
		{
			write(2, "Invalid arguments\n", 18);
			return (1);
		}
		i++;
	}
	return (0);
}

void	philo_lock_init(t_monitor *m, int *mutex_fail)
{
	int	i;

	i = 0;
	while (i < m->num_philos)
	{
		m->philos[i].philo_lock = ft_calloc(sizeof(pthread_mutex_t));
		if (!m->philos[i].philo_lock)
			cleanup(m);
		if (pthread_mutex_init(m->philos[i].philo_lock, NULL))
		{
			free(m->philos[i].philo_lock);
			m->philos[i].philo_lock = NULL;
			*mutex_fail = 1;
			break ;
		}
		i++;
	}
}

int	philo_mutex_init(t_monitor *m)
{
	int	mutex_fail;

	mutex_fail = 0;
	monitor_alloc(m);
	if (m->philos)
		philo_lock_init(m, &mutex_fail);
	if (!m->writing || !m->philos || !m->forks || mutex_fail)
	{
		cleanup(m);
		return (1);
	}
	return (0);
}
