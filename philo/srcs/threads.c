#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void assign_mutex_and_forks(t_philo *philo, pthread_mutex_t *mutex, int *forks, int philos_num);

/*Function to check if enough time has passed for a philospher
 * to die. It will take last meal time and do current_time - time_since_last meal
 * If the time since last meal is greater than philo's time to die, philo is dead.
 * */


void check_death(time_t last_meal_time, t_philo *philos)
{
  pthread_mutex_lock(philos->table->death_mutex);

  time_t relative_current_time = (time_to_ms() - philos->start_time);
  time_t relative_last_meal_time = (last_meal_time - philos->start_time);
  time_t time_since_last_meal  = relative_current_time - relative_last_meal_time;
  
  int should_print = 0;
  if ((time_since_last_meal >= philos->time_to_die) && philos->table->death_flag == 0)
  {
    philos->table->death_flag = 1;
    should_print = 1;
  }
  pthread_mutex_unlock(philos->table->death_mutex);
  if (should_print)
    printf("%li Philo[%i] has died\n",time_to_ms() - philos->start_time,philos->id);
}


/*While loop to create threads for each philosopher and join them.*/

int create_threads(t_philo **philos, t_table *table)
{
  int i = 0;
  
  while(i < table->num_of_philos)
  {
    if (pthread_create(&philos[i]->thread,NULL,routine,philos[i])!= 0)
    {
      printf("Error in creating thread");
      return 0;
    }
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
