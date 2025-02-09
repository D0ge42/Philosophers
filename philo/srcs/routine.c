#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>

/*Function will take start time and check when its time to stop sleeping*/
int safe_print(t_philo *philo, char *to_print);

void *routine(void *pointer)
{
  t_philo *philo = (t_philo *)pointer;
  // printf("%i\n",philo->id);
  if (philo->table->num_of_philos == 1)
  {
  
    printf("%li %i has taken a fork\n", time_to_ms() - philo->start_time, philo->id);
    usleep(philo->time_to_die * 1000); // Aspetta fino alla morte
    printf("%li %i has died\n", time_to_ms() - philo->start_time, philo->id);
    return NULL;
  }
  while(philo->table->death_flag == 0)
  {
    // printf("DEATH FLAG  = %i\n",philo->table->death_flag);
    check_death(philo->last_meal, philo);
    if (!philosopher_take_forks(philo))
        philosopher_think(philo);
    else
      philo->is_thinking = 0;
  }
  return 0;
}

/*With this function we'll make a mutex protected check.
 * That means that we'll use a mutex to check and set the forks
 * for the philosophers.
 * Once forks are set we'll decide if we can eat or not.*/
int philosopher_take_forks(t_philo *philo)
{
  int both_forks_available = 0;
  // Evitiamo deadlock: i filosofi pari prendono prima la destra, i dispari la sinistra
  if (philo->id % 2 == 0)
  {
    pthread_mutex_lock(philo->right_mutex);
    pthread_mutex_lock(philo->left_mutex);
  }
  else
  {
    pthread_mutex_lock(philo->left_mutex);
    pthread_mutex_lock(philo->right_mutex);
  }
  if (philo->left_fork[0] == 0 && philo->right_fork[0] == 0)
  {
    both_forks_available = 1;
    philo->left_fork[0] = 1;
    philo->right_fork[0] = 1;
  }
  pthread_mutex_unlock(philo->left_mutex);
  pthread_mutex_unlock(philo->right_mutex);
  
  if (both_forks_available)
  {
    if (!safe_print(philo, "has taken a fork")
      || !safe_print(philo,"has taken a fork"))
      return 0;
    philosopher_eat(philo);

    if(philo->id %2 == 0)
    {
      pthread_mutex_lock(philo->right_mutex);
      pthread_mutex_lock(philo->left_mutex);
    }
    else
    {
      pthread_mutex_lock(philo->left_mutex);
      pthread_mutex_lock(philo->right_mutex);
    }
    philo->left_fork[0] = 0;
    philo->right_fork[0] = 0;
    pthread_mutex_unlock(philo->left_mutex);
    pthread_mutex_unlock(philo->right_mutex);
    
    philosopher_sleep(philo);
    return 1;
  }
  return 0;
  // Fork checks
}

/*Philosoper eating function. Here we retrieve the philo->last->meal
 * which then will be passed to the check death function.*/
void philosopher_eat(t_philo *philo)
{
  philo->last_meal = time_to_ms();
  if (!safe_print(philo, "is eating"))
    return;
  custom_sleep(philo->time_to_eat * 1000);
}

/*Philosopher will sleep for an amount of time after eating.*/

void philosopher_sleep(t_philo *philo)
{
  if (!safe_print(philo, "is sleeping"))
    return;
  custom_sleep(philo->time_to_sleep * 1000);
}

/*Philosopher will think and print a message. This time we will protect
 * the print message with a mutex, since this is gonna be inside the routine loop
 * and accessible by everyone.*/

void philosopher_think(t_philo *philo)
{
  if (philo->is_thinking == 0)
  {
    if (!safe_print(philo, "is thinking"))
      return;
    philo->is_thinking = 1;
  }
}

/*Custom time to sleep function. This is useful to let the philosophers
 * sleep for a certain amount of time, specified in the main args.*/

int custom_sleep(time_t time_to_sleep)
{
  time_t start = time_to_ms();
  while((time_to_ms() - start) < time_to_sleep)
    usleep(200);
  return 0;
}

int safe_print(t_philo *philo, char *to_print)
{
  pthread_mutex_lock(philo->table->death_mutex);
   if (philo->table->death_flag == 0)
    {
        printf("%li %i %s\n", time_to_ms() - philo->start_time, philo->id, to_print);
        pthread_mutex_unlock(philo->table->death_mutex);
        return 1;
    }
    pthread_mutex_unlock(philo->table->death_mutex);
    return 0;
}
