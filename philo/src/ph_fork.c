#include "philo.h"

int	ph_fork_take(t_philosopher *philo, t_fork *fork)
{
	long long mcsec_current;

	while (philo->state != DEAD)
	{
		ph_get_current_mcsec(&mcsec_current);
		pthread_mutex_lock(&philo->common_data->fork_check);
		if (fork->is_taken == true)
		{
			pthread_mutex_unlock(&philo->common_data->fork_check);
			if(mcsec_current >= philo->next_meal_before)
				return (ph_die(mcsec_current, philo), DEAD);
			usleep(50);
		}
		else
		{
			fork->is_taken = true;
			pthread_mutex_unlock(&philo->common_data->fork_check);
			pthread_mutex_lock(&fork->mutex);
			if (ph_state_change(philo, TAKING_FORK) != STOP)
				return (ALL_FINE);
		}
	}
	return (ERROR);
}

void	ph_fork_put(t_philosopher *philo, t_fork *fork)
{
	pthread_mutex_lock(&philo->common_data->fork_check);
	fork->is_taken = false;
	pthread_mutex_unlock(&philo->common_data->fork_check);
	pthread_mutex_unlock(&fork->mutex);
}