#include "philo.h"


long long get_time_in_ms(void) 
{ 
    struct timeval tv; 
    static long long start;
    static int count;


    if (gettimeofday(&tv, NULL) != 0)
        return -1; 
    if (count == 0)
    {
        start =  (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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

long long	ft_current_time(long long start)
{
	struct timeval	tv;
	
      if (gettimeofday(&tv, NULL) != 0)
            return -1; 
	return  (tv.tv_sec * 1000 + tv.tv_usec / 1000) - start;
}
