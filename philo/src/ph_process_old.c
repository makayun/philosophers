/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_process_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:28:54 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/18 11:47:20 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ph_die(long long mcsec_current, t_philosopher *philo)
{
	philo->state = DEAD;
	pthread_mutex_lock(&philo->common_data->state_change);
	philo->common_data->someone_died = true;
	printf ("%lld %d %s", (mcsec_current - philo->rules.mcsec_start) / 1000, philo->id, STR_DEAD);
	pthread_mutex_unlock(&philo->common_data->state_change);	
}

int	ph_state_change(t_philosopher *philo, int new_state)
{
	long long		mcsec_current;

	ph_get_current_mcsec(&mcsec_current);
	if (mcsec_current - philo->last_meal >= philo->rules.mcsec_to_die)
		return (ph_die(mcsec_current, philo), STOP);
	else if (new_state < 4)
		philo->state = new_state;
	pthread_mutex_lock(&philo->common_data->state_change);
	if (philo->common_data->someone_died == true)
		new_state = STOP;
	else if (new_state == TAKING_FORK)
		printf ("%lld %d %s", (mcsec_current - philo->rules.mcsec_start) / 1000, philo->id, STR_FORK);
	else if (new_state == EATING)
		printf ("%lld %d %s", (mcsec_current - philo->rules.mcsec_start) / 1000, philo->id, STR_EATING);
	else if (new_state == SLEEPING)
		printf ("%lld %d %s", (mcsec_current - philo->rules.mcsec_start) / 1000, philo->id, STR_SLEEPING);
	else if (new_state == THINKING)
		printf ("%lld %d %s", (mcsec_current - philo->rules.mcsec_start) / 1000, philo->id, STR_THINKING);
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
	ph_get_current_mcsec(&philo->last_meal);
	usleep(philo->rules.mcsec_to_eat);
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
}

void	*ph_process(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	philo->last_meal = philo->rules.mcsec_start;
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
		if (ph_state_change(philo, SLEEPING) == STOP)
			return (0);
		usleep(philo->rules.mcsec_to_sleep);
	}
	return (0);
}
