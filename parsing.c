#include "philo.h"

static int check_is_number(char *num)
{
    int i;
    
    i = 0;
    while (num[i])
    {
        if (!ft_isdigit(num[i]))
            return (FALSE);
        i++; 
    }
    return (TRUE);
}

int    pargsing(char **av, int type)
{
    int i;

    i = 1;
    while (i < 3)
    {
        if (!check_is_number(av[i])) 
            return (FALSE);
        i++;
    }
    if (type == FIVENUMBER)
    {
        if (!check_is_number(av[i]))
            return (FALSE);
    }
    return (TRUE);
}

t_info    *save_data_to_strcut(t_info *info, char **av, int type)
{
    info->num_philos = ft_atoi(av[1]);
    info->time_to_dide = ft_atoi(av[2]);
    info->time_to_eate = ft_atoi(av[3]);
    info->time_to_sleep = ft_atoi(av[4]);
    info->start_time = get_time();
    if (type == FIVENUMBER)
        info->must_eate_counter = ft_atoi(av[5]);
    else
        info->must_eate_counter = -1;
    return (info);
}
