#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data
{
    long            opt;
    long			die_time;
	int			    num_of_ph;
	long			eat_time;
	long			sleep_time;
    int             die;
    int             begin_t;
    pthread_mutex_t		*forks; //to protect forks(lock - unlock)
    pthread_mutex_t		mutex_die;
    long long			start_time;
	// int					optional_arg;
	// pthread_mutex_t		mutex_stdout;
	// struct s_philo		*philo_array;
	// pthread_mutex_t		*mutex_forks;
	// int					flag_die;
	
}					t_data;

// typedef struct s_ph
// {
// 	// struct s_struct	*struct;
// 	// int				num;
// 	// pthread_t		threads;
// 	// long long		last_meal;
// 	// int				is_dead;
// 	// int				finished_eating;
// 	// int				flag_finished;
// 	// pthread_mutex_t	mutex_last_meal;
// 	// pthread_mutex_t	mutex_eating;
// }					t_ph;


int null_argv(int ac, char **av);
int is_num(char c);
int limit(long long value);
long long	ft_atoi(const char *str);
void error_msg(void);
int ft_strlen(const char *str);
int check_args(int argc, char **argv);
#endif