/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:05:12 by yaboumei          #+#    #+#             */
/*   Updated: 2025/07/12 21:05:16 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_monitor(t_philo *philos);

void	run_threads(t_philo *philos)
{
	int	i;

	i = 0;
	init_forks_of_philos(philos);
	while (i < philos[0].info->num_philos)
	{
		if (pthread_create(&philos[i].tread, NULL, &routine, &philos[i]))
			perror("pthread_create");
		i++;
	}
}

void	run_monitor(t_philo *philos)
{
	pthread_t	monitor_th;

	if (pthread_create(&monitor_th, NULL, &monitor, philos[0].info))
		printf("pthread_create is failed\n");
	pthread_join(monitor_th, NULL);
}

int	philo(int ac, char **av)
{
	int		status;
	t_philo	*philos;

	if (ac == 5)
		status = pargsing(av, FORNUMBER);
	else
		status = pargsing(av, FIVENUMBER);
	if (status == FALSE)
		return (print_parsing_err(), 0);
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philos->info = malloc(sizeof(t_info));
	if (ac == 5)
		save_data_to_strcut(philos->info, av, FORNUMBER);
	else
		save_data_to_strcut(philos->info, av, FIVENUMBER);
	full_arr(philos);
	run_threads(philos);
	run_monitor(philos);
	wait_for_treads(philos);
	free_meme(philos);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 6 || ac == 5)
		philo(ac, av);
}
