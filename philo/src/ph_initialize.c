/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:27:59 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/12 15:06:38 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_initialize_philos(t_data *data)
{
	int	i;
	int	total;

	i = data->rules.philos_total;
	total = data->rules.philos_total;
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].state = THINKING;
		data->philos[i].last_state_change = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % total];
		data->philos[i].times_ate = 0;
		data->philos[i].rules = &data->rules;
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
		data->forks[i].is_taken = false;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
			ph_exit(ERR_FORKS_INIT_FAILED, NULL);
	}
}

void	ph_initialize_rules(char **argv, t_rules *rules)
{
	rules->philos_total = (int)ph_atoll(argv[1]);
	rules->microsec_to_die = (time_t)ph_atoll(argv[2]) * 1000;
	rules->microsec_to_eat = (time_t)ph_atoll(argv[3]) * 1000;
	rules->microsec_to_sleep = (time_t)ph_atoll(argv[4]) * 1000;
	rules->times_must_eat = (int)ph_atoll(argv[5]);
	if (rules->philos_total < 1 || rules->philos_total > 200
		|| rules->microsec_to_die < 0
		|| rules->microsec_to_eat < 0
		|| rules->microsec_to_sleep < 0)
		ph_exit(ERR_WRONG_INPUT, NULL);
	rules->philos_ate_enough = 0;
	rules->someone_died = false;
	if (pthread_mutex_init(&rules->state_change, NULL))
		ph_exit(ERROR, NULL);
}

void	ph_initialize(char **argv, t_data *data)
{
	ph_initialize_rules(argv, &data->rules);
	ph_initialize_forks(data);
	ph_initialize_philos(data);
}
