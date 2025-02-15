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
void	init_processes(t_philo *philos, t_table *table, sem_t *forks, sem_t *print_block);
void	unlink_sems(t_philo *philos, t_table *table);
// int check_philos_health(t_philo **philos, t_table *table);
void	wait_pid_and_exit(t_philo *philo, t_table *table);
void	free_everything(t_philo **philo, t_table *table, pid_t **processes);
void	free_processes(pid_t **processes, t_table *table);
void school_shooting(t_philo *philo);
// Semaphore starting value will be n_fork.
// Every process will be able to access semaphore
// trough semaphore name.
// Forks are in the middle so every philo will access 2 forks
// whenver semaphore will allow them to.
// if a philosophers dies we can exit ?

int	main(int ac, char **av)
{
	t_philo	philos[200];
	t_table	table;
	sem_t	*forks;
	sem_t	*print_block;

	if (ac == 1)
		return (0);
	if (!is_input_valid(ac, av))
		return (0);
	create_philos(av, philos);
	create_table(av, ac, &table);
	table_initializer(&table, av, ac);
	forks = sem_open(FORKS, O_CREAT, 0644, table.num_of_philos);
	print_block = sem_open("/printblock", O_CREAT, 0644, table.num_of_philos);
  unlink_sems(philos, &table);
	init_processes(philos, &table, forks, print_block);
	sem_close(forks);
  sem_close(print_block);
  sem_close(table.death_sem);
}

void	unlink_sems(t_philo *philos, t_table *table)
{
	int	i;

	i = 0;
	sem_unlink(FORKS);
	sem_unlink("/printblock");
  sem_unlink("/death_sem");
	while (i < table->num_of_philos)
	{
    sem_close(philos[i].sem_meal);
		sem_close(philos[i].semaphore);
		sem_unlink(philos[i].sem_name);
		sem_unlink(philos[i].sem_meal_name);
		i++;
	}
}

/*Function to initialize philos.*/

void	init_processes(t_philo *philos, t_table *table, sem_t *forks, sem_t *print_block)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		philos[i].meals_eaten = 0;
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].last_meal = time_to_ms();
		philos[i].pid = fork();
		if ((philos[i].pid) == -1)
			return ;
		else if ((philos[i].pid) == 0)
			monitor(&philos[i], forks, print_block);
		i++;
	}
	wait_pid_and_exit(philos, table);
}

void	wait_pid_and_exit(t_philo *philo, t_table *table)
{
	int	i;
	int	status;
	int	philo_id;

	i = 0;
	while (i < table->num_of_philos)
	{
		waitpid(-1, &status, 0);
    if (status)
		{
			philo_id = WEXITSTATUS(status);
			i = 0;
      school_shooting(philo);
			printf("%li %i has died\n", time_to_ms() - table->start_time,philo_id);
			break ;
		}
		i++;
	}
}

void school_shooting(t_philo *philo)
{
  int i = 0;
  while (i < philo->table->num_of_philos)
	{
				kill(philo[i].pid, SIGKILL);
        i++;
			}
}
