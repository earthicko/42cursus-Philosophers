/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:50:57 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:04 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

int	free_tableinfo(t_tableinfo *tableinfo)
{
	if (tableinfo->philo_ids)
		free(tableinfo->philo_ids);
	if (tableinfo->philo_n_eats)
		free(tableinfo->philo_n_eats);
	if (tableinfo->philo_t_last_eat)
		free(tableinfo->philo_t_last_eat);
	if (tableinfo->fork_ids)
		free(tableinfo->fork_ids);
	if (tableinfo->queue)
		destroy_msg_queue(tableinfo->queue);
	return (-1);
}

int	alloc_tableinfo(t_tableinfo *tinfo)
{
	tinfo->queue = create_msg_queue(tinfo->n_philos * 2);
	if (!tinfo->queue)
		return (-1);
	tinfo->philo_ids = malloc(sizeof(t_thread) * tinfo->n_philos);
	tinfo->philo_n_eats = malloc(sizeof(int) * tinfo->n_philos);
	tinfo->philo_t_last_eat = malloc(sizeof(time_t) * tinfo->n_philos);
	tinfo->fork_ids = malloc(sizeof(t_mutex) * tinfo->n_philos);
	if (!(tinfo->philo_ids && tinfo->philo_n_eats
			&& tinfo->fork_ids && tinfo->philo_t_last_eat))
		return (free_tableinfo(tinfo));
	memset(tinfo->philo_ids, 0, sizeof(t_thread) * tinfo->n_philos);
	memset(tinfo->philo_n_eats, 0, sizeof(int) * tinfo->n_philos);
	memset(tinfo->philo_t_last_eat, 0, sizeof(time_t) * tinfo->n_philos);
	memset(tinfo->fork_ids, 0, sizeof(t_mutex) * tinfo->n_philos);
	return (0);
}

int	alloc_philoinfos(t_philoinfo **philoinfos, t_tableinfo *tableinfo)
{
	int	i;
	int	n;

	n = tableinfo->n_philos;
	*philoinfos = malloc(sizeof(t_philoinfo) * n);
	if (!(*philoinfos))
		return (-1);
	i = 0;
	while (i < n)
	{
		(*philoinfos)[i].tableinfo = tableinfo;
		(*philoinfos)[i].i = i;
		(*philoinfos)[i].forks[0] = tableinfo->fork_ids + i;
		(*philoinfos)[i].forks[1] = tableinfo->fork_ids + ((i + 1) % n);
		i++;
	}
	return (0);
}

int	alloc_infos(t_tableinfo *tableinfo, t_philoinfo **philoinfos)
{
	if (alloc_tableinfo(tableinfo))
		return (-1);
	if (alloc_philoinfos(philoinfos, tableinfo))
	{
		free_tableinfo(tableinfo);
		return (-1);
	}
	return (0);
}
