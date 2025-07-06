#include "philo.h" 

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(philo->left_fork);

    pthread_mutex_lock(&philo->info->write_lock);
    printf("%ld %d has taken a fork\n", get_time() - philo->info->start_time , philo->id);
    printf("%ld %d has taken a fork\n", get_time() - philo->info->current_time, philo->id);
    pthread_mutex_unlock(&philo->info->write_lock);
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->write_lock);
    printf("%s\n", "his eating");
    pthread_mutex_unlock(&philo->info->write_lock);

    philo->last_meal = get_time();
    philo->meals_eaten++;

    sleep(philo->info->time_to_eate * 1000);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->write_lock);
    printf("%s\n", "his thinking\n");
    pthread_mutex_unlock(&philo->info->write_lock);

}


void    sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->write_lock);
    printf("%s\n", "his slleping\n");
    pthread_mutex_unlock(&philo->info->write_lock);

    sleep(philo->info->time_to_sleep * 1000);
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *) arg;

    while (!philo->info->is_same_one_dei)
    {   
        if (philo->id % 2 == 0)
            sleep(1000);
        take_forks(philo);
        eating(philo);
        thinking(philo);
        sleeping(philo);
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
