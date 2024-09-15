/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/15 15:24:09 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// remove strcat
// remove printf
// remove snprintf
// fix normi
// fix maximum eat number
// fix cleanup

void	clear_existing_semaphores(void)
{
	sem_unlink("/forks_sem");
	sem_unlink("/sem_write");
	sem_unlink("/sem_stop");
	sem_unlink("/sem_killer");
	return ;
}


int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos = NULL;
	pid_t		*philos_pids = NULL;
	pid_t		monitor_pid;

	clear_existing_semaphores();
	config = init_config(argc, argv);
	if (!config)
		return (EXIT_FAILURE);
	philos = init_philos(config);
	if (!philos)
		return (cleanup(philos, config), EXIT_FAILURE);
	if (create_processes(&philos_pids, philos, config) != EXIT_SUCCESS)
	{
		cleanup(philos, config);
		return (EXIT_FAILURE);
	}
	wait_for_processes(config);
	cleanup(philos, config);
	return (EXIT_SUCCESS);
}


