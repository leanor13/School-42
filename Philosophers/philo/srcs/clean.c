#include "../includes/philo.h"

void	free_philos(t_philo *philos)
{
	t_philo	*current;
	t_philo	*next;

	current = philos;
	if (!philos)
		return ;
	while (current != NULL)
	{
		next = current->next;
		pthread_mutex_destroy(&current->mutex_eating);
		free(current);
		current = next;
	}
}

void cleanup(t_philo *philos, pthread_t *threads, t_config *config)
{
    if (threads)
        free(threads);
    if (philos)
        free_philos(philos);
   if (config) {
        for (int i = 0; i < config->number_of_philosophers; i++) {
            pthread_mutex_destroy(&config->forks[i]);
        }
        free(config->forks);
        free(config);
    }
}
