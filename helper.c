#include "philo.h"

long    get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

// int main()
// {
//     printf("time = %ld \n\n", get_time())
// }