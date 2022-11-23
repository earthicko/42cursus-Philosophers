/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:13 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:14 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>

int	handle_error(char *error_msg)
{
	printf("%s\n", error_msg);
	return (CODE_ERROR);
}

int	print_usage(void)
{
	printf("Philosophers - I never thought philosophy would be so deadly\n");
	printf("Usage:\n");
	printf("./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat\n");
	return (0);
}
