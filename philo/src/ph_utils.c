/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:37:14 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/16 13:00:26 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long ph_timeval_to_mcsec(struct timeval t)
{
	return (t.tv_sec * 1000000 + t.tv_usec);
}

void ph_get_current_mcsec(long long *mcsec_current)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	*mcsec_current = ph_timeval_to_mcsec(tv);
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
