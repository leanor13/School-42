/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/08 11:15:08 by yioffe           ###   ########.fr       */
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
			return (free_philos(temp), NULL);
		// Initialize philosopher
		temp->config = config;
		temp->id = i + 1;
		temp->eat_num = config->number_of_times_each_philosopher_must_eat;
		temp->alive = true;
		gettimeofday(&temp->last_eat_time, NULL);
		temp->eat_count = 0;
		pthread_mutex_init(&temp->mutex_eating, NULL);
		//if it's the first philosopher, there's no previous one to take the fork from. 
		if (i == 0)
			temp->left_fork = NULL;                                                               
		// Otherwise, the left fork is the previous philosopher's eating mutex. 
		else 
			temp->left_fork = &prev->mutex_eating; 
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

// Utility function to get current time in milliseconds
long	current_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void eat(t_philo *philo, t_config *config) 
{
    printf("%lu %d is trying to eat\n", current_time_in_ms(), philo->id);
	pick_up_forks(philo);
    // pthread_mutex_lock(philo->left_fork);
    // printf("%lu %d has picked up left fork\n", current_time_in_ms(), philo->id);
    // pthread_mutex_lock(philo->right_fork);
    // printf("%lu %d has picked up right fork\n", current_time_in_ms(), philo->id);

    printf("%lu %d is eating\n", current_time_in_ms(), philo->id);
    gettimeofday(&philo->last_eat_time, NULL); // Update the last eating time
    usleep(config->time_to_eat * 1000);        // Simulate eating by sleeping

	put_down_forks(philo);
    // pthread_mutex_unlock(philo->right_fork);
    // printf("%lu %d has put down right fork\n", current_time_in_ms(), philo->id);
    // pthread_mutex_unlock(philo->left_fork);
    // printf("%lu %d has put down left fork\n", current_time_in_ms(), philo->id);

    // Increment the eat count if there's a limit on the number of times they must eat
    if (config->number_of_times_each_philosopher_must_eat > 0) {
        philo->eat_count++;
    }
}


void	think(t_philo *philo)
{
	printf("%lu %d is thinking\n", current_time_in_ms(), philo->id);
	// No specific duration for thinking,
	//usleep(1000); // This line is optional, just simulates brief thinking time
}

void	sleep_philo(t_philo *philo, t_config *config)
{
	printf("%lu %d is sleeping\n", current_time_in_ms(), philo->id);
	usleep(config->time_to_sleep * 1000); 
	// Simulate sleeping, converting ms to microseconds
}

void	die(t_philo *philo)
{
	printf("%lu %d has died\n", current_time_in_ms(), philo->id);
	philo->alive = false;
		// This would cause the philosopher's thread to exit its routine
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

void pick_up_forks(t_philo *philo) {
    if (philo->id % 2 == 1) {  // Odd philosophers
        pthread_mutex_lock(philo->left_fork);  // Always pick up the left fork first if available
        pthread_mutex_lock(philo->right_fork);
    } else {  // Even philosophers
        pthread_mutex_lock(philo->right_fork);  // Always pick up the right fork first if available
        pthread_mutex_lock(philo->left_fork);
    }
    printf("%lu %d has picked up both forks and is now eating\n", current_time_in_ms(), philo->id);
}

void put_down_forks(t_philo *philo) {
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    struct timeval now;
    long time_since_last_meal;

    while (philo->alive) {
        think(philo);
        //pick_up_forks(philo);
        eat(philo, philo->config);
        //put_down_forks(philo);
        sleep_philo(philo, philo->config);

        gettimeofday(&now, NULL);
        time_since_last_meal = (now.tv_sec - philo->last_eat_time.tv_sec) * 1000
                             + (now.tv_usec - philo->last_eat_time.tv_usec) / 1000;

        if (time_since_last_meal > philo->config->time_to_die) {
            printf("%lu %d has died\n", current_time_in_ms(), philo->id);
            philo->alive = false;
            break;
        }
    }
    return NULL;
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
