#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>

void	is_even_or_odd(t_philo *philo);
/*Philosophers routine.
 * Check death at the start.
 * Let philosophers thinks
 * break whenever a philosopher dies.
 * If philo id is even they'll first try to take right fork, then left one.
 * Else the opposite
 * If a philosopher has 2 forks it can eat.
 * After eating we'll check if number of meals_eat is == meals_to_eat
 * If yes, we break, else philosoper can sleep and we repeat the loop.*/

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
		is_even_or_odd(philo);
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

void	is_even_or_odd(t_philo *philo)
{
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
}
