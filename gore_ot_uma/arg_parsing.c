#include "philo.h"

void error_msg(void)
{
   printf("Parsing error\n");
}


void print_usage(void)
{
      printf("Usage: ./philo num_of_philo "
              "time_to_die time_to_eat time_to_sleep "
              "[num_of_times_each_philo_must_eat]\n");
}

int check_args(int argc, char **argv)
{
    int i;
    int j;

    i = 0;
    if (argc != 5 && argc != 6)
    {
        print_usage();
        return 0;
    }
    while (++i < argc)
    {
        j = -1;
        while (argv[i][++j])
        {
            if (!is_num(argv[i][j]) || limit(ft_atoi(argv[i])) || (ft_strlen(argv[i]) > 10 && ft_atoi(argv[i]) < 0) || ft_atoi(argv[i]) > 2147483647)
            {
                error_msg();
                return 0;
            }
        }
    }
    return 1;
}
