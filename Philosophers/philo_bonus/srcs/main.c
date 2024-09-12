/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 14:42:49 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	pid_t		*philos_pids;
	int			created_processes;
	int			i;

	config = init_config(argc, argv);
	if (!config)
		return (EXIT_FAILURE);
	philos = initiate_philos(config);
	if (!philos)
		return (free(config), EXIT_FAILURE);
	created_processes = create_processes(&philos_pids, philos, config);
	if (created_processes != EXIT_SUCCESS)
	{
		handle_process_creation_error(philos, philos_pids, config, created_processes);
		return (EXIT_FAILURE);
	}
	for (i = 0; i < config->number_of_philos; i++)
		waitpid(philos_pids[i], NULL, 0);
	cleanup(philos, philos_pids, config);
	return (EXIT_SUCCESS);
}

