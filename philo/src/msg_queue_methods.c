/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue_methods.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:41 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:42 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg_queue.h"
#include <stdio.h>
#include <pthread.h>

static int	unlock_and_return(t_msg_queue *queue, int ret)
{
	pthread_mutex_unlock(&(queue->mutex));
	return (ret);
}

void	setstate_msg_queue(t_msg_queue *queue, int state)
{
	pthread_mutex_lock(&(queue->mutex));
	queue->enabled = state;
	pthread_mutex_unlock(&(queue->mutex));
}

int	push_msg_queue(t_msg_queue *queue, t_msg *p_msg)
{
	int	i;

	pthread_mutex_lock(&(queue->mutex));
	if (!queue->enabled)
		return (unlock_and_return(queue, 1));
	if (queue->len == queue->cap)
		return (unlock_and_return(queue, -1));
	queue->len++;
	i = (queue->head + queue->len) % queue->cap;
	queue->items[i].t = p_msg->t;
	queue->items[i].i = p_msg->i;
	queue->items[i].content = p_msg->content;
	return (unlock_and_return(queue, 0));
}

int	pop_msg_queue(t_msg_queue *queue, t_msg *ret_msg)
{
	pthread_mutex_lock(&(queue->mutex));
	if (!queue->enabled)
		return (unlock_and_return(queue, 1));
	if (!queue->enabled || queue->len == 0)
		return (unlock_and_return(queue, -1));
	queue->head = (queue->head + 1) % queue->cap;
	queue->len--;
	ret_msg->t = queue->items[queue->head].t;
	ret_msg->i = queue->items[queue->head].i;
	ret_msg->content = queue->items[queue->head].content;
	return (unlock_and_return(queue, 0));
}

void	flush_msg_queue(t_msg_queue *queue)
{
	int		ret;
	t_msg	buf;

	while (1)
	{
		ret = pop_msg_queue(queue, &buf);
		if (ret)
			return ;
		printf("%ld %d ", buf.t / 1000, buf.i);
		if (buf.content == FORKTAKEN)
			printf("has taken a fork\n");
		if (buf.content == EATING)
			printf("is eating\n");
		if (buf.content == SLEEPING)
			printf("is sleeping\n");
		if (buf.content == THINKING)
			printf("is thinking\n");
	}
}
