/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:41 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:42 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg_queue.h"
#include <stdlib.h>
#include <pthread.h>

t_msg_queue	*create_msg_queue(int cap)
{
	t_msg_queue	*queue;

	queue = malloc(sizeof(t_msg_queue));
	if (!queue)
		return (NULL);
	queue->cap = cap;
	queue->len = 0;
	queue->head = 0;
	queue->enabled = 1;
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
