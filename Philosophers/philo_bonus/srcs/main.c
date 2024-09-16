/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/16 09:55:58 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// put back flags

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	pid_t		monitor_pid;

	philos = NULL;
	config = init_config(argc, argv);
	if (!config)
		return (EXIT_FAILURE);
	if (init_philos(config) == EXIT_FAILURE)
		return (cleanup(config), EXIT_FAILURE);
	if (create_processes(config) != EXIT_SUCCESS)
	{
		cleanup(config);
		return (EXIT_FAILURE);
	}
	wait_for_processes(config);
	cleanup(config);
	return (EXIT_SUCCESS);
}
