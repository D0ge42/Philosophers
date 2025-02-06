#include "philosophers.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

// Args
// Number of philosophers
// time_to_die (milliseconds)
// time to eat (in milliseconds)
// time to sleep (in milliseconds)
// number of time each philo must eat (optional argument)
// If each philosopher have eat least * the simulation stops.
// If not specified when one philo dies.
// Each philo is identified by a number from 1 to number of philo.
// Philosopher 1 sits next to philo max. Any other philosophers numbers
// sits between n-1 and n + 1.



/* LOGS: 
 * Timestamp_in ms X has taken a fork
 * Timestamp_in_ms X is eating
 * Timestamp_in_ms X is sleeping
 * Timestamp_in_ms X is thinking
 * Timestamp_in_ms X died
 * A message announcing  a philosophers died should be displayed
 * no more than 10 ms after the actual death.
 * philosophers should not die.*/

void philo_initializer(t_philo **philos,int index, char **av, t_table *table)
{
  philos[index]->table = table;
  philos[index]->id = index + 1;
  philos[index]->time_to_die = ft_atoi(av[2]);
  philos[index]->time_to_eat = ft_atoi(av[3]);
  philos[index]->time_to_sleep = ft_atoi(av[4]);
}

void initialize_everything(t_philo **philos, t_table *table)
{
  memset(philos, '\0', sizeof(t_philo*) * table->num_of_philos);
  memset(table, '\0', sizeof(t_table));
}

int main(int ac, char **av)
{
  (void)ac;
  t_table *table;
  table = malloc(sizeof(t_table));
  table->num_of_philos = ft_atoi(av[1]);
  int i = 0;
  table->num_of_philos = ft_atoi(av[1]);
  t_philo **philos = malloc(sizeof(t_philo *) * ft_atoi(av[1]));
  // initialize_everything(philos,table);
  while(i < ft_atoi(av[1]))
  {
    philos[i] = malloc(sizeof(t_philo));
    philo_initializer(philos,i,av,table);
    printf("Philosopher at index [%i] has id %i\n",i,philos[i]->id);
    i++;
  }
  create_threads(philos,table);
}
