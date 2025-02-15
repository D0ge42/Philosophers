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

void	philosopher_eat(t_philo *philo)
{
	printf("%li %i is eating\n", time_to_ms() - philo->table->start_time,
		philo->id);
	custom_sleep(philo->table->time_to_eat, philo);
}

void	philosopher_sleep(t_philo *philo)
{
	printf("%li %i is sleeping\n", time_to_ms() - philo->table->start_time,
		philo->id);
	custom_sleep(philo->table->time_to_sleep, philo);
}

void	philosopher_think(t_philo *philo)
{
	printf("%li %i is thinking\n", time_to_ms() - philo->table->start_time,
		philo->id);
}

void	philosopher_took_fork(t_philo *philo)
{
	printf("%li %i has taken a fork\n", time_to_ms() - philo->table->start_time,
		philo->id);
}
