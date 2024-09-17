/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:55:58 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/17 13:54:02 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	cleanup(t_config *config)
{
	int		i;
	char	sem_name[10];
	char	id_str[5];

	if (config->philos)
	{
		kill_all_philos(config);
		free(config->philos);
	}
	if (config)
	{
		sem_close(config->forks_sem);
		sem_unlink("/forks_sem");
		sem_close(config->sem_write);
		sem_unlink("/sem_write");
		sem_close(config->sem_stop);
		sem_unlink("/sem_stop");
		sem_close(config->sem_killer);
		sem_unlink("/sem_killer");
		sem_close(config->sem_fed_up);
		sem_unlink("/sem_fed_up");
		free(config);
	}
}

void	kill_all_philos(t_config *config)
{
	int	i;

	i = 0;
	sem_wait(config->sem_write);
	while (i < config->number_of_philos)
	{
		//if (config->philos[i].pid == 0)
		//	philo_print("\nZERO:", &(config->philos[i]));
		if (config->philos[i].pid > 0)
		{
			kill(config->philos[i].pid, SIGKILL);
			sem_post(config->sem_write);
			//config->philos[i].pid = 0;
		}
		i++;
	}
	sem_post(config->sem_write);
}
