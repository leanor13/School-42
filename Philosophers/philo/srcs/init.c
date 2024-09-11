#include "../includes/philo.h"

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
		temp->config = config;
		temp->id = i + 1;
		temp->alive = true;
		gettimeofday(&temp->last_eat_time, NULL);
		pthread_mutex_init(&temp->mutex_eating, NULL);
		temp->left_fork = &config->forks[i];
		temp->right_fork = &config->forks[(i + 1) % config->number_of_philosophers];
		pthread_mutex_init(&temp->mutex_counter, NULL);
		pthread_mutex_lock(&temp->mutex_counter);
		temp->eat_counter = 0;
		pthread_mutex_unlock(&temp->mutex_counter);
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
		fprintf(stderr, "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [max_eat_times]\n");
		return (NULL);
	}
	i = 0;
	while (i < argc - 1)
	{
		arguments[i] = atoi_positive(argv[i + 1]);
		if (arguments[i] == NEG_ERROR || (i < 3 && arguments[i] == 0))
		{
			fprintf(stderr, "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [max_eat_times]\n");
			return (NULL);
		}
		i++;
	}
	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->number_of_philosophers = arguments[0];
	config->time_to_die = arguments[1];
	config->time_to_eat = arguments[2];
	config->time_to_sleep = arguments[3];
	config->first_philo = NULL;
	if (argc == 6)
		config->max_eat_times = arguments[4];
	else
		config->max_eat_times = -1;
	pthread_mutex_init(&config->mutex_write, NULL);
	pthread_mutex_init(&config->mutex_stop, NULL);
	if (config->max_eat_times == 0)
		set_config_stop(config, true);
	else
		set_config_stop(config, false);
	config->forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philosophers);
	if (!config->forks)
		return (free(config), NULL);
	for (i = 0; i < config->number_of_philosophers; i++) {
		pthread_mutex_init(&config->forks[i], NULL);
	}
	return (config);
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