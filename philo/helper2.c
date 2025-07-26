/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:53:06 by yaboumei          #+#    #+#             */
/*   Updated: 2025/07/12 20:53:09 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_meme(t_philo *philo)
{
	int	i;

	i = 0;
	free(philo->info->forks);
	free(philo->info);
	free(philo);
}

void	print_parsing_err(void)
{
	printf("Invalid input, Pleas enter valid number : -)\n");
}

void	wait_for_treads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].info->num_philos)
	{
		if (pthread_join(philos[i].tread, NULL) != 0)
			perror("pthread_join");
		i++;
	}
}

void	ft_usleep_interruptible(t_philo *philo, long start, long milli)
{
	size_t	now;

	while (1)
	{
		now = get_time();
		pthread_mutex_lock(&(philo->info->die_lock));
		if (philo->info->is_same_one_dei)
		{
			pthread_mutex_unlock(&(philo->info->die_lock));
			return ;
		}
		pthread_mutex_unlock(&(philo->info->die_lock));
		if ((now - start) >= milli)
			break ;
		usleep(200);
	}
	return ;
}

void	case_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (philo->info->num_philos == 1)
	{
		print_action(philo, "%ld %d has taken a fork\n");
		usleep(philo->info->time_to_dide * 1000);
		print_action(&philo[0], "%ld %d died️\n");
		philo->info->is_same_one_dei = TRUE;
	}
	pthread_mutex_unlock(philo->right_fork);
}
