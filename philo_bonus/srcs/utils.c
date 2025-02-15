/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:22:08 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 10:22:10 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>

static void	parse_input_string(t_philo *philo, char *to_print);

int	safe_print(t_philo *philo, char *to_print)
{
	if (philo->table->death_flag == 0)
	{
		parse_input_string(philo, to_print);
		return (0);
	}
	else
		return (1);
}

/*Custom time to sleep function. This is useful to let the philosophers
 * sleep for a certain amount of time, specified in the main args.*/

static void	parse_input_string(t_philo *philo, char *to_print)
{
	if (ft_strcmp(to_print, "is thinking") == 0)
		printf("%li %i %s%s%s\n", time_to_ms() - philo->table->start_time,
			philo->id, CYAN, to_print, RESET);
	else if (ft_strcmp(to_print, "is eating") == 0)
		printf("%li %i %s%s%s\n", time_to_ms() - philo->table->start_time,
			philo->id, GREEN, to_print, RESET);
	else if (ft_strcmp(to_print, "is sleeping") == 0)
		printf("%li %i %s%s%s\n", time_to_ms() - philo->table->start_time,
			philo->id, BLUE, to_print, RESET);
	else if (ft_strcmp(to_print, "has taken a fork") == 0)
		printf("%li %i %s%s%s\n", time_to_ms() - philo->table->start_time,
			philo->id, YELLOW, to_print, RESET);
	else
		printf("%li %i %s\n", time_to_ms() - philo->table->start_time,
			philo->id, to_print);
}

int	check_death(time_t last_meal_time, t_philo *philos)
{
	time_t	current_time;
	time_t	time_since_last_meal;

	current_time = time_to_ms();
	time_since_last_meal = current_time - last_meal_time;
	if (time_since_last_meal >= philos->table->time_to_die )
	{
		philos->table->death_flag = 1;
		// printf("%li %i has died\n", current_time - philos->table->start_time,
			// philos->id);
		return (1);
	}
	return (0);
}

int	custom_sleep(time_t time_to_sleep, t_philo *philo)
{
	time_t	start;

	(void)philo;
	start = time_to_ms() + time_to_sleep;
	while ((time_to_ms() < start))
	{
		// check_death(philo->last_meal, philo);
		usleep(50);
	}
	return (0);
}

/*Get current time in millisecond. Time is expressed in epoch time, which
 * is basically seconds passed since 1970-01-01 00:00:00
 * Returns time value */

time_t	time_to_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
