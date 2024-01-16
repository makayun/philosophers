/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:28:54 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/15 18:48:00 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_state_change(t_philosopher *philo, int new_state)
{
	if (new_state < 4)
		philo->state = new_state;
	pthread_mutex_lock(&philo->common_data->state_change);
	if (philo->common_data->someone_died == true)
		new_state = STOP;
	else if (new_state == TAKING_FORK)
		printf ("%d %s", philo->id, STR_FORK);
	else if (new_state == EATING)
		printf ("%d %s", philo->id, STR_EATING);
	else if (new_state == SLEEPING)
		printf ("%d %s", philo->id, STR_SLEEPING);
	else if (new_state == THINKING)
		printf ("%d %s", philo->id, STR_THINKING);
	else if (new_state == ATE_ENOUGH)
		if (++philo->common_data->philos_ate_enough >= philo->rules.philos_total)
			new_state = STOP;
	pthread_mutex_unlock(&philo->common_data->state_change);
	return (new_state);
}

void	ph_eat(t_philosopher *philo, t_fork *first_fork, t_fork *second_fork)
{
	pthread_mutex_lock(&first_fork->mutex);
	ph_state_change(philo, TAKING_FORK);
	pthread_mutex_lock(&second_fork->mutex);
	ph_state_change(philo, TAKING_FORK);
	ph_state_change(philo, EATING);
	usleep(philo->rules.microsec_to_eat);
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
}

void	*ph_process(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->state != DEAD
		&& philo->times_ate < philo->rules.times_must_eat)
	{
		if (ph_state_change(philo, THINKING) == STOP)
			return (0);
		if (philo->id % 2 == 0)
			ph_eat(philo, philo->left_fork, philo->right_fork);
		else
			ph_eat(philo, philo->right_fork, philo->left_fork);
		if (++philo->times_ate >= philo->rules.times_must_eat)
			if (ph_state_change(philo, ATE_ENOUGH) == STOP)
				return (0);
		ph_state_change(philo, SLEEPING);
		usleep(philo->rules.microsec_to_sleep);
	}
	return (0);
}
