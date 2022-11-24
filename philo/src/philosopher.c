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
#include "error_handler.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

time_t	get_t_simulation(t_tableinfo *info)
{
	struct timeval	t;
	time_t			temp;

	gettimeofday(&t, NULL);
	temp = t.tv_sec * 1000000;
	temp += t.tv_usec;
	temp -= info->t_start;
	return (temp);
}

void	philo_push_msg(t_philoinfo *info, int msg)
{
	(info->buf).t = get_t_simulation(info->tableinfo);
	(info->buf).content = msg;
	pthread_mutex_lock(&(info->tableinfo->queue->mutex));
	if (push_msg_queue(info->tableinfo->queue, &(info->buf)))
		exit(handle_error("Message queue full."));
	pthread_mutex_unlock(&(info->tableinfo->queue->mutex));
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
		philo_strategy_even(info);
	return (NULL);
}
