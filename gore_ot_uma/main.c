#include "philo.h"

int is_dead(t_sage *sage)
{
    int val;

    pthread_mutex_lock(sage->m_die);
    val = *(sage->is_die);
    pthread_mutex_unlock(sage->m_die);
    return (val);
}

int init_data(t_data *data, char **argv)
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
        return -1;
    data->philosophers = (t_sage *)
        malloc(sizeof(t_sage) * data->count_philo);
    if (!data->philosophers)
        return -1;
    return 1;
}

void fork_init(t_data *data)
{
    int i;

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
int init_sage(t_data *data, char **argv)
{
    int i;

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
    return 1;
}



void *woe_from_wit(void *arg)
{
    t_sage *sage;

    sage = (t_sage *)arg;
    if (sage->id % 2 != 0)
        usleep(1000);
    while (!is_dead(sage))
    {
        pthread_mutex_lock(sage->left_fork);

        pthread_mutex_lock(sage->m_printf);
        if (!is_dead(sage))
            printf("%d %lld has taken left fork\n", sage->id + 1, get_time_in_ms());
        pthread_mutex_unlock(sage->m_printf);

        pthread_mutex_lock(sage->right_fork);

        pthread_mutex_lock(sage->m_printf);
        if (!is_dead(sage))
            printf("%d %lld has taken right fork\n", sage->id + 1, get_time_in_ms());
        pthread_mutex_unlock(sage->m_printf);

        pthread_mutex_lock(sage->m_printf);
        if (!is_dead(sage))
            printf("%d %lld is eating\n", sage->id + 1, get_time_in_ms());
        pthread_mutex_unlock(sage->m_printf);

        pthread_mutex_lock(&(sage->m_last_meal_time));  
        sage->last_meal_time = get_time_in_ms();
        pthread_mutex_unlock(&(sage->m_last_meal_time));

        ft_my_usleep(sage, sage->eat_time);

        pthread_mutex_lock(&(sage->m_count_eat)); 
        sage->count_eat++;
        pthread_mutex_unlock(&(sage->m_count_eat));

        pthread_mutex_unlock(sage->left_fork);
        pthread_mutex_unlock(sage->right_fork);

        pthread_mutex_lock(sage->m_printf);
        if (!is_dead(sage))
            printf("%d %lld is sleeping\n", sage->id + 1, get_time_in_ms());
        pthread_mutex_unlock(sage->m_printf);
        ft_my_usleep(sage, sage->sleep_time);

        pthread_mutex_lock(sage->m_printf);
        if (!is_dead(sage))
            printf("%d %lld is thinking\n", sage->id + 1, get_time_in_ms());
        pthread_mutex_unlock(sage->m_printf);
    }
    return (NULL);
}

int die_case(t_data *data)
{
    int i;

    i = 0;
    while (i < data->count_philo)
    {
        pthread_mutex_lock(&(data->philosophers[i].m_last_meal_time));
        if ((get_time_in_ms() - data->philosophers[i].last_meal_time) > data->die_time)
        {
            pthread_mutex_lock(&data->m_die);
            data->is_die = 1;
            pthread_mutex_unlock(&data->m_die);
            pthread_mutex_lock(&data->m_printf);
            printf("%d %lld dead\n", data->philosophers[i].id + 1, get_time_in_ms());
            pthread_mutex_unlock(&data->m_printf);
            pthread_mutex_unlock(&(data->philosophers[i].m_last_meal_time));
            return 1;
        }
        pthread_mutex_unlock(&(data->philosophers[i].m_last_meal_time));
        i++;
    }
    return 0;
}

int eat_case(t_data *data)
{
    int i;

    i = 0;
    while (i < data->count_philo && data->max_eat != 0)
    {
        pthread_mutex_lock(&(data->philosophers[i].m_count_eat));
        if (data->philosophers[i].count_eat >= data->max_eat)
        {
            pthread_mutex_unlock(&(data->philosophers[i].m_count_eat));
            i++;
        }
        else
        {
            pthread_mutex_unlock(&(data->philosophers[i].m_count_eat));
            break ;
        }
    }
    if (i == data->count_philo)
    {
        pthread_mutex_lock(&(data->m_die));
        data->is_die = 1;
        pthread_mutex_unlock(&(data->m_die));
        return 1;
    }
    return 0;
}
int main(int argc, char **argv)
{
    t_data data;
    (void)argc;
    int i;
    i = 0;
    //parsing
   get_time_in_ms();
    if (init_data(&data, argv) == -1)
    {
        printf("Data Init error\n");
        return 1;
    }
    if (init_sage(&data, argv) == -1)
    {
        printf("Sage init error\n");
        return 1;
    }
    while (i < data.count_philo)
    {
        pthread_create(&(data.philosophers[i].threads),
            NULL, &woe_from_wit, (void *)&(data.philosophers[i]));
        i++;
    }
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

    return 0;
}