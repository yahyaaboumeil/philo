#include "philo.h"



void	*monitor(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (check_is_dei(philo))
	{
        pthread_mutex_lock(&philo->info->write_lock);
		printf("\033[1;31m%ld %d died ☠️\033[0m\n", get_time() - philo->info->start_time,
			philo->id);
		philo->info->is_same_one_dei = TRUE;
        return (NULL);
	}
	if (check_number_of_meals(philo))
	{
        philo->info->is_last_meal = TRUE;
		return (NULL);
	}
	return (NULL);
}