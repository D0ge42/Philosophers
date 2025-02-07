#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#define PHILO_MAX 200
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_table t_table;

typedef struct s_philo
{
  pthread_t thread;
  unsigned int meals_eaten;
  unsigned int id;
  size_t start_time;
  time_t last_meal;
  pthread_mutex_t *left_mutex;
  pthread_mutex_t *right_mutex;
  int *left_fork;
  int *right_fork;
  t_table *table;
}   t_philo;

typedef struct s_table
{
  size_t time_to_die;
  size_t time_to_eat;
  size_t time_to_sleep;
  int num_of_philos;
  t_philo *philos;
  pthread_mutex_t *mutexes;
  int *forks;
  int death_flag;
} t_table;

void philosopher_take_forks(t_philo *philo);
void philosopher_eat(t_philo *philo);
void philosopher_sleep(t_philo *philo);
void philosopher_think(t_philo *philo);
int custom_sleep(time_t time_to_sleep);
void check_death(time_t last_meal_time,t_philo *philos);
void assign_mutex_and_forks(t_philo *philo, pthread_mutex_t *mutex, int *forks, int philos_num);
int is_input_valid(int ac, char **av);

int ft_is_digit(char c);
int is_str_only_digits(char *str);
int ft_atoi(char *str);
void *routine(void *x);
int create_threads(t_philo **philos, t_table *table);
time_t time_to_ms(void);

void clean_table(t_table *table);
void clean_philos(t_philo **philos, char **av);


#endif // !PHILOSOPHERS_H

