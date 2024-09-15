/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:56:08 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/15 16:26:17 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	philo_fields_init(t_philo *philo, t_config *config, int num)
{
	char sem_name[10];
	char id_str[5];

	philo->config = config;
	philo->id = num + 1;
	gettimeofday(&philo->last_eat_time, NULL);
	philo->eat_counter = 0;
	philo->is_dead = false;
	philo->pid = 0;
}

t_philo	*init_philos(t_config *config)
{
	int		i;
	
	config->philos = malloc(sizeof(t_philo) * config->number_of_philos);
	if (!config->philos)
		return (NULL);
	i = 0;
	while (i < config->number_of_philos)
	{
		philo_fields_init(&config->philos[i], config, i);
		i ++;
	}

	return (config->philos);
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

static int	init_config_fields(t_config *config, int *arguments, int argc)
{
	config->number_of_philos = arguments[0];
	config->time_to_die = arguments[1];
	config->time_to_eat = arguments[2];
	config->time_to_sleep = arguments[3];
	if (argc == 6)
		config->max_eat_times = arguments[4];
	else
		config->max_eat_times = -1;
	config->sem_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	config->sem_stop = sem_open("/sem_stop", O_CREAT, 0644, 1);
	config->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, config->number_of_philos);
	config->sem_killer = sem_open("/sem_killer", O_CREAT, 0644, 1);
	if (config->max_eat_times == 0)
	{
		set_config_stop(config, true);
	}
	else
	{
		set_config_stop(config, false);
	}
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
		i ++;
	}
	if (validate_input(argc, argv, arguments) == EXIT_FAILURE)
		return (NULL);
	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	if (init_config_fields(config, arguments, argc) == EXIT_FAILURE)
	{
		free(config);
		return (NULL);
	}
	return (config);
}
