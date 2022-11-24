/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_info.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:40 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:41 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INFO_H
# define T_INFO_H
# include "philo.h"
# include "msg_queue.h"
# include <pthread.h>

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_tableinfo
{
	int			n_philos;
	time_t		time_die;
	time_t		time_eat;
	time_t		time_slp;
	int			n_eats_until_done;
	t_thread	*philo_ids;
	int			*philo_n_eats;
	time_t		*philo_t_last_eat;
	t_mutex		*fork_ids;
	time_t		t_start;
	t_msg_queue	*queue;
}	t_tableinfo;

typedef struct s_philoinfo
{
	t_msg		buf;
	t_tableinfo	*tableinfo;
	int			i;
	t_mutex		*forks[2];
}	t_philoinfo;

int	free_tableinfo(t_tableinfo *tableinfo);
int	alloc_tableinfo(t_tableinfo *tableinfo);
int	alloc_philoinfos(t_philoinfo **philoinfos, t_tableinfo *tableinfo);
int	alloc_infos(t_tableinfo *tableinfo, t_philoinfo **philoinfos);
int	init_tableinfo(t_tableinfo *tableinfo, t_philoinfo *philoinfos);
#endif
