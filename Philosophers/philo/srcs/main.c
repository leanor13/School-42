/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 14:29:42 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	pthread_t	*threads;
	pthread_t	monitor_thread;
	int			created_threads;

	config = init_config(argc, argv);
	if (!config)
		return (EXIT_FAILURE);
	philos = initiate_philos(config);
	if (!philos)
		return (free(config), EXIT_FAILURE);
	created_threads = create_threads(&threads, philos, config);
	if (created_threads != EXIT_SUCCESS)
		return (handle_thread_creation_error(philos, threads, config,
				created_threads));
	if (start_monitor_thread(config, &monitor_thread) != EXIT_SUCCESS)
	{
		cleanup(philos, threads, config);
		return (EXIT_FAILURE);
	}
	join_threads(threads, config->number_of_philos);
	pthread_join(monitor_thread, NULL);
	cleanup(philos, threads, config);
	return (EXIT_SUCCESS);
}
