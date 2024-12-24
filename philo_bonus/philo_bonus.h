/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:44:28 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/24 11:18:43 by yel-ouaz         ###   ########.fr       */
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

# define STILL 0
# define ENDED 1
# define HUNGRY 0
# define FULL 1

typedef struct s_child
{
	int			id;
	int 		t_eat;
	int			t_sleep;
	int			meal_max;
	_Atomic	int	philo_state;
	_Atomic int	satisfied;
	size_t		t_die;
	char		*writing;
	char		*forks;
	
}			t_child;

#endif