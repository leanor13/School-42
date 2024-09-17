/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:55:20 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/17 14:50:11 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

bool	check_config_stop(t_config *config)
{
	bool	status;

	sem_wait(config->sem_stop);
	status = config->stop;
	sem_post(config->sem_stop);
	return (status);
}

void	set_config_stop(t_config *config, bool status)
{
	sem_wait(config->sem_stop);
	config->stop = status;
	sem_post(config->sem_stop);
}
