#include "philo.h"

void	free_meme(t_philo *philo)
{
	t_philo	*temp;

	temp = philo;
	while (temp)
	{
		philo = philo->next;
		free(temp->info);
		free(temp->left_fork);
		free(temp->right_fork);
		free(temp);
		temp = philo;
	}
}

void	print_parsing_err(void)
{
	printf("Invalid input, Pleas enter valid number : -)\n");
}