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

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

# define PHILO_MAX 200
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define FORKS "/forks"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	unsigned int		meals_eaten;
	time_t				last_meal;
	t_table				*table;
	int					is_thinking;
	char				sem_name[50];
	char				sem_meal_name[50];
	sem_t				*semaphore;
	sem_t				*sem_meal;
	sem_t				*death_sem;
	pthread_t			monitor;
	sem_t				*forks;
	sem_t				*printblock;
	int					pid;
	sem_t				*print_block;
}						t_philo;

typedef struct s_table
{
	char				*semaphore_array;
	int					num_of_philos;
	t_philo				*philos;
	int					philos_full;
	unsigned int		meals_to_eat;
	int					*forks;
	int					death_flag;
	sem_t				*death_sem;
	time_t				start_time;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					everyone_ate;
}						t_table;

int						safe_print(t_philo *philo, char *to_print);
int						is_input_valid(int ac, char **av);
int						ft_strcmp(char *s1, char *s2);

void					monitor(t_philo *philo, sem_t *forks,
							sem_t *print_block);
void					*routine(void *ptr);
void					philosopher_eat(t_philo *philo);
void					philosopher_think(t_philo *philo);
void					philosopher_sleep(t_philo *philo);
void					philosopher_took_fork(t_philo *philo);
void					philosopher_drop_fork(t_philo *philo);
int						custom_sleep(time_t time_to_sleep, t_philo *philo);
void					create_philos(char **av, t_philo *philos);
void					create_table(char **av, int ac, t_table *table);
void					table_initializer(t_table *table, char **av, int ac);
char					*ft_itoa(int n);
char					*ft_strjoin(char const *s1, char const *s2);
int						check_death(time_t last_meal_time, t_philo *philos);

void					clean_processes(pid_t **processes, int num_of_philos);

int						ft_is_digit(char c);
int						is_str_only_digits(char *str);
int						ft_atoi(char *str);
time_t					time_to_ms(void);

#endif
