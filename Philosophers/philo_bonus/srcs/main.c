/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/13 12:25:12 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// remove strcat
// remove printf
// remove snprintf
// fix normi
// fix maximum eat number

void	clear_existing_semaphores(void)
{
	sem_unlink("/forks_sem");
	sem_unlink("/sem_write");
	sem_unlink("/sem_stop");

	for (int i = 1; i <= 300; i++)
	{
		char sem_name[10];
		snprintf(sem_name, sizeof(sem_name), "/%d", i);
		sem_unlink(sem_name);
	}
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
	philos = initiate_philos(config);
	if (!philos)
		return (cleanup(philos, philos_pids, config), EXIT_FAILURE);
	if (create_processes(&philos_pids, philos, config) != EXIT_SUCCESS)
	{
		handle_process_creation_error(philos, philos_pids, config, config->number_of_philos);
		return (EXIT_FAILURE);
	}
	if (start_monitor_process(config, &monitor_pid) != EXIT_SUCCESS)
	{
		kill_all_philos(config);
		cleanup(philos, philos_pids, config);
		return (EXIT_FAILURE);
	}
	for (int i = 0; i < config->number_of_philos; i++)
		waitpid(philos_pids[i], NULL, 0);
	waitpid(monitor_pid, NULL, 0);
	cleanup(philos, philos_pids, config);
	clear_existing_semaphores();
	return (EXIT_SUCCESS);
}


