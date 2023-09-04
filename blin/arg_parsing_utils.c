/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudzilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:17:23 by ksudzilo          #+#    #+#             */
/*   Updated: 2023/09/04 13:21:19 by ksudzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	limit(long long value)
{
	return (value < 1 || value > 2147483647);
}

int	null_argv(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!av[i] || av[i][0] == '\0')
		{
			printf("argv[%d] is NULL or empty\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

long long	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}
