/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:37:14 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/22 23:26:43 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ph_wait_until(t_philosopher *philo, long timestamp)
{
	while (ph_get_current_mcsec(&philo->mcsec_current) < timestamp)
		usleep(philo->rules.philos_total * 10);
}

void ph_print_message(t_philosopher *philo, char *str)
{
	printf ("%ld %d %s", (ph_get_current_mcsec(&philo->mcsec_current) - philo->rules.mcsec_start) / 1000, philo->id, str);
}

long ph_get_current_mcsec(long *mcsec_current)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	*mcsec_current = t.tv_sec * 1000000 + t.tv_usec;
	return (*mcsec_current);
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
