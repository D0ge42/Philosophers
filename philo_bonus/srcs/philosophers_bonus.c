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
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

pid_t	**create_processes(pid_t **processes, int num_philos);
void init_processes(pid_t **processes,t_philo **philos,t_table *table, sem_t *forks);
void unlink_sems(t_philo **philos, t_table *table);
int check_philos_health(t_philo **philos, t_table *table);
void wait_pid_and_exit(t_philo **philo, t_table *table, pid_t **processes);
void free_everything(t_philo **philo,t_table *table, pid_t **processes);

// Semaphore starting value will be n_fork.
// Every process will be able to access semaphore
// trough semaphore name.
// Forks are in the middle so every philo will access 2 forks
// whenver semaphore will allow them to.
// if a philosophers dies we can exit ?

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
	free_everything(philos,table,processes);
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
	sem_unlink("/printblock");
	sem_close(philos[i]->print_block);
	while(i < table->num_of_philos)
	{
		sem_close(philos[i]->semaphore);
		sem_unlink(philos[i]->sem_name);
		i++;
	}
}

void free_everything(t_philo **philo,t_table *table,pid_t **processes)
{
	int i = 0;
	while(i < table->num_of_philos)
	{

		free(philo[i]->sem_name);
		free(philo[i]);
		free(processes[i]);
		i++;
	}
	free(processes);
	free(table);
	free(philo);
}

/*Function to initialize each process.*/ 
void init_processes(pid_t **processes, t_philo **philos,t_table *table, sem_t *forks)
{
	int i = 0;
	while (i < table->num_of_philos)
	{
		philos[i]->meals_eaten = 0;
		philos[i]->id = i + 1;
		philos[i]->table = table;
		philos[i]->last_meal = time_to_ms();
		philos[i]->pid = fork();
		if ((philos[i]->pid) == -1)
		{
			clean_processes(processes,table->num_of_philos);
			return ;
		}
		else if ((philos[i]->pid) == 0)
			routine(philos[i], forks);
		i++;
	}
	wait_pid_and_exit(philos,table,processes);
}
	
void wait_pid_and_exit(t_philo **philo, t_table *table, pid_t **processes)
{
	(void)processes;
	int i;
	int status;
	i = 0;
	while(i < table->num_of_philos)
	{
		waitpid(-1,&status,0);
		if (status)
		{
			int philo_id = WEXITSTATUS(status);
			i = 0;
			while(i < table->num_of_philos)
			{
				kill(philo[i]->pid,SIGKILL);
				i++;
			}
			printf("%li %i has died\n",time_to_ms() - table->start_time,philo_id);
			break;
		}
		i++;
	}
}
