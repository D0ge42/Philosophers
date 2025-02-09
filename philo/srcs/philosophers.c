#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>


void philo_initializer(t_philo **philos,int index, char **av,t_table *table);


/*Each philospher will get a pointer to its left and right fork.
 * This pointers are pointers to the forks array. 
 * We'll use philo->id to determine which forks philospher will be able
 * to access.*/

void assign_mutex_and_forks(t_philo *philo, pthread_mutex_t *mutex, int *forks, int philos_num)
{
  philo->left_mutex = &mutex[philo->id - 1];
  philo->right_mutex = &mutex[philo->id % philos_num];
  
  philo->left_fork = &forks[philo->id - 1];
  philo->right_fork = &forks[philo->id % philos_num];
}

t_table *create_table(char **av)
{
  t_table *table;
  table = malloc(sizeof(t_table));
  if (!table)
    return NULL;
  memset(table,0,sizeof(t_table));
  table->num_of_philos = ft_atoi(av[1]);
  table->mutexes = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
  if (!table->mutexes)
  {
    free(table);
    return NULL;
  }
  memset(table->mutexes,0,sizeof(pthread_mutex_t) * table->num_of_philos);
  table->forks = malloc(sizeof(int) * table->num_of_philos);
  if (!table->forks)
  {
    free(table->mutexes);
    free(table);
    return NULL;
  }
  memset(table->forks,0,sizeof(int) * table->num_of_philos);
  return table;
}

void free_previous_philos(t_philo **philos, int i)
{
  while(i)
  {
    free(philos[i]);
    i--;
  }
  free(philos);
  return;
}

void free_previous_mutexes(t_philo **philos, int i)
{
  while(i)
  {
    free(philos[i]->death_mutex);
    i--;
  }
  free(philos);
  return;
}

t_philo **create_philos(char **av)
{
  int philos_num = ft_atoi(av[1]);
  int i = 0;
  t_philo **philos = malloc(sizeof(t_philo *) * ft_atoi(av[1]));
  if (!philos)
    return NULL;
  memset(philos,0,sizeof(t_philo *) * ft_atoi(av[1]));
  while(i < philos_num)
  {
    philos[i] = malloc(sizeof(t_philo));
    if (!philos[i])
    {
      free_previous_philos(philos, i);
      return 0;
    }
    memset(philos[i],0,sizeof(t_philo));
    philos[i]->death_mutex = malloc(sizeof(pthread_mutex_t));
    if (!philos[i]->death_mutex)
    {
      free_previous_mutexes(philos, i);
      return 0;
    }
    i++;
  }
  return philos;
}

void assign_and_initialize(t_philo **philos,t_table *table, char **av)
{
  int i = 0;
  while(i < table->num_of_philos)
  {
    philo_initializer(philos,i,av,table);
    assign_mutex_and_forks(philos[i],table->mutexes,table->forks, ft_atoi(av[1]));
    i++;
  }
}

int main(int ac, char **av)
{
  if (ac == 1)
    return 0;
  t_philo **philos;
  t_table *table;
  if (!is_input_valid(ac,av))
    return 0;
  philos = create_philos(av);
  table = create_table(av);
  assign_and_initialize(philos,table,av);
  clean_table(table);
  create_threads(philos,table);
  clean_philos(philos, av);
}

/*Function used to initialize allocated values. I'll probably use memset later on*/

void philo_initializer(t_philo **philos,int index, char **av,t_table *table)
{
  pthread_mutex_init(&table->mutexes[index],NULL);
  pthread_mutex_init(philos[index]->death_mutex,NULL);
  philos[index]->start_time = time_to_ms();
  philos[index]->table = table;
  philos[index]->id = index + 1;
  philos[index]->meals_eaten = 0;
  philos[index]->last_meal = time_to_ms();
  philos[index]->time_to_die = ft_atoi(av[2]);
  philos[index]->time_to_eat = ft_atoi(av[3]);
  philos[index]->time_to_sleep = ft_atoi(av[4]);
}
