/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudzilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:29:13 by ksudzilo          #+#    #+#             */
/*   Updated: 2023/09/04 14:34:12 by ksudzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv)
{
	data->die_time = ft_atoi(argv[2]);
	data->count_philo = ft_atoi(argv[1]);
	if (!argv[5])
		data->max_eat = 0;
	else
		data->max_eat = ft_atoi(argv[5]);
	data->is_die = 0;
	pthread_mutex_init(&(data->m_printf), NULL);
	pthread_mutex_init(&(data->m_die), NULL);
	data->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * data->count_philo);
	if (!data->forks)
		return (-1);
	data->philosophers = (t_sage *)
		malloc(sizeof(t_sage) * data->count_philo);
	if (!data->philosophers)
		return (-1);
	return (1);
}

void	fork_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_philo)
	{
		if (i == data->count_philo - 1)
		{
			data->philosophers[i].left_fork = &(data->forks[i]);
			data->philosophers[i].right_fork = &(data->forks[0]);
		}
		else
		{
			data->philosophers[i].left_fork = &(data->forks[i]);
			data->philosophers[i].right_fork = &(data->forks[i + 1]);
		}
		i++;
	}
}

int	init_sage(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (i < data->count_philo)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].eat_time = ft_atoi(argv[3]);
		data->philosophers[i].sleep_time = ft_atoi(argv[4]);
		data->philosophers[i].count_eat = 0;
		data->philosophers[i].last_meal_time = 0;
		data->philosophers[i].is_die = &(data->is_die);
		data->philosophers[i].m_printf = &(data->m_printf);
		data->philosophers[i].m_die = &(data->m_die);
		pthread_mutex_init(&(data->philosophers[i].m_last_meal_time), NULL);
		pthread_mutex_init(&(data->philosophers[i].m_count_eat), NULL);
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	fork_init(data);
	return (1);
}
