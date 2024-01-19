/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:14:17 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/19 10:48:23 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	int				i;

	if (argc < 5 || argc > 6)
		ph_exit(ERR_WRONG_INPUT, NULL);
	ph_initialize(argv, &data);
	i = -1;
	while (++i < data.rules.philos_total)
		pthread_join(data.philos[i].thread, NULL);
	while (--i >= 0)
		pthread_mutex_destroy(&data.forks[i].mutex);
	pthread_mutex_destroy(&data.common_data.state_change);
}
