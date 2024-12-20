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

typedef struct s_philo t_philo;
typedef struct s_monitor t_monitor;

typedef struct s_monitor
{
	size_t			t_die;
	int				t_eat;
	int				t_sleep;
	int				meal_max;
	int				num_philos;
	_Atomic int		sim_state;
	size_t			start;
	t_philo			*philos;
	pthread_t		*philos_th;
	pthread_mutex_t *forks;
	pthread_mutex_t	*writing;
}					t_monitor;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	_Atomic int		is_eating;
	int				number_of_meals;
	size_t			last_meal;
	t_monitor		*monitor;
	pthread_mutex_t	*philo_lock;
}					t_philo;

int	ft_atoi(char *str);
size_t	elapsed_time(size_t start);

#endif