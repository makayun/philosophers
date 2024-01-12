/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:28:54 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/12 14:17:37 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_state_change(t_philosopher *philo, int new_state)
{
	if (new_state < 4)
		philo->state = new_state;
	pthread_mutex_lock(&philo->rules->state_change);
	if (new_state == TAKING_FORK)
		printf ("%d %s\n", philo->id, STR_FORK);
	else if (new_state == EATING)
		printf ("%d %s\n", philo->id, STR_EATING);
	else if (new_state == SLEEPING)
		printf ("%d %s\n", philo->id, STR_SLEEPING);
	else if (new_state == THINKING)
		printf ("%d %s\n", philo->id, STR_THINKING);
	else if (new_state == ATE_ENOUGH)
		if (++philo->rules->philos_ate_enough >= philo->rules->philos_total)
			new_state = STOP;
	pthread_mutex_unlock(&philo->rules->state_change);
	return (new_state);
}

void	ph_eat(t_philosopher *philo, t_fork *first_fork, t_fork *second_fork)
{
	pthread_mutex_lock(&first_fork->mutex);
	ph_state_change(philo, TAKING_FORK);
	pthread_mutex_lock(&second_fork->mutex);
	ph_state_change(philo, TAKING_FORK);
	ph_state_change(philo, EATING);
	usleep(philo->rules->microsec_to_eat);
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
}

void	*ph_process(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->state != DEAD
		&& philo->times_ate < philo->rules->times_must_eat)
	{
		ph_state_change(philo, THINKING);
		if (philo->id % 2 == 0)
			ph_eat(philo, philo->left_fork, philo->right_fork);
		else
			ph_eat(philo, philo->right_fork, philo->left_fork);
		if (++philo->times_ate >= philo->rules->times_must_eat)
			if (ph_state_change(philo, ATE_ENOUGH) == STOP)
				return (0);
		ph_state_change(philo, SLEEPING);
		usleep(philo->rules->microsec_to_sleep);
	}
	return (0);
}
