/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:54:16 by yaboumei          #+#    #+#             */
/*   Updated: 2025/07/12 20:54:20 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_is_number(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '0' && num[1] == 0)
		return (FALSE);
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	pargsing(char **av, int type)
{
	int	i;

	i = 1;
	while (i < type)
	{
		if (!check_is_number(av[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	init_forks(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	i = 0;
	while (i < info->num_philos)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
}

t_info	*save_data_to_strcut(t_info *info, char **av, int type)
{
	info->num_philos = ft_atoi(av[1]);
	info->time_to_dide = ft_atoi(av[2]);
	info->time_to_eate = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->is_last_meal = FALSE;
	info->is_same_one_dei = FALSE;
	info->start_time = get_time();
	info->count_eaten = 0;
	info->count_how_many_philo_eat = 0;
	init_forks(info);
	pthread_mutex_init(&info->eate_lock, NULL);
	pthread_mutex_init(&info->die_lock, NULL);
	pthread_mutex_init(&info->write_lock, NULL);
	if (type == FIVENUMBER)
		info->must_eate_counter = ft_atoi(av[5]);
	else
		info->must_eate_counter = -1;
	return (info);
}

void	full_arr(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].info->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].meals_eaten = 0;
		philo[i].info = philo[0].info;
		philo[i].info->philo = &philo[0];
		i++;
	}
}
