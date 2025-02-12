/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:21:32 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/12 15:18:02 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdlib.h>

pid_t	**create_processes(pid_t **philos, int num_philos);
void init_processes(pid_t **philos, int num_philos);

// Semaphore starting value will be n_fork.
// Every process will be able to access semaphore
// trough semaphore name.
// Forks are in the middle so every philo will access 2 forks
// whenver semaphore will allow them to.
// if a philosophers dies we can exit ?
//

int	main(int ac, char **av)
{
	sem_t	*semaphore;
	pid_t	**philos = NULL;
	int		num_philos;

	if (ac == 1)
		return (0);
	if (!is_input_valid(ac, av))
	{
		return (0);
	}
	num_philos = ft_atoi(av[1]);
	sem_open(SEMAPHORE, O_CREAT, 0644, num_philos);
	philos = create_processes(philos, num_philos);
	init_processes(philos, num_philos);
}

pid_t	**create_processes(pid_t **philos, int num_philos)
{
	int	i;
	i = 0;
	philos = malloc(sizeof(pid_t *) * num_philos);
	while (i < num_philos)
	{
		philos[i] = malloc(sizeof(pid_t));
		i++;
	}
	return (philos);
}

void init_processes(pid_t **philos, int num_philos)
{
	int i = 0;
	i = 0;
	while (i < num_philos)
	{
		*philos[i] = fork();
		if (*philos[i] == -1)
		{
			return ;
			// Free previously allocated processes
			//Exit 
		}
		else if (*philos[i] == 0)
		{
			printf("%i\n",i);
			exit(0);
			//Child process
			//Execute routine for each process at index [i];
		}
		i++;
	}
	i = 0;
	while(i < num_philos)
	{
		waitpid(*philos[i],NULL,WNOHANG);
		i++;
	}
}
