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
	if (safe_print(philo, "is eating"))
		return ;
	custom_sleep(philo->table->time_to_eat, philo);
}

void	philosopher_sleep(t_philo *philo)
{
	if (safe_print(philo, "is sleeping"))
		return ;
	custom_sleep(philo->table->time_to_sleep, philo);
}

void	philosopher_think(t_philo *philo)
{
	if (safe_print(philo, "is thinking"))
		return ;
}

// void philosopher_drop_fork(t_philo *philo)
// {
// 	safe_print(philo, "dropped a fork");
// }

void	philosopher_took_fork(t_philo *philo)
{
	if (safe_print(philo, "has taken a fork"))
		return ;
}
