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

void *routine(void *ptr)
{
  t_philo *philo = (t_philo *)ptr;

  if (philo->id %2 == 1)
    usleep(500);

  while(philo->table->death_flag == 0 && philo->table->philos_full == 0)
  {

    philosopher_think(philo);
    
    sem_wait(philo->forks);
    philosopher_took_fork(philo);
    sem_wait(philo->forks);
    philosopher_took_fork(philo);

    sem_wait(philo->table->death_sem);
    philo->last_meal = time_to_ms();
    philo->meals_eaten+=1;
    sem_post(philo->table->death_sem);

    philosopher_eat(philo);

    sem_post(philo->forks);
    sem_post(philo->forks);

    philosopher_sleep(philo);
    
    usleep(100);
  }
  return (void *)(intptr_t)philo->id;
}

/*Each philo will access forks on the table by passing 2 sem_wait.
 * THey will decrease semaphor value by 1 for each sem_wait.*/

void monitor(t_philo *philo, sem_t *forks, sem_t *print_block)
{
  philo->print_block = print_block;
  philo->forks = forks;
  if (pthread_create(&philo->monitor,NULL, &routine, philo))
	{
		printf("failed to create thread\n");
    routine_sem_unlink(philo, forks,print_block);
		exit(0);
	}
  pthread_detach(philo->monitor);
  while(1)
  {
    sem_wait(philo->table->death_sem);
    int death = time_to_ms() - philo->last_meal;
    sem_post(philo->table->death_sem);
    if (death >= philo->table->time_to_die)
    {
      philo->table->death_flag = 1;
      routine_sem_unlink(philo, forks, print_block);
      exit(philo->id);
    }
    sem_wait(philo->table->death_sem);
    unsigned int meals_eaten = philo->meals_eaten;
    sem_post(philo->table->death_sem);

    if (meals_eaten >= philo->table->meals_to_eat)
    {
      sem_wait(philo->table->death_sem);
      philo->table->philos_full = 1;
      sem_post(philo->table->death_sem);
      break;
    }
	}
 pthread_join(philo->monitor, NULL);
}

void routine_sem_unlink(t_philo *philo, sem_t *forks, sem_t *print_block)
{
  sem_close(forks);
  sem_close(philo->table->death_sem);
  sem_close(print_block);
}
