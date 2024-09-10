#include "../includes/philo.h"

void	free_philos(t_philo *philos)
{
	t_philo	*current;
	t_philo	*next;

	current = philos;
	if (!philos)
		return ;
	// Now that the list is non-circular, use a while loop to free the list
	while (current != NULL)
	{
		next = current->next;
		// Destroy mutexes if necessary
		pthread_mutex_destroy(&current->mutex_eating);
		// Free the current philosopher
		free(current);
		// Move to the next philosopher
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
