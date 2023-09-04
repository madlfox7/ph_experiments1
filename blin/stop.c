#include "philo.h"

int is_dead(t_sage *sage)
{
    int val;

    pthread_mutex_lock(sage->m_die);
    val = *(sage->is_die);
    pthread_mutex_unlock(sage->m_die);
    return (val);
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
            printf("%lld %d died\n", get_time_in_ms(), data->philosophers[i].id + 1);
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