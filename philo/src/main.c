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

#include "philo.h"
#include "error_handler.h"
#include "parser.h"
#include "allocator.h"
#include "initializer.h"
#include "msg_printer.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	check_if_all_eat(t_tableinfo *tableinfo)
{
	int	i;

	i = 0;
	while (i < tableinfo->n_philos)
	{
		if ((tableinfo->philo_n_eats)[i] < tableinfo->n_eats_until_done)
			return (0);
		i++;
	}
	return (1);
}

int	check_if_dead(t_tableinfo *tableinfo)
{
	int		i;
	time_t	time_starve;
	time_t	time_now;

	time_now = get_t_simulation(tableinfo);
	i = 0;
	while (i < tableinfo->n_philos)
	{
		time_starve = time_now - (tableinfo->philo_t_last_eat)[i];
		if (time_starve > tableinfo->time_die)
		{
			printf("%ld %d died\n", time_starve, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	loop_until_done(t_tableinfo *tableinfo)
{
	while (1)
	{
		if (tableinfo->n_eats_until_done >= 0 && check_if_all_eat(tableinfo))
		{
			printf("All philosophers have eat %d times. Stopping Simulation.\n",
				tableinfo->n_eats_until_done);
			return (0);
		}
		if (check_if_dead(tableinfo))
			return (0);
		flush_msg_queue(tableinfo->queue);
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	t_tableinfo	tableinfo;
	t_philoinfo	*philoinfos;

	if (argc == 1)
		return (print_usage());
	if (!(argc == 5 || argc == 6))
		return (handle_error("Invalid number of arguments."));
	if (parse_args(argc, argv, &tableinfo))
		return (handle_error("Error while parsing arguments."));
	if (alloc_infos(&tableinfo, &philoinfos))
		return (handle_error("Error while allocating resources."));
	if (init_tableinfo(&tableinfo, philoinfos))
	{
		free_tableinfo(&tableinfo);
		free(philoinfos);
		return (handle_error("Error while initializing threads or mutexes."));
	}
	return (loop_until_done(&tableinfo));
}
