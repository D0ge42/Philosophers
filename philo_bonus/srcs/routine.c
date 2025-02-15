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
#include <pthread.h>
#include <semaphore.h>

void routine_sem_unlink(t_philo *philo, sem_t *forks, sem_t *print_block);

void *monitor(void *ptr)
{
  t_philo *philo = (t_philo *)ptr;
  while(1)
  {
    sem_wait(philo->table->death_sem);
    int death = check_death(philo->last_meal, philo);
    sem_post(philo->table->death_sem);
    if (death)
      return (void *)(size_t)philo->id;
    sem_wait(philo->table->death_sem);
    unsigned int meals_eaten = philo->meals_eaten;
    sem_post(philo->table->death_sem);
    if (meals_eaten >= philo->table->meals_to_eat)
    {
      sem_wait(philo->table->death_sem);
      philo->table->philos_full = 1;
      sem_post(philo->table->death_sem);
      return 0;
    }
    usleep(50);
	}
}

/*Each philo will access forks on the table by passing 2 sem_wait.
 * THey will decrease semaphor value by 1 for each sem_wait.*/

void routine(t_philo *philo, sem_t *forks, sem_t *print_block)
{
  if (philo->table->num_of_philos == 1)  // Special case for 1 philosopher
  {
    philosopher_think(philo);
    sem_wait(forks);
    philosopher_took_fork(philo);
    usleep(philo->table->time_to_die * 1000);
    sem_post(forks);
    routine_sem_unlink(philo, forks,print_block);
    exit(1);
  }
  void *status;
	if (pthread_create(&philo->monitor,NULL, &monitor, philo))
	{
		printf("failed to create thread\n");
    routine_sem_unlink(philo, forks,print_block);
		exit(0);
	}
	if (philo->id % 2 == 1)
    usleep(500);
	while(1)
	{
    int stop = 0;
    sem_wait(philo->table->death_sem);
    if (philo->table->philos_full == 1 || philo->table->death_flag == 1)
      stop = 1;
    sem_post(philo->table->death_sem);
    if (stop)
      break;
    philosopher_think(philo);
    sem_wait(forks);
		philosopher_took_fork(philo);
		sem_wait(forks);
   
    sem_wait(philo->table->death_sem);
		philosopher_took_fork(philo);
    philo->last_meal = time_to_ms();
    philo->meals_eaten+=1;
    sem_post(philo->table->death_sem);
    
    
    philosopher_eat(philo);
    
    sem_post(forks);
		sem_post(forks);
		philosopher_sleep(philo);
		usleep(100);
	}
  pthread_join(philo->monitor,&status);
  routine_sem_unlink(philo, forks,print_block);
  exit((size_t)status);
}

void routine_sem_unlink(t_philo *philo, sem_t *forks, sem_t *print_block)
{
  sem_close(forks);
  sem_close(philo->table->death_sem);
  sem_close(print_block);
}
