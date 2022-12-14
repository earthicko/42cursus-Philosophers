/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_supervisor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:20 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:21 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "timetools.h"
#include <unistd.h>
#include <stdio.h>

int	check_if_all_eat(t_table *table, t_env *env)
{
	int	i;
	int	n_eat;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_lock(table->lock_infos + i);
		n_eat = (table->philo_n_eats)[i];
		pthread_mutex_unlock(table->lock_infos + i);
		if (n_eat < env->n_eats_until_done)
			return (0);
		i++;
	}
	return (1);
}

int	check_if_dead(t_table *table, t_env *env)
{
	int		i;
	time_t	death_us;
	time_t	now_us;
	time_t	elapsed_ms;
	time_t	last_eat;

	i = 0;
	while (i < table->n_philos)
	{
		now_us = get_t_simulation(env);
		pthread_mutex_lock(table->lock_infos + i);
		last_eat = (table->philo_t_last_eat)[i];
		pthread_mutex_unlock(table->lock_infos + i);
		elapsed_ms = (now_us - last_eat) / 1000;
		if (elapsed_ms * 1000 > env->time_die)
		{
			death_us = last_eat + env->time_die;
			printf("%ld %d died\n", death_us / 1000, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	wait_for_all_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_lock(table->lock_infos + i);
		(table->terminate)[i] = 1;
		pthread_mutex_unlock(table->lock_infos + i);
		i++;
	}
	i = 0;
	while (i < table->n_philos)
	{
		pthread_join((table->philo_ids)[i], NULL);
		i++;
	}
}
