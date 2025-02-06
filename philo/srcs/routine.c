#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


/*Function will take start time and check when its time to stop sleeping*/

int custom_sleep(time_t time_to_sleep)
{
  time_t start = time_to_ms();
  while((time_to_ms() - start) > time_to_sleep)
    usleep(200);
  return 0;
}

/*Function will temporary lock with a mutex and access the value of fork
 * at index +1 and index -1 of philosopher with current id.
 * If forks are free philosopher will take them and start eating*/

void philosopher_take_forks(t_philo *philo)
{
  if (philo->right_fork[0] == 0 && philo->left_fork[0] == 0)
  {
    printf("Forks are available\n");
    philo->right_fork[0] = 1;
    philo->left_fork[0] = 1;
  }
  else if (philo->right_fork[0] == 1 && philo->left_fork[0] == 1)
    printf("Forks are not available\n");
}

void philosopher_eat(t_philo *philo)
{
  time_t last_meal_time = time_to_ms();
  check_death(last_meal_time,philo);
  printf("%i is eating\n",philo->id);
  custom_sleep(philo->time_to_eat);
}

void philosopher_sleep(t_philo *philo)
{
  printf("%i is sleeping\n",philo->id);
  custom_sleep(philo->time_to_sleep);
}

void philosopher_think(t_philo *philo)
{
  printf("%i is thinking\n",philo->id);
}

