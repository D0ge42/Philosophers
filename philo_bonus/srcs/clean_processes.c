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
#include <sched.h>

pid_t	**create_processes(pid_t **philos, int num_philos);

// Semaphore starting value will be n_fork.
// Every process will be able to access semaphore
// trough semaphore name.
// Forks are in the middle so every philo will access 2 forks
// whenver semaphore will allow them to.
// if a philosophers dies we can exit ?
//

void clean_processes(pid_t **philos, int num_philos)
{
	int i  = 0;
	while(i < num_philos)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

