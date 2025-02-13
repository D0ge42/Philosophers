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
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

pid_t	**create_processes(pid_t **processes, int num_philos);
void init_processes(pid_t **processes,t_philo **philos,t_table *table, sem_t *forks);
void unlink_sems(t_philo **philos, t_table *table);

// Semaphore starting value will be n_fork.
// Every process will be able to access semaphore
// trough semaphore name.
// Forks are in the middle so every philo will access 2 forks
// whenver semaphore will allow them to.
// if a philosophers dies we can exit ?
//

int	main(int ac, char **av)
{
	t_philo **philos = NULL;
	pid_t	**processes = NULL;
	t_table *table = NULL;
	sem_t *forks;

	if (ac == 1)
		return (0);
	if (!is_input_valid(ac, av))
		return (0);
	philos = create_philos(av);
	table = create_table(av,ac);
	table_initializer(table, av, ac);
	forks = sem_open(FORKS,O_CREAT,0644,table->num_of_philos);
	unlink_sems(philos, table);
	processes = create_processes(processes, table->num_of_philos);
	init_processes(processes, philos,table,forks);
	sem_close(forks);
}

/*Function to create an array of processes.*/

pid_t	**create_processes(pid_t **philos, int num_philos)
{
	int	i;
	i = 0;
	philos = malloc(sizeof(pid_t *) * num_philos);
	while (i < num_philos)
	{
		philos[i] = malloc(sizeof(pid_t));
		i++;
	}
	return (philos);
}

void unlink_sems(t_philo **philos, t_table *table)
{
	int i = 0;
	sem_unlink(FORKS);
	while(i < table->num_of_philos)
	{
		sem_unlink(philos[i]->sem_name);
		i++;
	}
}

/*Function to initialize each process.*/ 
void init_processes(pid_t **processes, t_philo **philos,t_table *table, sem_t *forks)
{
	int i = 0;
	while (i < table->num_of_philos)
	{
		philos[i]->id = i + 1;
		philos[i]->table = table;
		philos[i]->last_meal = time_to_ms();
		(*processes)[i] = fork();
		if ((*processes)[i] == -1)
		{
			//Clean everything
			clean_processes(processes,table->num_of_philos);
			return ;
			//Exit 
		}
		else if ((*processes)[i] == 0)
		{
			routine(philos[i], forks);
			//Child process
			//Execute routine for each process at index [i];
		}
		i++;
	}
	i = 0;
		// int ret = waitpid(-1,&status,WNOHANG);
	while(1)
	{

		int j = 0;
		while(i < table->num_of_philos / 2)
		{
			sem_post(philos[i + j]->semaphore);
			philos[i + j]->last_meal = time_to_ms();
			int k = check_death(philos[i + j]->last_meal, philos[i + j]);
			if (k)
			{
				i = 0;
				while(i < table->num_of_philos)
				{
					kill((*processes)[i],SIGKILL);
					i++;
				}
				exit(1);
			}
			j+=2;
		}
		i = (i + 1) % table->num_of_philos;
	}	
}
