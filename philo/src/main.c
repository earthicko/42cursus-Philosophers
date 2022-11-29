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

#include "t_info.h"
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
	time_t	death_us;
	time_t	now_us;
	time_t	elapsed_ms;

	i = 0;
	while (i < tableinfo->n_philos)
	{
		now_us = get_t_simulation(tableinfo);
		elapsed_ms = (now_us - (tableinfo->philo_t_last_eat)[i]) / 1000;
		if (elapsed_ms * 1000 > tableinfo->time_die)
		{
			death_us = (tableinfo->philo_t_last_eat)[i] + tableinfo->time_die;
			printf("%ld %d died\n", death_us / 1000, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	loop_until_done(t_tableinfo *tableinfo)
{
	while (1)
	{
		flush_msg_queue(tableinfo->queue);
		if (check_if_dead(tableinfo))
			return ;
		if (tableinfo->n_eats_until_done >= 0 && check_if_all_eat(tableinfo))
			return ;
	}
}

int	main(int argc, char **argv)
{
	t_tableinfo	tableinfo;
	t_philoinfo	*philoinfos;

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
	loop_until_done(&tableinfo);
	free_tableinfo(&tableinfo);
	free(philoinfos);
	return (0);
}
