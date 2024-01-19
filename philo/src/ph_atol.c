/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:47:15 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/19 14:54:41 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

static int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	ph_atol(const char *str)
{
	int	i;
	int	minus;
	int	res;

	i = 0;
	minus = 0;
	res = 0;
	if (!str)
		return (INT_MAX);
	while (is_space(str[i]) && str[i] != '\0')
		i++;
	if (str[i] == '-')
	{
		minus = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (is_number(str[i]))
		res = res * 10 + str[i++] - '0';
	if (minus != 0)
		res = res * -1;
	return (res);
}

// DON'T USE IT AS NORMAL ATOLL, LOOK AT THE LINES 41-42