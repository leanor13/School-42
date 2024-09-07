/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/07 16:11:47 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philos(t_philo *philos)
{
	t_philo	*current;
	t_philo	*next;

	current = philos;
	if (!philos)
		return ;
	// Break the circular link if necessary
	if (philos->previous)
		philos->previous->next = NULL;
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

t_philo	*initiate_philos(t_config *config)
{
	t_philo	*head;
	t_philo	*temp;
	t_philo	*prev;
	int		i;

	head = NULL;
	temp = NULL;
	prev = NULL;
	i = 0;
	while (i < config->number_of_philosophers)
	{
		temp = malloc(sizeof(t_philo));
		if (!temp)
			return(free_philos(temp), NULL);
		// Initialize philosopher
		temp->id = i + 1;
		temp->eat_num = config->number_of_times_each_philosopher_must_eat;
		temp->alive = true;
		gettimeofday(&temp->last_eat_time, NULL);
		temp->eat_count = 0;
		pthread_mutex_init(&temp->mutex_eating, NULL);
		if (i == 0)
    		temp->left_fork = NULL;  // If it's the first philosopher, there's no previous one to take the fork from.
		else
    		temp->left_fork = &prev->mutex_eating;  // Otherwise, the left fork is the previous philosopher's eating mutex.
		temp->right_fork = &temp->mutex_eating;
		temp->next = NULL;
		temp->previous = prev;
		if (prev)
			prev->next = temp;
		else
			head = temp;
		prev = temp;
		i++; // Increment the loop counter
	}
	// Correct the left fork setup for the first philosopher at the end of the loop
	if (config->number_of_philosophers > 1)
		head->left_fork = &prev->mutex_eating;
	return (head);
}

t_config	*init_config(int argc, char **argv)
{
	int			arguments[5] = {0};
	int			i;
	t_config	*config;

	if (argc != 5 && argc != 6)
		return (NULL);
	i = 0;
	while (i < argc - 1)
	{
		arguments[i] = atoi_positive(argv[i + 1]);
		if (arguments[i] == NEG_ERROR || (i < 3 && arguments[i] == 0))
			return (NULL);
		i++;
	}
	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->number_of_philosophers = arguments[0];
	config->time_to_die = arguments[1];
	config->time_to_eat = arguments[2];
	config->time_to_sleep = arguments[3];
	if (argc == 6)
		config->number_of_times_each_philosopher_must_eat = arguments[4];
	else
		config->number_of_times_each_philosopher_must_eat = -1;
	return (config);
}

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;

    while (philo->alive) {
        think(philo);
        pick_up_forks(philo);
        eat(philo);
        put_down_forks(philo);
        sleep(philo);
    }
    return NULL;
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;

	config = init_config(argc, argv);
	if (!config)
	{
		fprintf(stderr, "Error initializing configuration.\n");
		return (EXIT_FAILURE);
	}
	philos = initiate_philos(config);
	if (!philos)
	{
		free(config);
		fprintf(stderr, "Error initializing philosophers.\n");
		return (EXIT_FAILURE);
	}
	free(config);
	free_philos(philos);
	return (EXIT_SUCCESS);
}
