/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:06 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 12:16:40 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Define color codes
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

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	unsigned int		meals_eaten;
	time_t				start_time;
	time_t				last_meal;
	pthread_mutex_t		*left_mutex;
	pthread_mutex_t		*right_mutex;
	int					n_forks;
	int					*left_fork;
	int					*right_fork;
	t_table				*table;
	int					is_thinking;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
}						t_philo;

typedef struct s_table
{
	int					num_of_philos;
	t_philo				*philos;
	int					philos_full;
	unsigned int		meals_to_eat;
	pthread_mutex_t		*mutexes;
	pthread_mutex_t		*death_mutex;
	pthread_mutex_t		*meals_mutex;
	int					*forks;
	int					death_flag;
}						t_table;

t_philo					**create_philos(char **av);
t_table					*create_table(char **av, int ac);

int						safe_print(t_philo *philo, char *to_print);
void					philosopher_take_right(t_philo *philo);
void					philosopher_take_left(t_philo *philo);

int						philosopher_take_forks(t_philo *philo);
void					philosopher_eat(t_philo *philo);
void					philosopher_sleep(t_philo *philo);
void					philosopher_think(t_philo *philo);
int						custom_sleep(time_t time_to_sleep, t_philo *philo);
void					check_death(time_t last_meal_time, t_philo *philos);
void					assign_mutex_and_forks(t_philo *philo,
							pthread_mutex_t *mutex, int *forks, int philos_num);
int						is_input_valid(int ac, char **av);
int						ft_strcmp(char *s1, char *s2);

int						ft_is_digit(char c);
int						is_str_only_digits(char *str);
int						ft_atoi(char *str);
void					*routine(void *x);
int						create_threads(t_philo **philos, t_table *table);
time_t					time_to_ms(void);

void					clean_table(t_table *table);
void					clean_philos(t_philo **philos, char **av);

#endif // !PHILOSOPHERS_H
