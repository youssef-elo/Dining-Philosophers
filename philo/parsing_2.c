/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:05:42 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/12/23 16:06:14 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_err(char *str, int len)
{
	write(2, str, len);
	return (1);
}

void	*ft_calloc(int size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	memset(ret, 0, size);
	return (ret);
}
