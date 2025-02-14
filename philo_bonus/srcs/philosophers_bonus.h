/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:06 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 10:21:07 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H



// Define color codes
#include <sched.h>
# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

# define PHILO_MAX 200
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>


#define FORKS "/forks"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	unsigned int		meals_eaten;
	time_t				last_meal;
	t_table				*table;
	int					is_thinking;
	char 				*sem_name;
	sem_t				*semaphore;
	pthread_t			monitor;
	int					pid;
	sem_t				*print_block;
}						t_philo;

typedef struct s_table
{
	char 				*semaphore_array;
	int					num_of_philos;
	t_philo				*philos;
	int					philos_full;
	unsigned int		meals_to_eat;
	int					*forks;
	int					death_flag;
	time_t				start_time;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
}						t_table;

int						safe_print(t_philo *philo, char *to_print);
int						is_input_valid(int ac, char **av);
int						ft_strcmp(char *s1, char *s2);

void routine(t_philo *philo, sem_t *forks);
void philosopher_eat(t_philo *philo);
void philosopher_think(t_philo *philo);
void philosopher_sleep(t_philo *philo);
void philosopher_took_fork(t_philo *philo);
void philosopher_drop_fork(t_philo *philo);
int	custom_sleep(time_t time_to_sleep, t_philo *philo);
t_philo	**create_philos(char **av);
t_table	*create_table(char **av, int ac);
void table_initializer(t_table *table, char **av, int ac);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int	check_death(time_t last_meal_time, t_philo *philos);


void	clean_processes(pid_t **processes,int num_of_philos);

int						ft_is_digit(char c);
int						is_str_only_digits(char *str);
int						ft_atoi(char *str);
time_t					time_to_ms(void);


#endif // !PHILOSOPHERS_H
