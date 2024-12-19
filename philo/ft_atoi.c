#include "philo.h"

int	ft_isspace(int c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long		r;
	long		check;

	i = 0;
	r = 0;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		check = r * 10 + (str[i] - 48);
		if (check < r)
			return (-1);
		r *= 10;
		r += (str[i] - 48);
		i++;
	}
	return (r);
}
