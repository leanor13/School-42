/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/10 09:30:00 by yioffe           ###   ########.fr       */
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

void	ft_putnbr_fd(unsigned long long n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

void philo_print(const char *message, t_philo *philo)
{
    t_config *config = philo->config;
    struct timeval current_time;
	unsigned long long timestamp_in_ms;

    gettimeofday(&current_time, NULL);
    timestamp_in_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);

    pthread_mutex_lock(&config->mutex_write);

    ft_putnbr_fd(timestamp_in_ms, STDOUT_FILENO);
    write(STDOUT_FILENO, " Philosopher ", 13);

    ft_putnbr_fd(philo->id, STDOUT_FILENO);
    write(STDOUT_FILENO, " ", 1);

	while(*message)
	{
    	write(STDOUT_FILENO, message, 1);
		message ++;
	}
    write(STDOUT_FILENO, "\n", 1);

    pthread_mutex_unlock(&config->mutex_write);
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
		if (head != NULL)
			prev->next = temp;
		else
			head = temp;
		prev = temp;
		i++;
	}
	if (prev) 
	{
        prev->next = NULL;
    }
	config->first_philo = head;
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
	config->first_philo = NULL;
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
	t_philo *current = philos;

	i = 0;
	*threads = malloc(sizeof(pthread_t) * config->number_of_philosophers);
	if (!*threads)
	{
		fprintf(stderr, "Failed to allocate memory for threads.\n");
		return (-1);
	}
	while (i < config->number_of_philosophers)
	{
		pthread_create(&(*threads)[i], NULL, philosopher_routine, current);
		usleep(100);
		i ++;
		current = current->next;
	}
	return (0);
}

void p_sleep(int duration_ms, t_config *config) {
    int elapsed = 0;
    while (elapsed < duration_ms && !config->stop) {
        usleep(1000);
        elapsed += 1;
    }
}

long time_diff_in_ms(struct timeval start, struct timeval end)
{
    return ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000);
}

void *monitor_routine(void *params) {
    t_config *config = (t_config *)params;
    t_philo *philo;
    struct timeval current_time;

    while (!config->stop) {
        philo = config->first_philo;
        while (philo) {
            pthread_mutex_lock(&philo->mutex_eating);
            gettimeofday(&current_time, NULL);

			long time_since_last_eat = time_diff_in_ms(philo->last_eat_time, current_time);

			pthread_mutex_lock(&config->mutex_write);
			printf("\nPhilosopher %d: time since last meal %ld ms\n", philo->id, time_since_last_eat);
			pthread_mutex_unlock(&config->mutex_write);
			
            if (time_since_last_eat > config->time_to_die) {
                philo->alive = false;
                philo_print("died", philo);

				pthread_mutex_lock(&config->mutex_write);
				printf("\nPhilosopher %d died: time since last meal %ld ms\n", philo->id, time_since_last_eat);
				pthread_mutex_unlock(&config->mutex_write);

                config->stop = true;
				pthread_mutex_unlock(&philo->mutex_eating);
				return (NULL);
            }
            pthread_mutex_unlock(&philo->mutex_eating);
            
            philo = philo->next;
        }
        usleep(1000); 
    }
    return (NULL);
}

void philo_eat(t_philo *philo)
{
    t_config *config = philo->config;

	if (philo->config->stop || !philo->alive)
			return;
    pthread_mutex_lock(&philo->mutex_eating);

    philo_print("is eating", philo);

    p_sleep(config->time_to_eat, config);

	gettimeofday(&philo->last_eat_time, NULL);
    philo->eat_count++;

	pthread_mutex_lock(&config->mutex_write);
	printf("Philosopher %d finished eating, time updated\n", philo->id);
	pthread_mutex_unlock(&config->mutex_write);

    pthread_mutex_unlock(&philo->mutex_eating);
}


void philo_take_forks_and_eat(t_philo *philo)
{
	if (philo->config->stop || !philo->alive)
            return;
	if (philo->left_fork == philo->right_fork) 
	{
        pthread_mutex_lock(philo->left_fork);
		p_sleep(philo->config->time_to_die, philo->config);
        pthread_mutex_unlock(philo->left_fork);
    }
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);

		philo_eat(philo);

		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void *philosopher_routine(void *params) {
	t_philo		*philo;
	t_config	*config;

	philo = (t_philo *)params;
	config = philo->config;
	if (!config)
		return (NULL);
	if (philo->id % 2 && config->number_of_philosophers > 1)
		p_sleep(config->time_to_eat / 50, config);
	while (!config->stop && philo->alive)
	// add here check for maximum eat time
	{
		if (config->number_of_times_each_philosopher_must_eat != -1 && philo->eat_count >= config->number_of_times_each_philosopher_must_eat)
			// TODO: we need to check somewhere and stop if all philos eaten enough times.
    		break; // no need to continue if philo ate enough times
		if (config->stop || !philo->alive)
			break;
		philo_take_forks_and_eat(philo);
		if (config->stop || !philo->alive)
			break;
		philo_print("is sleeping", philo);
		p_sleep(config->time_to_sleep, config);
		if (config->stop || !philo->alive)
			break;
		philo_print("is thinking", philo);
	}
	return (NULL);
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


int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	pthread_t	*threads;
	int			created_threads;
	pthread_t   monitor_thread;
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
		cleanup(philos, threads, config);
		return (EXIT_FAILURE);
	}

	if (pthread_create(&monitor_thread, NULL, monitor_routine, config) != 0)
    {
        fprintf(stderr, "Failed to create monitor thread.\n");
        cleanup(philos, threads, config);
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
	cleanup(philos, threads, config);
	return (EXIT_SUCCESS);
}
