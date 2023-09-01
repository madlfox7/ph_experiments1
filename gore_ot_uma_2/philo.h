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
    long  long         		die_time;     // argv[2]
    int             	count_philo;      // argv[1]
    long           		max_eat; //  argv[5]
    int					is_die; 
    pthread_mutex_t    	*forks;        
    pthread_mutex_t		m_die;   
    pthread_mutex_t		m_printf;  //printf protection
    t_sage          	*philosophers; // Array of ph structures
}					t_data;



int null_argv(int ac, char **av);
int is_num(char c);
int limit(long long value);
long long	ft_atoi(const char *str);
void error_msg(void);
int ft_strlen(const char *str);
int check_args(int argc, char **argv);

void	ft_my_usleep(t_sage *sage, int milisecs);
long long	ft_current_time(long long start);
long long get_time_in_ms(void);

int is_dead(t_sage *sage);

#endif