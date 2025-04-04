/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:20:58 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 12:16:53 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>

/*Void function, takes pointer to table and cleans everything in it.
 * Also responsible for destroying mutexes.*/

void	clean_table(t_table *table)
{
	int	i;
	int	num_of_philos;

	free(table->forks);
	i = 0;
	num_of_philos = table->num_of_philos;
	while (i < num_of_philos)
	{
		if (pthread_mutex_destroy(&table->mutexes[i]))
		{
			printf("Error in destroying mutex\n");
			return ;
		}
		i++;
	}
	pthread_mutex_destroy(table->death_mutex);
	pthread_mutex_destroy(table->meals_mutex);
	free(table->mutexes);
	free(table->death_mutex);
	free(table->meals_mutex);
	free(table);
}

/*Just clean philos and philos array*/

void	clean_philos(t_philo **philos, char **av)
{
	int	i;
	int	num_of_philos;

	i = 0;
	num_of_philos = ft_atoi(av[1]);
	while (i < num_of_philos)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}
