#include "../includes/philo.h"

void *monitor_routine(void *params) 
{
    t_config *config = (t_config *)params;
    t_philo *philo;
    struct timeval current_time;
	int	done_philo;

    while (!config->stop) {

		gettimeofday(&current_time, NULL);

        philo = config->first_philo;
		done_philo = 0;
        while (philo) {
            pthread_mutex_lock(&philo->mutex_eating);
            gettimeofday(&current_time, NULL);

			long time_since_last_eat = time_diff_in_ms(philo->last_eat_time, current_time);
			
            if (time_since_last_eat > config->time_to_die) {
                philo->alive = false;
                philo_print("died", philo);

                config->stop = true;
				pthread_mutex_unlock(&philo->mutex_eating);
				return (NULL);
            }
            pthread_mutex_unlock(&philo->mutex_eating);
			if (config->max_eat_times >= 0 && philo->eat_count >= config->max_eat_times)
				done_philo ++;
            philo = philo->next;
        }
		if (config->max_eat_times >= 0 && done_philo == config->number_of_philosophers)
		{
			config->stop = true;
			return (NULL);
		}
        usleep(1000); 
    }
    return (NULL);
}

void *philosopher_routine(void *params) {
	t_philo		*philo;
	t_config	*config;
	struct timeval start_sleep, end_sleep;

	philo = (t_philo *)params;
	config = philo->config;
	if (!config)
		return (NULL);
	if (philo->id % 2 && config->number_of_philosophers > 1)
		philo_sleep(config->time_to_eat / 25, config);
	
	while (!config->stop && philo->alive)
	// add here check for maximum eat time
	{
		//if (config->max_eat_times != -1 && philo->eat_count >= config->max_eat_times)
			// TODO: we need to check somewhere and stop if all philos eaten enough times.
    	//	break; // no need to continue if philo ate enough times
		if (config->stop || !philo->alive)
			break;

		philo_take_forks_and_eat(philo);

		if (config->stop || !philo->alive)
			break;

		philo_print("is sleeping", philo);

		gettimeofday(&start_sleep, NULL);

		philo_sleep(config->time_to_sleep, config);

		gettimeofday(&end_sleep, NULL);

		if (config->stop || !philo->alive)
			break;

		philo_print("is thinking", philo);
	}
	return (NULL);
}