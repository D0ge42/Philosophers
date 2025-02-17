/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:32 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/17 11:04:50 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>

void	init_processes(t_philo *philos, t_table *table, sem_t *forks,
			sem_t *print_block);
void	unlink_sems(t_philo *philos, t_table *table);
void	wait_pid_and_exit(t_philo *philo, t_table *table);
void	school_shooting(t_philo *philo);

/*Main process.
 * Basically everything was made without the use of malloc to prevent
 * leaks, since we'll be dealing with both processed and threads.
 * Everything get initialized in both create_philo and table initializer.
 * 2 global semaphores are created.
 * One is gonna be responsible for forks. The other for the prints.
 * Init process will fork the main process into sub processes (philos.)
 * Inside each process there we'll find (main thread) and a subthread (routine)
 * Monitor will check for philos health. */

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
	unlink_sems(philos, &table);
	if (table.meals_to_eat == 0)
		return (0);
	forks = sem_open(FORKS, O_CREAT, 0644, table.num_of_philos);
	print_block = sem_open("/printblock", O_CREAT, 0644, table.num_of_philos);
	init_processes(philos, &table, forks, print_block);
	sem_close(forks);
	sem_close(print_block);
	sem_close(table.death_sem);
}

/*Since semaphores are created as files, we've to unlink them.*/

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

void	init_processes(t_philo *philos, t_table *table, sem_t *forks,
		sem_t *print_block)
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

/*Waitpid will basically wait for every process to end when set with -1.
 * That means that the execution of the main process
 will stop until each child
 * hasn't finished (or died/reached num of meals).
 * When a child dies we exit the process and return its ID as status.
 * We''ll then be able to retrieve the PHILO ID
 by applying a mask to the exit status.*/

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
			philo_id = (((status) & 0xff00) >> 8);
			i = 0;
			school_shooting(philo);
			printf("%li %i has died\n", time_to_ms() - table->start_time,
				philo_id);
			break ;
		}
		i++;
	}
}

/*Function to kill each child (process)*/

void	school_shooting(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->num_of_philos)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}
