#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <thread_db.h>
# include <threads.h>
# include <unistd.h>

# define FORNUMBER 4
# define FIVENUMBER 5
# define TRUE 1
# define FALSE 0

typedef struct t_info
{
	int				num_philos;
	int				time_to_dide;
	int				time_to_eate;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eate_counter;
	int				is_same_one_dei;
	long			current_time;
	long			start_time;
    int             is_last_meal;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	// t_philo         *philo;
}					t_info;

typedef struct t_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		tread;
	pthread_t		monitor_th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	struct t_philo	*next;
}					t_philo;

void				*monitor(void *arg);
void				free_meme(t_philo *philo);
int					check_is_dei(t_philo *philo);
int					check_number_of_meals(t_philo *philo);

t_philo				*creat_philo(t_philo *philo);
int					add_back(t_philo **head, t_philo *philo);
t_info				*save_data_to_strcut(t_info *info, char **av, int type);
void				*routine(void *arg);
long				get_time(void);

int					ft_isspace(int c);
int					ft_isdigit(int c);
int					ft_atoi(const char *nptr);
int					pargsing(char **av, int type);
void				print_parsing_err(void);

#endif