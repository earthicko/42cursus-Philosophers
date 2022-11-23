/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:57:32 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/23 14:57:32 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg_queue.h"
#include <stdio.h>
#include <unistd.h>

void	flush_msg_queue(t_msg_queue *queue)
{
	t_msg	buf;

	while (queue->len > 0)
	{
		pop_msg_queue(queue, &buf);
		printf("%ld %d ", buf.t_ms, buf.i);
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
