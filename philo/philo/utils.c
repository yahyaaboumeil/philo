/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:55:24 by yaboumei          #+#    #+#             */
/*   Updated: 2025/07/12 20:55:28 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_action(t_philo *philo, char *messag)
{
	pthread_mutex_lock(&philo->info->write_lock);
	pthread_mutex_lock(&philo->info->die_lock);
	if (!philo->info->is_same_one_dei)
		printf(messag, get_time() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(&philo->info->die_lock);
	pthread_mutex_unlock(&philo->info->write_lock);
}
