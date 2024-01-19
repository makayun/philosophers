/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:27:59 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/19 15:00:43 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_initialize_philos(t_data *data)
{
	int	i;
	int	total;

	i = data->rules.philos_total;
	total = data->rules.philos_total;
	ph_get_current_mcsec(&data->rules.mcsec_start);
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].state = THINKING;
		data->philos[i].last_meal = data->rules.mcsec_start;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % total];
		data->philos[i].times_ate = 0;
		data->philos[i].rules = data->rules;
		data->philos[i].common_data = &data->common_data;
		data->philos[i].last_meal = data->rules.mcsec_start;
		data->philos[i].next_meal_before = data->rules.mcsec_start + data->rules.mcsec_to_die;
		if(pthread_create(&data->philos[i].thread, NULL,
			ph_process, (void *)&data->philos[i]))
			ph_exit(ERR_PHILOS_INIT_FAILED, data);
	}
}

void	ph_initialize_forks(t_data *data)
{
	int	i;

	i = data->rules.philos_total;
	while (--i >= 0)
	{
		data->forks[i].id = i;
		data->forks[i].is_taken = NOT_TAKEN;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
			ph_exit(ERR_FORKS_INIT_FAILED, NULL);
	}
}

void	ph_initialize_rules(char **argv, t_data *data)
{
	data->rules.philos_total = ph_atol(argv[1]);
	data->rules.mcsec_to_die = ph_atol(argv[2]) * 1000;
	data->rules.mcsec_to_eat = ph_atol(argv[3]) * 1000;
	data->rules.mcsec_to_sleep = ph_atol(argv[4]) * 1000;
	data->rules.times_must_eat = (int)ph_atol(argv[5]);
	if (data->rules.philos_total < 1 || data->rules.philos_total > 200
		|| data->rules.mcsec_to_die < 0
		|| data->rules.mcsec_to_eat < 0
		|| data->rules.mcsec_to_sleep < 0)
		ph_exit(ERR_WRONG_INPUT, NULL);
	data->common_data.philos_ate_enough = 0;
	data->common_data.someone_died = false;
	if (pthread_mutex_init(&data->common_data.state_change, NULL))
		ph_exit(ERROR, NULL);
}

void	ph_initialize(char **argv, t_data *data)
{
	ph_initialize_rules(argv, data);
	ph_initialize_forks(data);
	ph_initialize_philos(data);
}
