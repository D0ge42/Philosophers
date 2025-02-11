#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>

void	free_previous_philos(t_philo **philos, int i);

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


t_table	*create_table(char **av, int ac)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	if (ac == 6)
		table->meals_to_eat = ft_atoi(av[5]);
	else
		table->meals_to_eat = -1;
	table->num_of_philos = ft_atoi(av[1]);
	table->mutexes = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!table->mutexes)
	{
		free(table);
		return (NULL);
	}
	memset(table->mutexes, 0, sizeof(pthread_mutex_t) * table->num_of_philos);
	table->forks = malloc(sizeof(int) * table->num_of_philos);
	if (!table->forks)
	{
		free(table->mutexes);
		free(table);
		return (NULL);
	}
	table->death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->death_mutex)
	{
		free(table->mutexes);
		free(table->forks);
		free(table);
		return (NULL);
	}
	memset(table->forks, 0, sizeof(int) * table->num_of_philos);
	return (table);
}

void	free_previous_philos(t_philo **philos, int i)
{
	while (i)
	{
		free(philos[i]);
		i--;
	}
	free(philos);
	return ;
}
