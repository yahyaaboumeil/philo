#include "philo.h"

void    add_back(t_philo **head, t_philo *philo)
{
    t_philo *temp;
    t_philo *new_philo;
    
    if (*head == NULL)
    {
        *head = creat_philo(philo); 
        return ;
    }
    new_philo = creat_philo(philo);
    if (!new_philo)
        return ;
    temp = *head;
    while (temp->next)    
    {
       temp = temp->next; 
    }
    temp->next = new_philo;
}

t_philo    *creat_philo(t_philo *philo)
{
    t_philo *new_philo;

    new_philo = malloc(sizeof(t_philo));
    new_philo->info = malloc(sizeof(t_info));

    new_philo->info->num_philos = philo->info->num_philos;
    new_philo->info->time_to_dide = philo->info->time_to_dide;
    new_philo->info->time_to_eate = philo->info->time_to_eate;
    new_philo->info->time_to_sleep = philo->info->time_to_sleep;
    new_philo->info->start_time = get_time();
    new_philo->info->must_eate_counter = philo->info->must_eate_counter;
    new_philo->next = NULL;

    return (new_philo);
}


t_philo    *list_of_philo(t_philo *philo)
{
    t_philo *head;
    t_philo *temp;
    int i;

    i = 0;
    head = NULL;
    while (i < philo->info->num_philos)
    {
        add_back(&head, philo);
        i++;
    }
    i = 0;
    temp = head;
    while (i < philo->info->num_philos)
    {
        temp->id = i+1; 
        temp = temp->next;
    }
    return (head);
}

void    run_threads(t_philo *philos)
{
    t_philo *temp;

    temp = philos;
    while (temp)
    {
        if (!pthread_create(&temp->tread, NULL, &routine, temp))
        {
            perror("pthread_create");
        }
        temp = temp->next; 
    }
}

void    wait_for_treads(t_philo *philos)
{
    t_philo *temp;

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

int    philo(int ac, char  **av)
{
    t_philo  *philos;

    philos = NULL;
    if (ac  == 4)
    {
        if (!pargsing(av, THRENUMBER))
            return (print_parsing_err(), 0);
        save_data_to_strcut(philos->info, av, THRENUMBER);
        philos = list_of_philo(philos);
        creat_philo(philos);
        wait_for_treads(philos);
    }
    else if (ac == 5)
    {
        if (!pargsing(av, FORNUMBER))
            return (print_parsing_err(),1);
        printf("valide input : \n"); 
    }
    return (1);
}

int main(int ac, char **av)
{
    philo(ac, av);
}