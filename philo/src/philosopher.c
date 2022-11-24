/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:22 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:23 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "timetools.h"
#include "error_handler.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void	philo_push_msg(t_philoinfo *info, int msg)
{
	(info->buf).t = get_t_simulation(info->tableinfo);
	(info->buf).content = msg;
	pthread_mutex_lock(&(info->tableinfo->queue->mutex));
	if (push_msg_queue(info->tableinfo->queue, &(info->buf)))
		exit(handle_error("Message queue full."));
	pthread_mutex_unlock(&(info->tableinfo->queue->mutex));
}

// strategy suitable for odd number of philos
// each philo will add a small delay every Nth cycle of their lives.
// philo n will start adding their delay from nth cycle.
// every philo will pick their forks from left to right.
// if counter is at 0, add delay.
// else if counter is even, sleep.
// else, eat.
void	philo_strategy_odd(t_philoinfo *info)
{
	int	counter;

	counter = info->i;
	while (1)
	{
		if (counter == 0)
			ft_usleep(T_INITIAL_DELAY);
		else if (counter % 2)
		{
			philo_think(info);
			philo_eat(info);
		}
		else
			philo_sleep(info);
		counter = (counter + 1) % info->tableinfo->n_philos;
	}
}

// strategy suitable for even number of philos
// philo with n % 2 == 1 will think, eat and sleep.
// philo with n % 2 == 0 will sleep, think and eat.
void	philo_strategy_even(t_philoinfo *info)
{
	if (info->i % 2)
	{
		while (1)
		{
			philo_think(info);
			philo_eat(info);
			philo_sleep(info);
		}
	}
	else
	{
		while (1)
		{
			philo_sleep(info);
			philo_think(info);
			philo_eat(info);
		}
	}
}

void	*philo_start_routine(void *arg)
{
	t_philoinfo		*info;

	info = arg;
	(info->buf).i = info->i + 1;
	pthread_detach((info->tableinfo->philo_ids)[info->i]);
	if (info->tableinfo->n_philos % 2 == 0)
		philo_strategy_even(info);
	else
		philo_strategy_odd(info);
	return (NULL);
}
