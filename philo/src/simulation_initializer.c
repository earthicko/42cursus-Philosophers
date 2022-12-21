/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_initializer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:20 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:21 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "philo.h"
#include <pthread.h>
#include <sys/time.h>

static int	abort_init_mutexes(t_table *table)
{
	destroy_mutexes(table->fork_ids, table->n_philos);
	destroy_mutexes(table->lock_infos, table->n_philos);
	return (-1);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_mutex_init(table->fork_ids + i, NULL))
			return (abort_init_mutexes(table));
		if (pthread_mutex_init(table->lock_infos + i, NULL))
			return (abort_init_mutexes(table));
		i++;
	}
	return (0);
}

int	init_simulation(t_table *table, t_env *env, t_philo *philos)
{
	int				i;
	struct timeval	t;

	if (init_mutexes(table))
		return (-1);
	gettimeofday(&t, NULL);
	env->t_start = t.tv_sec * 1000000 + t.tv_usec;
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_create(
				table->philo_ids + i,
				NULL,
				philo_start_routine,
				philos + i))
			return (-1);
		i++;
	}
	return (0);
}
