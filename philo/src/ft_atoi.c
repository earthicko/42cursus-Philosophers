/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:48:26 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/17 13:48:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c);
int	ft_isdigit(int c);

static int	is_number(char *str)
{
	char	*cursor;

	cursor = str;
	while (*cursor != '\0' && ft_isspace(*cursor))
		cursor++;
	if (*cursor == '-' || *cursor == '+')
		cursor++;
	if (!ft_isdigit(*cursor))
		return (0);
	while (*cursor != '\0' && ft_isdigit(*cursor))
		cursor++;
	if (*cursor != '\0')
		return (0);
	return (1);
}

static void	init_ft_atoi_strict(char **cursor, int *sign)
{
	while (**cursor != '\0' && ft_isspace(**cursor))
		(*cursor)++;
	*sign = 1;
	if (**cursor == '+' || **cursor == '-')
	{
		if (**cursor == '-')
			*sign = -1;
		(*cursor)++;
	}
}

static int	ft_atoi_strict(const char *str, int *ret)
{
	char	*cursor;
	int		nbr;
	int		nbr_prev;
	int		sign;

	nbr = 0;
	nbr_prev = 0;
	cursor = (char *) str;
	init_ft_atoi_strict(&cursor, &sign);
	while (*cursor != '\0' && ft_isdigit(*cursor))
	{
		nbr = nbr_prev * 10 + sign * ((int)(*cursor - '0'));
		if (sign == 1 && nbr < nbr_prev)
			return (1);
		if (sign == -1 && nbr > nbr_prev)
			return (1);
		nbr_prev = nbr;
		cursor++;
	}
	*ret = nbr;
	return (0);
}

int	ft_atoi_if_valid(char *str, int *ret)
{
	if (!is_number(str))
		return (1);
	return (ft_atoi_strict(str, ret));
}

int	ft_atoi(const char *str)
{
	char	*cursor;
	long	output;
	long	sign;

	output = 0;
	cursor = (char *) str;
	while (*cursor != '\0' && ft_isspace(*cursor))
		cursor++;
	sign = 1;
	if (*cursor == '+' || *cursor == '-')
	{
		if (*cursor == '-')
			sign = -1;
		cursor++;
	}
	while (*cursor != '\0' && ft_isdigit(*cursor))
	{
		output = output * 10 + ((long)(*cursor - '0'));
		cursor++;
	}
	output *= sign;
	return ((int) output);
}
