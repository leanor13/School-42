/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/09 14:14:10 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// TODO: remove printf and other not allowed functions
// TODO: remove printf for put up/down fork
// TODO: fix case for 1 philo

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
			return (free_philos(head), NULL);
		// Initialize philosopher
		temp->config = config;
		temp->id = i + 1;
		temp->eat_num = config->number_of_times_each_philosopher_must_eat;
		temp->alive = true;
		gettimeofday(&temp->last_eat_time, NULL);
		temp->eat_count = 0;
		pthread_mutex_init(&temp->mutex_eating, NULL);
		
		// Assign forks
		temp->left_fork = &config->forks[i]; // left philo fork
		temp->right_fork = &config->forks[(i + 1) % config->number_of_philosophers]; // right philo fork - fork of the next philosopher
		
		temp->next = NULL;
		temp->previous = prev;
		if (prev)
			prev->next = temp;
		else
			head = temp;
		prev = temp;
		i++;
	}
	return (head);
}

t_config	*init_config(int argc, char **argv)
{
	int			arguments[5] = {0};
	int			i;
	t_config	*config;

	if (argc != 5 && argc != 6)
	{
		fprintf(stderr, "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (NULL);
	}
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
	config->stop = false;
	if (argc == 6)
		config->number_of_times_each_philosopher_must_eat = arguments[4];
	else
		config->number_of_times_each_philosopher_must_eat = -1;
	pthread_mutex_init(&config->mutex_write, NULL);
	config->forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philosophers);
	if (!config->forks)
		return (free(config), NULL);
	for (i = 0; i < config->number_of_philosophers; i++) {
		pthread_mutex_init(&config->forks[i], NULL);
	}
	return (config);
}

// Utility function to get current time in milliseconds
long	current_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	create_threads(pthread_t **threads, t_philo *philos, t_config *config)
{
	int	i;

	i = 0;
	*threads = malloc(sizeof(pthread_t) * config->number_of_philosophers);
	if (!*threads)
	{
		fprintf(stderr, "Failed to allocate memory for threads.\n");
		return (-1);
	}
	while (i < config->number_of_philosophers)
	{
		if (pthread_create(&(*threads)[i], NULL, philosopher_routine,
				&philos[i]) != 0)
		{
			fprintf(stderr, "Failed to create thread for philosopher %d.\n", i
				+ 1);
			return (i);
			// Return the count of successfully created threads for cleanup
		}
		i++;
	}
	return (0);
}


void *philosopher_routine(void *params) {
    int			i;
	t_philo		*philo;
	t_config	*config;

	i = 0;
	philo = (t_philo *)params;
	config = philo->config;
	if (!config)
		return (NULL);
	if (philo->id % 2 && config->number_of_philosophers > 1)
		new_sleep(config->time_to_eat / 50, config);
	while (!config->stop)
	// add here check for maximum eat time
	{
		if (config->number_of_times_each_philosopher_must_eat != -1 && philo->eat_count >= config->number_of_times_each_philosopher_must_eat)
    		break; // no need to continue if philo ate enough times
		if (!philo->alive)
			break;
		philo_eat(philo);
		philo_print("is sleeping", philo, UNLOCK);
		p_sleep(config->time_to_sleep, config);
		philo_print("is thinking", philo, UNLOCK);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	pthread_t	*threads;
	int			created_threads;
	int			i;

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
	created_threads = create_threads(&threads, philos, config);
	if (created_threads != 0)
	{
		// Cleanup if thread creation failed
		i = 0;
		if (created_threads > 0)
		{
			while (i < created_threads)
			{
				pthread_join(threads[i], NULL);
				i++;
			}
		}
		free(threads);
		free_philos(philos);
		free(config);
		return (EXIT_FAILURE);
	}
	// Join all threads
	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	// Cleanup
	free(threads);
	free_philos(philos);
	free(config);
	return (EXIT_SUCCESS);
}
