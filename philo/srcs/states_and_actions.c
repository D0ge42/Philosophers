/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_and_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:51 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 12:13:25 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>

void	philosopher_take_left(t_philo *philo)
{
	pthread_mutex_lock(philo->left_mutex);
	if (philo->left_fork[0] == -1 || philo->left_fork[0] == philo->id)
	{
		pthread_mutex_unlock(philo->left_mutex);
		return ;
	}
	philo->left_fork[0] = -1;
	safe_print(philo, "has taken a fork");
	philo->n_forks++;
	pthread_mutex_unlock(philo->left_mutex);
}

void	philosopher_take_right(t_philo *philo)
{
	pthread_mutex_lock(philo->right_mutex);
	if (philo->right_fork[0] == -1 || philo->right_fork[0] == philo->id)
	{
		pthread_mutex_unlock(philo->right_mutex);
		return ;
	}
	philo->right_fork[0] = -1;
	safe_print(philo, "has taken a fork");
	philo->n_forks++;
	pthread_mutex_unlock(philo->right_mutex);
}

/*Philosoper eating function. Here we retrieve the philo->last->meal
 * which then will be passed to the check death function.*/

void	philosopher_eat(t_philo *philo)
{
	philo->last_meal = time_to_ms();
	philo->is_thinking = 0;
	if (!safe_print(philo, "is eating"))
		return ;
	if (custom_sleep(philo->time_to_eat, philo))
		return ;
	philo->meals_eaten++;
	philo->n_forks = 0;
	pthread_mutex_lock(philo->right_mutex);
	philo->right_fork[0] = philo->id;
	pthread_mutex_unlock(philo->right_mutex);
	pthread_mutex_lock(philo->left_mutex);
	philo->left_fork[0] = philo->id;
	pthread_mutex_unlock(philo->left_mutex);
}

/*Philosopher will sleep for an amount of time after eating.*/

void	philosopher_sleep(t_philo *philo)
{
	if (!safe_print(philo, "is sleeping"))
		return ;
	if (custom_sleep(philo->time_to_sleep, philo))
		return ;
	philo->n_forks = 0;
}

/*Philosopher will think and print a message. This time we will protect
 * the print message with a mutex,
	since this is gonna be inside the routine loop
 * and accessible by everyone.*/

void	philosopher_think(t_philo *philo)
{
	time_t	think_time;

	think_time = 0;
	if (philo->is_thinking == 0)
	{
		if (!safe_print(philo, "is thinking"))
			return ;
		custom_sleep(think_time, philo);
		philo->is_thinking = 1;
	}
}
