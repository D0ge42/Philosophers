/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:39 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 13:59:51 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>

static void	is_even_or_odd(t_philo *philo);
static int	meals_eaten_check(t_philo *philo);

/*Philosophers routine.
 * Check death at the start.
 * Let philosophers thinks
 * break whenever a philosopher dies.
 * If philo id is even they'll first try to take right fork, then left one.
 * Else the opposite
 * If a philosopher has 2 forks it can eat.
 * After eating we'll check if number of meals eaten for current philo is

	* equal to the number of the meals to eat.
  * If so it means a philosopher has eaten enough.
 * Once the number of philos full has reached num of philos we can break.

	* This is important because
  * if num of meals to eat is provided it won't prevent other
 * threads from printing their status on the stdout.
 * If yes, we break, else philosoper can sleep and we repeat the loop.*/

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		check_death(philo->last_meal, philo);
		if (philo->table->meals_to_eat == 0 || philo->table->death_flag)
			break ;
		if (philo->is_thinking == 0 && philo->n_forks == 0)
			philosopher_think(philo);
		is_even_or_odd(philo);
		if (philo->n_forks == 2)
		{
			philosopher_eat(philo);
			if (meals_eaten_check(philo))
				break ;
			philosopher_sleep(philo);
		}
	}
	return (0);
}

static int	meals_eaten_check(t_philo *philo)
{
	if (philo->meals_eaten == philo->table->meals_to_eat)
	{
		pthread_mutex_lock(philo->table->meals_mutex);
		philo->table->philos_full++;
		pthread_mutex_unlock(philo->table->meals_mutex);
	}
	pthread_mutex_lock(philo->table->meals_mutex);
	if (philo->table->philos_full == philo->table->num_of_philos)
	{
		pthread_mutex_unlock(philo->table->meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->table->meals_mutex);
	return (0);
}

static void	is_even_or_odd(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philosopher_take_right(philo);
		if (philo->n_forks == 1)
			philosopher_take_left(philo);
	}
	else
	{
		philosopher_take_left(philo);
		if (philo->n_forks == 1)
			philosopher_take_right(philo);
	}
}
