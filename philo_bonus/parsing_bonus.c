/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:58:00 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/24 10:58:33 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

