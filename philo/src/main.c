/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:22 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:23 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error_handler.h"
#include "parser.h"
#include "allocator.h"
#include "initializer.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_tableinfo	tableinfo;
	t_philoinfo	*philoinfos;

	if (!(argc == 5 || argc == 6))
		return (handle_error("Invalid number of arguments."));
	if (parse_args(argc, argv, &tableinfo))
		return (handle_error("Error while parsing arguments."));
	if (alloc_infos(&tableinfo, &philoinfos))
		return (handle_error("Error while allocating resources."));
	if (init_tableinfo(&tableinfo, philoinfos))
	{
		free_tableinfo(&tableinfo);
		free(philoinfos);
		return (handle_error("Error while initializing threads or mutexes."));
	}
	return (0);
}
