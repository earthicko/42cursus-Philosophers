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

int	parse_args(int argc, char **argv, t_tableinfo *tinfo)
{
	if (ft_atoi_if_valid(argv[1], &tinfo->n_philos) || tinfo->n_philos < 1)
		return (-1);
	if (ft_atoi_if_valid(argv[2], &tinfo->time_die) || tinfo->time_die < 0)
		return (-1);
	if (ft_atoi_if_valid(argv[3], &tinfo->time_eat) || tinfo->time_eat < 0)
		return (-1);
	if (ft_atoi_if_valid(argv[4], &tinfo->time_slp) || tinfo->time_slp < 0)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi_if_valid(argv[5], &tinfo->n_eats_until_done)
			|| tinfo->n_eats_until_done < 0)
			return (-1);
	}
	else
		tinfo->n_eats_until_done = -1;
	printf("N Philos: %d\n", tinfo->n_philos);
	printf("Time - die: %d\n", tinfo->time_die);
	printf("Time - eat: %d\n", tinfo->time_eat);
	printf("Time - sleep: %d\n", tinfo->time_slp);
	printf("N eatings until done: %d\n", tinfo->n_eats_until_done);
	return (0);
}
