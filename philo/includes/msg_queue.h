/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:41 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:42 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_QUEUE_H
# define MSG_QUEUE_H
# include <sys/time.h>
# define CODE_ERROR_MSG_QUEUE_FULL -1
# define CODE_ERROR_MSG_QUEUE_EMPTY -2

enum e_content
{
	FORKTAKEN = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_msg
{
	time_t	t;
	int		i;
	int		content;
}	t_msg;

typedef struct s_msg_queue
{
	int		cap;
	int		len;
	int		head;
	t_msg	*items;
}	t_msg_queue;
#endif
