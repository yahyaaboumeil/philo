#include "philo.h"



void	*monitor(void *arg)
{
	t_philo *philo;
	t_philo	*temp;

	philo = (t_philo *)arg;
	while (1)
	{
		temp = philo;
		while (temp)
		{
			if (check_is_dei(philo) && !philo->info->is_same_one_dei)
			{
				pthread_mutex_lock(&philo->info->write_lock);
				printf("\033[1;31m%ld %d died ☠️\033[0m\n", get_time() - philo->info->start_time,
					philo->id);
				philo->info->is_same_one_dei = TRUE;
				pthread_mutex_unlock(&philo->info->write_lock);
				return (NULL);
			}
			// if (check_is_dei(philo))
			// {
			// 	pthread_mutex_lock(&philo->info->write_lock);
			// 	printf("\033[1;31m%ld %d died ☠️\033[0m\n", get_time() - philo->info->start_time,
			// 		philo->id);
			// 	pthread_mutex_unlock(&philo->info->write_lock);
			// 	philo->info->is_same_one_dei = TRUE;
			// 	return (NULL);
			// }
			temp = temp->next;
		}
	}
 	return (NULL);
 }
