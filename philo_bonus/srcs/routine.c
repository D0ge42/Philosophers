/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:32 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 15:18:02 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <pthread.h>
#include <semaphore.h>


void *monitor(void *ptr)
{
    t_philo *philo = (t_philo *)ptr;
    while(1)
    {
        if (time_to_ms() - philo->last_meal >= philo->table->time_to_die)
        {
            philo->table->death_flag = 1;
            break;  // Return instead of exit
        }
        if (philo->meals_eaten >= philo->table->meals_to_eat)
			break;
	}
	usleep(1000);
	if (philo->table->death_flag == 1)
		exit(philo->id);
	else
		exit(0);
    return NULL;
}

/*Each philo will access forks on the table by passing 2 sem_wait.
 * THey will decrease semaphor value by 1 for each sem_wait.*/

void routine(t_philo *philo, sem_t *forks)
{
	if (pthread_create(&philo->monitor,NULL, &monitor, philo))
	{
		printf("failed to create thread\n");
		exit(0);
	}
	pthread_detach(philo->monitor);
	if (philo->id % 2 == 1)
		usleep(1000);
	while(philo->table->death_flag == 0)
	{
		philosopher_think(philo);
		sem_wait(forks);
		philosopher_took_fork(philo);
		sem_wait(forks);
		philosopher_took_fork(philo);
		philo->last_meal = time_to_ms();
		philosopher_eat(philo);
		philo->meals_eaten+=1;
		sem_post(forks);
		sem_post(forks);
		philosopher_sleep(philo);
		usleep(100);
	}
	sem_close(philo->semaphore);
	sem_close(philo->semaphore);
}

