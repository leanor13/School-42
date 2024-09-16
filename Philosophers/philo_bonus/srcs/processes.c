/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:15:06 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/16 10:00:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	wait_for_fed_up(t_config *config)
{
	return 1;
}

int	create_processes(t_config *config)
{
	int		i;
	pid_t	pid;
	t_philo *philos;

	philos = config->philos;
	i = 0;
	while (i < config->number_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			philosopher_routine(&philos[i]);
			exit(EXIT_SUCCESS);
		}
		else if (pid > 0)
			philos[i].pid = pid;
		else
			return (NEG_ERROR);
		i ++;
	}
	i = 0;
	if (config->max_eat_times > 0)
	{
		while (i < config->number_of_philos && !check_config_stop(config))
		{
			sem_wait(config->sem_fed_up);
			i ++;
		}
		philo_sleep(config->time_to_eat, config);
		set_config_stop(config, true);
		kill_all_philos(config);
	}
	return (EXIT_SUCCESS);
}

int	wait_for_processes(t_config *config)
{
	int i;
	int status;

	for (i = 0; i < config->number_of_philos; i++)
	{
		waitpid(config->philos[i].pid, &status, 0);
		break ;
	}
	return (EXIT_SUCCESS);
}

