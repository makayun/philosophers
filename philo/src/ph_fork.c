/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:01:27 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/24 23:06:50 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_fork_take(t_philosopher *philo, t_fork *fork)
{
	while (ph_get_current(&philo->current) < philo->next_meal_before)
	{
		pthread_mutex_lock(&fork->mutex);
		if (fork->is_taken == true)
		{
			pthread_mutex_unlock(&fork->mutex);
			usleep(100);
		}
		else
		{
			fork->is_taken = true;
			pthread_mutex_unlock(&fork->mutex);
			if (ph_state_change(philo, TAKING_FORK) != STOP)
				return (ALL_FINE);
			else
				return (STOP);
		}
	}
	return (ph_die(philo->current, philo), DEAD);
}

void	ph_fork_put(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->is_taken = false;
	pthread_mutex_unlock(&fork->mutex);
}
