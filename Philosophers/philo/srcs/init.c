/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:56:08 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 14:29:59 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_fields_init(t_philo *philo, t_config *config, int num)
{
	philo->config = config;
	philo->id = num + 1;
	gettimeofday(&philo->last_eat_time, NULL);
	pthread_mutex_init(&philo->mutex_eating, NULL);
	philo->left_fork = &config->forks[num];
	philo->right_fork = &config->forks[(num + 1) % config->number_of_philos];
	pthread_mutex_init(&philo->mutex_counter, NULL);
	pthread_mutex_lock(&philo->mutex_counter);
	philo->eat_counter = 0;
	pthread_mutex_unlock(&philo->mutex_counter);
}

t_philo	*initiate_philos(t_config *config)
{
	t_philo	*head;
	t_philo	*temp;
	t_philo	*prev;
	int		i;

	head = NULL;
	prev = NULL;
	i = 0;
	while (i < config->number_of_philos)
	{
		temp = malloc(sizeof(t_philo));
		if (!temp)
			return (free_philos(head), NULL);
		philo_fields_init(temp, config, i);
		temp->next = NULL;
		if (head != NULL)
			prev->next = temp;
		else
			head = temp;
		prev = temp;
		i++;
	}
	prev->next = NULL;
	config->first_philo = head;
	return (head);
}

static int	validate_input(int argc, char **argv, int *arguments)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (write(STDERR_FILENO, WRONG_INPUT, WRONG_INPUT_MSG_LEN),
			EXIT_FAILURE);
	i = 0;
	while (i < argc - 1)
	{
		arguments[i] = atoi_positive(argv[i + 1]);
		if (arguments[i] == NEG_ERROR || (i < 3 && arguments[i] == 0))
			return (write(STDERR_FILENO, WRONG_INPUT, WRONG_INPUT_MSG_LEN),
				EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	config_fields_init(t_config *config, int *arguments, int argc)
{
	config->number_of_philos = arguments[0];
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
	config->forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philos);
	if (!config->forks)
		return (free(config), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_config	*init_config(int argc, char **argv)
{
	int			arguments[5];
	int			i;
	t_config	*config;

	i = 0;
	while (i < 5)
	{
		arguments[i] = 0;
		i++;
	}
	if (validate_input(argc, argv, arguments) == EXIT_FAILURE)
		return (NULL);
	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	if (config_fields_init(config, arguments, argc) == EXIT_FAILURE)
		return (NULL);
	i = 0;
	while (i < config->number_of_philos)
	{
		pthread_mutex_init(&config->forks[i], NULL);
		i++;
	}
	return (config);
}
