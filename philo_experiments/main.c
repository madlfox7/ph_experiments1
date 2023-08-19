#include "philo.h"
#include <sys/time.h>

unsigned long long	get_current_time(long long start_time)
{
	struct timeval	tv;
	unsigned long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time;
	return (ms);
}

unsigned long long	get_time(void)
{
	struct timeval	tv;
	unsigned long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(unsigned long long ms)
{
	long long	start;
 
	start = get_time();
	while ((get_time() - start) < ms)
		usleep(ms / 10);
}


void	ft_create_mutex_forks(t_data *data, int num)
{
	int	i;

	data->forks = malloc(num * sizeof(pthread_mutex_t));
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&data->forks[i], 0); //default mutex, with 0
		i++;
	}
} //review and dealloc mem 



void init_num_fields(int argc, char **argv, t_data *data)
{
    data->num_of_ph = ft_atoi(argv[1]);
    data->die_time = ft_atoi(argv[2]);
    data->eat_time = ft_atoi(argv[3]);
    data->sleep_time = ft_atoi(argv[4]);
    data->opt = 0;
    if (argc == 6)
        data->opt = ft_atoi(argv[5]);
    // pthread_mutex_init(&(data->mutex_stdout), 0);
	pthread_mutex_init(&(data->mutex_die), 0);
	ft_create_mutex_forks(data, data->num_of_ph);
	//data->start_time = ft_get_time();

    struct timeval current_time;
     gettimeofday(&current_time, NULL);
     printf("%lld\n", get_time());
     printf("sec : %ld\nmicro sec :%d", current_time.tv_sec, current_time.tv_usec);

	data->die = 0;
}

int init_struct(int argc, char **argv, t_data *data)
{
    if (ft_atoi(argv[1]) == 0)
        return 0;
    init_num_fields(argc, argv, data);
    return 1;
}


void philo(t_data *data)
{
    (void)data;

    unsigned long long start_time = 0;
    start_time = get_time();

    printf("\nstart time %llu\n", start_time);
    usleep(2500);
    
    printf("curr_time %llu\n", get_current_time(start_time));
}
int main(int argc, char **argv)
{
    t_data data;

    if (null_argv(argc, argv) || !check_args(argc, argv))
        return 1;
    if (!init_struct(argc, argv, &data))
    {
        printf("Memory allocation error\n");
        return 1;
    }
    philo(&data);

    return 0;
}