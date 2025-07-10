#include "philo.h" 


void    take_forks(t_philo *philo)
{
        pthread_mutex_lock(&philo->info->die_lock);
        if (philo->info->is_same_one_dei)
        {
            pthread_mutex_unlock(&philo->info->die_lock);
            return ;
        }
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
    print_action(philo,"\033[33m%ld %d has taken a fork\033[0m\n");
    print_action(philo,"\033[33m%ld %d has taken a fork\033[0m\n");
}

void    eating(t_philo *philo)
{

         pthread_mutex_lock(&philo->info->die_lock);
        if (philo->info->is_same_one_dei)
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(&philo->info->die_lock);
            return ;
        }
        pthread_mutex_unlock(&philo->info->die_lock);
    print_action(philo,"\033[32m%ld %d is eating\033[0m\n");


    pthread_mutex_lock(&philo->info->eate_lock);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->info->eate_lock);

    usleep(philo->info->time_to_eate * 1000);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    thinking(t_philo *philo)
{
        pthread_mutex_lock(&philo->info->die_lock);
        if (philo->info->is_same_one_dei)
        {
            pthread_mutex_unlock(&philo->info->die_lock);
            return ;
        }
        pthread_mutex_unlock(&philo->info->die_lock);
        print_action(philo,"\033[34m%ld %d is thinking\033[0m\n");
        if (philo->info->num_philos && philo->id % 2)
        {
            if (philo->info->time_to_eate > philo->info->time_to_sleep)
            {
                usleep((philo->info->time_to_eate - philo->info->time_to_sleep) * 1000);
            } 
            usleep(1000);
        }
}


void    sleeping(t_philo *philo)
{
        pthread_mutex_lock(&philo->info->die_lock);
        if (philo->info->is_same_one_dei)
        {
            pthread_mutex_unlock(&philo->info->die_lock);
            return ;
        }
        pthread_mutex_unlock(&philo->info->die_lock);
    print_action(philo,"\033[36m%ld %d is sleeping\033[0m\n");

    usleep(philo->info->time_to_sleep * 1000);
}

void    print_action(t_philo *philo, char *messag)
{
    pthread_mutex_lock(&philo->info->die_lock);
    if (!philo->info->is_same_one_dei)
    {
        pthread_mutex_lock(&philo->info->write_lock);
        printf(messag,  get_time() - philo->info->start_time, philo->id);
        pthread_mutex_unlock(&philo->info->write_lock);
    }
    pthread_mutex_unlock(&philo->info->die_lock);
}


void    *routine(void *arg)
{
    t_philo *philo = (t_philo *) arg;
    int i;

    i = 0;
    if (philo->id % 2)
        usleep(1000);
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




















// void take_forks(t_philo *philo)
// {
//     pthread_mutex_lock(philo->right_fork);
//     pthread_mutex_lock(philo->left_fork);

//     pthread_mutex_lock(&philo->rules->write_lock);
//     printf("%ld %d has taken a fork\n", get_time() - philo->rules->start_time, philo->id);
//     printf("%ld %d has taken a fork\n", get_time() - philo->rules->start_time, philo->id);
//     pthread_mutex_unlock(&philo->rules->write_lock);
// }

// void eating(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->rules->write_lock);
//     printf("%ld %d is eating\n", get_time() - philo->rules->start_time, philo->id);
//     pthread_mutex_unlock(&philo->rules->write_lock);

//     philo->last_meal = get_time(); // update last meal timestamp
//     philo->meals_eaten++;

//     usleep(philo->rules->time_to_eat * 1000); // convert ms to µs
//     pthread_mutex_unlock(philo->right_fork);
//     pthread_mutex_unlock(philo->left_fork);
// }

// void sleeping(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->rules->write_lock);
//     printf("%ld %d is sleeping\n", get_time() - philo->rules->start_time, philo->id);
//     pthread_mutex_unlock(&philo->rules->write_lock);

//     usleep(philo->rules->time_to_sleep * 1000);
// }

// void thinking(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->rules->write_lock);
//     printf("%ld %d is thinking\n", get_time() - philo->rules->start_time, philo->id);
//     pthread_mutex_unlock(&philo->rules->write_lock);
// }

// void *routine(void *arg)
// {
//     t_philo *philo = (t_philo *) arg;

//     if (philo->id % 2 == 0)
//         usleep(1000); // prevent deadlock by delaying even-numbered philosophers

//     while (!philo->rules->someone_died)
//     {
//         take_forks(philo);
//         eating(philo);
//         sleeping(philo);
//         thinking(philo);
//     }
//     return NULL;
// }
