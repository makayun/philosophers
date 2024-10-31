/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:28:54 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/26 11:56:22 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_die(long current, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->common->state_change);
	if (philo->common->someone_died == false)
	{
		philo->common->someone_died = true;
		printf ("%ld %d %s", (current - philo->rules.start) / 1000,
			philo->id, STR_DEAD);
	}
	pthread_mutex_unlock(&philo->common->state_change);
}

int	ph_state_change(t_philosopher *philo, int new_state)
{
	if (ph_get_current(&philo->current) >= philo->next_meal_before)
		return (ph_die(philo->current, philo), STOP);
	pthread_mutex_lock(&philo->common->state_change);
	if (philo->common->philos_ate_enough >= philo->rules.philos_total
		|| philo->common->someone_died == true)
		new_state = STOP;
	else if (new_state == TAKING_FORK)
		ph_print_message(philo, STR_FORK);
	else if (new_state == EATING)
		ph_print_message(philo, STR_EATING);
	else if (new_state == SLEEPING)
		ph_print_message(philo, STR_SLEEPING);
	else if (new_state == THINKING)
		ph_print_message(philo, STR_THINKING);
	else if (new_state == ATE_ENOUGH)
		if (++philo->common->philos_ate_enough >= philo->rules.philos_total)
			new_state = STOP;
	pthread_mutex_unlock(&philo->common->state_change);
	return (new_state);
}

int	ph_eat(t_philosopher *philo, t_fork *first_fork, t_fork *second_fork)
{
	if (ph_get_current(&philo->current) >= philo->next_meal_before)
		return (ph_die(philo->current, philo), STOP);
	if (ph_fork_take(philo, first_fork) != ALL_FINE)
		return (STOP);
	if (ph_fork_take(philo, second_fork) != ALL_FINE)
		return (STOP);
	if (ph_state_change(philo, EATING) == STOP)
		return (STOP);
	philo->last_meal = philo->current;
	philo->next_meal_before = philo->last_meal + philo->rules.to_die;
	if (ph_wait(philo, philo->last_meal + philo->rules.to_eat) == DEAD)
		return (ph_die(philo->current, philo), STOP);
	ph_fork_put(first_fork);
	ph_fork_put(second_fork);
	return (ALL_FINE);
}

void	*ph_process(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (ph_state_change(philo, THINKING) != STOP)
	{
		if (ph_wait(philo, philo->last_meal + philo->offset) == DEAD)
			return (ph_die(philo->current, philo), NULL);
		if (philo->id % 2 == 0)
		{
			ph_wait(philo, philo->current + philo->rules.philos_total * 200);
			if (ph_eat(philo, philo->left_fork, philo->right_fork) == STOP)
				return (NULL);
		}
		else
			if (ph_eat(philo, philo->right_fork, philo->left_fork) == STOP)
				return (NULL);
		if (ph_state_change(philo, SLEEPING) == STOP)
			return (NULL);
		if (++philo->times_ate >= philo->rules.times_must_eat)
			if (ph_state_change(philo, ATE_ENOUGH) == STOP)
				return (NULL);
		ph_wait(philo,
			philo->last_meal + philo->rules.to_eat + philo->rules.to_sleep);
	}
	return (NULL);
}
