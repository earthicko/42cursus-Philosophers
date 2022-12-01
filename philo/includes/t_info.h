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
# include "msg_queue.h"
# include <sys/time.h>
# include <pthread.h>

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_env
{
	time_t	time_die;
	time_t	time_eat;
	time_t	time_slp;
	time_t	t_start;
	int		n_eats_until_done;
}	t_env;

typedef struct s_table
{
	int			n_philos;
	t_thread	*philo_ids;
	int			*philo_n_eats;
	time_t		*philo_t_last_eat;
	t_mutex		*fork_ids;
	t_msg_queue	*queue;
}	t_table;

typedef struct s_philo
{
	t_msg	buf;
	t_table	*table;
	t_env	*env;
	int		i;
	t_mutex	*forks[2];
}	t_philo;

int	free_table(t_table *table);
int	alloc_table(t_table *table);
int	alloc_philos(t_table *table, t_env *env, t_philo **philos);
int	alloc_players(t_table *table, t_env *env, t_philo **philos);
int	init_simulation(t_table *table, t_env *env, t_philo *philos);
#endif
