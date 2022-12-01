/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_info_initializer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:20 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:21 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_info.h"
#include "philo.h"
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

static int	abort_init_mutexes(t_table *tableinfo, int i)
{
	while (1)
	{
		i--;
		if (i < 0)
			return (-1);
		pthread_mutex_destroy(tableinfo->fork_ids + i);
	}
}

int	init_mutexes(t_table *tableinfo)
{
	int	i;

	i = 0;
	while (i < tableinfo->n_philos)
	{
		if (pthread_mutex_init(tableinfo->fork_ids + i, NULL))
			return (abort_init_mutexes(tableinfo, i));
		i++;
	}
	return (0);
}

int	init_simulation(
	t_table *tableinfo,
	t_env *env,
	t_philo *philoinfos)
{
	int				i;
	struct timeval	t;

	if (init_mutexes(tableinfo))
		return (-1);
	gettimeofday(&t, NULL);
	env->t_start = t.tv_sec * 1000000 + t.tv_usec;
	i = 0;
	while (i < tableinfo->n_philos)
	{
		if (pthread_create(
				tableinfo->philo_ids + i,
				NULL,
				philo_start_routine,
				philoinfos + i))
			return (-1);
		i++;
	}
	return (0);
}
