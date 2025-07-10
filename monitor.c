#include "philo.h"


// void	*monitor(void *arg)
// {
// 	t_info *philo;
// 	t_info	*temp;

// 	philo = (t_info *)arg;
// 	while (1)
// 	{
// 		temp = philo;
// 		temp->philo = philo->philo;
// 		while (temp->philo)
// 		{
// 			if (check_is_dei(temp->philo))
// 			{
// 				printf("\033[1;31m%ld %d died ☠️\033[0m\n", get_time() - temp->start_time,
// 				temp->philo->id);
// 				pthread_mutex_lock(&temp->die_lock);	
// 				temp->is_same_one_dei = TRUE;
// 				pthread_mutex_unlock(&temp->die_lock);	
// 				return (NULL);
// 			}
// 			// if (check_is_dei(philo))
// 			// {
// 				// 	pthread_mutex_lock(&philo->info->write_lock);
// 				// 	printf("\033[1;31m%ld %d died ☠️\033[0m\n", get_time() - philo->info->start_time,
// 				// 		philo->id);
// 				// 	pthread_mutex_unlock(&philo->info->write_lock);
// 				// 	philo->info->is_same_one_dei = TRUE;
// 				// 	return (NULL);
// 				// }
// 				temp->philo = temp->philo->next;
// 			}
// 			usleep(1000);
// 	}
//  	return (NULL);
//  }

void *monitor(void *arg)
{
	t_info	*info = (t_info *)arg;
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < info->num_philos)
		{
			// pthread_mutex_lock(&info->die_lock);
			// if (info->is_same_one_dei)
			// {
			// 	pthread_mutex_unlock(&info->die_lock);
			// 	return (NULL); // Stop monitoring if someone already died
			// }
			// pthread_mutex_unlock(&info->die_lock);

			int n = check_is_dei(&info->philo[i]);
			if (n == 1)
			{
				print_action(&info->philo[i], "\033[1;31m%ld %d died️\033[0m\n");
				pthread_mutex_lock(&info->die_lock);
				info->is_same_one_dei = TRUE;
				pthread_mutex_unlock(&info->die_lock);
				return (NULL);
			}
			i++;
		}
		usleep(1000); 
	}
	return (NULL);
}
