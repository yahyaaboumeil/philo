#include "philo.h"



void	*monitor(void *arg)
{
	t_info *philo;
	t_info	*temp;

	philo = (t_info *)arg;
	while (1)
	{
		temp = philo;
		temp->philo = philo->philo;
		while (temp->philo)
		{
			if (check_is_dei(temp->philo))
			{
				pthread_mutex_lock(&temp->write_lock);
				if (!temp->is_same_one_dei)
				{
					printf("\033[1;31m%ld %d died ☠️\033[0m\n", get_time() - temp->start_time,
						temp->philo->id);
					temp->is_same_one_dei = TRUE;
					return (NULL);
				}
				pthread_mutex_unlock(&temp->write_lock);
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
			temp->philo = temp->philo->next;
		}
	}
 	return (NULL);
 }
