/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudzilo <ksudzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:52:06 by ksudzilo          #+#    #+#             */
/*   Updated: 2023/09/13 12:54:08 by ksudzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(long long int time, t_sage *sage, char *s)
{
	pthread_mutex_lock(sage->m_printf);
	if (!is_dead(sage))
		printf("%lld %d %s", time, sage->id + 1, s);
	pthread_mutex_unlock(sage->m_printf);
}

void	increment_count(t_sage *sage)
{
	pthread_mutex_lock(&(sage->m_count_eat));
	sage->count_eat++;
	pthread_mutex_unlock(&(sage->m_count_eat));
}

void	*woe_from_wit(void *arg)
{
	t_sage	*sage;

	sage = (t_sage *)arg;
	if (sage->id % 2 != 0)
		usleep(sage->last_meal_time * 1000);
	while (!is_dead(sage))
	{
		pthread_mutex_lock(sage->left_fork);
		print(get_time_in_ms(), sage, "has taken a fork\n");
		pthread_mutex_lock(sage->right_fork);
		print(get_time_in_ms(), sage, "has taken a fork\n");
		print(get_time_in_ms(), sage, "is eating\n");
		pthread_mutex_lock(&(sage->m_last_meal_time));
		sage->last_meal_time = get_time_in_ms();
		pthread_mutex_unlock(&(sage->m_last_meal_time));
		ft_my_usleep(sage, sage->eat_time);
		increment_count(sage);
		pthread_mutex_unlock(sage->left_fork);
		pthread_mutex_unlock(sage->right_fork);
		print(get_time_in_ms(), sage, "is sleeping\n");
		ft_my_usleep(sage, sage->sleep_time);
		print(get_time_in_ms(), sage, "is thinking\n");
	}
	return (NULL);
}

void	fiat_philosophi_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_philo)
	{
		pthread_create(&(data->philosophers[i].threads),
			NULL, &woe_from_wit, (void *)&(data->philosophers[i]));
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (null_argv(argc, argv) || !check_args(argc, argv))
		return (1);
	get_time_in_ms();
	if (init_data(&data, argv) == -1 || init_sage(&data, argv) == -1)
	{
		printf("Initialization error\n");
		return (1);
	}
	fiat_philosophi_threads(&data);
	while (1)
	{
		if (die_case(&data) == 1 || eat_case(&data) == 1)
			break ;
	}
	i = 0;
	while (i < data.count_philo && data.count_philo != 1)
	{
		pthread_join(data.philosophers[i].threads, NULL);
		i++;
	}
	cleanup(&data);
	return (0);
}
