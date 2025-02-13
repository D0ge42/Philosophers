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
#include <semaphore.h>

/*Each philo will access forks on the table by passing 2 sem_wait.
 * THey will decrease semaphor value by 1 for each sem_wait.*/

void routine(t_philo *philo, sem_t *forks)
{
	while(1)
	{
		philosopher_think(philo);
		sem_wait(forks);
		philosopher_took_fork(philo);
		sem_wait(forks);
		philosopher_took_fork(philo);
		philo->last_meal = time_to_ms();
		philosopher_eat(philo);
		sem_post(forks);
		sem_post(forks);
		philosopher_sleep(philo);
	}
}

