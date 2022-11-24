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
# include <pthread.h>

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
	pthread_mutex_t	mutex;
	int				cap;
	int				len;
	int				head;
	t_msg			*items;
}	t_msg_queue;

t_msg_queue	*create_msg_queue(int cap);
void		destroy_msg_queue(t_msg_queue *queue);
int			push_msg_queue(t_msg_queue *queue, t_msg *p_msg);
int			pop_msg_queue(t_msg_queue *queue, t_msg *ret_msg);
void		flush_msg_queue(t_msg_queue *queue);
#endif
