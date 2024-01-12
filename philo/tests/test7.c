#include "../src/philo.h"

void change_total(t_arguments *args)
{
	args->philos_total = 5;
}

int	ph_initialize_forks(t_data *data)
{
	int i;

	change_total(&data->arguments);
	i = data->arguments.philos_total;
	while (--i >= 0)
	{
		data->forks[i].id = i;
		data->forks[i].is_taken = 0;
		if (pthread_mutex_init(&(data->forks[i].mutex), NULL))
			return (ERROR);
	}
	return (0);
}

void ph_initialize_philos(t_data *data)
{
	int i;

	i = data->arguments.philos_total;
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].state = THINKING;
		data->philos[i].last_state_change = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->arguments.philos_total];
	}
}

int main()
{
	t_data data;
	int i = 0;


	ph_initialize_forks(&data);
	ph_initialize_philos(&data);

	while (i < data.arguments.philos_total)
	{
		printf ("%d %d\n", data.philos[i].left_fork->id, data.philos[i].right_fork->id);
		i++;
	}
}
