#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/*Function will take start time and check when its time to stop sleeping*/

void *routine(void *pointer)
{
  t_philo *philo = (t_philo *)pointer;
  while(philo->table->death_flag == 0)
  {
    philosopher_take_forks(philo);
    philosopher_think(philo);
  }
  return 0;
}

/*With this function we'll make a mutex protected check.
 * That means that we'll use a mutex to check and set the forks
 * for the philosophers.
 * Once forks are set we'll decide if we can eat or not.*/

void philosopher_take_forks(t_philo *philo)
{
  int both_forks_available = 0;

  pthread_mutex_lock(philo->left_mutex);
  pthread_mutex_lock(philo->right_mutex);

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
    printf("Philo takes right fork\n");
    printf("Philo takes left fork\n");
    philosopher_eat(philo);
    pthread_mutex_lock(philo->left_mutex);
    pthread_mutex_lock(philo->right_mutex);
    philo->left_fork[0] = 0;
    philo->right_fork[0] = 0;
    pthread_mutex_unlock(philo->left_mutex);
    pthread_mutex_unlock(philo->right_mutex);
    philosopher_sleep(philo);
  }
  // Fork checks
}

/*Philosoper eating function. Here we retrieve the philo->last->meal
 * which then will be passed to the check death function.*/
void philosopher_eat(t_philo *philo)
{
  philo->last_meal = time_to_ms();
  printf("%i is eating\n",philo->id);
  custom_sleep(philo->table->time_to_eat);
}

/*Philosopher will sleep for an amount of time after eating.*/

void philosopher_sleep(t_philo *philo)
{
  check_death(philo->last_meal, philo);
  printf("%i is sleeping\n",philo->id);
  custom_sleep(philo->table->time_to_sleep);
}

/*Philosopher will think and print a message. This time we will protect
 * the print message with a mutex, since this is gonna be inside the routine loop
 * and accessible by everyone.*/

void philosopher_think(t_philo *philo)
{

  check_death(philo->last_meal,philo);
  // pthread_mutex_lock(philo->mutex);
  printf("%i is thinking\n",philo->id);
  // pthread_mutex_unlock(philo->mutex);
}

/*Custom time to sleep function. This is useful to let the philosophers
 * sleep for a certain amount of time, specified in the main args.*/

int custom_sleep(time_t time_to_sleep)
{
  time_t start = time_to_ms();
  while((time_to_ms() - start) > time_to_sleep)
    usleep(200);
  return 0;
}
