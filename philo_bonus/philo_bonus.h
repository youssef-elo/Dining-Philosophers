/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:44:28 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/24 16:43:49 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdatomic.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ALIVE 0
# define DEAD 1
# define HUNGRY 0
# define FULL 1

typedef struct s_data
{
	int			id;
	int 		t_eat;
	int			t_sleep;
	int			meal_max;
	int			num_philos;
	_Atomic	int	philo_state;
	_Atomic int	satisfied;
	size_t		t_die;
	sem_t		*writing;
	sem_t		*forks;
}			t_data;

int	ft_atoi(char *str);
int	struct_init(int ac, char **av, t_data *sim_d);
int	init_semaphore(t_data *sim_d);
int	check_args(int ac, char **av);

#endif