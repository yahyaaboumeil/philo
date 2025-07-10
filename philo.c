#include "philo.h"

// #include "err.c"
// #include "helper.c"
// #include "monitor.c"
// #include "parsing.c"
// #include "routin.c"

void	run_monitor(t_philo *philos);


void	init_forks_of_philos(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < philos->info->num_philos)
	{

    	//pthread_mutex_lock(&philos->info->eate_lock);
    	philos[i].last_meal = get_time();
   		//pthread_mutex_unlock(&philos->info->eate_lock);
		if (!(i + 1 == philos->info->num_philos))
		{
			philos[i].left_fork = &philos->info->forks[i+1];
			philos[i].right_fork = &philos->info->forks[i];
		}
		else 
		{
			philos[i].left_fork = &philos->info->forks[0];
			philos[i].right_fork = &philos->info->forks[i];
		}
		i++;
	}
}

void	run_threads(t_philo *philos)
{
	int	i;

	i = 0;
		
	init_forks_of_philos(philos);
	printf("%d\n",  philos[0].info->num_philos);
	while (i < philos[0].info->num_philos)
	{
		if (pthread_create(&philos[i].tread, NULL, &routine, &philos[i]))
			perror("pthread_create");
		i++;
	}
		// usleep(1000);
}

void	run_monitor(t_philo *philos)
{
	pthread_t monitor_th;

	if (pthread_create(&monitor_th, NULL, &monitor, philos[0].info))
		perror("pthread_create");
	pthread_join(monitor_th, NULL);
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


t_philo	*full_arr(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].info->num_philos)
	{
		philo[i].id = i+1;
		philo[i].last_meal = 0;
		philo[i].meals_eaten = 0;
		philo[i].info = philo[0].info;
		philo[i].info->philo = &philo[0];
		i++;
	}
}


int	philo(int ac, char **av)
{
	int		status;
    t_philo *philos;

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
	// free_meme(philos);
	return (1);
}

int	main(int ac, char **av)
{
	// ac = 5;
	// av[1] = "200";
	// av[2] = "410";
	// av[3] = "200";
	// av[4] = "200";
	if (ac == 6 || ac == 5)
		philo(ac, av);
}




// int	philo(int ac, char **av)
// {
// 	int		status;
//     t_philo *philos;

// 	if (ac == 5)
// 		status = pargsing(av, FORNUMBER);
// 	else
// 		status = pargsing(av, FIVENUMBER);
// 	if (status == FALSE)
// 		return (print_parsing_err(), 0);
// 	philos = malloc(sizeof(t_philo));
// 	philos->info = malloc(sizeof(t_info));
// 	if ((!philos || !philos->info) || (av[1][0] == '1' && !av[1][1]))
// 		return (0);
// 	if (ac == 5)
// 		save_data_to_strcut(philos->info, av, FORNUMBER);
// 	else
// 		save_data_to_strcut(philos->info, av, FIVENUMBER);
// 	philos = list_of_philo(philos);
// 	creat_philo(philos);
// 	run_threads(philos);
// 	// monitor(philos);
// 	run_monitor(philos);
// 	wait_for_treads(philos);
// 	// free_meme(philos);
// 	return (1);
// }


// void	wait_for_treads(t_philo *philos)
// {
// 	t_philo	*temp;

// 	temp = philos;
// 	while (temp)
// 	{
// 		if (pthread_join(temp->tread, NULL) != 0)
// 		{
// 			perror("pthread_join");
// 		}
// 	}
// }

// void	run_monitor(t_philo *philos)
// {
// 	t_philo	*temp;

// 	temp = philos;
// 	if (pthread_create(&temp->tread, NULL, &monitor, temp->info))
// 		perror("pthread_create");
// }

// void	run_threads(t_philo *philos)
// {
// 	t_philo	*temp;

// 	temp = philos;
// 	init_forks_of_philos(philos);
// 	while (temp)
// 	{
// 		if (pthread_create(&temp->tread, NULL, &routine, temp))
// 			perror("pthread_create");
// 		temp = temp->next;
// 	}
// 		// usleep(1000);
// }

// t_philo	*list_of_philo(t_philo *philo)
// {
// 	t_philo	*head;
// 	t_philo	*temp;
// 	int		i;

// 	i = 0;
// 	head = NULL;
// 	while (i < philo->info->num_philos)
// 	{
// 		if (!add_back(&head, philo))
// 			return (head);
// 		i++;
// 	}
// 	i = 0;
// 	temp = head;
// 	while (i < philo->info->num_philos)
// 	{
// 		temp->last_meal = 0;
//         temp->info = philo->info;
//         temp->info->philo = head;
// 		temp->id = i + 1;
// 		temp = temp->next;
// 		i++;
// 	}

// 	return (head);
// }

// int	add_back(t_philo **head, t_philo *philo)
// {
// 	t_philo	*temp;
// 	t_philo	*new_philo;

// 	if (*head == NULL)
// 	{
// 		*head = creat_philo(philo);
// 		return (*head != NULL);
// 	}
// 	new_philo = creat_philo(philo);
// 	if (!new_philo)
// 		return (FALSE);
// 	temp = *head;
// 	while (temp->next)
// 	{
// 		temp = temp->next;
// 	}
// 	temp->next = new_philo;
// }


// t_philo	*creat_philo(t_philo *philo)
// {
// 	t_philo	*new_philo;

// 	new_philo = malloc(sizeof(t_philo));
// 	if (!new_philo)
// 		return (NULL);
// 	new_philo->info = philo->info;
// 	new_philo->next = NULL;
// 	return (new_philo);
// }

// void	init_forks_of_philos(t_philo *philos)
// {
// 	t_philo *temp;
// 	int		i;

// 	i = 0;
// 	temp = philos;
// 	while (temp)
// 	{
// 		if (!(i + 1 == philos->info->num_philos))
// 		{
// 			temp->left_fork = &philos->info->forks[i+1];
// 			temp->right_fork = &philos->info->forks[i];
// 		}
// 		else 
// 		{
// 			temp->left_fork = &philos->info->forks[0];
// 			temp->right_fork = &philos->info->forks[i];
// 		}
// 		i++;
// 		temp = temp->next;
// 	}
// }