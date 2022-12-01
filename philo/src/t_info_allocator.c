/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_info_allocator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:50:57 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:04 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_info.h"
#include "msg_queue.h"
#include <stdlib.h>
#include <string.h>

int	free_table(t_table *table)
{
	int	i;

	if (table->philo_ids)
		free(table->philo_ids);
	if (table->philo_n_eats)
		free(table->philo_n_eats);
	if (table->philo_t_last_eat)
		free(table->philo_t_last_eat);
	if (table->fork_ids)
		free(table->fork_ids);
	if (table->fork_ids)
	{
		i = 0;
		while (i < table->n_philos)
		{
			pthread_mutex_destroy(table->fork_ids + i);
			i++;
		}
	}
	if (table->queue)
		destroy_msg_queue(table->queue);
	return (-1);
}

int	alloc_table(t_table *table)
{
	table->queue = create_msg_queue(table->n_philos * ((1 * 2 + 3) * 2));
	if (!table->queue)
		return (-1);
	table->philo_ids = malloc(sizeof(t_thread) * table->n_philos);
	table->philo_n_eats = malloc(sizeof(int) * table->n_philos);
	table->philo_t_last_eat = malloc(sizeof(time_t) * table->n_philos);
	table->fork_ids = malloc(sizeof(t_mutex) * table->n_philos);
	if (!(table->philo_ids && table->philo_n_eats
			&& table->fork_ids && table->philo_t_last_eat))
		return (free_table(table));
	memset(table->philo_ids, 0, sizeof(t_thread) * table->n_philos);
	memset(table->philo_n_eats, 0, sizeof(int) * table->n_philos);
	memset(table->philo_t_last_eat, 0, sizeof(time_t) * table->n_philos);
	memset(table->fork_ids, 0, sizeof(t_mutex) * table->n_philos);
	return (0);
}

int	alloc_philos(t_table *tableinfo, t_env *env, t_philo **philoinfos)
{
	int	i;
	int	n;

	n = tableinfo->n_philos;
	*philoinfos = malloc(sizeof(t_philo) * n);
	if (!(*philoinfos))
		return (-1);
	i = 0;
	while (i < n)
	{
		(*philoinfos)[i].table = tableinfo;
		(*philoinfos)[i].env = env;
		(*philoinfos)[i].i = i;
		(*philoinfos)[i].forks[0] = tableinfo->fork_ids + i;
		(*philoinfos)[i].forks[1] = tableinfo->fork_ids + ((i + 1) % n);
		i++;
	}
	return (0);
}

int	alloc_players(
	t_table *tableinfo,
	t_env *env,
	t_philo **philoinfos)
{
	if (alloc_table(tableinfo))
		return (-1);
	if (alloc_philos(tableinfo, env, philoinfos))
	{
		free_table(tableinfo);
		return (-1);
	}
	return (0);
}
