/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:55:20 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/15 19:57:55 by yioffe           ###   ########.fr       */
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
	sem_post(config->sem_stop);
}


// int	get_eat_counter(t_philo *philo)
// {
// 	int	result;

// 	sem_wait(philo->sem_counter);
// 	result = philo->eat_counter;
// 	sem_post(philo->sem_counter);
// 	return (result);
// }

// void	increment_eat_counter(t_philo *philo)
// {
// 	sem_wait(philo->sem_counter);
// 	philo->eat_counter += 1;
// 	sem_post(philo->sem_counter);
// }
