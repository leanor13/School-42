/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:55:58 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/15 16:26:42 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	cleanup(t_philo *philos, t_config *config)
{
	int		i;
	char	sem_name[10];
	char	id_str[5];
	
	if (philos)
	{	
		kill_all_philos(config);
		free(philos);
	}
	if (config)
	{
		//if (config->monitor_pids)
		//	free(config->monitor_pids);
		//if (config->philos_pids)
		//	free(config->philos_pids);
		sem_close(config->forks_sem);
		sem_unlink("/forks_sem");
		sem_close(config->sem_write);
		sem_unlink("/sem_write");
		sem_close(config->sem_stop);
		sem_unlink("/sem_stop");
		sem_close(config->sem_killer);
		sem_unlink("/sem_killer");
		free(config);
	}
}

void	kill_all_philos(t_config *config)
{
	int i;

	i = 0;
	while (i < config->number_of_philos)
	{
		// if not already killed - kill
		if (config->philos[i].pid > 0)
			kill(config->philos[i].pid, SIGKILL);
		i ++;
	}
}
