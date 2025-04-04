/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:12 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 12:20:30 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

static void	free_previous_philos(t_philo **philos, int i);
void		create_mutexes(t_table *table);
static void	free_mutexes(t_table *table);

/*Function responsible for creating philos.
 * It will allocate enough memory for an array
 * of philos, memset it to 0,
 * and check for eventual malloc errors in philosophers creation.*/

t_philo	**create_philos(char **av)
{
	int		philos_num;
	int		i;
	t_philo	**philos;

	philos_num = ft_atoi(av[1]);
	i = 0;
	philos = malloc(sizeof(t_philo *) * ft_atoi(av[1]));
	if (!philos)
		return (NULL);
	memset(philos, 0, sizeof(t_philo *) * ft_atoi(av[1]));
	while (i < philos_num)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			free_previous_philos(philos, i);
			return (0);
		}
		memset(philos[i], 0, sizeof(t_philo));
		i++;
	}
	return (philos);
}

/*Create table, forks int array and initialize everything.
 * Also mutexes creation function is called in here.*/

t_table	*create_table(char **av, int ac)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->philos_full = 0;
	if (ac == 6)
		table->meals_to_eat = ft_atoi(av[5]);
	else
		table->meals_to_eat = -1;
	table->num_of_philos = ft_atoi(av[1]);
	table->forks = malloc(sizeof(int) * table->num_of_philos);
	if (!table->forks)
	{
		free(table->mutexes);
		free(table);
		return (NULL);
	}
	memset(table->forks, 0, sizeof(int) * table->num_of_philos);
	create_mutexes(table);
	return (table);
}

/*Function to initialize and create death and forks mutexes*/

void	create_mutexes(t_table *table)
{
	table->mutexes = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!table->mutexes)
	{
		free(table);
		return ;
	}
	memset(table->mutexes, 0, sizeof(pthread_mutex_t) * table->num_of_philos);
	table->death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->death_mutex)
	{
		free(table->mutexes);
		free(table->forks);
		free(table);
		return ;
	}
	memset(table->death_mutex, 0, sizeof(pthread_mutex_t));
	table->meals_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->meals_mutex)
	{
		free_mutexes(table);
		return ;
	}
	memset(table->meals_mutex, 0, sizeof(pthread_mutex_t));
}

static void	free_mutexes(t_table *table)
{
	free(table->death_mutex);
	free(table->mutexes);
	free(table->forks);
	free(table);
}

static void	free_previous_philos(t_philo **philos, int i)
{
	while (i)
	{
		free(philos[i]);
		i--;
	}
	free(philos);
	return ;
}
