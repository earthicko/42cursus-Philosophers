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

void	*start_routine(void *arg)
{
	return (arg);
}

int	init_tableinfo(t_tableinfo *tableinfo, t_philoinfo *philoinfos)
{
	int	i;

	if (init_mutexes(tableinfo))
		return (-1);
	i = 0;
	while (i < tableinfo->n_philos)
	{
		if (pthread_create(
				tableinfo->philo_ids + i,
				NULL,
				start_routine,
				philoinfos + i))
			return (-1);
		i++;
	}
	return (0);
}
