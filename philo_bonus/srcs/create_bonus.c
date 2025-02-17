/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:32 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/17 10:56:07 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>

char	*ft_strcpy(char *s1, char *s2);
char	*ft_strcat(char *s1, char *s2);

void	create_philos(char **av, t_philo *philos)
{
	int		philos_num;
	int		i;
	char	*str;

	philos_num = ft_atoi(av[1]);
	i = 0;
	while (i < philos_num)
	{
		memset(&philos[i], 0, sizeof(t_philo));
		philos[i].meals_eaten = 0;
		str = ft_itoa(i + 1);
		ft_strcpy(philos[i].sem_name, "/philosophers");
		ft_strcpy(philos[i].sem_meal_name, "/philo_meal");
		ft_strcat(philos[i].sem_name, str);
		ft_strcat(philos[i].sem_meal_name, str);
		free(str);
		philos[i].semaphore = sem_open(philos[i].sem_name, O_CREAT | O_EXCL,
				0644, 0);
		philos[i].sem_meal = sem_open(philos[i].sem_meal_name, O_CREAT | O_EXCL,
				0644, 1);
		i++;
	}
}

void	create_table(char **av, int ac, t_table *table)
{
	memset(table, 0, sizeof(t_table));
	table->philos_full = 0;
	if (ac == 6)
		table->meals_to_eat = ft_atoi(av[5]);
	else
		table->meals_to_eat = -1;
	table->num_of_philos = ft_atoi(av[1]);
	table->death_sem = sem_open("/death_sem", O_CREAT, 0644, 1);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strcat(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		s1[i] = s2[j];
		j++;
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
