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
#include <fcntl.h>

static void	free_previous_philos(t_philo **philos, int i);

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
		philos[i]->sem_name = ft_strjoin("/philosophers",ft_itoa(i + 1));
		philos[i]->semaphore = sem_open(philos[i]->sem_name,O_CREAT | O_EXCL,0644,0);
		i++;
	}
	return (philos);
}


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
	return (table);
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


