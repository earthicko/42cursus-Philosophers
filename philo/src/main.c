/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:22 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:23 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "philo.h"
#include "timetools.h"
#include "error_handler.h"
#include "parser.h"
#include "msg_queue.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	handle_error(char *error_msg)
{
	printf("%s\n", error_msg);
	return (1);
}

int	check_if_all_eat(t_table *table, t_env *env)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if ((table->philo_n_eats)[i] < env->n_eats_until_done)
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

	i = 0;
	while (i < table->n_philos)
	{
		now_us = get_t_simulation(env);
		elapsed_ms = (now_us - (table->philo_t_last_eat)[i]) / 1000;
		if (elapsed_ms * 1000 > env->time_die)
		{
			death_us = (table->philo_t_last_eat)[i] + env->time_die;
			printf("%ld %d died\n", death_us / 1000, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	loop_until_done(t_table *table, t_env *env)
{
	while (1)
	{
		flush_msg_queue(table->queue);
		if (check_if_dead(table, env))
			return ;
		if (env->n_eats_until_done >= 0 && check_if_all_eat(table, env))
			return ;
	}
}

int	main(int argc, char **argv)
{
	t_env	env;
	t_table	table;
	t_philo	*philos;

	if (!(argc == 5 || argc == 6))
		return (handle_error("Invalid number of arguments."));
	if (parse_args(argc, argv, &env, &table))
		return (handle_error("Error while parsing arguments."));
	if (alloc_players(&table, &env, &philos))
		return (handle_error("Error while allocating resources."));
	if (init_simulation(&table, &env, philos))
	{
		free_table(&table);
		free(philos);
		return (handle_error("Error while initializing threads or mutexes."));
	}
	loop_until_done(&table, &env);
	free_table(&table);
	free(philos);
	return (0);
}
