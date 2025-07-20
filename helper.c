/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:53:54 by yaboumei          #+#    #+#             */
/*   Updated: 2025/07/12 20:53:58 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_dei(t_philo *philo)
{
	size_t	n;
	int		result;

	result = 0;
	pthread_mutex_lock(&philo->info->eate_lock);
	n = get_time() - philo->last_meal;
	result = (n >= philo->info->time_to_dide);
	pthread_mutex_unlock(&philo->info->eate_lock);
	return (result);
}

int	check_number_of_meals(t_info *info)
{
	size_t	result;

	result = 0;
	pthread_mutex_lock(&info->eate_lock);
	if (info->must_eate_counter != -1)
	{
		if (info->count_eaten == info->must_eate_counter)
		{
			pthread_mutex_lock(&info->die_lock);
			info->is_same_one_dei = TRUE;
			pthread_mutex_unlock(&info->die_lock);
			result = (info->count_eaten / info->num_philos);
			result = (result == info->num_philos);
		}
		pthread_mutex_unlock(&info->eate_lock);
		return (result);
	}
	pthread_mutex_unlock(&info->eate_lock);
	return (FALSE);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	init_forks_of_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->num_philos)
	{
		philos[i].last_meal = get_time();
		philos[i].left_fork = &philos->info->forks[i];
		philos[i].right_fork = &philos->info->forks[(i + 1)
			% philos->info->num_philos];
		i++;
	}
}
