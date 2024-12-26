/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:44:28 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/26 18:27:16 by yel-ouaz         ###   ########.fr       */
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
# include <string.h>
# include <sys/time.h>

# define ALIVE 0
# define DEAD 1
# define HUNGRY 0
# define FULL 1

# define WRITESM "/lektaba"
# define FORKSM "/forks"
# define DEADSM "/dead"
# define FULLSM "/full"
# define PHILOSM "/philo_lock"

typedef struct s_data
{
	int			id;
	int			t_eat;
	int			t_sleep;
	int			meal_max;
	int			num_philos;
	int			number_of_meals;
	size_t		t_die;
	size_t		start;
	size_t		last_meal;
	sem_t		*writing;
	sem_t		*forks;
	sem_t		*dead;
	sem_t		*full;
	sem_t		*philo_lock;
}				t_data;

typedef struct s_watcher
{
	_Atomic int	full;
	_Atomic int	sim_state;
	int			*ids;
	t_data		*sim_d;
}				t_watcher;

int		ft_atoi(char *str);
void	*philo(t_data *sim_d);
size_t	elapsed_time(size_t start);
int		init_semaphore(t_data *sim_d);
int		check_args(int ac, char **av);
void	announce_death(t_data *sim_d);
void	watchers(t_data *sim_d, int *ids);
void	release_semaphores(t_data *sim_d);
void	kill_process(int *ids, int number);
int		*make_childreen(t_data *sim_d, int i);
int		ft_usleep(t_data *sim_d, size_t duration_ms);
int		struct_init(int ac, char **av, t_data *sim_d);
#endif