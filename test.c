#include "philo.h"


int main(int ac, char **av)
{
    t_philo *philos;

    save_data_to_strcut(philos->info, av, FORNUMBER);
   int i = 0; 
    while (i < philos->info->num_philos) 
    {
        printf("num[%d] %d\n", i,philos[i].info->num_philos);
        i++;
    }
}