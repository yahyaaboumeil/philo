/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:55:09 by yaboumei          #+#    #+#             */
/*   Updated: 2025/07/12 20:55:13 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->die_lock);
	pthread_mutex_unlock(&philo->info->die_lock);
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	pthread_mutex_lock(&philo->info->eate_lock);
	if (!(philo->info->must_eate_counter != -1
			&& philo->info->count_eaten == philo->info->must_eate_counter))
	{
		print_action(philo, "%ld %d has taken a fork\n");
		print_action(philo, "%ld %d has taken a fork\n");
	}
	pthread_mutex_unlock(&philo->info->eate_lock);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->die_lock);
	if (philo->info->is_same_one_dei || philo->info->is_last_meal)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->info->die_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->info->die_lock);
	if (!(philo->info->must_eate_counter != -1
			&& philo->info->count_eaten == philo->info->must_eate_counter))
		print_action(philo, "%ld %d is eating\n");
	pthread_mutex_lock(&philo->info->eate_lock);
	philo->info->count_how_many_philo_eat++;
	philo->last_meal = get_time();
	if (philo->info->count_how_many_philo_eat == philo->info->num_philos)
	{
		philo->info->count_how_many_philo_eat = 0;
		philo->info->count_eaten++;
	}
	pthread_mutex_unlock(&philo->info->eate_lock);
	ft_usleep_interruptible(philo, get_time(), philo->info->time_to_eate);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	thinking(t_philo *p)
{
	long	now;
	long	budget;
	long	think_time;

	pthread_mutex_lock(&p->info->die_lock);
	if (p->info->is_same_one_dei)
	{
		pthread_mutex_unlock(&p->info->die_lock);
		return ;
	}
	pthread_mutex_unlock(&p->info->die_lock);
	now = get_time();
	budget = p->info->time_to_dide - (now - p->last_meal) - 10;
	if (budget <= 0)
		return ;
	if (budget > p->info->time_to_sleep)
		budget = p->info->time_to_sleep;
	if (budget > p->info->time_to_eate)
		budget = p->info->time_to_eate;
	think_time = budget / 2;
	if (p->info->time_to_eate > p->info->time_to_sleep)
		think_time = p->info->time_to_eate * 2 - p->info->time_to_sleep;
	print_action(p, "%ld %d is thinking\n");
	ft_usleep_interruptible(p, get_time(), think_time);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->die_lock);
	if (philo->info->is_same_one_dei)
	{
		pthread_mutex_unlock(&philo->info->die_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->info->die_lock);
	print_action(philo, "%ld %d is sleeping\n");
	ft_usleep_interruptible(philo, get_time(), philo->info->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	if (philo->info->num_philos == 1)
		return (case_one_philo(philo), NULL);
	if (philo->id % 2)
		usleep(2000);
	while (1)
	{
		pthread_mutex_lock(&philo->info->die_lock);
		if (philo->info->is_same_one_dei)
		{
			pthread_mutex_unlock(&philo->info->die_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->info->die_lock);
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
