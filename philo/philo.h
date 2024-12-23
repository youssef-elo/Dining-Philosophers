/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:52:08 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/23 16:11:17 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdatomic.h>

# define SET 0
# define GET 1
# define STILL 0
# define ENDED 1
# define HUNGRY 0
# define FULL 1

typedef struct s_philo		t_philo;
typedef struct s_monitor	t_monitor;

typedef struct s_monitor
{
	size_t			t_die;
	int				t_eat;
	int				t_sleep;
	int				meal_max;
	int				num_philos;
	_Atomic int		sim_state;
	_Atomic int		satisfied;
	size_t			start;
	t_philo			*philos;
	pthread_t		*philos_th;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*writing;
}					t_monitor;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				number_of_meals;
	size_t			last_meal;
	t_monitor		*monitor;
	pthread_mutex_t	*philo_lock;
}					t_philo;

int		ft_atoi(char *str);
void	*monitor(void *arg);
void	*ft_calloc(int size);
void	*philo_routine(void *arg);
int		get_forks(t_philo *philo);
int		philo_eat(t_philo *philo);
size_t	elapsed_time(size_t start);
int		philo_sleep(t_philo *philo);
int		put_err(char *str, int len);
int		philo_think(t_philo *philo);
int		check_args(int ac, char **av);
void	cleanup(t_monitor *monitor_d);
void	monitor_alloc(t_monitor *monitor_d);
void	init_philo_time(t_monitor *monitor_d);
int		philo_mutex_init(t_monitor *monitor_d);
int		ft_usleep(t_philo *philo, size_t duration);
int		lock_forks(t_philo *philo, int first, int second);
int		init_monitor(int ac, char **av, t_monitor *monitor_data);
void	join_clean(t_monitor *monitor_d, pthread_t monitor_th, int i, int m);

#endif