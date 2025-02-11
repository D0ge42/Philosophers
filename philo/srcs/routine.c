#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>

/*Function will take start time and check when its time to stop sleeping*/
int		safe_print(t_philo *philo, char *to_print);
void	philosopher_take_right(t_philo *philo);
void	philosopher_take_left(t_philo *philo);

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		check_death(philo->last_meal, philo);
		if (philo->is_thinking == 0 && philo->n_forks == 0)
			philosopher_think(philo);
		if (philo->table->death_flag)
			break ;
		if (philo->id % 2 == 0)
		{
			philosopher_take_right(philo);
			if (philo->n_forks == 1)
				philosopher_take_left(philo);
		}
		else
		{
			philosopher_take_left(philo);
			if (philo->n_forks == 1)
				philosopher_take_right(philo);
		}
		if (philo->n_forks == 2)
		{
			philosopher_eat(philo);
			if (philo->meals_eaten == philo->table->meals_to_eat)
				break ;
			philosopher_sleep(philo);
		}
	}
	return (0);
}

void	philosopher_take_left(t_philo *philo)
{
	pthread_mutex_lock(philo->left_mutex);
	if (philo->left_fork[0] == -1 || philo->left_fork[0] == philo->id)
	{
		pthread_mutex_unlock(philo->left_mutex);
		return ;
	}
	philo->left_fork[0] = -1;
	safe_print(philo, "has taken a fork");
	philo->n_forks++;
	pthread_mutex_unlock(philo->left_mutex);
}

void	philosopher_take_right(t_philo *philo)
{
	pthread_mutex_lock(philo->right_mutex);
	if (philo->right_fork[0] == -1 || philo->right_fork[0] == philo->id)
	{
		pthread_mutex_unlock(philo->right_mutex);
		return ;
	}
	philo->right_fork[0] = -1;
	safe_print(philo, "has taken a fork");
	philo->n_forks++;
	pthread_mutex_unlock(philo->right_mutex);
}

/*Philosoper eating function. Here we retrieve the philo->last->meal
 * which then will be passed to the check death function.*/
void	philosopher_eat(t_philo *philo)
{
	philo->last_meal = time_to_ms();
	philo->is_thinking = 0;
	if (!safe_print(philo, "is eating"))
		return ;
	if (custom_sleep(philo->time_to_eat, philo))
	{
		return ;
	}
	philo->meals_eaten++;
	philo->n_forks = 0;
	pthread_mutex_lock(philo->right_mutex);
	philo->right_fork[0] = philo->id;
	pthread_mutex_unlock(philo->right_mutex);
	pthread_mutex_lock(philo->left_mutex);
	philo->left_fork[0] = philo->id;
	pthread_mutex_unlock(philo->left_mutex);
}

/*Philosopher will sleep for an amount of time after eating.*/

void	philosopher_sleep(t_philo *philo)
{
	if (!safe_print(philo, "is sleeping"))
		return ;
	if (custom_sleep(philo->time_to_sleep, philo))
		return ;
	philo->n_forks = 0;
}

/*Philosopher will think and print a message. This time we will protect
 * the print message with a mutex,
	since this is gonna be inside the routine loop
 * and accessible by everyone.*/

void	philosopher_think(t_philo *philo)
{
	time_t	think_time;

	think_time = 0;
	if (philo->is_thinking == 0)
	{
		if (!safe_print(philo, "is thinking"))
			return ;
		custom_sleep(think_time, philo);
		philo->is_thinking = 1;
	}
}

