/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:20 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:21 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

static int	abort_init_mutexes(t_tableinfo *tableinfo, int i)
{
	while (1)
	{
		i--;
		if (i < 0)
			return (-1);
		pthread_mutex_destroy(tableinfo->fork_ids + i);
	}
}

int	init_mutexes(t_tableinfo *tableinfo)
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

int	init_tableinfo(t_tableinfo *tableinfo, t_philoinfo *philoinfos)
{
	int				i;
	struct timeval	t;

	if (init_mutexes(tableinfo))
		return (-1);
	gettimeofday(&t, NULL);
	tableinfo->t_start = t.tv_sec * 1000 + t.tv_usec / 1000;
	printf("Simulation start at %ld us\n", tableinfo->t_start);
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
