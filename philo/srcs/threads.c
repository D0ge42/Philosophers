#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void assign_forks(t_philo *philo, int *forks);


void check_death(time_t last_meal_time, t_philo *philos)
{
  time_t current_time = time_to_ms();   
  time_t time_since_last_meal = current_time - last_meal_time;

  if (time_since_last_meal > philos->time_to_die)
  {
    philos->table->death_flag = 1; 
    printf("Philosopher[%i] has died\n", philos->id);
  }
}

void *routine(void *pointer)
{

  t_philo *philo = (t_philo *)pointer;
 
  philo->mutex = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(philo->mutex,NULL);
  // int i = 0;
  if (philo->id %2 == 0)
    custom_sleep(philo->time_to_sleep);
  printf("Left fork of current philo %i =  %i\n",philo->id,philo->left_fork[0]);
  printf("Right fork of current philo %i = %i\n",philo->id,philo->right_fork[0]);
  printf("Current philo id %i\n",philo->id);
  while(philo->table->death_flag == 0)
  {
    pthread_mutex_lock(philo->mutex);
    philosopher_take_forks(philo);
    pthread_mutex_unlock(philo->mutex);
    philosopher_eat(philo);
    philosopher_sleep(philo);
    philosopher_think(philo);
  }
  return 0;
}

// &philos[i]->thread
// &philos[0][i].thread


void assign_forks(t_philo *philo, int *forks)
{
  philo->left_fork = &forks[philo->id - 1];
  philo->right_fork = &forks[philo->id % philo->table->num_of_philos];
}

int create_threads(t_philo **philos, t_table *table)
{
  int i = 0;
  int *forks = malloc(sizeof(int) * philos[i]->table->num_of_philos);
    while(i < table->num_of_philos)
  {
    if (pthread_create(&philos[i]->thread,NULL,routine,philos[i])!= 0)
    {
      printf("Error in creating thread");
      return 0;
    }
    assign_forks(philos[i],forks);
    i++;
  }
  i = 0;
  while(i < table->num_of_philos)
  {
    if (pthread_join(philos[i]->thread,NULL) != 0)
    {
      printf("Error in creating thread");
      return 0;
    }
    i++;
  }
  return 1;
}
