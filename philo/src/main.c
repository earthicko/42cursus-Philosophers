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

void	loop_until_done(t_table *table, t_env *env)
{
	while (1)
	{
		flush_msg_queue(table->queue);
		if (check_if_dead(table, env))
			break ;
		if (env->n_eats_until_done >= 0 && check_if_all_eat(table, env))
			break ;
	}
	setstate_msg_queue(table->queue, 0);
	if (table->n_philos > 1)
		wait_for_all_philos(table);
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
