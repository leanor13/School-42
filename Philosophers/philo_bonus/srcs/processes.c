/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:15:06 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/13 12:25:43 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_processes(pid_t **pids, t_philo *philos, t_config *config)
{
	int		i;
	pid_t	pid;

	*pids = malloc(sizeof(pid_t) * config->number_of_philos);
	if (!*pids)
		return (NEG_ERROR);
	for (i = 0; i < config->number_of_philos; i++)
	{
		pid = fork();
		if (pid == 0)
		{
			philosopher_routine(&philos[i]);
			exit(EXIT_SUCCESS);
		}
		else if (pid > 0)
		{
			(*pids)[i] = pid;
		}
		else
		{
			return (NEG_ERROR);
		}
	}
	return (EXIT_SUCCESS);
}

int	start_monitor_process(t_config *config, pid_t *monitor_pid)
{
	*monitor_pid = fork();
	if (*monitor_pid == 0)
	{
		monitor_routine(config);
		exit(EXIT_SUCCESS);
	}
	else if (*monitor_pid > 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	wait_for_processes(t_config *config)
{
	int i;
	int status;

	for (i = 0; i < config->number_of_philos; i++)
	{
		waitpid(config->philos_pids[i], &status, 0);
	}
	return (EXIT_SUCCESS);
}
