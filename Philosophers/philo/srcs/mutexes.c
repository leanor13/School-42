/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:55:20 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/11 19:59:14 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_config_stop(t_config *config)
{
	bool	status;

	pthread_mutex_lock(&config->mutex_stop);
	status = config->stop;
	pthread_mutex_unlock(&config->mutex_stop);
	return (status);
}

void	set_config_stop(t_config *config, bool status)
{
	pthread_mutex_lock(&config->mutex_stop);
	config->stop = status;
	pthread_mutex_unlock(&config->mutex_stop);
}

int	get_eat_counter(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->mutex_counter);
	result = philo->eat_counter;
	pthread_mutex_unlock(&philo->mutex_counter);
	return (result);
}

void	increment_eat_counter(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_counter);
	philo->eat_counter += 1;
	pthread_mutex_unlock(&philo->mutex_counter);
}
