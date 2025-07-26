/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:52:56 by yaboumei          #+#    #+#             */
/*   Updated: 2025/07/12 20:53:00 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				i_looked;
	int				num_philos;
	int				time_to_dide;
	int				time_to_eate;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eate_counter;
	int				is_same_one_dei;
	long			current_time;
	long			start_time;
	size_t			count_eaten;
	size_t			count_how_many_philo_eat;
	int				is_last_meal;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	die_lock;
	pthread_mutex_t	lastmeal_lock;
	pthread_mutex_t	think_lock;
	pthread_mutex_t	eate_lock;
	pthread_mutex_t	*forks;
	struct t_philo	*philo;
}					t_info;

typedef struct t_philo
{
	long			extra_think;
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	pthread_t		tread;
	pthread_t		monitor_th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	struct t_philo	*next;
}					t_philo;

void				case_one_philo(t_philo *philo);
void				ft_usleep_interruptible(t_philo *philo, long start,
						long milli);
void				wait_for_treads(t_philo *philos);
void				full_arr(t_philo *philo);
void				init_forks_of_philos(t_philo *philos);
void				*monitor(void *arg);
void				free_meme(t_philo *philo);
int					check_is_dei(t_philo *philo);
int					check_number_of_meals(t_info *info);

t_info				*save_data_to_strcut(t_info *info, char **av, int type);
void				*routine(void *arg);
size_t				get_time(void);

void				print_action(t_philo *philo, char *messag);
int					ft_isspace(int c);
int					ft_isdigit(int c);
int					ft_atoi(const char *nptr);
int					pargsing(char **av, int type);
void				print_parsing_err(void);

#endif
