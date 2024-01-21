/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:28:54 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/21 23:30:39 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ph_die(long mcsec_current, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->common_data->state_change);
	if (philo->common_data->someone_died == false)
	{
		philo->common_data->someone_died = true;
		printf ("%ld %d %s", (mcsec_current - philo->rules.mcsec_start) / 1000, philo->id, STR_DEAD);
	}
	pthread_mutex_unlock(&philo->common_data->state_change);
}

int	ph_state_change(t_philosopher *philo, int new_state)
{
	if (ph_get_current_mcsec(&philo->mcsec_current) - philo->last_meal >= philo->rules.mcsec_to_die)
		return (ph_die(philo->mcsec_current, philo), STOP);
	pthread_mutex_lock(&philo->common_data->state_change);
	if (philo->common_data->philos_ate_enough >= philo->rules.philos_total)
		new_state = STOP;
	else if (philo->common_data->someone_died == true)
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
		if (++philo->common_data->philos_ate_enough >= philo->rules.philos_total)
			new_state = STOP;
	pthread_mutex_unlock(&philo->common_data->state_change);
	return (new_state);
}


int	ph_eat(t_philosopher *philo, t_fork *first_fork, t_fork *second_fork)
{
	if (ph_fork_take(philo, first_fork) != ALL_FINE)
		return (STOP);
	if (ph_fork_take(philo, second_fork) != ALL_FINE)
		return (STOP);
	if (ph_state_change(philo, EATING) == STOP)
		return (STOP);
	ph_get_current_mcsec(&philo->last_meal);
	while (ph_get_current_mcsec(&philo->mcsec_current) < philo->last_meal + philo->rules.mcsec_to_eat)
		usleep (50);
	ph_fork_put(first_fork);
	ph_fork_put(second_fork);
	philo->next_meal_before = philo->mcsec_current + philo->rules.mcsec_to_die;
	return (ALL_FINE);
}

void	*ph_process(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (ph_state_change(philo, THINKING) != STOP)
	{
		if (philo->id % 2 == 0)
		{
			usleep(500);
    		if (ph_eat(philo, philo->left_fork, philo->right_fork) == STOP)
				return (NULL);
		}
		else
			if (ph_eat(philo, philo->right_fork, philo->left_fork) == STOP)
				return (NULL);
		if (++philo->times_ate >= philo->rules.times_must_eat)
			if (ph_state_change(philo, ATE_ENOUGH) == STOP)
				return (NULL);
		if (ph_state_change(philo, SLEEPING) == STOP)
			return (NULL);
		while (ph_get_current_mcsec(&philo->mcsec_current) < philo->last_meal + philo->rules.mcsec_to_eat + philo->rules.mcsec_to_sleep)
			usleep(50);
	}
	return (NULL);
}
