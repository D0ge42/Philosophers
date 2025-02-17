/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:32 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/17 11:05:04 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <pthread.h>
#include <semaphore.h>

void	routine_sem_unlink(t_philo *philo, sem_t *forks, sem_t *print_block);
void	*philo_routine(t_philo *philo);
int		meals_eaten_check(t_philo *philo);
void	check_philos(t_philo *philo, sem_t *forks, sem_t *print_block);

/*Each philo will access forks on the table by passing 2 sem_wait.
 * THey will decrease semaphor value by 1 for each sem_wait.*/

void	monitor(t_philo *philo, sem_t *forks, sem_t *print_block)
{
	philo->print_block = print_block;
	philo->forks = forks;
	if (pthread_create(&philo->monitor, NULL, &routine, philo))
	{
		printf("failed to create thread\n");
		routine_sem_unlink(philo, forks, print_block);
		exit(0);
	}
	pthread_detach(philo->monitor);
	while (1)
		check_philos(philo, forks, print_block);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 1)
		usleep(500);
	philo_routine(philo);
	return (NULL);
}

void	check_philos(t_philo *philo, sem_t *forks, sem_t *print_block)
{
	sem_wait(philo->table->death_sem);
	check_death(philo->last_meal, philo);
	if (philo->table->death_flag == 1)
	{
		sem_post(philo->table->death_sem);
		routine_sem_unlink(philo, forks, print_block);
		exit(philo->id);
	}
	if (philo->table->everyone_ate)
	{
		philo->table->philos_full++;
		if (philo->table->philos_full == philo->table->num_of_philos)
		{
			sem_post(philo->table->death_sem);
			routine_sem_unlink(philo, forks, print_block);
			exit(0);
		}
	}
	sem_post(philo->table->death_sem);
	usleep(100);
}

void	*philo_routine(t_philo *philo)
{
	while (1)
	{
		philosopher_think(philo);
		sem_wait(philo->forks);
		philosopher_took_fork(philo);
		sem_wait(philo->forks);
		philosopher_took_fork(philo);
		sem_wait(philo->table->death_sem);
		philo->last_meal = time_to_ms();
		philo->meals_eaten++;
		sem_post(philo->table->death_sem);
		philosopher_eat(philo);
		sem_wait(philo->table->death_sem);
		if (meals_eaten_check(philo))
			return (NULL);
		sem_post(philo->table->death_sem);
		sem_post(philo->forks);
		sem_post(philo->forks);
		philosopher_sleep(philo);
		usleep(100);
	}
	return (NULL);
}

int	meals_eaten_check(t_philo *philo)
{
	if (philo->meals_eaten == philo->table->meals_to_eat)
	{
		philo->table->everyone_ate = 1;
		sem_post(philo->table->death_sem);
		sem_post(philo->forks);
		sem_post(philo->forks);
		return (1);
	}
	return (0);
}
