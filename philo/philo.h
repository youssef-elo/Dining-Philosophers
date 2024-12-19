#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_monitor
{
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			meal_max;
	long			num_philos;
	struct timeval	*start;
	pthread_mutex_t *forks;
	pthread_t		*philos;
	pthread_mutex_t	*writing;
}					t_monitor;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	long			number_of_meals;
	t_monitor		*monitor;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*philo_lock;
}					t_philo;

int	ft_atoi(char *str);

#endif