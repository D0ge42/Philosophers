#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>


void clean_table(t_table *table)
{
  free(table->forks);
  int i = 0;
  int num_of_philos = table->num_of_philos;
  while(i < num_of_philos)
  {
    if(pthread_mutex_destroy(&table->mutexes[i]))
    {
      printf("Error in destroying mutex\n");
      return ;
    }
    i++;
  }
  free(table->mutexes);
  free(table->death_mutex);
  free(table);
}

void clean_philos(t_philo **philos, char **av)
{
  int i = 0;
  int num_of_philos  = ft_atoi(av[1]); 
  while(i < num_of_philos)
  {
    free(philos[i]);
    i++;
  }
  free(philos);
}
