/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:57:33 by yaboumei          #+#    #+#             */
/*   Updated: 2025/07/12 20:57:36 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	norminett(int *i, t_info *info)
{
	while (*i < info->num_philos)
	{
		if (check_number_of_meals(info))
		{
			pthread_mutex_lock(&info->lastmeal_lock);
			info->is_last_meal = TRUE;
			pthread_mutex_unlock(&info->lastmeal_lock);
			return (FALSE);
		}
		(*i)++;
	}
	return (TRUE);
}

int	norminett2(t_info *info)
{
	t_philo	*philos;
	long	time_since_last_meal;
	int		i;

	i = -1;
	philos = info->philo;
	while (++i < info->num_philos)
	{
		pthread_mutex_lock(&info->eate_lock);
		time_since_last_meal = get_time() - philos[i].last_meal;
		pthread_mutex_unlock(&info->eate_lock);
		if (time_since_last_meal >= info->time_to_dide)
		{
			print_action(&philos[i], "%ld %d died\n");
			pthread_mutex_lock(&info->die_lock);
			info->is_same_one_dei = TRUE;
			pthread_mutex_unlock(&info->die_lock);
			return (TRUE);
		}
	}
	return (FALSE);
}

void	*monitor(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info->die_lock);
		if (info->is_same_one_dei)
		{
			pthread_mutex_unlock(&info->die_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&info->die_lock);
		if (norminett2(info))
			i = 0;
		if (!norminett(&i, info))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
