/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:37:14 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/24 23:07:00 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_wait(t_philosopher *philo, long timestamp)
{
	while (ph_get_current(&philo->current) < timestamp)
		usleep(philo->rules.philos_total * 10);
}

void	ph_print_message(t_philosopher *philo, char *str)
{
	printf ("%ld %d %s", (ph_get_current(&philo->current)
			- philo->rules.start) / 1000, philo->id, str);
}

long	ph_get_current(long *current)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	*current = t.tv_sec * 1000000 + t.tv_usec;
	return (*current);
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
