#include "philo.h"

void    *test(t_philo *arr)
{

    arr[0].id = 0;
    arr[1].id = 1;
    arr[2].id = 2;
    return (arr);
}

int main(int ac, char **av)
{
    t_philo *philos;

    philos = test(philos);
    int i = 0; 
    while (i < 3) 
    {
        printf("num[%d] %d\n", i, philos[i].id);
        i++;
    }
}