#include "philo.h"

int	ft_isalnum(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' && s[i + 1])
		i++;
	while(s[i])
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
	while(i < ac)
	{
		if (!ft_isalnum(av[i]))
		{
			write(2, "Invalid arguments\n", 18);
			return (1);
		}
		i++;
	}
	return (0);
}
int	put_err(char *str, int len)
{
	write(2, str, len);
	return (1);
}
int	init_monitor(int ac, char **av, t_monitor *monitor_data)
{
	monitor_data->num_philos = ft_atoi(av[1]);
	if (monitor_data->num_philos > 600 || monitor_data->num_philos == -1)
		return(put_err("Too many philosophers\n", 22));
	monitor_data->t_die = ft_atoi(av[2]);
	if (monitor_data->t_die  == -1 || monitor_data->t_die < 60)
		return (put_err("time to die is invalid\n", 23));
	monitor_data->t_eat = ft_atoi(av[3]);
	if (monitor_data->t_eat == -1 || monitor_data->t_eat < 60)
		return (put_err("time to eat is invalid\n", 23));
	monitor_data->t_sleep = ft_atoi(av[4]);
	if (monitor_data->t_sleep == -1 || monitor_data->t_sleep < 60)
		return (put_err("time to sleep is invalid\n", 25));
	if (ac == 6)
	{
		monitor_data->meal_max = ft_atoi(av[5]);
		if (monitor_data->meal_max == -1)
			return (put_err("Number of meals is too big\n", 27));
	}
	else 
		monitor_data->meal_max = -1;
	return (0);
}

void *ft_calloc(int size)
{
	void *ret;

	ret = malloc(size);
	memset(ret, 0, size);
	return (ret);
}

void	cleanup(t_monitor *monitor_d)
{
	int	i;

	i = 0;
	if (monitor_d->writing)
	{
		pthread_mutex_destroy(monitor_d->writing);
		free(monitor_d->writing);
	}
	if (monitor_d->forks)
	{
		while(i < monitor_d->num_philos)
		{
			pthread_mutex_destroy(&(monitor_d->forks[i]));
			i++;
		}
		free(monitor_d->forks);
	}
	if (monitor_d->philos)
	{
		i = 0;
		while(i < monitor_d->num_philos)
		{
			if ((monitor_d->philos)[i].philo_lock)
			{
				pthread_mutex_destroy((monitor_d->philos)[i].philo_lock);
				free((monitor_d->philos)[i].philo_lock);
			}
			i++;
		}
		free(monitor_d->philos);
	}
	free(monitor_d->start);
}

int	philo_mutex_init(t_monitor *monitor_d)
{
	int	i;

	i = 0;
	monitor_d->start = ft_calloc(sizeof(struct timeval));
	monitor_d->writing = ft_calloc(sizeof(pthread_mutex_t));
	if(monitor_d->writing)
		pthread_mutex_init(monitor_d->writing, NULL);
	monitor_d->philos = ft_calloc(sizeof(t_philo) * monitor_d->num_philos);
	monitor_d->forks = ft_calloc(sizeof(pthread_mutex_t) * monitor_d->num_philos);
	monitor_d->philos_th = ft_calloc(sizeof(pthread_t) * monitor_d->num_philos);
	if (monitor_d->forks)
	{
		while(i < monitor_d->num_philos)
		{
			pthread_mutex_init(monitor_d->forks + i, NULL);
			i++;
		}
	}
	if (monitor_d->philos)
	{
		i = 0;
		while(i < monitor_d->num_philos)
		{
			monitor_d->philos[i].philo_lock = ft_calloc(sizeof(pthread_mutex_t));
			if (!monitor_d->philos[i].philo_lock)
				cleanup(monitor_d);
			pthread_mutex_init(monitor_d->philos[i].philo_lock, NULL);
			i++;
		}
	}
	if (!monitor_d->start || !monitor_d->writing || !monitor_d->philos || !monitor_d->forks)
	{
		cleanup(monitor_d);
		return (1);
	}
	i = 0;
	while(i < monitor_d->num_philos)
	{
		monitor_d->philos[i].id = i + 1;
		monitor_d->philos[i].right_fork = i;
		monitor_d->philos[i].left_fork = (i +1) % monitor_d->num_philos;
		i++;
	}
	return (0);
}

int sim_state(int action, int arg)
{
	static int state;

	if (action == SET)
		state = arg;
	if (action == GET)
		return (state);
	return (state);
}
size_t	elapsed_time(size_t start)
{
	struct timeval tim;
	size_t now;

	gettimeofday(&tim, NULL);
	now = (tim.tv_sec *1000) + (tim.tv_usec / 1000);
	return (now - start);
}

void	*monitor(void *arg)
{
	int i;
	int meal_maxed;
	t_monitor *monitor_d;

	i = 0;
	meal_maxed = 0;
	monitor_d = (t_monitor *)arg;
	while(i < monitor_d->num_philos)
	{
		pthread_mutex_lock(monitor_d->philos[i].philo_lock);
		if ((elapsed_time(monitor_d) - monitor_d->philos[i].last_meal) <= monitor_d->t_die)
		{
			if (monitor_d->meal_max != -1 && monitor_d->philos[i].number_of_meals < meal_maxed)
				sim_state(SET, ENDED);
		}
		if (monitor_d->meal_max != -1 && monitor_d->philos[i].number_of_meals == monitor_d)
			meal_maxed++;
		pthread_mutex_unlock(monitor_d->philos[i].philo_lock);
	}
	if (meal_maxed == monitor_d->meal_max)
		sim_state(SET, ENDED);
}

void print_monitor(t_monitor *m)
{
	printf("number of philos: %d\ntime to die: %d\ntime to eat: %d\ntime to sleep : %d\n meal max : %d\n", m->num_philos, m->t_die , m->t_eat, m->t_sleep, m->meal_max);
	gettimeofday(m->start, NULL);
	printf("start time : %ld\n", m->start);
	for ( int i =0; i < m->num_philos;i++)
		printf("philo :%d\tright : %d\tleft : %d\n", m->philos[i].id, m->philos[i].right_fork, m->philos[i].left_fork);
	printf("forks %p\n\nwriting%p\nthread %p\n", m->forks, m->writing, m->philos_th);
}

int	main(int ac, char **av)
{
	t_monitor	monitor_data;

	if (check_args(ac, av))
		return (1);
	if (init_monitor(ac, av, &monitor_data))
		return (2);
	if (philo_mutex_init(&monitor_data))
		return (3);
	print_monitor(&monitor_data);
}
 