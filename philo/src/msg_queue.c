/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:41 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:42 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg_queue.h"
#include <stdlib.h>
#include <stdio.h>

t_msg_queue	*create_msg_queue(int cap)
{
	t_msg_queue	*queue;

	queue = malloc(sizeof(t_msg_queue));
	if (!queue)
		return (NULL);
	queue->cap = cap;
	queue->len = 0;
	queue->head = 0;
	queue->items = malloc(sizeof(t_msg) * cap);
	if (!queue->items)
	{
		free(queue);
		return (NULL);
	}
	if (pthread_mutex_init(&(queue->mutex), NULL))
	{
		free(queue->items);
		free(queue);
		return (NULL);
	}
	return (queue);
}

void	destroy_msg_queue(t_msg_queue *queue)
{
	pthread_mutex_destroy(&(queue->mutex));
	free(queue->items);
	free(queue);
}

int	push_msg_queue(t_msg_queue *queue, t_msg *p_msg)
{
	int	i;

	if (queue->len == queue->cap)
		return (CODE_ERROR_MSG_QUEUE_FULL);
	queue->len++;
	i = (queue->head + queue->len) % queue->cap;
	queue->items[i].t = p_msg->t;
	queue->items[i].i = p_msg->i;
	queue->items[i].content = p_msg->content;
	return (0);
}

int	pop_msg_queue(t_msg_queue *queue, t_msg *ret_msg)
{
	if (queue->len == 0)
		return (CODE_ERROR_MSG_QUEUE_EMPTY);
	queue->head = (queue->head + 1) % queue->cap;
	queue->len--;
	ret_msg->t = queue->items[queue->head].t;
	ret_msg->i = queue->items[queue->head].i;
	ret_msg->content = queue->items[queue->head].content;
	return (0);
}

void	flush_msg_queue(t_msg_queue *queue)
{
	t_msg	buf;

	pthread_mutex_lock(&(queue->mutex));
	while (queue->len > 0)
	{
		pop_msg_queue(queue, &buf);
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
	pthread_mutex_unlock(&(queue->mutex));
}
