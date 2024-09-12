/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:55:58 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 15:54:21 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup(t_philo *philos, pid_t *philos_pids, t_config *config)
{
	int		i;
	char	sem_name[10];
	char	id_str[5];

	if (philos_pids)
		free(philos_pids);
	if (philos)
	{
		for (i = 0; i < config->number_of_philos; i++)
		{
			sem_close(philos[i].sem_eating);
			sem_name[0] = '/';
			sem_name[1] = '\0';
			int_to_string(philos[i].id, id_str);
			strcat(sem_name, id_str);
			sem_unlink(sem_name);
		}
		free(philos);
	}
	if (config)
	{
		sem_close(config->forks);
		sem_unlink("/forks_sem");
		sem_close(config->sem_write);
		sem_unlink("/sem_write");
		sem_close(config->sem_stop);
		sem_unlink("/sem_stop");
		free(config);
	}
}


void	handle_process_creation_error(t_philo *philos, pid_t *philos_pids,
		t_config *config, int created_processes)
{
	int	i;

	for (i = 0; i < created_processes; i++)
	{
		kill(philos_pids[i], SIGKILL);
	}
	free(philos_pids);
	cleanup(philos, philos_pids, config);
	write(STDERR_FILENO, "Error: Failed to create all philosopher processes.\n",
		51);
	exit(EXIT_FAILURE);
}

void	kill_all_philos(t_config *config)
{
	int i;

	for (i = 0; i < config->number_of_philos; i++)
	{
		if (kill(config->philos_pids[i], SIGKILL) == -1)
		{
			perror("kill");
		}
	}
}
