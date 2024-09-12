/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:56:08 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 16:42:06 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void int_to_string(int num, char *str)
{
	int i = 0;
	int temp_num = num;

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return;
	}

	while (temp_num != 0)
	{
		temp_num /= 10;
		i++;
	}
	str[i] = '\0';
	while (num != 0)
	{
		str[--i] = (num % 10) + '0';
		num /= 10;
	}
}

static void	philo_fields_init(t_philo *philo, t_config *config, int num)
{
	char sem_name[10];
	char id_str[5];

	philo->config = config;
	philo->id = num + 1;
	gettimeofday(&philo->last_eat_time, NULL);

	sem_name[0] = '/';
	sem_name[1] = '\0';
	int_to_string(philo->id, id_str);
	strcat(sem_name, id_str);
	philo->sem_eating = sem_open(sem_name, O_CREAT, 0644, 1);
	if (philo->sem_eating == SEM_FAILED)
		exit(EXIT_FAILURE);
	philo->eat_counter = 0;
}

t_philo	*initiate_philos(t_config *config)
{
	int		i;
	
	config->philos = malloc(sizeof(t_philo) * config->number_of_philos);
	if (!config->philos)
		return (NULL);
	for (i = 0; i < config->number_of_philos; i++)
	{
		philo_fields_init(&config->philos[i], config, i);
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

static int	config_fields_init(t_config *config, int *arguments, int argc)
{
	config->number_of_philos = arguments[0];
	config->time_to_die = arguments[1];
	config->time_to_eat = arguments[2];
	config->time_to_sleep = arguments[3];
	config->philos_pids = malloc(sizeof(pid_t) * config->number_of_philos);
	if (!config->philos_pids)
		return (free(config), EXIT_FAILURE);
	if (argc == 6)
		config->max_eat_times = arguments[4];
	else
		config->max_eat_times = -1;
	config->sem_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	if (config->sem_write == SEM_FAILED)
	{
		free(config->philos_pids);
		free(config);
		return (EXIT_FAILURE);
	}
	config->sem_stop = sem_open("/sem_stop", O_CREAT, 0644, 1);
	if (config->sem_stop == SEM_FAILED)
	{
		sem_close(config->sem_write);
		sem_unlink("/sem_write");
		free(config->philos_pids);
		free(config);
		return (EXIT_FAILURE);
	}
	config->forks = sem_open("/forks_sem", O_CREAT, 0644, config->number_of_philos);
	if (config->forks == SEM_FAILED)
	{
		sem_close(config->sem_write);
		sem_unlink("/sem_write");
		sem_close(config->sem_stop);
		sem_unlink("/sem_stop");
		free(config->philos_pids);
		free(config);
		return (EXIT_FAILURE);
	}
	if (config->max_eat_times == 0)
		set_config_stop(config, true);
	else
		set_config_stop(config, false);
	return (EXIT_SUCCESS);
}


t_config	*init_config(int argc, char **argv)
{
	int			arguments[5];
	int			i;
	t_config	*config;

	for (i = 0; i < 5; i++)
		arguments[i] = 0;
	if (validate_input(argc, argv, arguments) == EXIT_FAILURE)
		return (NULL);
	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	if (config_fields_init(config, arguments, argc) == EXIT_FAILURE)
	{
		free(config);
		return (NULL);
	}
	return (config);
}
