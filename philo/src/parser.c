/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:24 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:25 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_info.h"
#include "ft_atoi.h"
#include <string.h>
#include <stdio.h>

static int	parse_times(int argc, char **argv, t_env *env)
{
	int	buffer;

	if (ft_atoi_if_valid(argv[2], &buffer) || buffer < 0)
		return (-1);
	env->time_die = buffer * 1000;
	if (ft_atoi_if_valid(argv[3], &buffer) || buffer < 0)
		return (-1);
	env->time_eat = buffer * 1000;
	if (ft_atoi_if_valid(argv[4], &buffer) || buffer < 0)
		return (-1);
	env->time_slp = buffer * 1000;
	if (argc == 6)
	{
		if (ft_atoi_if_valid(argv[5], &buffer) || buffer < 0)
			return (-1);
		env->n_eats_until_done = buffer;
	}
	else
		env->n_eats_until_done = -1;
	return (0);
}

int	parse_args(int argc, char **argv, t_env *env, t_table *table)
{
	memset(env, 0, sizeof(t_env));
	memset(table, 0, sizeof(t_table));
	if (ft_atoi_if_valid(argv[1], &table->n_philos) || table->n_philos < 1)
		return (-1);
	if (parse_times(argc, argv, env))
		return (-1);
	return (0);
}
