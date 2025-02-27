/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:22:00 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 12:17:40 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void	assign_mutex_and_forks(t_philo *philo, pthread_mutex_t *mutex,
			int *forks, int philos_num);

/*Function to check if enough time has passed for a philospher
 * to die. It will take last meal time and do current_time
	- time_since_last meal
 * If the time since last meal is >= than philo's time to die,
	philo is dead.
 * */

void	check_death(time_t last_meal_time, t_philo *philos)
{
	time_t	current_time;
	time_t	time_since_last_meal;

	pthread_mutex_lock(philos->table->death_mutex);
	current_time = time_to_ms();
	time_since_last_meal = current_time - last_meal_time;
	if (time_since_last_meal >= philos->time_to_die
		&& philos->table->death_flag == 0)
	{
		philos->table->death_flag = 1;
		printf("%li %i has died\n", current_time - philos->start_time,
			philos->id);
	}
	pthread_mutex_unlock(philos->table->death_mutex);
}

/*While loop to create threads for each philosopher and join them.*/

int	create_threads(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_create(&philos[i]->thread, NULL, routine, philos[i]) != 0)
		{
			printf("Error in creating thread");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_join(philos[i]->thread, NULL) != 0)
		{
			printf("Error in joining thread");
			return (0);
		}
		i++;
	}
	return (1);
}
