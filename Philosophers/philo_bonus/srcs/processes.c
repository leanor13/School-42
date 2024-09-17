/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:15:06 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/17 14:28:12 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	wait_for_fed_up(t_config *config)
{
	return (1);
}

static void release_all_forks(t_config *config)
{
	int i = 0;

	while (i<config->number_of_philos)
	{
		sem_post(config->forks_sem);
		i ++;
	}
}

int	create_processes(t_config *config)
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
		{
			//philo_print("\nPID:", &philos[i]);
			//printf("PID %d: %d\n", i + 1, pid);
			philos[i].pid = pid;
		}
		else
			return (NEG_ERROR);
		i++;
	}
	i = 0;
	while (i < config->number_of_philos)
	{
		//printf("here: %d\n", i);
		sem_wait(config->sem_fed_up);
		i++;
	}
	//philo_sleep(config->time_to_eat, config);
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
		//break ;
	}
	return (EXIT_SUCCESS);
}
