#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

void	initializer(t_philo **philos, int index, char **av, t_table *table);
t_table	*create_table(char **av, int ac);
void	free_previous_philos(t_philo **philos, int i);
t_philo	**create_philos(char **av);
void	assign_and_initialize(t_philo **philos, t_table *table, char **av);

int	main(int ac, char **av)
{
	t_philo	**philos;
	t_table	*table;

	if (ac == 1)
		return (0);
	if (!is_input_valid(ac, av))
		return (0);
	philos = create_philos(av);
	table = create_table(av, ac);
	assign_and_initialize(philos, table, av);
	create_threads(philos, table);
	clean_table(table);
	clean_philos(philos, av);
}

/*Each philospher will get a pointer to its left and right fork.
 * This pointers are pointers to the forks array.
 * We'll use philo->id to determine which forks philospher will be able
 * to access.*/

void	assign_mutex_and_forks(t_philo *philo, pthread_mutex_t *mutex,
		int *forks, int philos_num)
{
	philo->left_mutex = &mutex[philo->id - 1];
	philo->right_mutex = &mutex[philo->id % philos_num];
	philo->left_fork = &forks[philo->id - 1];
	philo->right_fork = &forks[philo->id % philos_num];
}

void	assign_and_initialize(t_philo **philos, t_table *table, char **av)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		initializer(philos, i, av, table);
		assign_mutex_and_forks(philos[i], table->mutexes, table->forks,
			ft_atoi(av[1]));
		i++;
	}
}

/*Function to initialize different values and mutexes*/

void	initializer(t_philo **philos, int index, char **av, t_table *table)
{
	pthread_mutex_init(&table->mutexes[index], NULL);
	pthread_mutex_init(table->death_mutex, NULL);
	philos[index]->is_thinking = 0;
	philos[index]->start_time = time_to_ms();
	philos[index]->table = table;
	philos[index]->id = index + 1;
	philos[index]->meals_eaten = 0;
	philos[index]->last_meal = time_to_ms();
	philos[index]->time_to_die = ft_atoi(av[2]);
	philos[index]->time_to_eat = ft_atoi(av[3]);
	philos[index]->time_to_sleep = ft_atoi(av[4]);
	philos[index]->n_forks = 0;
}
