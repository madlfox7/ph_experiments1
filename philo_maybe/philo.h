/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudzilo <ksudzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:26:11 by ksudzilo          #+#    #+#             */
/*   Updated: 2023/09/13 12:54:32 by ksudzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_sage
{
	long long		last_meal_time;
	int				eat_time;
	int				sleep_time;
	int				count_eat;
	int				id;
	int				*is_die;
	pthread_t		threads;
	pthread_mutex_t	m_last_meal_time;
	pthread_mutex_t	m_count_eat;
	pthread_mutex_t	*m_die;
	pthread_mutex_t	*m_printf;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_sage;

typedef struct s_data
{
	long long			die_time;
	int					count_philo;
	long				max_eat;
	int					is_die;
	pthread_mutex_t		*forks;
	pthread_mutex_t		m_die;
	pthread_mutex_t		m_printf;
	t_sage				*philosophers;
}					t_data;

int			null_argv(int ac, char **av);
int			is_num(char c);
int			limit(long long value);
long long	ft_atoi(const char *str);
void		error_msg(void);
int			ft_strlen(const char *str);
int			check_args(int argc, char **argv);
void		ft_my_usleep(t_sage *sage, int milisecs);
long long	ft_current_time(long long start);
long long	get_time_in_ms(void);
int			is_dead(t_sage *sage);
int			die_case(t_data *data);
int			eat_case(t_data *data);
int			init_sage(t_data *data, char **argv);
void		fork_init(t_data *data);
int			init_data(t_data *data, char **argv);
void		cleanup(t_data *data);

#endif
