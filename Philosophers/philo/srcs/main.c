/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/04 19:03:03 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *myThreadFun(void *arg) 
{ 
	(void)arg;
    sleep(1);
    printf("Printing Hello Philo from Thread \n"); 
	sleep(3);
    return NULL; 
} 

int	main(void)
{
	pthread_t thread_id; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, myThreadFun, NULL); 
    pthread_join(thread_id, NULL); 
    printf("After Thread\n"); 
    exit(0); 
}