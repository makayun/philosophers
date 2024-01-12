/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:37:14 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/12 15:03:39 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	mcsec_to_mlsec(time_t input)
{
	return (input / 1000);
}

void	ph_exit(int code, t_data *data)
{
	int	i;

	if (code == ERR_WRONG_INPUT)
		printf ("Wrong input!\n");
	else if (code == ERR_FORKS_INIT_FAILED)
		printf ("Error, forks initialization failed!\n");
	else if (code == ERR_PHILOS_INIT_FAILED)
		printf ("Error, philosophers initialization failed!\n");
	if (data)
	{
		i = data->rules.philos_total;
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i].mutex);
	}
	exit (code);
}
