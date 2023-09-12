/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudzilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:28:14 by ksudzilo          #+#    #+#             */
/*   Updated: 2023/09/04 13:37:04 by ksudzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval		tv;
	static long long	start;
	static int			count;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (count == 0)
	{
		start = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
		count++;
	}
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start);
}

void	ft_my_usleep(t_sage *sage, int milisecs)
{
	long long	t_start;

	t_start = get_time_in_ms();
	while (!is_dead(sage))
	{
		if (get_time_in_ms() - t_start < milisecs)
			usleep(50);
		else
			break ;
	}
}
