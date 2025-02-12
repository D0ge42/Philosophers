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
#define SEMAPHORE "/semaphore"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	unsigned int		meals_eaten;
	time_t				start_time;
	time_t				last_meal;
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
  int					*forks;
	int					death_flag;
}						t_table;

int						safe_print(t_philo *philo, char *to_print);
int						is_input_valid(int ac, char **av);
int						ft_strcmp(char *s1, char *s2);

int						ft_is_digit(char c);
int						is_str_only_digits(char *str);
int						ft_atoi(char *str);
time_t					time_to_ms(void);


#endif // !PHILOSOPHERS_H
