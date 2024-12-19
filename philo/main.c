#include "philo.h"

int ft_isalnum(char *s)
{
	int i;

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

int check_args(int ac, char **av)
{
	int i;

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
			return (0);
		}
		i++;
	}
	return (1);
}
int	put_err(char *str, int len)
{
	write(2, str, len);
	return (1);
}
int	init_monitor(int ac, char **av, t_monitor *monitor_data)
{
	monitor_data->num_philos = ft_atoi(av[1]);
	if (monitor_data->num_philos > 600)
		return(put_err("Too many philosophers\n", 22));
	monitor_data->t_die = ft_atoi(av[2]);
	if (monitor_data->t_die  == -1)
		return (put_err("time to die is too big\n", 23));
	monitor_data->t_eat = ft_atoi(av[3]);
	if (monitor_data->t_eat == -1)
		return (put_err("time to eat is too big\n", 23));
	monitor_data->t_sleep = ft_atoi(av[4]);
	if (monitor_data->t_sleep == -1)
		return (put_err("time to sleep is too big\n", 25));
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

void	cleanup(t_monitor *monitor_d)
{
	int i;

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
		}
		free(monitor_d->forks);
	}
	free(monitor_d->philos);
	free(monitor_d->start);
}

int	philo_mutex_init(t_monitor *monitor_d)
{
	monitor_d->start = malloc(sizeof(struct timeval));
	monitor_d->writing = malloc(sizeof(pthread_mutex_t));
	monitor_d->philos = malloc(sizeof(t_philo) * monitor_d->num_philos);
	monitor_d->forks = malloc(sizeof(pthread_mutex_t) * monitor_d->num_philos);
	if (!monitor_d->start || !monitor_d->writing || !monitor_d->philos || monitor_d->forks)
	{
		cleanup(monitor_d);
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_monitor monitor_data;

	if (!check_args(ac, av))
		return (1);
	if (init_monitor(ac, av, &monitor_data))
		return (2);
	if (philo_mutex_init(&monitor_data))
		return (3);
}
 