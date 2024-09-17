/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:15:06 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/17 14:52:33 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	wait_for_fed_up(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philos)
	{
		sem_wait(config->sem_fed_up);
		i++;
	}
}

static void	release_all_forks(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philos)
	{
		sem_post(config->forks_sem);
		i ++;
	}
}

int	init_processes(t_config *config)
{
	int		i;
	pid_t	pid;
	t_philo	*philos;

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
		i++;
	}
	wait_for_fed_up(config);
	release_all_forks(config);
	set_config_stop(config, true);
	kill_all_philos(config);
	return (EXIT_SUCCESS);
}

int	wait_for_processes(t_config *config)
{
	int	i;
	int	status;

	i = 0;
	while (i < config->number_of_philos)
	{
		waitpid(config->philos[i].pid, &status, 0);
		i ++;
	}
	return (EXIT_SUCCESS);
}
