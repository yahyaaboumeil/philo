#include "philo.h"


int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (c);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int check_is_dei(t_philo *philo)
{
	// printf("time - last = %d\n", (get_time() - philo->last_meal));
    return ((get_time() - philo->last_meal) > philo->info->time_to_dide);
}

int check_number_of_meals(t_philo *philo)
{
    if (philo->info->must_eate_counter != -1)
        return (philo->info->must_eate_counter == philo->meals_eaten);
    return (FALSE);
}

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