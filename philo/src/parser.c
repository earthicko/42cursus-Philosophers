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

#include "philo.h"
#include "ft_atoi.h"
#include <stdio.h>

static int	parse_times(char **argv, t_tableinfo *tinfo)
{
	int	buffer;

	if (ft_atoi_if_valid(argv[2], &buffer) || buffer < 0)
		return (-1);
	tinfo->time_die = buffer;
	if (ft_atoi_if_valid(argv[3], &buffer) || buffer < 0)
		return (-1);
	tinfo->time_eat = buffer;
	if (ft_atoi_if_valid(argv[4], &buffer) || buffer < 0)
		return (-1);
	tinfo->time_slp = buffer;
	return (0);
}

int	parse_args(int argc, char **argv, t_tableinfo *tinfo)
{
	if (parse_times(argv, tinfo))
		return (-1);
	if (ft_atoi_if_valid(argv[1], &tinfo->n_philos) || tinfo->n_philos < 1)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi_if_valid(argv[5], &tinfo->n_eats_until_done)
			|| tinfo->n_eats_until_done < 0)
			return (-1);
	}
	else
		tinfo->n_eats_until_done = -1;
	printf("N Philos            : %d\n", tinfo->n_philos);
	printf("Time: die|eat|slp   : %ld|%ld|%ld\n",
		tinfo->time_die, tinfo->time_eat, tinfo->time_slp);
	printf("N eatings until done: %d\n", tinfo->n_eats_until_done);
	tinfo->time_eat *= 1000;
	tinfo->time_slp *= 1000;
	return (0);
}
