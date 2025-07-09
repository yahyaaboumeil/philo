#include "philo.h"

// #include "err.c"
// #include "helper.c"
// #include "monitor.c"
// #include "parsing.c"
// #include "routin.c"

void	run_monitor(t_philo *philos);
int	add_back(t_philo **head, t_philo *philo)
{
	t_philo	*temp;
	t_philo	*new_philo;

	if (*head == NULL)
	{
		*head = creat_philo(philo);
		return (*head != NULL);
	}
	new_philo = creat_philo(philo);
	if (!new_philo)
		return (FALSE);
	temp = *head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new_philo;
}

t_philo	*creat_philo(t_philo *philo)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	new_philo->info = malloc(sizeof(t_info));
	if (!new_philo || !new_philo->info)
		return (NULL);
	new_philo->info->num_philos = philo->info->num_philos;
	new_philo->info->time_to_dide = philo->info->time_to_dide;
	new_philo->info->time_to_eate = philo->info->time_to_eate;
	new_philo->info->time_to_sleep = philo->info->time_to_sleep;
	new_philo->info->start_time = get_time();
	new_philo->info->must_eate_counter = philo->info->must_eate_counter;
	new_philo->left_fork = malloc(sizeof(pthread_mutex_t));
	new_philo->right_fork = malloc(sizeof(pthread_mutex_t));
	if (!new_philo->left_fork || !new_philo->right_fork)
		return (NULL);
	new_philo->next = NULL;
	return (new_philo);
}

t_philo	*list_of_philo(t_philo *philo)
{
	t_philo	*head;
	t_philo	*temp;
	int		i;

	i = 0;
	head = NULL;
	while (i < philo->info->num_philos)
	{
		if (!add_back(&head, philo))
			return (head);
		i++;
	}
	i = 0;
	temp = head;
	while (i < philo->info->num_philos)
	{
		temp->id = i + 1;
		temp = temp->next;
		i++;
	}
	return (head);
}

void	run_threads(t_philo *philos)
{
	t_philo	*temp;

	temp = philos;
	while (temp)
	{
		if (pthread_create(&temp->tread, NULL, &routine, temp))
			perror("pthread_create");
		usleep(1000);
		temp = temp->next;
	}
    run_monitor(philos);
}

void	run_monitor(t_philo *philos)
{
	t_philo	*temp;

	temp = philos;
	while (temp)
	{
		if (pthread_create(&temp->tread, NULL, &monitor, temp))
			perror("pthread_create");
		temp = temp->next;
	}
}

void	wait_for_treads(t_philo *philos)
{
	t_philo	*temp;

	temp = philos;
	while (temp)
	{
		if (pthread_join(temp->tread, NULL) != 0)
		{
			perror("pthread_join");
		}
		temp = temp->next;
	}
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
	philos = malloc(sizeof(t_philo));
	philos->info = malloc(sizeof(t_info));
	if ((!philos || !philos->info) || (av[1][0] == '1' && !av[1][1]))
		return (0);
	if (ac == 5)
		save_data_to_strcut(philos->info, av, FORNUMBER);
	else
		save_data_to_strcut(philos->info, av, FIVENUMBER);
	philos = list_of_philo(philos);
	creat_philo(philos);
	run_threads(philos);
	// run_monitor(philos);
	wait_for_treads(philos);
	free_meme(philos);
	return (1);
}

int	main(int ac, char **av)
{
    // ac = 5;
    // av[1] = "5";
    // av[2] = "800";
    // av[3] = "200";
    // av[4] = "200"; 
	if (ac == 6 || ac == 5)
		philo(ac, av);
}